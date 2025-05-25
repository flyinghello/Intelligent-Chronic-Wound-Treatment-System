const http=require('http')
const express=require('express')
const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');
const socketio=require('socket.io')
const app=express();
const server = http.Server(app);
const io=socketio(server,{
    pingTimeout: 1000 * 60,//超时时间
    pingInterval: 1000 * 1,//ping的时间
    transports: ['websocket', 'polling'],//传输方式
    allowUpgrades: true,//传输是否升级
    httpCompression: true,//是否加密
    allowEIO3: true,
    cors:{//118.25.16.45:4000/
        // origin: "http://localhost:7457", // from the screenshot you provided
        methods: ["GET", "POST"],
        credentials: true}
});

const faker = require('faker');

function generatePatientData(id) {
    // 随机生成病人数据
    const name = faker.name.firstName() + faker.name.lastName();  // 随机生成名字
    const imageurl = faker.image.avatar();  // 随机生成头像图片URL
    const introduceurl = faker.internet.url();  // 随机生成介绍页面URL
    const woundimageurl = faker.image.imageUrl(200, 200, 'abstract');  // 随机生成伤口图片URL
    const introduce = faker.lorem.sentence();  // 随机生成病人的介绍

    // 生成随机体温数据
    const temperaturearray = [];
    for (let i = 0; i < 10; i++) {
        temperaturearray.push(faker.datatype.float({ min: 36.0, max: 37.5, precision: 0.1 }));
    }

    // 生成随机电压数据
    const voltagearray = [];
    for (let i = 0; i < 10; i++) {
        voltagearray.push(faker.datatype.float({ min: 3.0, max: 5.0, precision: 0.1 }));
    }

    return {
        id: id,  // 使用传入的 id
        imageurl: imageurl,
        introduceurl: introduceurl,
        introduce: introduce,
        woundimageurl: woundimageurl,
        name: name,
        temperaturearray: temperaturearray,
        voltagearray: voltagearray  // 添加电压数据
    };
}

// 生成100个病人数据
function generatePatientsData(num) {
    const patientsData = [];
    for (let i = 0; i < num; i++) {
        const patient = generatePatientData(i);  // 使用i作为ID
        patientsData.push(patient);
    }
    return patientsData;
}

// Express 路由处理函数
app.post('/getpatientdata', (req, res) => {
    console.log("get patientdata");
    const patientsData = generatePatientsData(100); // 生成100个病人数据
    let data = { patientslist: patientsData }
    console.log(patientsData);  // 打印生成的数据
    res.send(data);  // 返回数据
});



io.on('connection',(socket:any)=>{
    console.log('连上')
    socket.emit('connect_success','success')
    
    socket.on('image', (base64Image:any,imagename:any) => {
        console.log('接收到图片');
        console.log(imagename)
        const savePath = path.join(__dirname, imagename);
        // 将Base64解码并保存为文件
        const imageBuffer = Buffer.from(base64Image, 'base64');
        fs.writeFile(savePath, imageBuffer, (err:any) => {
            if (err) {
                console.error('保存图片时发生错误:', err);
                socket.emit('image_save_message','图片保存失败')
                return;
            }
            // console.log('图片已保存:', savePath);
            socket.emit('image_save_message', '图片保存成功');
            const pythonProcess = spawn('python3', ['app_test.py'], {cwd: '/www/wwwroot/wound_recognize/notebooks'});
            // 向 Python 子进程的标准输入流中写入数据
            pythonProcess.stdin.write(savePath+'\n'); // 写入第一个参数
            pythonProcess.stdin.end(); // 结束输入
            pythonProcess.stdout.on('data', (data:any) => {
                console.log(`Python 输出：${data}`);
                socket.emit('resdata',data)
            });
            pythonProcess.stderr.on('data', (data:any) => {console.error(`Python 错误：${data}`);});
            pythonProcess.on('close', (code:any) => {console.log(`Python 进程退出，退出码 ${code}`);});
            
            
        });
    })
    
    socket.on('get_data',(data:any)=>{
        console.log(data)
    })
    
})

server.listen('4000', (err: any) => {
    if (err) {
        return console.error(err);
    }
    console.log('listen');
});