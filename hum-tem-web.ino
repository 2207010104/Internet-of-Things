#define BLINKER_WIFI

#include <Blinker.h> //物联网平台
#include <DHT.h>

char auth[] = "58be2446c2e9";
char ssid[] = "air";
char pswd[] = "88888889";

BlinkerNumber HUMI("humi");
BlinkerNumber TEMP("temp");

#define DHTPIN D4

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

float humi_read = 0, temp_read = 0;

void heartbeat()
{
    HUMI.print(humi_read);
    TEMP.print(temp_read);
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    Blinker.begin(auth, ssid, pswd);
    Blinker.attachHeartbeat(heartbeat);
    dht.begin();
}

void loop()
{
    Blinker.run();

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
        BLINKER_LOG("Failed to read from DHT sensor!");
    }
    else
    {
        BLINKER_LOG("Humidity: ", h, " %");
        BLINKER_LOG("Temperature: ", t, " *C");
        humi_read = h;
        temp_read = t;
    }

    Blinker.delay(2000);
}
