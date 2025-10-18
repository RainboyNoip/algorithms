# 编译脚本 author Rainboy https://github.com/Rainboylvx

VERSION="20231207"

print_help ()
{
    printf "help"
}
print_help

#--- 参数 start
no_input=0  # 不需要重定向输入
run=0       # 不需要编译后运行
std="c++17" # c++标准
def="-DDEBUG" # 宏
input=""    # 重定向的输入文件
ouput=""    # 重定向的输出文件
compileFlags="-g" #编译选项
cc="g++"    # 编译器
cppFile=""  # cpp代码文件
cppOut=""   # cpp代码输出文件
#--- 参数 end

#--- 参数读取 start
while [[ $1 ]]; do
    
done
#--- 参数读取 end

#=== 编译前

#=== 编译中
$cc $compileFlags -std=$std $def -o $cppOut $cppFile

# 编译失败
if [[ $? -ne 0 ]];then
    exit 1
fi


#=== 编译后

if [[ $run -eq 0 ]];then
    exit 0
fi

if [[ $no_input -eq 1 ]] && [[ $output -ne 0 ]];then
elif [[ ]];then
fi

$cppFile < $input > $output
