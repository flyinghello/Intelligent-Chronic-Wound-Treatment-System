// app.ts
App<IAppOption>({
  globalData: {
    data1: null, // 场强
    data2: null, // 电压值
    data3: null, // 温度值
    data4: null, // 治疗时间
    data5: null, // PWM值
  },
  onLaunch() {
    // 展示本地存储能力
    const logs = wx.getStorageSync('logs') || []
    logs.unshift(Date.now())
    wx.setStorageSync('logs', logs)

    // 登录
    wx.login({
      success: res => {
        console.log(res.code)
        // 发送 res.code 到后台换取 openId, sessionKey, unionId
      },
    })
  },
})

