#!/usr/bin/env python
import argparse
import os
import random
import glob

def list_dots(directory):
    return glob.glob(os.path.join(directory, '*.dot'))

example_text = '''example:
 dp.py 1 2 
 dp.py program_a pb.py'''

parser = argparse.ArgumentParser(description="对拍",epilog=example_text,formatter_class=argparse.RawDescriptionHelpFormatter)

parser.add_argument("a_program",help="对拍的程序1",type=str,default="1",nargs="?")
parser.add_argument("b_program",help="对拍的程序2",type=str,default="2",nargs="?")
parser.add_argument("-i","--input",help="设定数据生成的input的文件名",type=str,default="input",nargs="?")
parser.add_argument("-o","--output",help="设定对拍的output的文件名的前缀",type=str,default="out",nargs="?")
# parser.add_argument("-o","--ouput",help="",type=str,default=)
# parser.add_argument("-O","--output_path",help="输出的目录",type=str,default=".")

args = parser.parse_args()

def do_compare(user_programa,right_program,data_gen_program,input_file_name='input',output_file_name='out'):
    """TODO: Docstring for do_compare.

    :user_programa: TODO
    :right_program: TODO
    :data_gen_program: TODO
    :input_file_name: TODO
    :output_file_name: TODO
    :returns: TODO

    """
    run_program_by_ext = {
        '':'',
        '.py':'python3'
    }
    os.system('{run} {data_gen_program} > {input_file_name}'.format())
    os.system('{run} user_programa < {input_file_name} > {out}'.format())
    os.system('{run} right_program < {input_file_name} > {out}'.format())
    return os.system('diff {out1} {out2}'.format())

if __name__ == "__main__":
    print(args)


