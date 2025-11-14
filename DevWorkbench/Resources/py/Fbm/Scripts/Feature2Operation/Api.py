import json
import argparse
import importlib.util
import os
import re

class OperationIndexManager:
    """
    根据tool_type和operation_type分别递增index，生成唯一label。
    支持从已有label自动初始化index。
    """
    def __init__(self):
        self.tool_type_index = {}
        self.operation_type_index = {}
        self.geometry_type_index = {}

    def init_from_injson(self, injson):
        # 初始化tool index
        for tool in injson.get("Tools", []):
            typename = tool.get("TypeName", "")
            label = tool.get("Label", "")
            idx = self._extract_index(label, typename)
            if typename and idx:
                self.tool_type_index[typename] = max(self.tool_type_index.get(typename, 0), idx)
        # 初始化operation index
        for op in injson.get("Operations", []):
            typename = op.get("TypeName", "")
            label = op.get("Label", "")
            idx = self._extract_index(label, typename)
            if typename and idx:
                self.operation_type_index[typename] = max(self.operation_type_index.get(typename, 0), idx)
        # 初始化geometry index
        for geo in injson.get("Geometries", []):
            typename = geo.get("TypeName", "")
            label = geo.get("Label", "")
            idx = self._extract_index(label, typename)
            if typename and idx:
                self.geometry_type_index[typename] = max(self.geometry_type_index.get(typename, 0), idx)

    def _extract_index(self, label, typename):
        # 提取label后缀的index，如"STD_TOOL_5"返回5
        if label and typename and label.startswith(typename):
            parts = label[len(typename):].lstrip("_")
            if parts.isdigit():
                return int(parts)
            # 支持如"Through_Hole_0"等带下划线的类型
            if "_" in parts:
                try:
                    return int(parts.split("_")[-1])
                except Exception:
                    return None
        return None

    def get_tool_label(self, tool_type):
        idx = self.tool_type_index.get(tool_type, 0) + 1
        self.tool_type_index[tool_type] = idx
        return f"{tool_type}_{idx}"

    def get_operation_label(self, operation_type):
        idx = self.operation_type_index.get(operation_type, 0) + 1
        self.operation_type_index[operation_type] = idx
        return f"{operation_type}_{idx}"

    def get_geometry_label(self, geometry_type):
        idx = self.geometry_type_index.get(geometry_type, 0) + 1
        self.geometry_type_index[geometry_type] = idx
        return f"{geometry_type}_{idx}"

def only_english(s):
    return re.sub(r'[^a-zA-Z]', '', s)
def normalize_bor(s):
    # 全部小写，去掉非英文字符，再将bore和boring都替换为bor
    # 后续如果有其他需要替换的词，可以在这里添加
    s = only_english(s.lower())
    s = s.replace("boring", "bor").replace("bore", "bor")
    return s
# ---------------------- 分组函数 ----------------------

def group_features(features, tol=0.01):
    def round_with_tol(value):
        return round(float(value) / tol) * tol

    def normalize_direction(direction):
        mag = sum(x**2 for x in direction) ** 0.5
        return tuple(round_with_tol(x / mag) for x in direction)

    grouped = {}
    for feature in features:
        key = (
            feature.get("TYPE"),
            round_with_tol(feature.get("DIAMETER_1", 0)),
            round_with_tol(feature.get("DEPTH", 0)),
            round_with_tol(feature.get("ANGLE_TOP_CHAMFER_1", 0)),
            normalize_direction(feature.get("DIRECTION", [0, 0, 1]))
        )
        grouped.setdefault(key, []).append(feature)
    return grouped

# ---------------------- 动态加载rules目录下的规则 ----------------------

def load_rule_modules():
    rules_dir = os.path.join(os.path.dirname(__file__), "rules")
    modules = []
    if not os.path.isdir(rules_dir):
        return modules
    for fname in os.listdir(rules_dir):
        if fname.endswith(".py") and not fname.startswith("_"):
            path = os.path.join(rules_dir, fname)
            spec = importlib.util.spec_from_file_location(fname[:-3], path)
            mod = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(mod)
            modules.append(mod)
    return modules

def recommend_tools_by_extra_rules(feature):
    """优先遍历rules目录下的规则，返回所有适用的刀具/工序"""
    modules = load_rule_modules()
    tools = []
    for mod in modules:
        if hasattr(mod, "check") and mod.check(feature):
            if hasattr(mod, "get_tool"):
                tool = mod.get_tool(feature)
                if tool:
                    tools.append(tool)
    return tools

# ---------------------- 默认刀具推荐函数 ----------------------

