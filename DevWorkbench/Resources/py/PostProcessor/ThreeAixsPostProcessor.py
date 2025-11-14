# import PySimpleGUI as sg
import argparse
import json
import os
import re
# import tkinter as tk
# from tkinter import filedialog

"""=============================================Gcode命令============================================================="""
class GCodeMapper:
    def __init__(self):
        # 指令字典（完全按照图片顺序和格式）

        # ===== 左侧列指令 =====
        # 运动控制指令
        self.gmotion = {
            "Rapid_Move" : "L",    # 快速运动/定位
            "Linear_Move":"L",     # 直线插补切削
            "CLW_Arc" : "DR-",          # 顺时针圆弧插补（图片中为"CLW"）
            "CCLW_Arc": "DR+" ,        # 逆时针圆弧插补（图片中为"CCLW"）
            "Drilling":"G81",
            "Drilling_with_Dwell":"G82",
            "Deep_Drill":"G83",
            "Peck_Drilling" : "G73",
            "Boring" :"G85",
            "Boring_with_Dwell":"G89"
        }

        # 平面选择
        self.gplane = {
            "XY_Plane" : "G17",        # 选择XY加工平面
            "XZ_Plane" :"G18",        # 图片中误为"ZZ"，实际应为XZ
            "YZ_Plane" : "G19"        # 选择YZ加工平面
        }

        # 坐标模式
        self.gsystm = {
            "Absolute" : "G90",        # 绝对坐标
            "Incremental" : "G91",    # 增量坐标
            "Coordinate_Reset" : "G92" # 坐标系重置
        }
                
        
        # 刀具补偿
        self.Tool_Comp_Off = "G40"   # 取消刀具半径补偿
        self.Tool_Comp_Left = "G41"  # 左刀补
        self.Tool_Comp_Right = "G42" # 右刀补
        
        # 刀具长度
        self.Tool_Length_Add = "G43" # 刀具长度正补偿
        self.Tool_Length_Sub = "G44" # 减补偿
        self.Tool_Length_Cancel = "G49" # 取消长度补偿

        # 单位制
        self.Inch_Mode = "G70"      # 英制模式
        self.Metric_Mode ="G71"     # 公制模式

        # 循环加工指令
        self.Cycle_Start = "G79"   # 循环开始代码
        self.Cycle_Off = "G80"      # 循环关闭
        self.Drilling = "G81"       # 循环钻
        self.Drilling_with_Dwell = "G82"  # 循环钻驻留
        self.Deep_Drill = "G83"     # 深孔钻循环
        self.Peck_Drilling = "G73"   # 断屑钻循环
        self.Boring = "G85"          # 镗孔循环（图片中为"馍"）
        self.Boring_Rapid_Retract = "G86" # 快速退刀镗孔
        self.Boring_with_Side_Shift= "G76" # 横向偏置镗孔（图片特殊描述）
        self.Boring_with_Dwell = "G89" # 镗孔延时
        self.Manual_Boring = "G88"    # 手动退刀镗孔（图片中为"手工筐"）
        self.Back_Boring = "G87"     # 反向镗孔（图片中为"退刀管"）
        self.Auto_Retract = "G98"   # 自动退刀
        self.Manual_Retract = "G99"  # 手动退刀
        
    
        # 主轴控制
        self.Constant_Surface_Speed = "G96" # 恒线速控制（CSS）
        self.RPM_Mode = "G97"        # 恒定转速（图片中误为"RPⅡ"）
        
        # 延时指令
        self.Dwell_seconds = "G04" # 秒级暂停
        self.Dwell_revolutions = "G04" # 转数暂停

        #进给率模式


        self.placeholder_to_category = {
            # 运动指令 → gmotion
            "gmotion": {"L", "L", "DR-", "DR+", "G81"},
            
            # 平面选择 → gplane
            "gplane": {"G17", "G18", "G19"},
            
            # 坐标模式 → gsystm
            "gsystm": {"G90", "G91", "G92"}
        }


    def get_motion_value(self, gmotionstr):
        """通过字典键直接获取值"""
        return self.gmotion.get(gmotionstr, None)# 返回None或抛异常

