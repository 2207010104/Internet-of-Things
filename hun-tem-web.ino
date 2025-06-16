#include <DHT.h>//调用dht11驱动库
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DHTPIN D4 //说明数据接口为8266开发板的D4口，也可以写为#define DHTPIN 2既8266芯片的IO口2
#define DHTTYPE DHT11//说明使用的模块是DHT11
DHT dht(DHTPIN,DHTTYPE);//DHT11初始化
//定义浮点类型变量保存测量值
float Temperature;
float Humidity;
//定义WIFI信息
const char* ssid = "find5";  // Enter SSID here
const char* password = "88888888";  //Enter Password here

ESP8266WebServer server(80);
            
void setup() {    
  pinMode(D4, INPUT);
  Serial.begin(115200);
  delay(100);
  dht.begin();              
  Serial.println("Connecting to ");
  Serial.println(ssid);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  
  server.handleClient();
  
}

void handle_OnConnect() {

 Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head> <meta name=\"viewport\" content=\"width=device-width,  initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr +="<meta charset=\"UTF-8\">\n";
  ptr +="<title>温湿计</title>\n";
  ptr +="<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
  ptr +="body{margin-top: 50px;}\n";
  ptr +="h1 {margin: 50px auto 30px;}\n";
  ptr +=" .wd {margin: 50px auto 30px;width: auto;color: #f39c12}\n";
  ptr +=" .wd1 {margin: 50px auto 30px;width: auto;color: #3498db}\n";
  ptr +=".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  ptr +=".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n";
  ptr +=".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n";
  ptr +=".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  ptr +=".data{padding: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  
   ptr +="<div id=\"webpage\">\n";
   
   ptr +="<h1>温湿度检测系统</h1>\n";
   ptr +="<div class=\"data\">\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side temperature-text\">温度：</div>\n";
   ptr +="<div class=\"side-by-side temperature\">";
   ptr +=(int)Temperaturestat;
   ptr +="<span class=\"superscript\">°C</span></div>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"data\">\n";
    ptr +="</div>\n";
   ptr +="<div class=\"side-by-side humidity-text\">湿度：</div>\n";
   ptr +="<div class=\"side-by-side humidity\">";
  ptr +=(int)Humiditystat;
   ptr +="<span class=\"superscript\">%</span></div>\n";
   ptr +="</div>\n";

   
   ptr +="</div>\n";
   ptr +="</body>\n";
   ptr +="</html>\n";
   return ptr;
   }
