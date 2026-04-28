// utils/chat.js
import axios from '../utils/axios.js';
import mpAdapter from '../utils/axios-adapter.js';

axios.defaults.adapter = mpAdapter;

const api_key = '1rnPxIPF8op0tQ9EmWaccf1v';
const secret_key = 'NQsLMmjQS7wrhcjvZBClz84hvH0eMiDT';
const app_id = '67297590';

export { 
	sendMessage, 
	addMessage 
};

async function getAccessToken() {
  try {
    const response = await axios({
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
    });
    return response.data.access_token;
  } catch (error) {
    console.error('获取 access_token 失败', error);
    throw error;
  }
}

async function getChatResponse(contentValue, accessToken) {
  try {
    const response = await axios({
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
    });
    return response.data.result;
  } catch (error) {
    console.error('获取聊天响应失败', error);
    throw error;
  }
}

async function fetchBotResponse(contentValue) {
  try {
    const accessToken = await getAccessToken();
    console.log('拿到token', accessToken);
    const response = await getChatResponse(contentValue, accessToken);
    return response;
  } catch (error) {
    console.error('Main Error:', error.message);
    throw error;
  }
}


function addMessage(messages, role, content) {
  const newMessage = { role, content };
  return [...messages, newMessage];
}


async function sendMessage(page, inputValue) {
  if (!inputValue) return;

  // 添加用户消息到消息列表
  page.setData({
    messages: addMessage(page.data.messages, 'user', inputValue),
    inputValue: ''
  });

  try {
    const response = await fetchBotResponse(inputValue);
    page.setData({
      messages: addMessage(page.data.messages, 'bot', response)
    });
  } catch (error) {
    console.error('发送消息失败', error);
    wx.showToast({
      title: '发送消息失败',
      icon: 'none'
    });
  }
}

