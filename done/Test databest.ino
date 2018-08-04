// Code By ArduinoALL
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "IOT01"; // แก้ ssid
const char* password = "0123456789"; // แก้ password


// Config MQTT Server
const char * topic = "/server"; // topic ชื่อ /server
#define mqtt_server "m14.cloudmqtt.com" // server
#define mqtt_port 14498   // เลข port
#define mqtt_user "wfhrwbfi" // user
#define mqtt_password "qMQ_axLbWVrd" // password


#define LED_PIN D4

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // เชื่อมต่อ network
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // จบการเชื่อมต่อ network

  client.setServer(mqtt_server, mqtt_port); // เชื่อมต่อ mqtt server
}
String Switch;
void loop() {
  if (!client.connected()) {
    Serial.print("MQTT connecting...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) { // ถ้าเชื่อมต่อ mqtt สำเร็จ
      Serial.println("connected");
    }
    // ในกรณีเชื่อมต่อ mqtt ไม่สำเร็จ
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // หน่วงเวลา 5 วินาที แล้วลองใหม่
      return;
    }
  }
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  Switch = "LED ON";
  Publish();
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  Switch = "LED OFF";
  Publish();
  //  if (digitalRead(LED_PIN) == HIGH) { // ถ้า topic ส่งคำว่า on
  //    client.publish("/NodeMCU", "1"); // ส่งข้อความกลับไปที่ topic คือ ชื่ออุปกรณ์ที่ส่ง , ข้อความ
  //  } else if(digitalRead(LED_PIN) == LOW){
  //    client.publish("/NodeMCU", "0");
  //  }
}
void Publish() {
  char buff[10];
  Switch.toCharArray(buff, 10);
  client.publish(topic, buff); // ชื่อ topic ที่ต้องการติดตาม
}
