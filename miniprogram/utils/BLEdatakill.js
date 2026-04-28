var app = getApp();  

function BLEdatakill( bluetooth_data ) { 
    var cs_data = JSON.parse(bluetooth_data)
    if(cs_data){
        console.log("指令回显",cs_data["cmd"]);
        if(cs_data.recognition == 1){app.globalData.csData.up += 1}
        else if(cs_data.recognition == 2){app.globalData.csData.down += 1}
        else if(cs_data.recognition == 3){app.globalData.csData.left += 1}
        else if(cs_data.recognition == 4){app.globalData.csData.right += 1}
        else if(cs_data.recognition == 5){app.globalData.csData.LeftFlexion += 1}
        else if(cs_data.recognition == 6){app.globalData.csData.RightFlexion += 1}
        else if(cs_data.recognition == 7){app.globalData.csData.LeftLoop += 1}
        else if(cs_data.recognition == 8){app.globalData.csData.RightLoop += 1}
        else if(cs_data.recognition == 0){app.globalData.csNativedata.push(cs_data.sensor)}
        else if(cs_data.cmd == "ATCustom+AccCali=1"){ 
            app.globalData.acc_success = 1 ,
            console.log(app.globalData.acc_success);
        }
        else if(cs_data.cmd == "ATCustom+AngleRefSet=1"){ 
            app.globalData.angle_success = 1,
            console.log(app.globalData.angle_success);
        }
        else if(cs_data.cmd == "ATCustom+SensorInit=1"){
            app.globalData.initial_success = 1
            console.log(app.globalData.initial_success);
        }
        else { 
            app.globalData.devices_bluetooth_group_data.push(cs_data[0]),
            app.globalData.devices_bluetooth_group_data.push(cs_data[1])
        } 
    }
    console.log('kill后',app.globalData.csData)
}
 
  module.exports = {
    BLEdatakill:BLEdatakill,
   
  }