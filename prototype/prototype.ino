/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

// Motor A connections
int enA = 9;
int in2 = 8;
int in1 = 7;
// Motor B connections
int enB = 3;
int in3 = 4;
int in4 = 5;

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void loop() {
  Usb.Task();
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatY) > 137) {
      Serial.print(F("\r\nLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }
    if (PS3.getAnalogHat(LeftHatY) < 117) {
      Serial.print(F("\r\nLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
     if (PS3.getAnalogHat(RightHatY) > 137) {
      Serial.print(F("\r\nRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    if (PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }

    if (PS3.getAnalogHat(RightHatY) > 116 && PS3.getAnalogHat(RightHatY) < 138) {
      Serial.print(F("\r\nRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }

    if (PS3.getAnalogHat(LeftHatY) > 116 && PS3.getAnalogHat(LeftHatY) < 138) {
      Serial.print(F("\r\nLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
    
    
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
      }
      
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
    }
#if 0 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
}
