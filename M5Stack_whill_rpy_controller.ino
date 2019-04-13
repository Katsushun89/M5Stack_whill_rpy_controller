#include <M5Stack.h>
#include "utility/MPU9250.h"
#include "WHILL.h"
#include "imu.h"
#include "RPYController.h"

// Devices
MPU9250 IMU;
WHILL whill(&Serial2);
RPYController rpyController;

void setup()
{
  Serial.begin(115200);
  // Power ON Stabilizing...
  delay(500);
  M5.begin();
  Wire.begin();
  
  initIMU(&IMU);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
}

void loop() {
  
  if(M5.BtnA.wasPressed())
  {
    whill.setPower(true);  // Turn WHILL on
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("POWER:ON");
  }
  if(M5.BtnB.wasPressed())
  {
    whill.setPower(false);  // Turn WHILL off
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("POWER:OFF");
  }
  
  if(calcIMU(&IMU)){
      {
        Serial.print("Yaw, Pitch, Roll: ");
        Serial.print(IMU.yaw, 2);
        Serial.print(", ");
        Serial.print(IMU.pitch, 2);
        Serial.print(", ");
        Serial.print(IMU.roll, 2);
      }
      if(M5.BtnC.isPressed()){        
        rpyController.setRPY(&IMU);
        rpyController.updateDirectionControl(&whill);
        Serial.print(", ");
        Serial.print("X:");
        Serial.print(String(rpyController.getJoyX(), DEC));
        Serial.print(", ");
        Serial.print("Y:");
        Serial.print(String(rpyController.getJoyY(), DEC));
        Serial.println("");
      }else{
        Serial.println("");
      }
  }
  delay(100);
  M5.update();
}