"""=============================================Mcode命令============================================================="""
class MCodeMapper:
    def __init__(self):
        # ===== 完全按照图片中的指令和代码对应关系 =====
        self.Stop_Manual_Tool_Change = "M00"     # 停止/手工换刀
        self.Optional_Stop = "M01"               # 选择性停刀
        self.Program_End = "M02"                # 程序结束
        
        # 主轴控制指令
        self.Spindle_CW = "M03"                   # 主轴正转(图片中为"主轴开/CL")
        self.Spindle_CCW = "M04"                 # 主轴反转(图片中为"主轴CCL")
        self.Spindle_Off = "M05"               # 主轴关
        
        # 换刀指令
        self.Tool_Change = "M06"                  # 换刀/退刀
        
        # 冷却液控制指令
        self.Coolant_On = "M08"                # 冷却液开
        self.Mist_Coolant = "M07"                # 雾状冷却液
        self.Liquid_Coolant = "M08"          # 液态冷却液(与冷却液开同代码)
        self.Coolant_Thru_Spindle = "M26"        # 冷却液通孔
        self.Coolant_Tapping = "M27"              # 冷却液攻丝
        self.Coolant_Off = "M09"                   # 冷却液关
        
        # 其他指令
        self.Rewind = "M30"                       # 倒回  


"""=============================================Motion命令============================================================="""
class ToolPathParamers:
    def __init__(self):
        """初始路径移动参数，可选传入参数指令"""

        self.move_x = "X"  
        self.move_y = "Y"
        self.move_z = "Z"
        self.move_f = "F" 
        self.move_s = "S"

        self.center_x = "X"
        self.center_y = "Y"
        self.center_z = "Z"
        self.nor_x = "NX"
        self.nor_y = "NY"
        self.nor_z = "NZ"
        self.center_radius = "R"

        self.Q200 = "Q200"
        self.Q201 = "Q201"
        self.Q206 = "Q206"
        self.Q202 = "Q202"
        self.Q210 = "Q210"
        self.Q211 = "Q211"
        self.Q203 = "Q203"
        self.Q204 = "Q204"
        
        
        
class ToolPathCode:
    def __init__(self):
        """初始化 GCode 解析器，可选传入 GOTO 指令"""

        #############机床控制
        self.spindl_command = "M03 S"

        #############运动路径
        self.line_move_command = "L X Y Z F S"  
        self.circle_move_command = ['CC X Y Z', 'C X Y Z F DR-']
        self.rapid_move_command = "L X Y Z F MAX"
        self.fedrat_command = "F"

        ############循环
        self.drill_command = "G81 X Y Z R2= R3= R10= F"

    #############起始序列
    # def start_prog_seq(self, function_names):
        



"""=============================================定制命令============================================================="""
class Customcommands:
    def __init__(self, toolpathcode=None, toolpathparamer = None, mcode = None, gcode = None):
        self.toolpathparamer = toolpathparamer if toolpathparamer else ToolPathParamers()
        self.toolpathcode = toolpathcode if toolpathcode else ToolPathCode()
        self.mcode = mcode if mcode else MCodeMapper()
        self.gcode = gcode if gcode else GCodeMapper()
               
         
    def Hedehan_Drill_handle(self, axis=None, current_point=None, pre_Q200=None,pre_Q201=None,pre_Q206=None,pre_Q210=None,pre_Q211 = None,pre_Q202=None,pre_Q203=None,pre_Q204=None, **kwargs):
        result_lines=[]


        # 检查是否有X/Y/Z/F/S参数传入
        param_values = {
            self.toolpathparamer.Q200: kwargs.get('Q200'),
            self.toolpathparamer.Q201: kwargs.get('Q201'),   
            self.toolpathparamer.Q206: kwargs.get('Q206'),
            self.toolpathparamer.Q202: kwargs.get('Q202'),
            self.toolpathparamer.Q210: kwargs.get('Q210'),
            self.toolpathparamer.Q211: kwargs.get('Q211'),
            self.toolpathparamer.Q203: kwargs.get('Q203'),
            self.toolpathparamer.Q204: kwargs.get('Q204'),
        }
        # 前一个值字典
        pre_values = {
            self.toolpathparamer.Q200: pre_Q200,
            self.toolpathparamer.Q201: pre_Q201,  
            self.toolpathparamer.Q206: pre_Q206,
            self.toolpathparamer.Q202: pre_Q202,
            self.toolpathparamer.Q210: pre_Q210,
            self.toolpathparamer.Q211: pre_Q211,
            self.toolpathparamer.Q203: pre_Q203,
            self.toolpathparamer.Q204: pre_Q204, 
        }

        
        # 判断是否有任意一个参数不同（精度保留到三位小数）
        has_difference = False
        for key in param_values:
            current = param_values[key]
            previous = pre_values[key]
            if current is not None:
                rounded_current = round(current, 3)
                rounded_previous = round(previous, 3) if previous is not None else None
                if rounded_current != rounded_previous:
                    has_difference = True
                    break  # 有任何一个不同就退出判断
                
        # 如果存在差异，则输出所有参数到 result_lines
        if has_difference:
            result_lines.append("CYCL DEF  200")
            for key in param_values:
                val = param_values[key]
                if val is not None:
                    formatted_val = f"{val:.3f}".rstrip('0').rstrip('.') if '.' in f"{val:.3f}" else f"{val}"
                    result_lines.append(f"{key}={formatted_val}")
        
        xvalue = current_point[0]+axis[0]*param_values[self.toolpathparamer.Q201]
        yvalue = current_point[1]+axis[0]*param_values[self.toolpathparamer.Q201]
        result_lines.append(f"L X{xvalue} Y{yvalue} R0 F MAX")
        result_lines.append(f"CYCL CALL")
        # 组合成最终的G代码
        return "\n".join(result_lines)


