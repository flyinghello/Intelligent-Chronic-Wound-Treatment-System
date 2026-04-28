// socketioUploader.js
const io = require('../../utils/weapp.socket.io');
const fs = wx.getFileSystemManager();

const client = io.connect("http://134.175.127.33:4000");

function connectToServer() {
  client.on('connnet_success', (data) => {
    console.log(data);
  });

  client.on('resdata', (data) => {
    console.log(data);
  });
}

function sendImage(base64Image, suffix) {
  client.emit('image', base64Image, suffix);
}

function uploadPhoto(filePath) {
  return new Promise((resolve, reject) => {
    fs.readFile({
      filePath: filePath,
      encoding: 'base64',
      success(res) {
        const base64Image = res.data;
        const suffix = filePath.substring(filePath.length - 4);
        sendImage(base64Image, suffix);
        resolve();
      },
      fail(error) {
        console.error('读取图片文件失败:', error);
        reject(error);
      }
    });
  });
}

function uploadImages(imgList) {
  wx.showLoading({ title: '上传中' });

  const uploadTasks = imgList.map(item => uploadPhoto(item));

  return Promise.all(uploadTasks)
    .then(() => {
      wx.hideLoading();
      wx.showToast({ title: '上传图片成功', icon: 'success' });
    })
    .catch(() => {
      wx.hideLoading();
      wx.showToast({ title: '上传图片错误', icon: 'error' });
    });
}

module.exports = {
  connectToServer,
  uploadImages
};
