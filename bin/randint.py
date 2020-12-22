#!/bin/env python3
# 随机生成一组数据
# randint.py [10] [-min 20] [-max 30]
# -min default 1
# -max default 10
import argparse
import random
parser = argparse.ArgumentParser(description="随机生成一组数据")
parser.add_argument("numCount",help="输出随机数的个数",type=int,default=5,nargs="?")
parser.add_argument("-min","--Min",help="输出随机数的最小值",type=int,default=1)
parser.add_argument("-max","--Max",help="输出随机数的最大值",type=int,default=10)
args = parser.parse_args()
# print(*vars(args))

locals().update(vars(args))
# print(locals())

l = [str(random.randint(Min,Max)) for _i in range(0,numCount)]
print(' '.join(l))