"""=============================================其他命令============================================================="""
class Outputcontrol:
    def __init__(self):
        self.showlinenumber = True
        

    
"""=============================================CLS文件数值转换============================================================="""
class CLScodeParser:             #解析cls文件行数值
    def __init__(self):
        self.gcodemap = GCodeMapper()
        
    def _parse_circle(self, circle_line, goto_line,i=None, j=None, k=None):
        """解析 CIRCLE 指令，返回圆心、法向量、半径等参数"""
        parts = circle_line.split("/")[1].split(",")
        self.center_x = float(parts[0])
        self.center_y = float(parts[1])
        self.center_z = float(parts[2])
        self.normal_x = float(parts[3])
        self.normal_y = float(parts[4])
        self.normal_z = float(parts[5])
        self.radius = float(parts[6])
        self.tolerance = float(parts[7])
        self.step_size = float(parts[8])
        self.max_angle = float(parts[9])
        self.start_angle = float(parts[10])

        if self.normal_z == 1.:
            self.cirmotion = self.gcodemap.get_motion_value("CLW_Arc")
        elif self.normal_z == -1.:
            self.cirmotion = self.gcodemap.get_motion_value("CCLW_Arc") 
    

        gotoparts = goto_line.split("/")[1].split(",")
        gotoparts = [float(p) for p in gotoparts]  # 全部转成 float

        if len(gotoparts) == 3:
            self.goto_x, self.goto_y, self.goto_z = gotoparts

        elif len(gotoparts) == 6:
            self.goto_x, self.goto_y, self.goto_z, self.goto_i, self.goto_j, self.goto_k = gotoparts
    
        else:
            raise ValueError(f"GOTO 指令格式错误，应为 3 或 6 个值，但得到 {len(gotoparts)} 个值: {goto_line}")

        return self


##########################钻孔
    def _parse_drill(self,pre_point, current_point, clear,fedto,feed_rate, step,dwell_type, dwell):
        #safe_z为安全平面的z值
        # 提取循环类型（DRILL或ON）

        # 初始化所有属性（避免未定义）

        self.Q200 = clear
        self.Q201 = -fedto
        self.Q206 = feed_rate
        if step == 0.:
            step = fedto
            self.Q202 = step
        else:
            self.Q202 = step
        self.Q210 = 0.0
        self.Q203 = current_point[2]
        if dwell_type == "Rev" or dwell_type == "Sec":
            self.Q211 = dwell
        else:
            self.Q211 = 0.001

        self.Q204 = pre_point[2] - current_point[2]

        return self


