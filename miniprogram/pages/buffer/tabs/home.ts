const app = getApp();
const getWXApi = require("../../utils/wxyychat");

// pages/sockettest/sockettest.ts
const io = require('../../utils/weapp.socket.io.js')
import axios from '../../utils/axios.js'
import mpAdapter from '../../utils/axios-adapter.js'
axios.defaults.adapter = mpAdapter
const app_id = '67297590' //appid
const secret_key = 'NQsLMmjQS7wrhcjvZBClz84hvH0eMiDT' //secret_key
const api_key = '1rnPxIPF8op0tQ9EmWaccf1v' //api_key
// let socket=io("http://localhost:8000")

Page({
  onShareAppMessage() {
    return {
      title: 'tabs',
      path: 'page/weui/example/tabs/tabs'
    }
  },
  data: {
    tabs: [],
    activeTab: 0,

    messages: [],
    inputValue: '', //输入框的内容
  },

  onLoad() {
    const tabs = [
      {
        title: '发生装置',
        img: 'http://134.175.127.33/1.jpg',
      },
      {
        title: '评估模型',
        img: 'http://134.175.127.33/2.jpg',  
      },    
      {
        title: '数据传输',
        img: 'http://134.175.127.33/3.jpg',
      },
      {
        title: '客户端',
        img: 'http://134.175.127.33/4.jpg',
      },
      {
        title: '传感器',
        img: 'http://134.175.127.33/5.jpg',
      },
    ]
    this.setData({ tabs });

  },

  onTabClick(e) {
    const index = e.detail.index
    this.setData({ 
      activeTab: index 
    })
  },

  onChange(e) {
    const index = e.detail.index
    this.setData({ 
      activeTab: index 
    })
  },

  handleClick(e) {
    wx.navigateTo({
      url: './webview',
    })
  }
})

