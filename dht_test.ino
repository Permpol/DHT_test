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

void setup()
{
Serial.begin(115200);




pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
pinMode(D1, OUTPUT); // ***ควบคุมอุณหภูมิ*** ///
digitalWrite(D1, HIGH);

dht.begin();
timer.setInterval(1000L, sendSensor);

}

BLYNK_CONNECTED() {
Blynk.syncAll();
}

void sendSensor()
{
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
   Blynk.virtualWrite(V1, t); //หรือผมต้องมากำหนด เงื่อนไข >=, <= , == ตรงนีครับ
 Blynk.virtualWrite(V2, h);

  Serial.println("Humidity: ");
  Serial.print(h + String("%"));
  Serial.println("Temperature: ");
  Serial.print(t + String("c"));

}


void loop()
{
//if(Blynk.connected()) {
Blynk.run();
timer.run();

}