"""=============================================刀具路径命令============================================================="""
class ToolPathGenerator:
    def __init__(self, toolpathcode=None, toolpathparamer = None, mcode = None, gcode = None):
        self.toolpathparamer = toolpathparamer if toolpathparamer else ToolPathParamers()
        self.toolpathcode = toolpathcode if toolpathcode else ToolPathCode()
        self.mcode = mcode if mcode else MCodeMapper()
        self.gcode = gcode if gcode else GCodeMapper()

        self.spindl_c = self.toolpathcode.spindl_command
        self.fedrat_move = self.toolpathcode.fedrat_command

        self.linear_move = self.toolpathcode.line_move_command
        self.circle_move = self.toolpathcode.circle_move_command
        self.rapid_move = self.toolpathcode.rapid_move_command
        self.drill = self.toolpathcode.drill_command
        


    def generate_spindl_gcode_string(self, spindlcommand, pre_s=None, **kwargs):
        if not spindlcommand:
            return "未生成线性移动命令"
        m_value = kwargs.get('M')
        # 检查是否有X/Y/Z/F/S参数传入
        param_values = {   
            self.toolpathparamer.move_s: kwargs.get('S'),
        }
        # 前一个值字典
        pre_values = {
            self.toolpathparamer.move_s: pre_s,
        }
        # 分割命令中的每个部分（如 ["G1", "X", "Y", "F"]）
        parts = spindlcommand.split()
        output_parts = []
        for part in parts:
            # 检查是否是参数（X/Y/Z/F/S）
            if part in param_values:
                current_value = param_values[part]
                pre_value = pre_values[part]
                # 如果当前值不为None且与前一个值不同
                if current_value is not None and current_value != pre_value:
                    output_parts.append(f"{part}{int(current_value)}")
            elif hasattr(self.mcode, part):
                # 如果part是self.mcode的属性
                if m_value == "CLW":
                    output_parts.append(f"{self.mcode.Spindle_CW}")
                elif m_value == "CCLW":
                    output_parts.append(f"{self.mcode.Spindle_CCW}")
                else:
                    output_parts.append(part)
            else:
                # 如果不是参数，直接保留原样
                output_parts.append(part)
        # 组合成最终的G代码
        return " ".join(output_parts)
    
    ##########################运动命令
    def generate_rapid_gcode_string(self, movecommand,pre_gmotion = None, pre_x=None, pre_y=None, pre_z=None, **kwargs):
        """
        参数:
            movecommand: G代码命令（如 "G00 X Y F"）
            pre_x, pre_y, pre_z, pre_f, pre_s: 前一个坐标/速度值
            kwargs: 可选的X/Y/Z/F/S参数值
        返回:
            生成的G代码字符串（如 "G00 X10 Y20 F100"）
            当参数值与pre_*相同时，不输出该参数
        """
        if not movecommand:
            return "未生成线性移动命令"
        # 检查是否有X/Y/Z/F/S参数传入
        param_values = {
            self.toolpathparamer.move_x: kwargs.get('X'),
            self.toolpathparamer.move_y: kwargs.get('Y'),   
            self.toolpathparamer.move_z: kwargs.get('Z'),
        }

        # 前一个值字典
        pre_values = {
            self.toolpathparamer.move_x: pre_x,
            self.toolpathparamer.move_y: pre_y,
            self.toolpathparamer.move_z: pre_z,
        }

        # 分割命令中的每个部分（如 ["G1", "X", "Y", "F"]）
        parts = movecommand.split()
        output_parts = []
        for part in parts:
            # 检查是否是参数（X/Y/Z/F/S）
            if part in param_values:
                current_value = param_values[part]
                pre_value = pre_values[part]
                # 如果当前值不为None且与前一个值不同
                if current_value is not None and current_value != pre_value:
                    formatted_value = f"{current_value:.3f}".rstrip('0').rstrip('.') if '.' in f"{current_value:.3f}" else f"{current_value}"
                    output_parts.append(f"{part}{formatted_value}")
            else:
                # 如果不是参数，直接保留原样
                output_parts.append(part)
        # 组合成最终的G代码
        return " ".join(output_parts)

    def generate_linemove_gcode_string(self, movecommand,pre_gmotion = None, pre_x=None, pre_y=None, pre_z=None, pre_f=None, pre_s=None, **kwargs):
        """
        参数:
            movecommand: G代码命令（如 "G00 X Y F"）
            pre_x, pre_y, pre_z, pre_f, pre_s: 前一个坐标/速度值
            kwargs: 可选的X/Y/Z/F/S参数值

        返回:
            生成的G代码字符串（如 "G00 X10 Y20 F100"）
            当参数值与pre_*相同时，不输出该参数
        """
        if not movecommand:
            return "未生成线性移动命令"

        # 检查是否有X/Y/Z/F/S参数传入
        param_values = {
            self.toolpathparamer.move_x: kwargs.get('X'),
            self.toolpathparamer.move_y: kwargs.get('Y'),   
            self.toolpathparamer.move_z: kwargs.get('Z'),
            self.toolpathparamer.move_f: kwargs.get('F'),
            self.toolpathparamer.move_s: kwargs.get('S'),
        }

        # 前一个值字典
        pre_values = {
            self.toolpathparamer.move_x: pre_x,
            self.toolpathparamer.move_y: pre_y,
            self.toolpathparamer.move_z: pre_z,
            self.toolpathparamer.move_f: pre_f,
            self.toolpathparamer.move_s: pre_s,
        }

        # 分割命令中的每个部分（如 ["G1", "X", "Y", "F"]）
        parts = movecommand.split()
        output_parts = []

        for part in parts:
            if part in param_values:
                current_value = param_values[part]
                pre_value = pre_values[part]
                if current_value is not None:
                    if part in [self.toolpathparamer.move_x, self.toolpathparamer.move_y, self.toolpathparamer.move_z]:
                        # 保留三位小数后再比较
                        if round(current_value, 3) != round(pre_value if pre_value is not None else -999999, 3):
                            formatted_value = f"{current_value:.3f}".rstrip('0').rstrip('.') if '.' in f"{current_value:.3f}" else f"{current_value}"
                            output_parts.append(f"{part}{formatted_value}")
                    else:
                        # F 和 S 等参数直接比较
                        if current_value != pre_value:
                            if part == self.toolpathparamer.move_s:
                                output_parts.append(f"{part}{int(current_value)}")
                            else:
                                formatted_value = f"{current_value:.3f}".rstrip('0').rstrip('.') if '.' in f"{current_value:.3f}" else f"{current_value}"
                                output_parts.append(f"{part}{formatted_value}")
            else:
                output_parts.append(part)


        # 组合成最终的G代码
        return " ".join(output_parts)
    
    def generate_circlemove_gcode_string(self, movecommand, pre_gmotion=None, pre_x=None, pre_y=None, pre_z=None, pre_f=None, pre_s=None, pre_r=None, **kwargs):
        if not movecommand:
            return ["未生成线性移动命令"]  # <--- 返回列表

        # 前一个值字典, 可
        pre_values = {
            self.toolpathparamer.move_x: pre_x,
            self.toolpathparamer.move_y: pre_y,
            self.toolpathparamer.move_z: pre_z,
            self.toolpathparamer.move_f: pre_f,
            self.toolpathparamer.move_s: pre_s,
            self.toolpathparamer.center_radius: pre_r,
        }
        nomal_z = kwargs.get('NZ')
        # 统一转为列表处理（兼容字符串或列表输入）
        commands = movecommand if isinstance(movecommand, list) else [movecommand]
        output_line = []  # <--- 存储每行G代码
        result_lines= []
        for i, cmd in enumerate(commands):
            parts = cmd.split()
            current_line_parts = []  # <--- 当前行的组成部分
            for part in parts:
                # 根据当前命令的索引选择参数来源
                if i == 0:  # 第一个命令（CC X Y Z）使用 center_x/center_y/center_z
                    param_mapping = {
                        'X': (self.toolpathparamer.center_x, kwargs.get('CX')),
                        'Y': (self.toolpathparamer.center_y, kwargs.get('CY')),
                        'Z': (self.toolpathparamer.center_z, kwargs.get('CZ')),
                        'F': (self.toolpathparamer.move_f, kwargs.get('F')),
                        'S': (self.toolpathparamer.move_s, kwargs.get('S')),
                        'R': (self.toolpathparamer.center_radius, kwargs.get('R')),
                    }
                else:  # 其他命令（如 C X Y Z F DR-）用 move_x/move_y/move_z
                    param_mapping = {
                        'X': (self.toolpathparamer.move_x, kwargs.get('X')),
                        'Y': (self.toolpathparamer.move_y, kwargs.get('Y')),
                        'Z': (self.toolpathparamer.move_z, kwargs.get('Z')),
                        'F': (self.toolpathparamer.move_f, kwargs.get('F')),
                        'S': (self.toolpathparamer.move_s, kwargs.get('S')),
                        'R': (self.toolpathparamer.center_radius, kwargs.get('R')),
                    }
                # 检查是否是参数（X/Y/Z/F/S/R）
                if part in param_mapping:
                    param_key, current_value = param_mapping[part]
                    pre_value = pre_values.get(param_key, None)
                    if i==0:
                        if current_value is not None and part != 'Z':
                            formatted_value = f"{current_value:.3f}".rstrip('0').rstrip('.') if '.' in f"{current_value:.3f}" else f"{current_value}"
                            current_line_parts.append(f"{part}{formatted_value}")
                    else:
                        if current_value is not None and current_value != pre_value:
                            if part == 'S':
                                current_line_parts.append(f"{part}{int(current_value)}")
                            else:
                                formatted_value = f"{current_value:.3f}".rstrip('0').rstrip('.') if '.' in f"{current_value:.3f}" else f"{current_value}"
                                current_line_parts.append(f"{part}{formatted_value}")
                elif part in self.gcode.gmotion.values():
                    if nomal_z == 1.:
                        current_line_parts.append(f"{self.gcode.get_motion_value('CLW_Arc')}")
                    elif nomal_z == -1.:
                        current_line_parts.append(f"{self.gcode.get_motion_value('CCLW_Arc')}")
                    else:
                        continue
                else:
                    current_line_parts.append(part)
            # 将当前行的部分组合成字符串，并添加到输出列表
            line = " ".join(current_line_parts)
            result_lines.append(line)
        return ("\n".join(result_lines))  # 将所有行合并为一个字符串，用换行符分隔  # <--- 返回分行结果



