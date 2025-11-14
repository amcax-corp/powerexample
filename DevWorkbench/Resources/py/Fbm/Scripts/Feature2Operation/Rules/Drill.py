# def check(feature):
#     # 只处理直径大于10的通孔
#     return feature.get("TYPE") == "Through Hole" and feature.get("DIAMETER_1", 0) > 10

# def get_tool(feature):
#     diameter = feature.get("DIAMETER_1", 0)
#     depth = feature.get("DEPTH", 0)
#     # 检查feature类型是否为dict
#     if not isinstance(feature, dict):
#         raise TypeError("feature参数必须是dict类型")
#     return {
#         "tool_type": "STD_TOOL",
#         "operation": "SPOT_DRILLING",
#         "parameters": {
#             "Main/NonCuttingPortion/NeckDiameter": diameter,
#             "Main/CuttingPortion/PAAngle": 118.0,
#             "Main/CuttingPortion/PitchLength": 2.0,
#             "Main/CuttingPortion/CornerRadius": 0.5,
#             "Main/CuttingPortion/FlutelLength": round(depth * 1.2, 2),
#             "Main/NonCuttingPortion/TotalLength": round(depth * 1.2 + 10, 2)
#         }
#     }# This module defines a custom drill tool for large through holes.