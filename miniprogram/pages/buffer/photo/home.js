// pages/photo/photo.js
const QQMapWX = require('../../libs/qqmap-wx-jssdk.js');
const util = require('../../../utils/util.js');
var qqmapsdk;
const app = getApp();

Page({

  /**
   * 页面的初始数据
   */
  data: {
    url: app.globalData.api.business_api,
    tid: null,
    type: 'reply',
    files: [],
    photo: {
      _id: util.guid()
    }
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.data.tid = options.id;
    this.data.type = options.type;
    this.data.photo.user = app.globalData.user;
    this.setData({
      selectFile: this.selectFile.bind(this),
      uploadFile: this.uploadFile.bind(this)
    });
    qqmapsdk = new QQMapWX({
      key: '7XHBZ-OC7CW-DVNRE-RJOMF-QSD23-JYBA4'
    });
    wx.getLocation({
      type: 'gcj02', //返回可以用于wx.openLocation的经纬度
      success: (res) => {
        this.data.photo.lng = res.longitude;
        this.data.photo.lat = res.latitude;
        qqmapsdk.reverseGeocoder({
          location: {
            latitude: res.latitude,
            longitude: res.longitude
          },
          success:  (res) => {
            console.log(res);
            this.data.photo.address = res.result.address;
            this.setData({
              photo: this.data.photo
            });
          },
          fail: function (error) {
            console.error(error);
          },
          complete: function (res) {
            console.log(res);
          }
        });
      }
    });
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    this.data.photo._id = util.guid();
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  },
  
  previewImage(e) {
    const current = e.target.dataset.src;
    const photo = e.target.dataset.photo;
    wx.previewImage({
      current: current,
      urls: photo.photos.map(photo => this.data.url + '/images/' + photo)
    })
  },

  selectFile(files) {
    console.log('files', files)
    // 返回false可以阻止某次文件上传
  },

  uploadFile(files) {
    console.log('upload files', files)
    const paths = files.tempFilePaths;
    const promises = [];

    paths.forEach(path => {
      promises.push(new Promise((resolve, reject) => {
        wx.uploadFile({
          url: app.globalData.api.business_api + '/upload/image', //仅为示例，非真实的接口地址
          filePath: path,
          name: 'file',
          success: (res) => {
            const data = JSON.parse(res.data);
            this.data.photo.photos = this.data.photo.photos || [];
            this.data.photo.photos.push(data.paths[0].auto_name);
            // this.setData({
            //   photo: this.data.photo
            // });
            resolve(this.data.url + '/images/' + data.paths[0].auto_name);
          }
        });
      }));
    });
    return Promise.all(promises).then(results => {
      console.log(results);
      // Promise的callback里面必须resolve({urls})表示成功，否则表示失败
      return { urls: results };
    });
  },

  uploadError(e) {
    console.log('upload error', e.detail)
  },

  uploadSuccess(e) {
    console.log('upload success', e.detail)
  },

  bindInputChange(e) {
    // 取出定义的变量名
    let name = e.currentTarget.dataset.modal;

    // 取出实时的变量值
    let value = e.detail.value;

    // 设置这个键值对的键和值
    this.data.photo[name] = value;

    // 刷新数据
    this.setData({
      photo: this.data.photo
    });
  },

  submit() {
    wx.showLoading({
      title: "正在提交...",
      mask: true
    });
    wx.request({
      url: app.globalData.api.business_api + '/tasks/mini/' + this.data.tid + '/' + this.data.type + '/photo/update',
      method: 'POST',
      data: {
        record: this.data.photo
      },
      success: (result) => {
        if (result.data.result) {
          wx.hideLoading();
          wx.showToast({
            title: '提交成功'
          });
          wx.navigateBack({
            delta: 0,
          })
        }
      }
    })
  }
})