"""=============================================行号设置============================================================="""
def process_gcode_lines(gcode_lines, gcodemape = None, initial_values=None):
    """
    处理G代码行，支持多类指令的重复移除
    
    Returns:
        tuple: (处理后的gcode_lines列表, 更新后的指令状态字典)
    """

     # 初始化当前指令状态
    current_state = {
        'gmotion': None,
        'gplane': None,
        'gsystm': None
    }

    gcodemapeer = gcodemape if gcodemape else GCodeMapper()

    # 初始化当前指令状态
    current_state = {k: (initial_values[k] if initial_values and k in initial_values else None) 
                    for k in gcodemapeer.placeholder_to_category.keys()}
    
    processed_lines = []
    
    for line in gcode_lines:
        line_stripped = line.strip()
        if not line_stripped:
            processed_lines.append(line)
            continue
            
        words = line_stripped.split()
        new_words = []
        line_modified = False
        
        for word in words:
            word_matched = False
            
            # 检查是否属于任何指令类别
            for category, config in gcodemapeer.placeholder_to_category.items():
                if word in config:
                    # 如果与当前状态相同，跳过该指令
                    if word == current_state[category]:
                        line_modified = True
                        word_matched = True
                        break
                    # 否则更新状态并保留
                    else:
                        current_state[category] = word
                        new_words.append(word)
                        word_matched = True
                        break
            
            # 非指令类单词直接保留
            if not word_matched:
                new_words.append(word)
        
        # 如果行被修改或需要保留
        if new_words or not line_modified:
            processed_lines.append(' '.join(new_words) if new_words else '')
    
    return processed_lines



