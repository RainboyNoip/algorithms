# 生成 用于 vim plugin 的数据
# 使用: python3 bin/gen_vim_plugin_data.py


# 算法过程
# 1. 得到所有的hpp头文件
# 2. 生成一个dict型邻接表
# 3. 提取 header,info,word,abbr等信息
# 4. top sort -> 生成 头序列

import glob
import re
import json
from os import path
#glob.glob(
include_path = path.realpath( path.join(path.dirname(__file__),'../include') )
header_files = glob.glob( include_path + '/**/*.hpp',recursive=True) 
#print(header_files)
#print(include_path)

# {
#   "hpp_name" : {
#       depHeaders : [] # 依赖的头
#       items: {} #  提取的 complete_items
#   }
# }
linkedNode = {}

def ensure_header(header):
    print('->',header)
    if header not in linkedNode:
        linkedNode[header] = {'depHeaders':[],'complete_items':None}

def setCompleteItems(header,items):
    ensure_header(header)
    linkedNode[header]['complete_items']= items

def addDepHeader(header,depHeaders):
    for h in [header] + depHeaders:
        ensure_header(h)
    for dh in depHeaders:
        if dh not in linkedNode[header]:
            linkedNode[header]['depHeaders'].append(dh)

# 
# 得到所依赖的hpp头文件
def getDepHeaders(str):
    depHeaders = []
    for line in str.split('\n'):
        if len(line) < 8 :
            continue
        matchObj = re.match(r'#include\s*"(.+)"\s*',line)
        if matchObj:
            depHeaders.append(matchObj.group(1))
    return depHeaders
for header in header_files:
    header_conent = open(header,encoding = "utf-8").read()
    matchObj =  re.search(r'/\*---\s*((.|\n)*)\s*---\*/',header_conent,re.M)
    key = path.relpath(header,include_path)
    print(key)
    if matchObj :
        print('yes')
        item_str = matchObj.group(1)
        setCompleteItems(key,json.loads(item_str))
        addDepHeader(key, getDepHeaders(header_conent))
    else:
        print('no')
print(json.dumps(linkedNode,indent=4))

# 2. 生成 complete_items 列表
# 每个word 对应的 头文件

all_complete_items = []
all_word_pairs= {}
for key in linkedNode:
    if linkedNode[key]['complete_items']:
        word = linkedNode[key]['complete_items']['word']
        expand = linkedNode[key]['complete_items']['expand']
        info = linkedNode[key]['complete_items']['info']
        all_word_pairs[word] = {
                'header':key,
                'expand':expand
                }
        #linkedNode[key]['complete_items']['user_data'] = "ralgo|{}".format(key)
        all_complete_items.append({'word':word,'info':info})
print(all_complete_items)
print(all_word_pairs)
# 3. top-sort

topSortHeader = []
headerTot = len(linkedNode.keys())

stack = [key for key in linkedNode.keys() if len(linkedNode[key]['depHeaders']) == 0]

headerCnt = len(stack)

while len(stack) != 0:
    h = stack.pop()
    topSortHeader.append(h)
    if headerCnt == headerTot:
        continue
    for key in linkedNode:
        if h in linkedNode[key]['depHeaders']:
            linkedNode[key]['depHeaders'].remove(h)
            if len(linkedNode[key]['depHeaders']) == 0:
                stack.append(key)

print('\n'.join(topSortHeader))
