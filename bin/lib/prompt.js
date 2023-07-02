/
const readline = require('readline');

// 创建 readline.Interface 实例
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

// 定义可选项数组
const options = ['Option 1', 'Option 2', 'Option 3'];

// 定义变量来存储选择的选项索引
let selectedIndex = -1;

// 定义递归函数来处理用户输入
function promptUser() {
  // 显示可选项列表
  console.log('请选择一个选项:');
  options.forEach((option, index) => {
    console.log(`${index + 1}. ${option}`);
  });

  // 提示用户输入
  rl.question('> ', (answer) => {
    // 解析用户输入为数字
    const userInput = parseInt(answer);

    // 检查用户输入是否有效
    if (isNaN(userInput) || userInput < 1 || userInput > options.length) {
      console.log('无效的选项，请重新选择。\n');
      promptUser();
      return;
    }

    // 存储选择的选项索引
    selectedIndex = userInput - 1;

    // 显示选择的选项
    console.log(`您选择了 ${options[selectedIndex]}\n`);

    // 关闭 readline.Interface
    rl.close();
  });
}

// 启动交互式界面
promptUser();
