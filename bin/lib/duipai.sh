#!/bin/bash
total_count=200
compare_dir="compare"
data_generator=data.out
usr_program=1.out
std_program=right.out

# 比较的基本路径
# tmp 是一个在内存的中filesystem,速度快
base_dir=/tmp

show_progress() {
    local total=$1
    local current=$2
    local width=50  # 进度条宽度

    # 计算进度百分比
    local percentage=$((current * 100 / total))
    # 计算进度条填充的长度
    local progress=$((current * width / total))
    # 生成进度条字符串
    local bar=$(printf "=%.0s" $(seq 1 $progress) )
    # 显示进度条和百分比
    # printf "\r[%-${width}s] %d%%" "$bar" "$percentage"
    printf "\r[%-${width}s] %d/%d %d%%" "$bar" $current $total $percentage
}

mkdir -p $compare_dir

show_progress $total_count 0
for ((i=1; i<=total_count; i++))
do
    # ./$data_generator > $compare_dir/in 
    # ./$usr_program < $compare_dir/in > $compare_dir/user_out 2> /dev/null
    # ./$std_program < $compare_dir/in > $compare_dir/std_out 2> /dev/null
    
    ./$data_generator > $base_dir/in 
    ./$usr_program < $base_dir/in > $base_dir/user_out 2> /dev/null
    ./$std_program < $base_dir/in > $base_dir/std_out 2> /dev/null
    if ! /usr/bin/diff -q $compare_dir/user_out $compare_dir/std_out &> /dev/null; then
        # 如果diff出错
        echo  # 换行
        echo "diff出错，i的值为 $i"
        vimdiff $base_dir/user_out  $base_dir/std_out # 执行vimdiff进行比较
        rm $base_dir/user_out  $base_dir/std_out
        exit 1
    fi
    show_progress $total_count $i
done
rm $base_dir/user_out  $base_dir/std_out
