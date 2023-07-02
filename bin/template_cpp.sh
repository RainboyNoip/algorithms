#!/bin/bash
#把 代码模板 生成成当前文件
filename="${1:-1.cpp}"
if [[ ! "$filename" =~ \.cpp$ ]]; then
  filename="${filename}.cpp"
fi
# 获取当前脚本所在的目录
script_dir=$(dirname "$0")/..

# 复制 a.cpp 到当前运行目录下
cp "$script_dir/template.cpp" ./$filename

echo "复制成功！当前目录下的文件 "$filename
