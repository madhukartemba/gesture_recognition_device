#define ESP32_RTOS  // Uncomment this line if you want to use the code with freertos only on the ESP32
// Has to be done before including "OTA.h"

#include "OTA.h"
#include <credentials.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremote.h>
#include "model.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


Eloquent::ML::Port::RandomForest classifier;

#define NUM_SAMPLES 150
#define NUM_AXES 6

#define TRUNCATE 20
#define ACCEL_THRESHOLD 3

#define BUZZER D8
#define BUTTON1 D3
#define BATT A0

Adafruit_MPU6050 mpu ;

float ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0;

float baseline[NUM_AXES];
float features[NUM_SAMPLES * NUM_AXES];


//GENERAL VARIABLES
unsigned long maintime = millis();

//OLED VARIABLES
float batteryconst=420, battmultiplier=0.714;
bool updateoled = 1, oledactive = 1;
unsigned long oledtimer=0, screentime=2000; 

//FUNCTIONS
void oleddisplay(char a[], int x=0, int y=0, int fontsize=1,int pr = 0 ,int cl=0);
void oleddisplay(float a, int x=0, int y=0, int fontsize=1,int pr = 0 ,int cl=0);


void finaldisplay()
{
  if(updateoled)
  {
    updateoled = 0;
    oledactive = 1;
    oledtimer = millis();
    display.display();
  }
  
  if(oledactive && millis()-oledtimer>screentime)
  {
    display.clearDisplay();
    display.display();
    oledtimer = millis();
    oledactive = 0;
  }
}
void oleddisplay(char a[], int x, int y, int fontsize,int pr ,int cl)
{
  if(cl==1)
  {
    display.clearDisplay();
    
  }
  display.setTextSize(fontsize);
  display.setCursor(x, y);
  display.println(a);
  if(pr==1)
  {
    display.display();
  }
  
}

void oleddisplay(float a, int x, int y, int fontsize,int pr ,int cl)
{
  if(cl==1)
  {
    display.clearDisplay();
    
  }
  display.setTextSize(fontsize);
  display.setCursor(x, y);
  display.println(a);
  if(pr==1)
  {
    display.display();
  }
  
}

void batterypercent()
{
  int batteryper = analogRead(BATT);
  batteryper-=batteryconst;
  batteryper*=battmultiplier;
  
  if(batteryper>100)
  {
    batteryper=100;
  }
  
  if(batteryper<1)
  {
    oleddisplay("LOW", 110, 0);
    return;
    
  }
  char a[3];
  itoa(batteryper, a, 10);
  strcat(a, "%");
  
  if(strlen(a)>3)
  {
    oleddisplay(a, 104, 0);
    return;
  }
  if (strlen(a)==3)
  {
    oleddisplay(a, 110, 0);
    return;
     
  }
  if(strlen(a) == 2)
  {
    oleddisplay(a, 115, 0);
    return;
  }
  
}
void setupoled()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // Address 0x3C for most of these displays, if doesn't work try 0x3D 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                      // Don't proceed, loop forever
  } 
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);            // Draw white text
  display.clearDisplay();
  
}
void setupmpu()
{
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}


void buzz(int freq = 2000, int delt0 = 100, int numberofbeeps = 1, int delt1 = 50)
{
  int i = 0;
  while (i < numberofbeeps)
  {
    tone(BUZZER, freq);
    delay(delt0);
    noTone(BUZZER);
    if (numberofbeeps > 1)
    {
      delay(delt1);
    }
    i++;
  }
}

