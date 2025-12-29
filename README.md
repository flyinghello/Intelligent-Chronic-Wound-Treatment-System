# 慢性伤口智能治疗系统(Intelligent-Chronic-Wound-Treatment-System)
本项目是基于图像识别算法+物联网技术搭建的一个慢性伤口居家治疗系统，利用云端服务器作为数据处理中心，微信小程序为用户交互平台，PC端软件为医生处理交互平台，实现慢性伤口智能化远程居家治疗与监护一体化。  

## 系统结构：
### 整体架构
  本项目通过微信小程序调用手机摄像头采集伤口图像信息，利用nodejs+socket.io技术实现手机移动端与云端服务器的双向信息通信，将获取的图像信息上传至云端服务器，利用伤口评估模型和电极测距评估模型对图像进行评估，得到评估结果（伤口周长、伤口面积、两电极贴片距离、伤口红热等级）并在数据库中进行存储。再将评估结果返回微信小程序。微信小程序可通过调用手机蓝牙串口与电刺激设备实现实时交互，控制电刺激装置输出电场强度以及获取伤口温度信息，当温度超过阈值时，小程序会触发提示报警，提醒用户可能存在感染风险。此外，微信小程序还提供“文心一言”大语言模型接口，实现患者的深入沟通，缓解焦虑情绪。
<div align="center">
  <img width="362" height="210" alt="image" src="https://github.com/user-attachments/assets/3f7319b3-f275-41dd-a144-fc33d3fc1e4c" />
  <br/> 
  <img width="426" height="153" alt="image" src="https://github.com/user-attachments/assets/eeb208bb-ea11-4280-85b9-c8d796cddfa9" />
</div>

### 核心组成
1.硬件层：STM32F4 单片机（数据采集）+ ESP32（蓝牙通信），负责温度、电压数据采集与蓝牙数据传输。  
2.移动端：微信小程序，提供蓝牙连接、参数设置、图像上传、数据可视化功能。  
2.服务端：Node.js 云服务器，负责图像接收存储、Python AI 模型调用与结果返回。    
3.AI 算法层：基于 U-Net、Yolov8等模型对伤口进行分割，计算伤口周长与面积和红热等级。

## 优势
1.AI算法：通过利用YOLOv8识别参照物图案，将伤口颜色亮度从绝对评估转为相对评估，降低图像分割过程中受不同光线而影响最终评估结果，增强模型鲁棒性。  
2.信息交互：采用C/S架构模式，以Cloud Server为核心，实现信息交互、处理及存储的中心化管理。通过整合ME-DE-PC端的数据，形成高效、便捷的慢性病管理平台。

## 适用场景
适用于糖尿病足溃疡、静脉性腿部溃疡及压力性溃疡等因真皮细胞修复障碍导致的慢性伤口患者居家护理

## 实验结果
<div align="center">
<img width="586" height="513" alt="image" src="https://github.com/user-attachments/assets/39cc5a7e-faf4-4020-934f-b669d1c8c484" />
</div>

## 目录结构
```text
伤口识别与监测系统/
├── Equipment/
│   ├── STM32/                # STM32核心代码
│   │   ├── main.c            # 主函数（初始化+逻辑控制）
│   │   ├── serial.c          # 串口通信配置
│   │   ├── oled.c            # OLED显示驱动
│   │   ├── pwm.c             # PWM驱动配置
│   │   ├── key.c             # 按键输入处理
│   │   └── led.c             # LED指示控制
│   └── ESP32/                # ESP32蓝牙代码
│       └── ble_server.ino    # BLE服务配置与数据收发
├── Mobile/
│   ├── pages/
│   │   ├── device/           # 蓝牙+图像核心功能页
│   │   │   ├── device.ts     # 逻辑代码（蓝牙/上传/数据处理）
│   │   │   ├── device.wxml   # 页面结构
│   │   │   └── device.wxss   # 样式文件
│   │   ├── user/             # 用户中心页
│   │   └── home/             # 首页
│   ├── utils/
│   │   └── weapp.socket.io.js# Socket.io通信工具
│   ├── app.json              # 小程序全局配置
│   └── project.config.json   # 项目配置
├── PC/
│   ├── aHardware_control_system.ts  # Node.js服务端主程序
│   └── app.py                       # AI图像分割算法
│   ├── models/               # 模型定义
│   │   ├── Unet.py           # U-Net模型
│   │   ├── deeplab.py        # DeepLabv3+模型
│   │   └── SegNet.py         # SegNet模型
│   ├── dataset.py            # 数据预处理与增强
│   ├── utils.py              # 评估指标（IoU/Dice）
│   ├── train.py              # 模型训练脚本
│   ├── augment.py            # 图像增强工具
│   └── padding.py            # 图像补边处理
└── 辅助工具/
    └── save_result.py        # 分析结果统计
```
## requestment
