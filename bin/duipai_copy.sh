#把 对拍模板 生成成当前文件

#!/bin/bash

# 获取当前脚本所在的目录
script_dir=$(dirname "$0")/lib

# 复制 a.cpp 到当前运行目录下
#cp "$script_dir/duipai_template.cpp" ./duipai.cpp
cp "$script_dir/data.cpp" ./data.cpp
cp "$script_dir/duipai.sh" ./duipai.sh

echo "复制成功！当前目录下的文件 duipai.cpp,data.cpp"
