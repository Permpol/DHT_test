#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SimpleTimer.h>
#define DHTPIN D4 // กำหนดขาให้กับอุปกรณ์ตรวจสอบความชื้น DHT11
#define DHTTYPE DHT11
//////////////////////////////////////////จุดที่เพิ่ม

int setTemp;
int setHumid;

BLYNK_WRITE(V4) //temperature slider in app on pin V22
{
setTemp = param.asInt();
}
BLYNK_WRITE(V3) //temperature slider in app on pin V23
{
setHumid = param.asInt();
}

//////////////////////////////////////////

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

//* **BLYNK TOKEN** //
char auth[] = "XXXXXXXXXXXXXXXX";
char ssid[] = "AndroidAP";
char pass[] = "123654789a";


BLYNK_CONNECTED() {
Blynk.syncAll();
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
Serial.begin(115200);




pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
pinMode(D1, OUTPUT); // ***ควบคุมอุณหภูมิ*** ///
digitalWrite(D1, HIGH);

dht.begin();

timer.setInterval(1000L, sendUptime);

}

void sendUptime()
 {
 // *****ชุดคำสั่งการทำงานของอุณหภูมิ***** *//
 Blynk.virtualWrite(V5, millis() / 1000);
 sensors_event_t event;
 dht.temperature().getEvent(&event);
 if (!isnan(event.temperature)) //ตรงนี้เป็นการกำหนดเงื่อนไข >=, <= , ==  ใช่ไหมครับ
   {
 Blynk.virtualWrite(V1, event.temperature); //หรือผมต้องมากำหนด เงื่อนไข >=, <= , == ตรงนีครับ
  }
 dht.humidity().getEvent(&event);
 if (!isnan(event.relative_humidity)) {
 Blynk.virtualWrite(V2, event.relative_humidity);
 
 }
 }
void loop()
{
//if(Blynk.connected()) {
Blynk.run();
timer.run();

}
