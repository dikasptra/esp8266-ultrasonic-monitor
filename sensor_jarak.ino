#define BLYNK_TEMPLATE_ID "########"
#define BLYNK_TEMPLATE_NAME "#####"
#define BLYNK_AUTH_TOKEN "#################"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

int trig_sensor_jarak = 12; 
int echo_sensor_jarak = 14;
int buzzer_pin = 2; 
int led_pin = 5;

char auth[] = "#############";

char ssid[] = "#######"; 
char pass[] = "########";

BlynkTimer timer;

void setup()
{
  Serial.begin(9600);
  pinMode(trig_sensor_jarak, OUTPUT);
  pinMode(echo_sensor_jarak, INPUT);
  pinMode(buzzer_pin, OUTPUT); 
  pinMode(led_pin, OUTPUT); 

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, sendSensor); 
}

void loop()
{
  Blynk.run();
  timer.run();
}

void sendSensor() {
    long duration, distance;
    
    digitalWrite(trig_sensor_jarak, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trig_sensor_jarak, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_sensor_jarak, LOW);
    
    duration = pulseIn(echo_sensor_jarak, HIGH);
    
    distance = duration * 0.034 / 2;
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    Blynk.virtualWrite(V14, distance);

     if (distance < 10) {
        digitalWrite(buzzer_pin, HIGH);
        digitalWrite(led_pin, HIGH);   
        Blynk.logEvent("notif_sensor");
    } else {
        digitalWrite(buzzer_pin, LOW);
        digitalWrite(led_pin, LOW);   
    }
} 