def add_line_numbers(gcode_lines, show_line_numbers=True, start_number=10, comment_char="; "):
    """
    为 G 代码行添加行号（可选是否显示）
    
    Args:
        gcode_lines (list[str]): 原始 G 代码行列表
        show_line_numbers (bool): 是否显示行号（默认 True）
        start_number (int): 起始行号（默认 1）
        comment_char (str): 行号注释符号（默认 "; "）
    
    Returns:
        list[str]: 处理后的 G 代码行列表
    """
    processed_lines = []
    current_line_number = start_number
    if show_line_numbers:
        for line in gcode_lines:
            # 添加行号（如: "N10 ; G0 X10"）
            numbered_line = f"N{current_line_number}{' '}{line}"
            processed_lines.append(numbered_line)
            current_line_number += 10
    else:
        processed_lines = gcode_lines 

    return processed_lines
     

"""=============================================CLS转换Gcode============================================================="""
def cls_to_gcode(json_input, cls_toolpathgenerate=None, showlinenumber = None):
    """
    将CLS内容转换为G代码
    这是一个简单示例，您需要根据实际的CLS格式进行调整
    """
    gcode_lines = []
    clstoolpathgenerate = cls_toolpathgenerate if cls_toolpathgenerate else ToolPathGenerator()
    gcodemap = GCodeMapper()
    customcommand = Customcommands(clstoolpathgenerate.toolpathcode,clstoolpathgenerate.toolpathparamer, clstoolpathgenerate.mcode,clstoolpathgenerate.gcode)

    clsparser = CLScodeParser()
    
    pre_x = None
    pre_y = None
    pre_z = None     
    pre_f = None
    pre_s = None
    pre_r = None
    pre_gmotion = None
    pre_point = []
    # drill_lines = []

    pre_Q200 = None
    pre_Q201 = None
    pre_Q206 = None
    pre_Q202 = None
    pre_Q210 = None
    pre_Q211 = None
    pre_Q203 = None
    pre_Q204 = None

    with open(json_input, 'r') as f:
        prams_settings = json.load(f)
        paths = prams_settings[0]["path"]

        #添加程序起始序列
        tool = prams_settings[0]["tool"]
        tool_number =tool["number"]
        start_line = f"""
BEGIN PGM program MM
;Begin Operation
CYCL DEF 247 DATUM SETTING ~ Q339=+1    ;DATUM NUMBER
PLANE RESET STAY
M5
L C+0 A+0 F1000
TOOL CALL{tool_number} Z S12000
M3 M8
"""
        gcode_lines.append(start_line)

        #工序起始序列
        start_x, start_y, start_z = prams_settings[0]["start_pos"]
        start_axis = prams_settings[0]["start_dir"]
        rapid_line = clstoolpathgenerate.generate_rapid_gcode_string(clstoolpathgenerate.rapid_move,pre_gmotion, pre_x, pre_y, pre_z, X= start_x, Y= start_y, Z= start_z)
        pre_x = start_x
        pre_y = start_y
        pre_z = start_z
        pre_point = [pre_x, pre_y, pre_z]
        pre_gmotion = gcodemap.get_motion_value("Rapid_Move")
        gcode_lines.append(rapid_line)

        #处理刀具路径
        for segment in paths:
            gtype = segment.get("type")
            
            if gtype == "linear":
                current_x, current_y, current_z = segment["point"]
                current_feedrate = segment["feedrate"]
                current_speedrate = segment["speedrate"]
                gcode_line = clstoolpathgenerate.generate_linemove_gcode_string(clstoolpathgenerate.linear_move,pre_gmotion, pre_x, pre_y, pre_z,pre_f, X= current_x, Y= current_y, Z= current_z, F= current_feedrate)
                pre_x = current_x
                pre_y = current_y
                pre_z = current_z
                pre_point = [pre_x, pre_y, pre_z]
                pre_f = current_feedrate
                pre_gmotion = gcodemap.get_motion_value("Linear_Move")
                gcode_lines.append(gcode_line)
                continue
            elif gtype == "RAPID":
                current_x, current_y, current_z = segment["point"]
                current_feedrate = segment["feedrate"]
                current_speedrate = segment["speedrate"]
                gcode_line = clstoolpathgenerate.generate_rapid_gcode_string(clstoolpathgenerate.rapid_move,pre_gmotion, pre_x, pre_y, pre_z, X= current_x, Y= current_y, Z= current_z)
                pre_x = current_x
                pre_y = current_y
                pre_z = current_z
                pre_point = [pre_x, pre_y, pre_z]
                pre_gmotion = gcodemap.get_motion_value("Rapid_Move")
                gcode_lines.append(gcode_line)
                continue
            elif gtype == "circle":
                current_x, current_y, current_z = segment["point"]
                cx, cy, cz = segment["center"]
                radius = segment["radius"]
                nx, ny, nz = segment["normal"]
                current_feedrate = segment["feedrate"]
                speedrate = segment["speedrate"]
                circle_line = clstoolpathgenerate.generate_circlemove_gcode_string(clstoolpathgenerate.circle_move,pre_gmotion, pre_x, pre_y, pre_z,pre_r, X=current_x, Y= current_y, Z= current_z, R=radius,CX = cx, CY = cy, CZ = cz, NZ = nz)
                pre_x = current_x
                pre_y = current_y
                pre_z = current_z
                pre_point = [pre_x, pre_y, pre_z]
                pre_f = current_feedrate
                pre_r = radius
                if nz == 1.:
                    pre_gmotion= gcodemap.get_motion_value("CLW_Arc") 
                else:
                    pre_gmotion = gcodemap.get_motion_value("CCLW_Arc")
                gcode_lines.append(circle_line)                
                continue
            elif gtype == "cycle":
                cycle_type = segment["cycle_type"]
                clear = segment["clear"]
                fedto = segment["fedto"]
                feed_rate = segment["feedrate"]
                current_point = segment["point"]
                step = segment["step"]
                dwell_type = segment["dwell_type"]
                dwell = segment["dwell"]
                drill_values = clsparser._parse_drill(pre_point, current_point, clear, fedto, feed_rate,step,dwell_type, dwell)
                drill_gcodelines = customcommand.Hedehan_Drill_handle(start_axis,current_point, pre_Q200,pre_Q201, pre_Q206, pre_Q210, pre_Q211, pre_Q202,pre_Q203, pre_Q204, Q200 = drill_values.Q200, Q201 = drill_values.Q201,Q206 = drill_values.Q206, Q210 = drill_values.Q210, Q211 = drill_values.Q211, Q202 = drill_values.Q202, Q203 = drill_values.Q203, Q204 = drill_values.Q204)
                pre_Q200 = drill_values.Q200
                pre_Q201 = drill_values.Q201
                pre_Q206 = drill_values.Q206
                pre_Q210 = drill_values.Q210
                pre_Q211 = drill_values.Q211
                pre_Q202 = drill_values.Q202
                pre_Q203 = drill_values.Q203
                pre_Q204 = drill_values.Q204
                gcode_lines.append(drill_gcodelines)
                continue
                                        
            else:
                continue
    end_line = """
M9
M127
M129
;REMARK END OF OPERATION
M30
;End Operation
"""
    gcode_lines.append(end_line)        
    
    # gcode_lines = process_gcode_lines(gcode_lines, gcodemap)
    # gcode_lines = add_line_numbers(gcode_lines,showlinenumber)
    
    return gcode_lines


