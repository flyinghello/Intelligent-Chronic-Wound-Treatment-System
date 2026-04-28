
// import { xxx } from './util';

// 导出所有的工具函数
export {
  formatTime,
  formatNumber,
  formattime,
  regexConfig,
  trim,
  isNumber,
  isObj,
  emptyFun
};

// 格式化时间，将日期对象转换为字符串格式
const formatTime = (date: Date) => {
  const year = date.getFullYear();
  const month = date.getMonth() + 1;
  const day = date.getDate();
  const hour = date.getHours();
  const minute = date.getMinutes();
  const second = date.getSeconds();

  return (
    [year, month, day].map(formatNumber).join('/') +
    ' ' +
    [hour, minute, second].map(formatNumber).join(':')
  );
};

// 格式化数字，将单个数字转换为两位数的字符串
const formatNumber = (n: number) => {
  const s = n.toString();
  return s[1] ? s : '0' + s;
};

// 根据给定的格式格式化时间戳
const formattime = (number: number, format: string) => {
  if (number != null) {
    const formateArr = ['Y', 'M', 'D', 'h', 'm', 's'];
    const returnArr = [];
    const date = new Date(number);
    returnArr.push(date.getFullYear());
    returnArr.push(formatNumber(date.getMonth() + 1));
    returnArr.push(formatNumber(date.getDate()));
    returnArr.push(formatNumber(date.getHours()));
    returnArr.push(formatNumber(date.getMinutes()));
    returnArr.push(formatNumber(date.getSeconds()));
    for (let i = 0; i < returnArr.length; i++) {
      format = format.replace(formateArr[i], returnArr[i].toString());
    }
    return format.replace(/\//g, '-');
  } else {
    return number;
  }
};

// 返回一个包含正则表达式配置的对象
const regexConfig = () => {
  return {
    phone: /^1(3|4|5|7|8)\d{9}$/ // 手机号码匹配规则
  };
};

// 去除字符串两端的空白字符
const trim = (str: string) => {
  return str.replace(/(^\s*)|(\s*$)/g, '');
};

// 检查字符串是否为数字
const isNumber = (str: string) => {
  const n = Number(str);
  return !isNaN(n);
};

// 检查传入的参数是否为对象
const isObj = (obj: any) => {
  return typeof obj === 'object' && obj !== null;
};

// 检查传入的参数是否为空值
const emptyFun = (obj: any) => {
  return obj === '' || obj === null || obj === undefined || obj === 'null' || obj === 'undefined';
};
