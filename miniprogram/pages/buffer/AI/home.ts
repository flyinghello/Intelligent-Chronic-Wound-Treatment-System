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

    messages: [],
    inputValue: '', //输入框的内容
  },

  onLoad() {
  },


   
  //
  onInput(event) {
    this.setData({
      inputValue: event.detail.value
    });
  },
  
  async sendMessage() {
    const { inputValue, messages } = this.data;
    if (!inputValue) return;
  
    // 添加用户消息到消息列表
    this.addMessage('user', inputValue);
  
    try {
      const response = await this.fetchBotResponse(inputValue);
      this.addMessage('bot', response);
    } catch (error) {
      console.error('发送消息失败', error);
      wx.showToast({
        title: '发送消息失败',
        icon: 'none'
      });
    }
  },
  
  addMessage(role, content) {
    const { messages } = this.data;
    const newMessage = { role, content };
    this.setData({
      messages: [...messages, newMessage],
      inputValue: role === 'user' ? '' : this.data.inputValue
    });
  },
  
  async fetchBotResponse(contentValue) {
    try {
      const accessToken = await this.getAccessToken();
      console.log('拿到token', accessToken);
      const response = await this.getChatResponse(contentValue, accessToken);
      return response;
    } catch (error) {
      console.error('Main Error:', error.message);
      throw error;
    }
  },
  
  getAccessToken() {
    return axios({
      method: 'POST',
      url: 'https://aip.baidubce.com/oauth/2.0/token',
      headers: {
        'Content-Type': 'application/json',
      },
      params: {
        'grant_type': 'client_credentials',
        'client_id': api_key,
        'client_secret': secret_key,
      },
    })
    .then(response => response.data.access_token)
    .catch(error => {
      console.error('获取 access_token 失败', error);
      throw error;
    });
  },
  
  getChatResponse(contentValue, accessToken) {
    return axios({
      method: 'POST',
      url: 'https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/yi_34b_chat',
      headers: {
        'Content-Type': 'application/json',
      },
      params: {
        access_token: accessToken,
      },
      data: {
        messages: [{ role: 'user', content: contentValue }],
      },
    })
    .then(response => response.data.result)
    .catch(error => {
      console.error('获取聊天响应失败', error);
      throw error;
    });
  }
  
})

