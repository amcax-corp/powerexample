#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
import os
from pathlib import Path
import time
import importlib.util
import json

start_time = time.time()

if len(sys.argv) != 4:
    print("Usage: python fbmmanager.py scripts.py <in.json> <out.json>")
    sys.exit(1)
    
    # 获取当前脚本所在目录的父目录（即项目根目录）
project_root = Path(__file__).parent / "scripts" # 调整层级关系

py_file = os.path.abspath(os.path.join(project_root, sys.argv[1]))

spec = importlib.util.spec_from_file_location("process_json", py_file)

if spec is None:
    print(f"Failed to load module from {py_file}")
    sys.exit(1)
    
user_module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(user_module)    

input_file = sys.argv[2]
output_file = sys.argv[3]

if os.path.exists(output_file):
    os.remove(output_file)
    
data = ""

if os.path.exists(input_file):
    # Read the input file
    with open(input_file, 'r', encoding='utf-8') as f:
        data = f.read()
else:
    print(f"Input file {input_file} does not exist.")
    sys.exit(1)
  

out_data = user_module.ProcessJson(data)

with open(output_file, 'w', encoding='utf-8') as f:
    json.dump(out_data, f, indent=4, ensure_ascii=False)

end_time = time.time()
print(f"Total execution time: {end_time - start_time:.2f} seconds")
    

    

    

