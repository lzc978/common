// 前端请求
// 开灯函数，发起请求 GET /open
function open() {
    let oReq = new XMLHttpRequest();
    oReq.open("GET", "/open");
    oReq.send();
}

// 关灯函数，发起请求 GET /close
function close() {
    let oReq = new XMLHttpRequest();
    oReq.open("GET", "/close");
    oReq.send();
}

// 为按钮添加事件
document.getElementById("open").addEventListener("click",open)
document.getElementById("close").addEventListener("click",close)

// 获取数据函数，发起请求 GET /data
function getData() {
    let oReq = new XMLHttpRequest();
    oReq.open("GET", "/data");
    // 取得数据,并渲染到网页上
    oReq.onload = function callback() {
        let result = oReq.response;
        let obj = JSON.parse(result);
        document.getElementById("equipment-addr").textContent = obj.addr
        document.getElementById("equipment-data").textContent = obj.data

    }
    oReq.send();
}
//HTTP 轮询：每一秒拿一次数据。
setInterval(getData,1000)