def recommend_tool_for_feature(feature):
    feature_type = feature["TYPE"]
    diameter = feature.get("DIAMETER_1", 0)
    depth = feature.get("DEPTH", 0)

    tools = []

    def spot_drill(diameter,depth):
        return {
            "tool_type": "STD_TOOL",
            "operation": "SPOT_DRILLING",
            "parameters": {
                "Main/NonCuttingPortion/NeckDiameter":diameter,
                "Main/CuttingPortion/PAAngle": 90.0,
                "Main/CuttingPortion/PitchLength": round(diameter / 2, 2),
                "Main/CuttingPortion/CornerRadius": 0.0,
                "Main/CuttingPortion/FlutelLength": round(depth + diameter, 2),
                "Main/NonCuttingPortion/TotalLength": round(depth * 2 + diameter, 2)
            }
        }
    def drilling(diameter,depth):
        return {
            "tool_type": "STD_TOOL",
            "operation": "DRILLING",
            "parameters": {
                "Main/NonCuttingPortion/NeckDiameter": diameter,
                "Main/CuttingPortion/PAAngle": 150.0,
                #"Main/CuttingPortion/PitchLength": 6.0,
                "Main/CuttingPortion/CornerRadius": 0,
                "Main/CuttingPortion/FlutelLength": round(depth + diameter, 2),
                "Main/NonCuttingPortion/TotalLength": round(depth * 2 + diameter, 2)
            }
        }
    def tap_tool():
        return {
            "tool_type": "TAP_TOOL",
            "operation": "TAPPING",
            "parameters": {
                "Main/CuttingPortion/TAPDiameter": diameter,
                "Main/CuttingPortion/InternalAngle": 60,
                "Main/CuttingPortion/ThreadDiameter": max(diameter - 3, 1),
                "Main/CuttingPortion/ThreadLength": 3.0,
                "Main/CuttingPortion/BAngle": 1.0,
                "Main/CuttingPortion/ThreadDepthLength": depth,
                "Main/NonCuttingPortion/NeckDiameter": max(diameter - 3, 1),
                "Main/NonCuttingPortion/TotalLength": round(depth * 2, 2)
            }
        }

    # def thread_tool():
    #     return {
    #         "tool_type": "THREADMILL_TOOL",
    #         "operation": "BORING_REAMING",
    #         "parameters": {
    #             "Main/CuttingPortion/ThreadMillDiameter": max(diameter - 0.5, 0.5),
    #             "Main/NonCuttingPortion/NeckDiameter": diameter,
    #             "Main/NonCuttingPortion/TotalLength": round(depth * 1.2 + 10, 2),
    #             "Main/CuttingPortion/FlutelLength": round(depth * 1.2, 2)
    #         }
    #     }
    def counterbore_tool():
        return {
            "tool_type": "COUNTERBORE_TOOL",
            "operation": "SPOT_FACING",
            "parameters": {
                "Main/CuttingPortion/CounterBoreDiameter": diameter,
                "Main/CuttingPortion/CornerRadius": diameter,
                "Main/CuttingPortion/PitchLength": 2.0,
                "Main/CuttingPortion/FlutelLength": 2.0,
                "Main/NonCuttingPortion/NeckDiameter": diameter * 1.2,
                "Main/NonCuttingPortion/TotalLength": round(depth * 2, 2),
            }
        }
    def chamfer_tool():
        return {
            "tool_type": "CHAMFER_TOOL",
            "operation": "DRILLING",
            "parameters": {
                "Main/NonCuttingPortion/NeckDiameter": diameter,
                "Main/CuttingPortion/TaperAngle": 45.0,
                "Main/CuttingPortion/FlutelLength": 2.0* diameter,
                "Main/CuttingPortion/Radius": diameter/4.0,
                "Main/CuttingPortion/CLength": diameter/4.0 + 2.0,
                "Main/NonCuttingPortion/TotalLength": 3.0* diameter,
            }
    }
    def thread_tool():
        # 从feature中提取相关参数，若无则用默认值
        thread_diameter = feature.get("THREAD_TAPPER_DRILL_SIZE", feature.get("DIAMETER_1", 0))
        flutel_length = feature.get("THREAD_LENGTH", feature.get("DEPTH", 0))
        neck_diameter = feature.get("THREAD_MAJOR_DIAMETER", thread_diameter)
        total_length = round(feature.get("DEPTH", 0) * 2 + 10, 2)
        flutes = feature.get("THREAD_NUMBER_OF_STARTS", 1)

        return {
            "tool_type": "THREADMILL_TOOL",
            "operation": "TAPPING",
            "parameters": {
                "Main/CuttingPortion/ThreadMillDiameter": thread_diameter,
                "Main/CuttingPortion/FlutelLength": flutel_length,
                "Main/NonCuttingPortion/NeckDiameter": neck_diameter/2,
                "Main/NonCuttingPortion/TotalLength": total_length,
                "Main/NonCuttingPortion/Futes": flutes
            }
        }
    def counterbore_tool(dia_1,dia_2,depth,depth_1,):
        PL = min(dia_2, 0.8 * (depth - depth_1))
        FL = (depth_1) + min(5.0,dia_2, 0.2 * (depth - depth_1))
        return {
            "tool_type": "COUNTERBORE_TOOL",
            "operation": "DRILLING",
            "parameters": {
                "Main/CuttingPortion/CounterBoreDiameter": round(dia_2, 2),#PD
                "Main/CuttingPortion/CornerRadius": 0.0,#R
                "Main/CuttingPortion/PitchLength": round(PL , 2),
                "Main/CuttingPortion/FlutelLength": round(FL, 2),
                "Main/NonCuttingPortion/NeckDiameter": round(dia_1, 2),#D
                "Main/NonCuttingPortion/TotalLength": round((FL+PL) * 2, 2),
                "Main/NonCuttingPortion/Futes": 1  # 可根据需要调整
            }
        }


    # 判断feature内所有key小写带bore的，只要value>0，代表有孔。
    if "counter bore" in feature_type.lower() and "hole" in feature_type.lower():
        DIAMETER_1 = feature.get("DIAMETER_1", 0)
        DEPTH = feature.get("DEPTH", 0)

        DIAMETER_2 = feature.get("DIAMETER_2", 0)
        DEPTH_1 = feature.get("DEPTH_1", 0)

        tools.append(spot_drill(DIAMETER_2, DEPTH))
        tools.append(drilling(DIAMETER_2, DEPTH))

        tools.append(counterbore_tool(DIAMETER_1,DIAMETER_2, DEPTH,DEPTH_1))
    elif "hole" in feature_type.lower():
        
        # 根据孔径，阶梯钻孔
        if diameter/depth < 1.5:
            tools.append(spot_drill(diameter,depth))
            tools.append(drilling(diameter,depth))
        elif diameter/depth < 5:
            tools.append(spot_drill(min(10, diameter * 2/3),depth))
            tools.append(drilling(min(10, diameter * 2/3),depth))
            tools.append(drilling(diameter))
        else:
            tools.append(spot_drill(min(10, diameter* 1/3),depth))
            tools.append(drilling(min(10, diameter* 1/3),depth))
            tools.append(drilling(min(50, diameter* 2/3),depth))
            tools.append(drilling(diameter,depth))
        # 判断feature内所有key小写带chamfer的，只要value>0，代表有倒角。
        if any("chamfer" in k.lower() and feature.get(k, 0) > 0 for k in feature):
            tools.append(chamfer_tool())
    if "thread" in feature.get("TYPE", "").lower():
        tools.append(thread_tool())
    return tools

