#bin!/bin/bash
#把 代码模板 生成成当前文件
filename="${1:-1.cpp}"
cols=$(tput cols)
preview_window_opt="--preview-window right,50%"

if (( cols <= 120 ));then
    preview_window_opt="--preview-window bottom,50%"
fi
# echo $preview_window_opt
# echo $cols
# exit 0

if [[ ! "$filename" =~ \.cpp$ ]]; then
  filename="${filename}.cpp"
fi
# 获取当前脚本所在的目录
script_dir=$(dirname "$0")/../template

# 复制 a.cpp 到当前运行目录下
choose=$(find $script_dir -maxdepth 2 -type f -name "*" -printf "%P\n" | fzf \
        --tac --layout=reverse --border=top \
        --border-label="choose input" --border-label-pos=4 \
        --select-1 --ansi \
        $preview_window_opt \
        --preview="bat --color=always ${script_dir}/{}"
    )

if [ -z "$choose" ];then
    echo "没有选择任何模板"
    exit 0
fi

if [ -f $filename ];then 
    echo "当前目录存在文件 $filename"
    read -p "是否替换(y/N):" choice
    if [[ "$choice" == "N" || "$choice" == "n" || "$choice" == "" ]];then
        exit 0
    fi
fi

cp "$script_dir/$choose" $filename

echo "复制成功！当前目录下的文件: "$filename
