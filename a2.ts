const { spawn } = require('child_process');

// 创建 Python 子进程，设置工作目录为 'D:\\nodejstest'
const pythonProcess = spawn('python3', ['a1.py'], {
  cwd: '/www/wwwroot/nodejs'
});

// 向 Python 子进程的标准输入流中写入数据
pythonProcess.stdin.write('3\n'); // 写入第一个参数
pythonProcess.stdin.write('5\n'); // 写入第二个参数
pythonProcess.stdin.end(); // 结束输入

// 监听子进程的输出
pythonProcess.stdout.on('data', (data:any) => {
  console.log(`Python 输出：${data}`);
});

pythonProcess.stderr.on('data', (data:any) => {
  console.error(`Python 错误：${data}`);
});

pythonProcess.on('close', (code:any) => {
  console.log(`Python 进程退出，退出码 ${code}`);
});
