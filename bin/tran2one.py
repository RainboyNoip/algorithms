#!/bin/env python3
# 作用: 过能include 所有的头 包含进行转成一个文件
#
#
#
#
#
import argparse
import os
import re
import sys
from subprocess import Popen, PIPE
# p = Popen(['xsel','-pi'], stdin=PIPE)
# p.communicate(input='Hello, World')


parser = argparse.ArgumentParser(description="转换代码")
parser.add_argument("file_name",help="转换的代码文件名",nargs="?")
parser.add_argument("-o","--output",help="转换输出的程序名,默认到剪贴板")
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
if not ARGS["output"]:
    ARGS["output"] = os.path.splitext(ARGS["file_name"])[0]

verbose("转换的代码 %s\n" % ARGS["file_name"])
if not ARGS["output"]:
    verbose("转化到剪切板")
else:
    verbose("转化为: %s\n" % ARGS["output"])

# algorithm include 的目录
algorithm_include_path = os.path.abspath(
    os.path.join(
            os.path.dirname(os.path.realpath(__file__)),
            '../include'
            ))

print(algorithm_include_path)

def readFile(fileName):
    with open(fileName) as f:
        return f.read().splitlines()

# 读取文件

out_str = ''

include_file_set = set()


def tran_file(fileName):
    global out_str
    for line in readFile(fileName):
        if line.strip() == "#pragma once":
            continue;
        # matchObj = re.match('^#include\ ?"(\w+|/)+"$',line,re.I)
        matchObj = re.match('^#include\ ?"([\w/\.]+)"\s*$',line,re.I)
        if matchObj:
            include_file = matchObj.group(1)
            real_file_path = os.path.join(algorithm_include_path,include_file)
            if os.path.exists(real_file_path) :
                if real_file_path not in include_file_set:
                    include_file_set.add(real_file_path)
                    tran_file(real_file_path)
            else:
                out_str += line +'\n'
        else:
            out_str += line +'\n'

tran_file(ARGS["file_name"])
print(out_str)
