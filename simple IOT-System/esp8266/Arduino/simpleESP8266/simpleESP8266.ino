// #define LED_BUILTIN 2 //引脚
#include <ESP8266WiFi.h>

//必须修改：填写你的WIFI帐号密码
const char* ssid = "you-wifi";
const char* password = "you-wifi-password";

const char* host = "119.29.107.47";
const int port = 9002;//v0.1 tcp 使用 9002端口

const char* id = "1234abcd";
int tick = 1000;

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  //连接WIFI
  WiFi.begin(ssid, password);
  //设置读取socket数据时等待时间为100ms（默认值为1000ms，会显得硬件响应很慢）
  client.setTimeout(100);

  //等待WIFI连接成功
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connecting...");
    delay(500);
  }
  Serial.println("WiFi connected!.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connect(host, port))
  {
    Serial.println("host connected!");
    //发送第一条TCP数据，发送ID号
    client.print(id);
  }
  else
  {
    // TCP连接异常
    Serial.println("host connecting...");
    delay(500);
  }

  while (client.connected()) {
    // 接收到TCP数据
    if (client.available())
    {
      String line = client.readStringUntil('\n');
      if (line == "1") {
        Serial.println("command:open led.");
        digitalWrite(LED_BUILTIN, LOW);
        client.print("OK");
      }
      else if (line == "0") {
        Serial.println("command:close led.");
        digitalWrite(LED_BUILTIN, HIGH);
        client.print("OK");
      }
    }
    else {
      //若没收到TCP数据，每隔一段时间打印并发送tick值
      Serial.print("tem:");
      Serial.println(tick);
      client.print(tick);
      tick++;
      delay(1000);
    }
  }
}
