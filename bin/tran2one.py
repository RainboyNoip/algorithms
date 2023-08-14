#!/bin/env python3
# 作用: 把include 所有的头 包含进行转成一个文件
# 原理
# feature:
# - [ ] 过滤所有注释
# - [x] 安装的自动写入,a.cpp -> a_tran.cpp
# - [x] 添加-c命令,是否复制到剪切板
#
#
import argparse
import os
import re
import sys
import subprocess
from subprocess import Popen, PIPE
# p = Popen(['xsel','-pi'], stdin=PIPE)
# p.communicate(input='Hello, World')


parser = argparse.ArgumentParser(description="转换代码")
parser.add_argument("file_name",help="转换的代码文件名",nargs="?")
parser.add_argument("-c","--copy",help="复制到剪贴板",action="store_true")
parser.add_argument("-v","--verbose",help="显示详细信息",action='store_true')
ARGS = vars(parser.parse_args())

def verbose(*args,**kwargs):
    if ARGS["verbose"]:
        print(*args,**kwargs,end="",file=sys.stderr)

# 没有指定文件名
if not ARGS["file_name"]:
    verbose("没有指定代码名,当前目录下的源代码为: ")
    cpplist = sorted(list(filter(lambda x: x.endswith(".cpp"),os.listdir())))
    if len(cpplist) == 0:
        verbose("空,退出\n")
        sys.exit(1)
    verbose("  ".join(cpplist)+"\n")
    ARGS["file_name"] = cpplist[0]

# 没有指定编译输出
# if not ARGS["output"]:
#     ARGS["output"] = os.path.splitext(ARGS["file_name"])[0]

verbose("转换的代码 %s\n" % ARGS["file_name"])
# if not ARGS["output"]:
#     verbose("转化到剪切板")
# else:
#     verbose("转化为: %s\n" % ARGS["output"])

ignore_includes = ["utils.hpp"]

# algorithm include 的目录
algorithm_include_path = os.path.abspath(
    os.path.join(
            os.path.dirname(os.path.realpath(__file__)),
            '../include'
            ))

verbose('algorithm库目录 ',algorithm_include_path)

#读取文件
def readFile(fileName):
    with open(fileName) as f:
        return f.read().splitlines()

# 读取文件

out_str = ''

include_file_set = set()


status = ""
s_block_comment = "block comment"
s_debug = "debug"
line_num = 0 # 行计数



def tran_file(fileName):
    global out_str
    global status
    global line_num
    for line in readFile(fileName):
        line_num += 1
        if line.strip() == "#pragma once": # 去除 #pragma once 行
            continue;
        if line_num!=1 and status != s_block_comment and line.strip().startswith("/*"):
            status = s_block_comment

        if status == s_block_comment :
            if line.strip().endswith("*/"):
                status = ""
            continue

        if line.strip().startswith("//"):
            continue

        if line.strip() == "": # 空行
            continue

        if line.strip() == '#ifdef DEBUG':
            status = s_debug

        if status == s_debug:
            out_str += line +'\n'
            if line.strip() == '#endif' :
                status = ""
            continue


        # matchObj = re.match('^#include\ ?"(\w+|/)+"$',line,re.I)
        matchObj = re.match('^#include\ ?"([\w/\.]+)"[\s\S]*$',line,re.I)
        if matchObj:
            include_file = matchObj.group(1)
            if include_file in ignore_includes: # 忽略的头文件
                continue
            real_file_path = os.path.join(algorithm_include_path,include_file)
            if os.path.exists(real_file_path) : # 存在这个文件
                # print(real_file_path)
                # out_str += '//---> '+ line +'\n' # 注释掉
                if real_file_path not in include_file_set:
                    include_file_set.add(real_file_path)
                    tran_file(real_file_path) 
            else:
                out_str += line +'\n'
        else:
            out_str += line +'\n'

tran_file(ARGS["file_name"])
#print(out_str)
[file_name_noext,extname] = os.path.splitext(ARGS["file_name"])
out_filename = file_name_noext + "_tran" + extname
write_flag = "y"
while True:
    if os.path.exists(out_filename):
        write_flag = input(f"文件: [{out_filename}] 已经存在,是否写入 [Y/n]? ")
        if write_flag.lower() in ['y', 'n' ,'']:
            break
    else:
        write_flag = "y"
        break







# 声明头
copyright = '''/*
 *   rainboyNoip/algorithms, some helpful cpp utils for noi/acm user
 *    Copyright (C) 2020-2021  Rainboy
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
'''






out_str = copyright + out_str

if write_flag.lower() in ['y','']:
    # 写入文件的代码
    with open(out_filename, "w") as file:
        file.write(out_str)
    print(f"写入文件: {out_filename}")
else:
    print("不写入文件")
    

if ARGS["copy"]:
    subprocess.run(['xsel', '-i','-b'], input=out_str, encoding='utf-8')
    print("已经复制转化的内容到剪切板上!")