# ---------------------- 主结构生成函数 ----------------------

def generate_process_structure(fullJson,features, tool_filter=None,pre_tools=None, pre_operations=None,Geometries=None,reuse = True):
    structure = {
        "Tools": [],
        "Programs": [{"Label": "p1", "TypeName": "p1"}],
        "Methods": [],
        "Operations": [],
        "FeatureGeometries": [],
        "ObjectData": []
    }
    manager = OperationIndexManager()
    manager.init_from_injson(fullJson)
    ParentName = ''
    for geometry in Geometries:
        if geometry.get("TypeName") == "MCS":
            ParentName = geometry.get("Label", "")
            break
    tool_map = {}
    tool_index = 1
    operation_index = 1

    grouped = group_features(features)

    # 预处理filter为小写
    filter_lc = [normalize_bor(f) for f in tool_filter] if tool_filter else None

    for group_index, (key, group_feats) in enumerate(grouped.items()):
        feature_type = key[0]

        representative = group_feats[0]

        # 优先用rules目录下的规则
        recommended_tools = recommend_tools_by_extra_rules(representative)
        if not recommended_tools:
            # 若无匹配规则，则用主流程默认规则
            recommended_tools = recommend_tool_for_feature(representative)

        # 过滤刀具类型，忽略大小写,去掉非英文字符,只要包含即可
        if filter_lc:
            def match_filter(tool):
                ttype = normalize_bor(str(tool.get("tool_type", "")).lower())
                oper = normalize_bor(str(tool.get("operation", "")).lower())
                return any(f in ttype or f in oper for f in filter_lc)
