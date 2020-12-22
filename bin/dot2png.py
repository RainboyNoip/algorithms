#!/usr/bin/env python
import argparse
import os
import random
import glob

def list_dots(directory):
    return glob.glob(os.path.join(directory, '*.dot'))

parser = argparse.ArgumentParser(description="把dot文件转成png文件")

# parser.add_argument("dot",help="",type=int,default=5,nargs="?")
parser.add_argument("input_path",help="目录文件下的所有dot文件",type=str,default=".",nargs="?")
# parser.add_argument("-o","--ouput",help="",type=str,default=)
parser.add_argument("-O","--output_path",help="输出的目录",type=str,default=".")

args = parser.parse_args()

if __name__ == "__main__":
    l = list_dots(args.input_path)
    for dot in l:
        os.system("dot -Tpng -o {} {}".format(os.path.splitext(dot)[0]+'.png',dot))


