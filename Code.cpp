#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Replace with your network credentials
const char* ssid = "Jay Smart IoT";
const char* password = "JayXGamer71";

// Initialize Telegram BOT
#define BOTtoken "2047395346:AAEWftZSS1UEvcbyDl1xglV1Z8mCtUplT4s"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "352271612"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 19;
const int echoPin = 18;

float duration, distance;

int pirSensor1 = 2;
int pirSensor2 = 4;

int buzzer = 5;

void setup() 
{
  Serial.begin(115200);

  //PIR Motion Sensor
  pinMode(pirSensor1,INPUT);
  pinMode(pirSensor2,INPUT);

  //Buzzer
  pinMode(buzzer,OUTPUT);

  //Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Address 0x3D for 128x64
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Bot started up");
  display.display(); 
}

void loop() 
{
  if(digitalRead(pirSensor1) == HIGH)
  {
    bot.sendMessage(CHAT_ID, "Motion detected at the Car Pouch!!", "");
    Serial.println("Motion Detected at the Car Pouch");
    digitalWrite(buzzer,HIGH); //Buzzer Turn On
   
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Motion Detected at   the Car Pouch");
    display.display();

    delay(5000);
    digitalWrite(buzzer,LOW); //Buzzer Turn Off 
  }

  if(digitalRead(pirSensor2) == HIGH)
  {
    bot.sendMessage(CHAT_ID, "Motion detected at the Garage!!", "");
    Serial.println("Motion Detected at the Garage");
    digitalWrite(buzzer,HIGH); //Buzzer Turn On

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Motion Detected at   the Garage");
    display.display();

    delay(5000);
    digitalWrite(buzzer,LOW); //Buzzer Turn Off
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

  if(distance < 100.5)
  {
    bot.sendMessage(CHAT_ID, "Someone is Infornt Of your Door!!", "");
    Serial.println("Someone is Infront Of your Door");
    digitalWrite(buzzer,HIGH); //Buzzer Turn On

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Someone is Infront Of your Door");
    display.display();

    delay(5000);
    digitalWrite(buzzer,LOW); //Buzzer Turn Off
  }
}