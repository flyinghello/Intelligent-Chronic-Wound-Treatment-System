const app = getApp();

Page({
  data: {
  

    // 富文本
    richTextNodes: [{ 
      name: 'div',
      attrs: { class: 'big-text' },
      children: [{ type: 'text', text: '这是一段初始的富文本内容' }]
    }],

    // 对话框和按钮
    showDialog: false,
    options: ['选项一', '选项二', '选项三'], 
    typeS: false,
    dialogTitle: ' ',
    dialogSubTitle: ' ',
    dialogDesc: ' ',
    dialogTips: ' ',

    buttons: [
      { type: 'default', className: '', text: '辅助操作', value: 0 },
      { type: 'primary', className: '', text: '主操作', value: 1 }
    ]
  },
  
  onLoad() {
    // 初始化富文本内容
    this.updateRichText();

    // 每秒更新一次时间并更新富文本内容
    setInterval(() => {
      this.updateRichText();
    }, 1000); // 每秒执行一次
  },

  // 富文本
  updateRichText() {
    const now = new Date();
    const hours = now.getHours().toString().padStart(2, '0');
    const minutes = now.getMinutes().toString().padStart(2, '0');
    const seconds = now.getSeconds().toString().padStart(2, '0');

    const timeText = `${hours}:${minutes}:${seconds}`;

    this.setData({
      richTextNodes: [{
        name: 'div',
        attrs: { class: 'big-text' },
        children: [{ type: 'text', text: 'TIME：' + timeText }]
      }]
    });
  },

  //按钮
  openTypeS(event: any) {
    const { title, subtitle, desc, tips } = event.currentTarget.dataset;
    this.setData({
      typeS: true,
      dialogTitle: title,
      dialogSubTitle: subtitle,
      dialogDesc: desc,
      dialogTips: tips
    });
  },

  buttontap(e: any) {
    console.log(e.detail);
  },
});

