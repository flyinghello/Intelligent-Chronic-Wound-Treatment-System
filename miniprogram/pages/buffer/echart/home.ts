import * as echarts from "../../ec-canvas/echarts";


Page({
  data: {
    ec1: {
      onInit: initChart.bind(null, getOption1, 'bar')
    },
    ec2: {
      onInit: initChart.bind(null, getOption2, 'line')
    },
    // 在此处添加新的属性即可，之后再去配置一下新的getOption
    // https://echarts.apache.org/examples/zh/index.html
    lazyEc: {
      // 不能使用自动初始化，得使用手动初始化，这样才能控制延迟渲染
      lazyLoad: true 
    },
    chart:{},
    lazyComponent: {},// 该空对象用于获取组件
    type:'income',  //作用于按钮的类型

    chartOptionData:{
      income:[],
      outcome:[]
    }
  },

  onLoad: function (option) {
    // 获取到组件
    this.lazyComponent = this.selectComponent('#lazy-mychart-dom');

    // 模拟请求（延迟以等待数据接收，随后进行初始化）
    setTimeout(() => {
      //模拟数据接收，在这里更新到data里
      this.setData({
        chartOptionData:{
          income:[150, 230, 224, 218, 135, 147, 260],
          outcome:[1, 100, 11, 200, 100, 27, 300]
        }
      }),

      
      this.init()
    
    }, 3000);
  },

  //手动初始化
  init() {
    this.lazyComponent.init((canvas, width, height, dpr) => {
      const chart = echarts.init(canvas, null, {
        width: width,
        height: height,
        devicePixelRatio: dpr
      });

      let option = getOption(this.data.chartOptionData[this.data.type]);
      chart.setOption(option);
      this.chart = chart; // 将图表实例绑定到this上，方便在其他的函数中访问
      return chart;
    });
  },

  changeType(e){ //根据传的参数来切换效果
    this.setData({
      type: e.currentTarget.dataset.type
    })
    //根据传参索引，直接动态绑定到data里到时候要显示的值
    let option = getOption(this.data.chartOptionData[e.currentTarget.dataset.type]) 
    
    this.chart.setOption(option) 
  }
});

function initChart(getOptionFunc, seriesType, canvas, width, height, dpr) {
  const chart = echarts.init(canvas, null, {
    width: width,
    height: height,
    devicePixelRatio: dpr
  });

  canvas.setChart(chart);
  const option = getOptionFunc();
  option.series[0].type = seriesType;

  chart.setOption(option);
}

// 各个图表的样式配置

function getOption1() {
  return {
    xAxis: {
      type: 'category',
      data: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
    },
    yAxis: {
      type: 'value'
    },
    series: [{
      data: [120, 200, 150, 80, 70, 110, 130],
      type: 'bar'
    }]
  };
}

function getOption2() {
  return {
    xAxis: {
      type: 'category',
      data: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
    },
    yAxis: {
      type: 'value'
    },
    series: [{
      data: [120, 200, 150, 80, 70, 110, 130],
      type: 'bar'
    }]
  };
}

function getOption(data) {
  return {
    xAxis: {
      type: 'category',
      data: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
    },
    yAxis: {
      type: 'value'
    },
    series: [{
      data: data,
      type: 'line'
    }]
  };
  
}