#            recommended_tools = [tool for tool in recommended_tools if match_filter(tool)]
        all_Op_Exit = True
        exit_Feat_NameList  = []
        Geo_Label = ""
        if reuse:
            for tool in recommended_tools:
                exit_Group_Op = False
                for pre_tool in pre_tools:
                    para = tool.get("parameters", {})
                    if all(pre_tool.get(k) == v for k, v in para.items()):
                        label = pre_tool.get("Label")
                        for pre_op in pre_operations:
                            if(pre_op.get("Tool") == label and pre_op.get("TypeName") == tool["operation"]):
                                
                                exit_Group_Op = True
                                Geo_Label = pre_op.get("Geometry", "")
                                if Geo_Label:
                                    for geometry in Geometries:
                                        if geometry.get("Label") == Geo_Label:
                                            exit_Feat_NameList.extend(i for i in geometry.get("NameList", []))
                                            break
                if exit_Group_Op == False:
                    all_Op_Exit = False
                    break
            if all_Op_Exit:
                NameList = [f["Label"] for f in group_feats]
                for Name in NameList:
                    exit_Feat_NameList.append(Name)
                exit_Feat_NameList = list(dict.fromkeys(exit_Feat_NameList))
                structure["ObjectData"].append({
                "Label": Geo_Label,
                    "Properties": {
                        "NameList": [f for f in exit_Feat_NameList],
                    }
                })
                structure["FeatureGeometries"].append({
                    "Label": Geo_Label,
                    "TypeName": feature_type,
                    "ParentName": ParentName,
                })
                continue
        # 如果不能直接复用，加入已有的Geometry NameList，则新增
        
        geometry_label = manager.get_geometry_label(feature_type)
        structure["FeatureGeometries"].append({
            "Label": geometry_label,
            "TypeName": feature_type,
            "ParentName": ParentName,
        })
        for tool in recommended_tools:
            tool_key = json.dumps(tool, sort_keys=True)
            for pre_tool in pre_tools:
                if all(pre_tool.get(k) == v for k, v in tool.items()):
                    label = pre_tool.get("Label")
                    # 如果预处理的刀具已经存在，则跳过
            if tool_key not in tool_map:
                label = manager.get_tool_label(tool["tool_type"])
                tool_map[tool_key] = label
                structure["Tools"].append({
                    "Label": label,
                    "TypeName": tool["tool_type"]
                })
                structure["ObjectData"].append({
                    "Label": label,
                    "Properties": tool["parameters"]
                })
                tool_index += 1
            else:
                label = tool_map[tool_key]
          
            op_label = manager.get_operation_label(tool["operation"])
            structure["Operations"].append({
                "Label": op_label,
                "Program": "p1",
                "Geometry": geometry_label,
                "Method": "",
                "Tool": label,
                "TypeName": tool["operation"]
            })
            structure["ObjectData"].append({
                "Label": op_label,
                "Properties": {
                    "Main/SpecifyFeatureGeometry/Optimization": 2,
                    "Main/SpecifyFeatureGeometry/Pattern": False,
                    "Main/SpecifyFeatureGeometry/BandWidth": 3.0
                }
            })
            structure["ObjectData"].append({
                "Label": geometry_label,
                "Properties": {
                    "NameList": [f["Label"] for f in group_feats],
                }
            })
            operation_index += 1



    return structure

# ---------------------- 命令行/函数入口 ----------------------

def ProcessJson(json_sdata):
    fullJson = json.loads(json_sdata)
    features = fullJson['Features']
    tool_filter = fullJson.get('Filter')
    # 如果有可复用的tools和operations
    tools = fullJson.get('Tools', [])
    operations = fullJson.get('Operations', [])
    reuse = fullJson.get('Auto', True)
    Geometries = fullJson.get('Geometries', [])
    return generate_process_structure(fullJson,features, tool_filter,tools, operations,Geometries,reuse)

def main():
    # parser = argparse.ArgumentParser(description="Generate machining process plan from feature JSON.")
    # parser.add_argument("-i", "--input", required=True, help="Input JSON file (feature array)")
    # parser.add_argument("-o", "--output", required=True, help="Output JSON file (process plan array)")
    # args = parser.parse_args()

    # with open(args.input, "r", encoding="utf-8") as f:
    #     fullJson = json.load(f)
    # features = fullJson['Features']
    # tool_filter = fullJson.get('Filter')
    # results = generate_process_structure(features, tool_filter)

    # with open(args.output, "w", encoding="utf-8") as f:
    #     json.dump(results, f, indent=4, ensure_ascii=False)
    script_dir = os.path.dirname(os.path.abspath(__file__))
    input_path = os.path.join(script_dir, "in.json")
    output_path = os.path.join(script_dir, "out.json")

    with open(input_path, "r", encoding="utf-8") as f:
        fullJson = json.load(f)
    features = fullJson['Features']
    tool_filter = fullJson.get('Filter')
    # 如果有可复用的tools和operations
    tools = fullJson.get('Tools', [])
    operations = fullJson.get('Operations', [])
    reuse = fullJson.get('Auto', True)
    Geometries = fullJson.get('Geometries', [])
    results = generate_process_structure(fullJson,features, tool_filter,tools, operations,Geometries,reuse)

    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=4, ensure_ascii=False)

if __name__ == "__main__":
    main()