void classify() 
{
  Serial.print("Detected gesture: ");
  char* gest = (char*)classifier.predictLabel(features);
  Serial.println(gest);
  if(strcmp(gest, "noaction")==0)
  {
    return;
  }
  updateoled = 1;
  oleddisplay(gest,0,30);
  if(strcmp(gest, "swipeup")==0)
  {
    for(int i=0;i<10;i++)
    {
      IrSender.sendSony(0x1 & 0x1F, 0x12 & 0x7F, 2);
      delay(20);
    }
  }
  if(strcmp(gest, "swipedown")==0)
  {
    for(int i=0;i<10;i++)
    {
      IrSender.sendSony(0x1 & 0x1F, 0x13 & 0x7F, 2);
      delay(20);
    }
  }
  if(strcmp(gest, "tripletap")==0)
  {
    IrSender.sendSony(0x1 & 0x1F, 0x15 & 0x7F, 2);
  }
  if(strcmp(gest, "leftswipe")==0)
  {
    IrSender.sendSony(0x1 & 0x1F, 0x34 & 0x7F, 2);
    delay(20);
    IrSender.sendRC6((unsigned long long)0xC00020, 24);
  }
  if(strcmp(gest, "rightswipe")==0)
  {
    IrSender.sendSony(0x1 & 0x1F, 0x33 & 0x7F, 2);
    delay(20);
    IrSender.sendRC6((unsigned long long)0xC00021, 24);
  }
  if(strcmp(gest, "b")==0)
  {
    IrSender.sendSony(0x1 & 0x1F, 0x97 & 0x7F, 2);
    delay(20);
    IrSender.sendRC6((unsigned long long)0xC00083, 24);
  }
  if(strcmp(gest, "doubletap")==0)
  {
    IrSender.sendRC6((unsigned long long)0xC0000C, 24);
  }
  if(strcmp(gest, "x")==0)
  {
    IrSender.sendSony(0x1 & 0x1F, 0x14 & 0x7F, 2);
    delay(20);
    IrSender.sendRC6((unsigned long long)0xC0000D, 24);
  }
  if(strcmp(gest, "a")==0)
  {
    IrSender.sendSony(0x1 & 0x1F, 0x65 & 0x7F, 2);
    delay(20);
    IrSender.sendRC6((unsigned long long)0xC0005C, 24);
  }

  buzz(2500);
}

void printfeatures() 
{
  const uint16_t numFeatures = sizeof(features) / sizeof(float);

  for (int i = 0; i < numFeatures; i++) {
    Serial.print(features[i]);
    Serial.print(',');
  }
  Serial.println();
}

void recordIMU() 
{
  for (int i = 0; i < NUM_SAMPLES; i++) {
    imuread();

    ax = constrain(ax - baseline[0], -TRUNCATE, TRUNCATE);
    ay = constrain(ay - baseline[1], -TRUNCATE, TRUNCATE);
    az = constrain(az - baseline[2], -TRUNCATE, TRUNCATE);

    features[i * NUM_AXES + 0] = ax;
    features[i * NUM_AXES + 1] = ay;
    features[i * NUM_AXES + 2] = az;
    features[i * NUM_AXES + 3] = gx;
    features[i * NUM_AXES + 4] = gy;
    features[i * NUM_AXES + 5] = gz;

    delay(10);
  }
}

bool motionDetected()
{
  if((abs(ax) + abs(ay) + abs(az)) > ACCEL_THRESHOLD)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void calibrate()
{
//  int i = 0;
//  for (i = 0; i < 10; i++)
//  {
//    imuread();
//    delay(100);
//  }
  imuread();
  baseline[0] = ax;
  baseline[1] = ay;
  baseline[2] = az;
}


void imuread()
{
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;
  gx = g.gyro.x;
  gy = g.gyro.y;
  gz = g.gyro.z;
}



void setup() 
{
  Serial.begin(115200);
  Serial.println("Booting");

  setupOTA("NodeMCU Gesture Recognition", mySSID, myPASSWORD);

  // Your setup code
  pinMode(D8, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);

  digitalWrite(D4, HIGH);
  
  setupoled();
  setupmpu();
  IrSender.begin(D4);
  
}



void loop() {
  maintime = millis();
  
  #ifdef defined(ESP32_RTOS) && defined(ESP32)
  #else // If you do not use FreeRTOS, you have to regulary call the handle method.
    ArduinoOTA.handle();
  #endif

  
  finaldisplay();
  imuread();

  ax = constrain(ax - baseline[0], -TRUNCATE, TRUNCATE);
  ay = constrain(ay - baseline[1], -TRUNCATE, TRUNCATE);
  az = constrain(az - baseline[2], -TRUNCATE, TRUNCATE);
  //Serial.println(digitalRead(BUTTON1));
  if (!motionDetected())
  {
    delay(10);
    return;
  }
  
  recordIMU();
  //printfeatures();
  display.clearDisplay();
  classify();
  calibrate();
  batterypercent();

}
