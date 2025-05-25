
// 获取应用实例
const app = getApp();
const io = require('../../utils/weapp.socket.io');
let client = io.connect("http://134.175.127.33:4000");
const fs = wx.getFileSystemManager();

//const socketioUploader = require("../../moudule/");


// 辅助函数：检查数组中是否包含特定键值对
function inArray(arr: string | any[], key: string, val: string) {
  for (let i = 0; i < arr.length; i++) {
    if (arr[i][key] === val) {
      return i;
    }
  }
  return -1;
}

// 辅助函数：将字符串转换为 ArrayBuffer
function str2ab(str: string) {
  let buf = new ArrayBuffer(str.length);
  let bufView = new Uint8Array(buf);
  for (var i = 0, strLen = str.length; i < strLen; i++) {
    bufView[i] = str.charCodeAt(i);
  }
  return buf;
}

// 辅助函数：将 ArrayBuffer 转换为字符串
function ab2str(buffer: Iterable<number>) {
  return String.fromCharCode.apply(null, new Uint8Array(buffer));
}

Page({
  data: {

    //参数操作部分

    // Picker 数据
    array_pwm: ['50%', '70%', '100%'],
    index_pwm: 0,

    // 富文本

    richText_E: [{
      name: 'div',
      attrs: { class: 'big-text' },
      children: [
        { name: 'span', attrs: { class: 'param-name' }, children: [{ type: 'text', text: '电压(mV):' }] },
        { name: 'span', attrs: { class: 'param-value' }, children: [{ type: 'text', text: '---' }] }
      ]
    }],
    richText_temperature: [{
      name: 'div',
      attrs: { class: 'big-text' },
      children: [
        { name: 'span', attrs: { class: 'param-name' }, children: [{ type: 'text', text: '当前伤口温度(摄氏度): ' }] },
        { name: 'span', attrs: { class: 'param-value' }, children: [{ type: 'text', text: '___' }] }
      ]
    }],

    // 当前展开的部分
    expandedSection: null,

    //蓝牙连接部分

    devices: [], // 存储找到的蓝牙设备
    chs: [], // 存储蓝牙特征

    
    isConnected: false, // 蓝牙连接状态
    isFound: false, //设备搜索状态

    // 图片上传部分
    imgList: [], // 图片路径列表
    imgMaxNumber: 4, // 最大图片数量
    imgCnt: 0  //上传的图片总数量
  },
  // Setting选择成功之后
  setting1change()
  {
    wx.showToast({ title: "输出电压设置成功", icon: "none" });
  },
  // PICKER选择器改变值
  bindPickerChange(e: { currentTarget: { dataset: { type: any; }; }; detail: { value: any; }; }) {
    const type = e.currentTarget.dataset.type;
    const value = e.detail.value;
    console.log('picker发送选择改变，携带值为', value);

    if (type === 'pwm') {
      this.setData({
        index_pwm: value
      });
    }
  },
  // 通过wxml传参，可以得知需要展开的选项是pwm还是电压还是温度
  toggleSection(event: { currentTarget: { dataset: { section: any; }; }; }) {
    const section = event.currentTarget.dataset.section; //得到传递的参数
    this.setData({
      expandedSection: this.data.expandedSection === section ? null : section // 赋值为传递的参数
    });
  },
  // 富文本更新
  updateRichText() {
    const T = app.globalData.temperature || 'NULL';
    const V = app.globalData.voltage || 'NULL';
    const PWM = app.globalData.pwm || 'NULL';
    const E = app.globalData.fieldIntensity || 'NULL';

    this.setData({
      richText_T: [{
        name: 'div',
        attrs: { class: 'big-text' },
        children: [
          { name: 'span', attrs: { class: 'param-name' }, children: [{ type: 'text', text: '当前伤口温度：' }] },
          { name: 'span', attrs: { class: 'param-value' }, children: [{ type: 'text', text: T }] },
          { name: 'span', attrs: { class: 'param-value' }, children: [{ type: 'text', text: '摄氏度' }] }
        ]
      }],
      richText_E: [{
        name: 'div',
        attrs: { class: 'big-text' },
        children: [
          { name: 'span', attrs: { class: 'param-name' }, children: [{ type: 'text', text: '电压：' }] },
          { name: 'span', attrs: { class: 'param-value' }, children: [{ type: 'text', text: E }] },
          { name: 'span', attrs: { class: 'param-value' }, children: [{ type: 'text', text: '(mV)' }] }
       
        ]
      }],
    });
  },

  

  // 初始化蓝牙模块
  openBluetoothAdapter() {
    this.closeBluetoothAdapter();
    wx.openBluetoothAdapter({
      success: response => {
        console.log("初始化蓝牙模块成功：openBluetoothAdapter", response);
        this.startBluetoothDevicesDiscovery(); // 开始搜索蓝牙设备
      },
      fail: err => {
        if (err.errCode === 10001) {
          wx.onBluetoothAdapterStateChange(res => {
            console.log("监听蓝牙适配器状态变化事件：onBluetoothAdapterStateChange", res);
            res.available && this.startBluetoothDevicesDiscovery();
          });
        }
      },
    });
  },
  
  // 获取蓝牙适配器状态
  getBluetoothAdapterState() {
    wx.getBluetoothAdapterState({
      success: res => {
        console.log("getBluetoothAdapterState", res);
        if (res.discovering) {
          this.onBluetoothDeviceFound(); // 搜索到设备
        } else if (res.available) {
          this.startBluetoothDevicesDiscovery(); // 开始搜索设备
        }
      },
    });
  },
  
  // 开始搜索蓝牙设备
  startBluetoothDevicesDiscovery() {
    if (this._discoveryStarted) return;

    this._discoveryStarted = true;
    wx.startBluetoothDevicesDiscovery({
      allowDuplicatesKey: true,
      success: response => {
        console.log("开始搜寻附近的蓝牙外围设备：startBluetoothDevicesDiscovery", response);
        this.onBluetoothDeviceFound(); // 注册设备发现事件
       
      },
      fail: err => {
        console.log("搜索设备失败", err);
        wx.showToast({ title: "搜索设备失败", icon: "error" });
      },
    });
  },
  
  // 停止搜索蓝牙设备
  stopBluetoothDevicesDiscovery() {
    console.log("停止搜寻附近的蓝牙外围设备");
    wx.stopBluetoothDevicesDiscovery();
  },
  
  // 处理发现的蓝牙设备
  onBluetoothDeviceFound() {
    wx.onBluetoothDeviceFound(res => {
      res.devices.forEach(device => {
        if (!device.name && !device.localName) {
          return;
        }

        const foundDevices = this.data.devices;
        const idx = inArray(foundDevices, "deviceId", device.deviceId);
        const data = {};
        if (idx === -1) {
          data[`devices[${foundDevices.length}]`] = device;
        } else {
          data[`devices[${idx}]`] = device;
        }
        this.setData(data); // 更新页面数据
      });


      // // 如果当前面板是折叠状态，则展开面板
      // if (!this.data.isFound) {
      //   this.setData({ isFound: true });
      // }
      
    }); 
  },
  
  // 创建蓝牙连接
 createBLEConnection(e: { currentTarget: { dataset: any; }; }) {
  const ds = e.currentTarget.dataset;
  const deviceId = ds.deviceId;
  const name = ds.name;
  wx.createBLEConnection({
    deviceId,
    success: () => {
      this.setData({ isConnected: true, name, deviceId });
      //定时器延时显示
      setTimeout(() => {
        wx.showToast({ title: "连接蓝牙设备成功", icon: "success" });
      }, 500);
      this.getBLEDeviceServices(deviceId); // 获取蓝牙服务
      
      // 连接成功后跳转到新页面
      // wx.navigateTo({
      //   url: '/pages/device/bluetooth/bluetooth',
      // });
    },
    fail: e => {
      console.log("连接失败", e.errMsg);
      wx.showToast({ title: "连接失败,错误信息: " + e.errMsg, icon: "error" });
    },
  });
  this.stopBluetoothDevicesDiscovery(); // 停止搜索设备
},

  
  // 断开蓝牙连接
  closeBLEConnection() {
    console.log("断开与蓝牙低功耗设备的连接");
    wx.showToast({ title: "已断开和蓝牙设备的连接", icon: "none" });
    wx.closeBLEConnection({ deviceId: this.data.deviceId });
    this.setData({ isConnected: false, chs: [], canWrite: false });
  },
  
  // 获取蓝牙设备服务
  getBLEDeviceServices(deviceId: any) {
    wx.getBLEDeviceServices({
      deviceId,
      success: res => {
        for (let i = 0; i < res.services.length; i++) {
          if (res.services[i].isPrimary) {
            this.getBLEDeviceCharacteristics(deviceId, res.services[i].uuid);
            return;
          }
        }
      },
    });
  },
  
  // 获取蓝牙服务特征
  getBLEDeviceCharacteristics(deviceId: any, serviceId: string) {
    wx.getBLEDeviceCharacteristics({
      deviceId,
      serviceId,
      success: res => {
        console.log("获取蓝牙低功耗设备某个服务中所有特征：getBLEDeviceCharacteristics");

        for (let i = 0; i < res.characteristics.length; i++) {
          let item = res.characteristics[i];
          if (item.properties.read) {
            wx.readBLECharacteristicValue({ deviceId, serviceId, characteristicId: item.uuid });
          }
          if (item.properties.write) {
            this.setData({ canWrite: true });
            this._deviceId = deviceId;
            this._serviceId = serviceId;
            this._characteristicId = item.uuid;
          }
          if (item.properties.notify || item.properties.indicate) {
            wx.notifyBLECharacteristicValueChange({
              deviceId,
              serviceId,
              characteristicId: item.uuid,
              state: true,
              success(res) {
                console.log("notifyBLECharacteristicValueChange success", res);
              },
            });
          }
        }
      },
      fail(res) {
        console.error("getBLEDeviceCharacteristics", res);
      },
    });

    // 接收蓝牙特征值变化事件
    wx.onBLECharacteristicValueChange(characteristic => {
      console.log("收到原始的数据", characteristic, characteristic.value);
      const receivedData = ab2str(characteristic.value); // 转换为字符串
      console.log("接收到的数据", receivedData);
      
      // 解析数据并存储
      this.parseReceivedData(receivedData);
    });
  },
  
  // 发送数据到蓝牙设备
  writeBLECharacteristicValue(jsonStr: any) {
    let arrayBufferValue = str2ab(jsonStr); // 转换为 ArrayBuffer
    console.log("发送数据给蓝牙", "原始字符串", jsonStr, "转换arrayBuffer", arrayBufferValue);

    wx.writeBLECharacteristicValue({
      deviceId: this._deviceId,
      serviceId: this._serviceId,
      characteristicId: this._characteristicId,
      value: arrayBufferValue,
      success(res) {
        console.log("消息发送成功", res.errMsg);
        wx.showToast({ title: "消息发送成功", icon: "none" });
      },
      fail(e) {
        console.log("发送消息失败", e);
        wx.showToast({ title: "发送消息失败,错误信息: " + e.errMsg, icon: "none" });
      },
    });
  },
  
  // 关闭蓝牙模块
  closeBluetoothAdapter() {
    console.log("关闭蓝牙模块");
    wx.closeBluetoothAdapter();
    this._discoveryStarted = false;
  },

  // 解析通过蓝牙接收到的数据
  parseReceivedData(data: string) {
    
    // 将接收到的数据按照换行符分割为多行
    const lines = data.split('\n');
    
    // 遍历每一行，解析并更新相应的数据字段
    lines.forEach((line: { split: (arg0: string) => [any, any]; }) => {
      // 将每一行数据按照冒号分割为键和值
      const [key, value] = line.split(':');
      
      // 根据键的不同，更新相应的数据字段
      switch (key) {
        case 'T':
          app.globalData.temperature = value;
          break;
        case 'Tim':
          app.globalData.treatmentTime = value;
          break;
        case 'V':
          app.globalData.voltage = value;
          break;
        case 'PWM':
          app.globalData.pwm = value;
          break;
        case 'E':
          app.globalData.fieldIntensity = value;
          break;
        default:
          console.log("未知数据格式", line);
      }
    });

  },

  ChooseImageTap() {
    let _this = this;
    wx.showActionSheet({
      itemList: ['从相册中选择', '拍一张'],
      itemColor: "#f7982a",
      success(res){
        if (!res.cancel) {
          if (res.tapIndex == 0) {
            // 从相册中选择
            _this.ChooseImage('album')
          } else if (res.tapIndex == 1) {
            // 使用相机
            _this.ChooseImage('camera')
          }
        }
      }
    })
  },

  // 选择图片方法
  ChooseImage(type:any) {
    wx.chooseImage({
      count: this.data.imgMaxNumber, // 设置选择图片的数量，默认是9
      sizeType: ['original', 'compressed'], // 可以指定是原图还是压缩图，默认二者都有
      sourceType: [type], // 从相册选择
      success: (res) => {
        // 成功选择图片后的回调
        if (this.data.imgList.length != 0) {
          this.setData({
           imgList: this.data.imgList.concat(res.tempFilePaths) // 如果已有图片，添加新选中的图片
          
          });
          console.log(this.data.imgList);
        } else {
          this.setData({
            imgList: res.tempFilePaths // 如果没有图片，直接赋值
          });
          console.log(this.data.imgList);
        }
      }
    });
  },

  // 预览图片方法
  ViewImage(e: { currentTarget: { dataset: { url: any; }; }; }) {
    wx.previewImage({
      urls: this.data.imgList, // 要预览的图片链接列表
      current: e.currentTarget.dataset.url // 当前预览的图片链接
    });
  },

  // 删除图片方法
  DelImg(e: { currentTarget: { dataset: { index: number; }; }; }) {
    wx.showModal({
      title: '确定删除这张图片吗？', // 弹出确认删除对话框
      cancelText: '取消', // 取消按钮文本
      confirmText: '确定', // 确认按钮文本
      success: res => {
        if (res.confirm) {
          this.data.imgList.splice(e.currentTarget.dataset.index, 1); // 删除图片
          this.setData({
            imgList: this.data.imgList // 更新图片列表
          })
        }
      }
    })
  },

  SendImg(res:any,suffix:string)
  {
    const base64Image = res.data;
        // 将Base64编码的图片发送到服务器
    this.setData({
      imgCnt: this.data.imgCnt+1
    }); 
    client.emit('image', base64Image, this.data.imgCnt.toString()+suffix );

  },
  // 上传单张图片方法
  uploadPhoto(filePath: string) {
    // return wx.cloud.uploadFile({
    //   //cloudPath: `${Date.now()}-${Math.floor(Math.random(0, 1) * 10000000)}.png`, // 云存储路径，使用时间戳和随机数生成唯一文件名
    //   filePath // 本地文件路径
    // })
      let that = this;
      fs.readFile({
        filePath:filePath,
        encoding:'base64',//指定编码格式为 Base64
        success(res:any)  {
          console.log(filePath);
          that.SendImg(res,filePath.substring(filePath.length-4));
        },
        fail(error){
          console.log(filePath);
          console.error('读取图片文件失败:',error);
        }
      })
    },
  

  // 上传所有图片方法
  uploadImgs() {
    wx.showLoading({
      title: '上传中' // 显示上传中提示
    })
    const uploadTask = this.data.imgList.map(item => this.uploadPhoto(item)) // 为每张图片创建上传任务
    
    Promise.all(uploadTask).then(result => {
      console.log("上传结果", result) // 打印上传结果
      
      // let resultImageUrls = [];
      // for (const file of result) {
      //   resultImageUrls.push(file.fileID); // 获取上传后的文件ID
      // }
       
      wx.hideLoading(); // 隐藏加载提示
      wx.showToast({
        title: '上传图片成功', // 显示成功提示
        icon: 'success'
      })
    }).catch(() => {
      wx.hideLoading() // 隐藏加载提示
      wx.showToast({
        title: '上传图片错误', // 显示错误提示
        icon: 'error'
      })
    })
  },

  
  onLoad() {
    // 初始化富文本内容
    this.updateRichText();
  
    client.on('connnet_success',(data:any)=>{
      console.log(data);
    })
    client.on('resdata',(data:any)=>{
      // console.log(JSON.parse(data));
      console.log(data);
    })
 
  },

  onShow() {
    // 页面显示时启动定时器
    this.timer = setInterval(() => {
      this.updateRichText();
    }, 1000); // 每秒执行一次
  },

  onHide() {
    // 页面隐藏时清除定时器
    clearInterval(this.timer);
  },

  onUnload() {
    // 页面卸载时清除定时器
    clearInterval(this.timer);
  },
  // 
});