"""=============================================主程序============================================================="""
if __name__ == "__main__":
    # 设置命令行参数
    parser = argparse.ArgumentParser(description="CLS 转 G 代码转换器")
    parser.add_argument("--input", "-i", required=True, help="输入的JSON文件路径")
    parser.add_argument("--output", "-o", required=True, help="输出的 G 代码文件路径")
    args = parser.parse_args()

    # 初始化解析器和工具路径生成器
    parser = CLScodeParser()
    toolpathcode = ToolPathCode()
    paramer = ToolPathParamers()
    mcode = MCodeMapper()
    gcode = GCodeMapper()
    toolpath = ToolPathGenerator(toolpathcode, paramer, mcode, gcode)

    # 生成 G 代码并保存
    g_lines = cls_to_gcode(args.input, toolpath,True)
    with open(args.output, "w", encoding="utf-8") as f:
        for item in g_lines:
            f.write(item + "\n")
    
    print(f"G 代码已生成并保存到 {args.output}")


# def select_file():
    # """打开文件选择对话框，返回选择的文件路径"""
    # root = tkinter.Tk()
    # root.withdraw()  # 隐藏主窗口
    # file_path = filedialog.askopenfilename(
        # title="选择 CLS 文件",
        # filetypes=[("CLS 文件", "*.cls"), ("文本文件", "*.txt"), ("所有文件", "*.*")]
    # )
    # return file_path
# 
# if __name__ == "__main__":
    # 
    # clscontent = select_file()
    # if not clscontent:  # 如果用户取消选择
        # print("未选择文件，程序退出。")
        # exit()
# 
#    初始化解析器和工具路径生成器
    # parser = CLScodeParser()
    # toolpathcode = ToolPathCode()
    # paramer = ToolPathParamers()
    # mcode = MCodeMapper()
    # gcode = GCodeMapper()
    # toolpath = ToolPathGenerator(toolpathcode, paramer, mcode, gcode)
# 
    # g_lines = cls_to_gcode(clscontent, toolpath,True)
    # with open("file.txt", "w", encoding="utf-8") as f:
        # for item in g_lines:
            # f.write(item + "\n")
    # 
    # print(f"G 代码已生成并保存到 file.txt")