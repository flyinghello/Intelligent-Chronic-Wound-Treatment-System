// 访问模型服务
const axios = require("./axios");

const app_id = '67297590' //appid
const secret_key = 'NQsLMmjQS7wrhcjvZBClz84hvH0eMiDT' //secret_key
const api_key = '1rnPxIPF8op0tQ9EmWaccf1v' //api_key
 
// 获取 access_token
function getAccessToken() {
    return new Promise((resolve:any, reject:any) => {
        axios({
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
        .then((response:any) => {
            // 在 Promise 成功时返回 access_token
            resolve(response.data.access_token);
        })
        .catch((error:any) => {
            // 在 Promise 失败时返回错误
            reject(error);
        });
    });
}
function Yi34BChat(contentValue:any,access_token:any){
    return new Promise(async (resolve, reject) => {
        try {
            const res = await axios({
                method: 'POST',
                url: 'https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/yi_34b_chat',
                headers: {
                    'Content-Type': 'application/json',
                },
                params: {
                    access_token: access_token,
                },
                data: {
                    messages: [{
                        role: 'user',
                        content: contentValue,
                    }],
                },
            });
            console.log(':', res.data.result);
            resolve(res.data.result);
        } catch (error:any) {
            console.error('Error:', error.message);
            reject(error);
        }
    });
    
}
 
async function getWXApi(contentValue:any) {
    try {
        const access_token = await getAccessToken();
        console.log('拿到token', access_token);
        const res=await Yi34BChat(contentValue,access_token)
    } catch (error:any) {
        console.error('Main Error:', error.message);
    }
    
}
// getWXApi("你过的还好吗")调用方法
  // 导出 initUrl 函数
module.exports = getWXApi;