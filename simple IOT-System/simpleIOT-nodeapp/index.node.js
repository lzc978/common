/**
 * node原生http web并发测试
 * 可以和golang原生net/http、io并发比较
 */
const fs = require('fs');
let http = require('http');
const net = require('net');
const HTTP_PORT = "8000";
const TCP_PORT = "9000"
const TIMEOUT = 60000;//tcp客户端超过60秒没发数据判为超时并断开连接
let tcpClient=null;//tcp客户端

// 创建http server，并传入回调函数:
const httpServer = http.createServer(function (request, response) {
  // 回调函数接收request和response对象,
  // 获得HTTP请求的method和url:
  console.log(request.method + ': ' + request.url);
  switch (request.url) {
    case "/":
      //访问首页
      response.writeHead(200, {'Content-Type': 'text/html; charset=utf8'});
      // 读取html文件并发送
      response.end(fs.readFileSync('./index.html'));
      break;
    case "/open":
      // 开灯命令
      openLed()
      response.end('succeed');
      break;
    case "/close":
      // 开灯命令
      closeLed()
      response.end('succeed');
      break;
    case "/data":
      // 获取数据
      let data = getData() || "无数据";

      let addr = "无连接";
      if(tcpClient && tcpClient.addr){
        addr = tcpClient.addr
      }
      
      // 将结果转换成字符串再发出去
      let result = JSON.stringify({addr:addr,data:data});
      response.end(result);
      break;
    default:
      response.writeHead(400);
      response.end();
      break;
  }
});

httpServer.listen(HTTP_PORT);
httpServer.on('error', onError);
httpServer.on('listening', onListening);

//Event listener for HTTP server "error" event.
function onError(error) {
    if (error.syscall !== 'listen') {
      throw error;
    }
  
    var bind = typeof port === 'string'
      ? 'Pipe ' + port
      : 'Port ' + port;
  
    // handle specific listen errors with friendly messages
    switch (error.code) {
      case 'EACCES':
        console.error(bind + ' requires elevated privileges');
        process.exit(1);
        break;
      case 'EADDRINUSE':
        console.error(bind + ' is already in use');
        process.exit(1);
        break;
      default:
        throw error;
    }
  }

//Event listener for HTTP server "listening" event.
function onListening() {
var addr = httpServer.address();
var bind = typeof addr === 'string'
    ? 'pipe ' + addr
    : 'port ' + addr.port;
console.log('http server Listening on ' + bind);
}

//创建TCP服务器
const tcpServer = net.createServer((socket)=>{
  //connect
  let addr = socket.address().address + ':' + socket.address().port
  console.log(addr," connect.")
  socket.addr = addr
  tcpClient = socket

  // recieve data
  socket.on("data",data=>{
    let str = addr+" receive: " + data.toString('ascii') + '\n'
    console.log(str)
    socket.lastValue = data.toString('ascii')
  })

  // close
  socket.on('close',()=>{
    console.log(addr,"close")
    tcpClient = null;
  })

  socket.on('error',(err)=>{
    console.log("error",err)
    tcpClient = null;
  })

  socket.setTimeout(TIMEOUT);
	// 超过一定时间 没接收到数据，就主动断开连接。
	socket.on('timeout', () => {
		console.log(socket.id,socket.addr,'socket timeout');
    socket.end();
    tcpClient = null;
	});
})

tcpServer.on("error",(err)=>{
  console.log(err)
  tcpClient = null;
})

tcpServer.listen({port: TCP_PORT,host: '0.0.0.0'}, () => {
  console.log('demo0.1 tcp server running on', tcpServer.address())
})

// http/mqtt控制物联网设备，mqtt在v0.2中，先局域网tcp/ip控制，socket
// 开灯
function openLed() {
  // 向TCP客户端发送1
  if(tcpClient){
    tcpClient.write('1', 'ascii')
  }
  else{
    console.log("openLed error:not tcpClient.")
  }
}

// 关灯
function closeLed() {
  // 向TCP客户端发送0
  if(tcpClient){
    tcpClient.write('0', 'ascii')
  }
  else{
    console.log("closeLed error:not tcpClient.")
  }
}

// 获取数据
function getData() {
  // 获取设备最新数据
  if(tcpClient){
    return tcpClient.lastValue
  }
  else{
    console.log("getData error:not tcpClient.")
  }
}
