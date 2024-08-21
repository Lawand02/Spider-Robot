 
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>


SoftwareSerial Bluetooth (A1,A0);// Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
// Leg 1
int s16 = 0 ;//rot
int s17 = 1 ;
int s18 = 2 ;
// Leg 2
int s19 = 4 ;//rot
int s20 = 5 ;
int s21 = 6 ;
// Leg 3
int s22 = 8 ;//rot
int s23 = 9 ;
int s24 = 10 ;
// Leg 4
int s10 = 2 ;
int s11 = 1 ;
int s12 = 0 ;//rot
// Leg 5
int s7 = 6 ;
int s8 = 5 ;
int s9 = 4 ;//rot
// Leg 6
int s1 = 10 ;
int s2 = 9 ;
int s3 = 8 ;//rot

int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 0;
int i4L1 = 0;
int i5L1 = 0;
int i6L1 = 0;


int i1L2 = 0;
int i2L2 = 0;
int i3L2 = 0;
int i4L2 = 0;
int i5L2 = 0;
int i6L2 = 0;

int dataIn = 0;
int m = 0;

boolean l1status = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  pwm.begin();
  pwm.setPWMFreq(60);  // This is the maximum PWM frequency

  pwm2.begin();
  pwm2.setPWMFreq(60);  // This is the maximum PWM frequency
  // Leg 1
  pwm.setPWM(s18,0,angleToPulse(50));
  pwm.setPWM(s17,0,angleToPulse(90));
  pwm.setPWM(s16,0,angleToPulse(70));//rot
  // Leg 2
  pwm.setPWM(s21,0,angleToPulse(40));
  pwm.setPWM(s20,0,angleToPulse(78));
  pwm.setPWM(s19,0,angleToPulse(75));//rot
  // Leg 3
  pwm.setPWM(s24,0,angleToPulse(40));
  pwm.setPWM(s23,0,angleToPulse(80));
  pwm.setPWM(s22,0,angleToPulse(110));//rot
  // Leg 4
  pwm2.setPWM(s10,0,angleToPulse(75));
  pwm2.setPWM(s11,0,angleToPulse(35));
  pwm2.setPWM(s12,0,angleToPulse(70));//rot
  // Leg 5
  pwm2.setPWM(s7,0,angleToPulse(90));
  pwm2.setPWM(s8,0,angleToPulse(70));
  pwm2.setPWM(s9,0,angleToPulse(25));//rot
  // Leg 6
  pwm2.setPWM(s1,0,angleToPulse(100));
  pwm2.setPWM(s2,0,angleToPulse(55));
  pwm2.setPWM(s3,0,angleToPulse(30));//rot
  
  
  delay(5000);

}
void loop() {

    moveLeg1();
    moveLeg3();
    moveLeg5();
    if (l1status == HIGH) {
      moveLeg2();
      moveLeg4();
      moveLeg6();
    }
    delay(20);

  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.read();  // Read the data
    if (dataIn == 2) {
    moveLeg1();
    moveLeg3();
    moveLeg5();
    if (l1status == HIGH) {
      moveLeg2();
      moveLeg4();
      moveLeg6();
    }
    delay(50);

    }
    if (dataIn == 3) {
      moveLeg1();
    moveLeg3();
    moveLeg5Left();
    if (l1status == HIGH) {
      moveLeg2();
      moveLeg4Left();
      moveLeg6Left();
    }
    delay(50);
    }
    if (dataIn == 4) {
      moveLeg1Right();
    moveLeg3Right();
    moveLeg5();
    if (l1status == HIGH) {
      moveLeg2Right();
      moveLeg4();
      moveLeg6();
    }
    delay(50);
    }
    if (dataIn == 5) {
       moveLeg1Rev();
    moveLeg3Rev();
    moveLeg5Rev();
    if (l1status == HIGH) {
      moveLeg2Rev();
      moveLeg4Rev();
      moveLeg6Rev();
    }
    delay(50);
    }
   
  }
 
}


void moveLeg1() {
  // Swign phase - move leg though air - from initial to final position
  // Rise the leg
  if (i1L1 <= 10) {
    pwm.setPWM(s18,0,angleToPulse(50 - i1L1 * 2));
    pwm.setPWM(s17,0,angleToPulse(90 - i1L1 * 3));
    //delay(500);
    //s18.write(60 - i1L1 * 2);
    //s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    pwm.setPWM(s16,0,angleToPulse(70 - i2L1));
    //delay(500);
    //s16.write(100 - i2L1);
    i2L1++;

  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm.setPWM(s18,0,angleToPulse(30 + i3L1 * 2));
    pwm.setPWM(s17,0,angleToPulse(60 + i3L1 * 3));
    //delay(500);
    //s18.write(40 + i3L1 * 2);
    //s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    pwm.setPWM(s16,0,angleToPulse(40 + i4L1));
    //delay(500);
    //s16.write(70 + i4L1);
    i4L1++;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
  // Each iteration or step is executed in the main loop section where there is also a delay time for controlling the speed of movement
}

void moveLeg2() {
  if (i1L2 <= 10) {
    pwm.setPWM(s21,0,angleToPulse(40 - i1L2 * 2));
    pwm.setPWM(s20,0,angleToPulse(78 - i1L2 * 3));
    //delay(500);
    //s21.write(50 - i1L2 * 2);
    //s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    pwm.setPWM(s19,0,angleToPulse(75 - i2L2));
    //delay(500);
    //s19.write(75 - i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    pwm.setPWM(s21,0,angleToPulse(20 + i3L2 * 2));
    pwm.setPWM(s20,0,angleToPulse(50 + i3L2 * 3));
    //delay(500);
    //s21.write(30 + i3L2 * 2);
    //s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    pwm.setPWM(s19,0,angleToPulse(45 + i4L2));
    //delay(500);
    //s19.write(45 + i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}
void moveLeg3() {
  if (i1L1 <= 10) {
    pwm.setPWM(s24,0,angleToPulse(40 - i1L1 * 2));
    pwm.setPWM(s23,0,angleToPulse(80 - i1L1 * 3));
    //s24.write(50 - i1L1 * 2);
    //s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    pwm.setPWM(s22,0,angleToPulse(110 - i2L1));
    //s22.write(80 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm.setPWM(s24,0,angleToPulse(20 + i3L1 * 2));
    pwm.setPWM(s23,0,angleToPulse(50 + i3L1 * 3));
    //s24.write(30 + i3L1 * 2);
    //s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    pwm.setPWM(s22,0,angleToPulse(80 + i4L1));
    //s22.write(50 + i4L1);
  }
}


void moveLeg4() {
  if (i1L2 <= 10) {
    pwm2.setPWM(s10,0,angleToPulse(75 + i1L2 * 2));
    pwm2.setPWM(s11,0,angleToPulse(40 + i1L2 * 3));
    //s10.write(65 + i1L2 * 2);
    //s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    pwm2.setPWM(s12,0,angleToPulse(70 + i2L2));
    //s12.write(35 + i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {

    pwm2.setPWM(s10,0,angleToPulse(95 - i3L2 * 2));
    pwm2.setPWM(s11,0,angleToPulse(70 - i3L2 * 3));
    //s10.write(85 - i3L2 * 2);
    //s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    pwm2.setPWM(s12,0,angleToPulse(100 - i4L2));
    //s12.write(65 - i4L2);
  }
}

void moveLeg5() {
  if (i1L1 <= 10) {
    pwm2.setPWM(s7,0,angleToPulse(90 + i1L1 * 2));
    pwm2.setPWM(s8,0,angleToPulse(70 + i1L1 * 3));
    //s7.write(80 + i1L1 * 2);
    //s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    pwm2.setPWM(s9,0,angleToPulse(30 + i2L1));
    //s9.write(30 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm2.setPWM(s7,0,angleToPulse(110 - i3L1 * 2));
    pwm2.setPWM(s8,0,angleToPulse(100 - i3L1 * 3));
    //s7.write(100 - i3L1 * 2);
    //s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    pwm2.setPWM(s9,0,angleToPulse(60 - i4L1));
    //s9.write(60 - i4L1);
  }
}

void moveLeg6() {
  if (i1L2 <= 10) {
    pwm2.setPWM(s1,0,angleToPulse(100 + i1L2 * 2));
    pwm2.setPWM(s2,0,angleToPulse(55 + i1L2 * 3));
    //s1.write(90 + i1L2 * 2);
    //s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    pwm2.setPWM(s3,0,angleToPulse(30 + i2L2));
    //s3.write(60 + i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    pwm2.setPWM(s1,0,angleToPulse(120 - i3L2 * 2));
    pwm2.setPWM(s2,0,angleToPulse(85 - i3L2 * 3));
    //s1.write(110 - i3L2 * 2);
    //s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    pwm2.setPWM(s3,0,angleToPulse(60 - i4L2));
    //s3.write(90 - i4L2);
  }
}

void moveLeg1Rev() {
   if (i1L1 <= 10) {
    pwm.setPWM(s18,0,angleToPulse(50 - i1L1 * 2));
    pwm.setPWM(s17,0,angleToPulse(90 - i1L1 * 3));
    //delay(500);
    //s18.write(60 - i1L1 * 2);
    //s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    pwm.setPWM(s16,0,angleToPulse(70 + i2L1));
    //s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm.setPWM(s18,0,angleToPulse(30 + i3L1 * 2));
    pwm.setPWM(s17,0,angleToPulse(60 + i3L1 * 3));
    //delay(500);
    //s18.write(40 + i3L1 * 2);
    //s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    pwm.setPWM(s16,0,angleToPulse(100 - i4L1));
    //s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Rev() {
 if (i1L2 <= 10) {
    pwm.setPWM(s21,0,angleToPulse(40 - i1L2 * 2));
    pwm.setPWM(s20,0,angleToPulse(78 - i1L2 * 3));
    //delay(500);
    //s21.write(50 - i1L2 * 2);
    //s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    pwm.setPWM(s19,0,angleToPulse(75 + i2L2));
    //s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    pwm.setPWM(s21,0,angleToPulse(20 + i3L2 * 2));
    pwm.setPWM(s20,0,angleToPulse(50 + i3L2 * 3));
    //delay(500);
    //s21.write(30 + i3L2 * 2);
    //s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    pwm.setPWM(s19,0,angleToPulse(105 - i4L2));
    //s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Rev() {
  if (i1L1 <= 10) {
    pwm.setPWM(s24,0,angleToPulse(40 - i1L1 * 2));
    pwm.setPWM(s23,0,angleToPulse(80 - i1L1 * 3));
    //s24.write(50 - i1L1 * 2);
    //s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    pwm.setPWM(s22,0,angleToPulse(110 + i2L1));
    //s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm.setPWM(s24,0,angleToPulse(20 + i3L1 * 2));
    pwm.setPWM(s23,0,angleToPulse(50 + i3L1 * 3));
    //s24.write(30 + i3L1 * 2);
    //s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    pwm.setPWM(s22,0,angleToPulse(140 - i4L1));
    //s22.write(80 - i4L1);
  }
}

void moveLeg4Rev() {
  if (i1L2 <= 10) {
    pwm2.setPWM(s10,0,angleToPulse(75 + i1L2 * 2));
    pwm2.setPWM(s11,0,angleToPulse(40 + i1L2 * 3));
    //s10.write(65 + i1L2 * 2);
    //s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    pwm2.setPWM(s12,0,angleToPulse(70 - i2L2));
    //s12.write(65 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {

    pwm2.setPWM(s10,0,angleToPulse(95 - i3L2 * 2));
    pwm2.setPWM(s11,0,angleToPulse(70 - i3L2 * 3));
    //s10.write(85 - i3L2 * 2);
    //s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    pwm2.setPWM(s12,0,angleToPulse(40 + i4L2));
    //s12.write(35 + i4L2);
  }
}

void moveLeg5Rev() {
 if (i1L1 <= 10) {
    pwm2.setPWM(s7,0,angleToPulse(90 + i1L1 * 2));
    pwm2.setPWM(s8,0,angleToPulse(70 + i1L1 * 3));
    //s7.write(80 + i1L1 * 2);
    //s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    pwm2.setPWM(s9,0,angleToPulse(30 - i2L1));
    //s9.write(60 - i2L1);

  }
 if (i2L1 > 20 & i3L1 <= 10) {
    pwm2.setPWM(s7,0,angleToPulse(110 - i3L1 * 2));
    pwm2.setPWM(s8,0,angleToPulse(100 - i3L1 * 3));
    //s7.write(100 - i3L1 * 2);
    //s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    pwm2.setPWM(s9,0,angleToPulse(0 + i4L1));
    //s9.write(30 + i4L1);
  }
}

void moveLeg6Rev() {
  if (i1L2 <= 10) {
    pwm2.setPWM(s1,0,angleToPulse(100 + i1L2 * 2));
    pwm2.setPWM(s2,0,angleToPulse(55 + i1L2 * 3));
    //s1.write(90 + i1L2 * 2);
    //s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    pwm2.setPWM(s3,0,angleToPulse(30 - i2L2));
    //s3.write(90 - i2L2);
  }
 if (i2L2 > 20 & i3L2 <= 10) {
    pwm2.setPWM(s1,0,angleToPulse(120 - i3L2 * 2));
    pwm2.setPWM(s2,0,angleToPulse(85 - i3L2 * 3));
    //s1.write(110 - i3L2 * 2);
    //s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    pwm2.setPWM(s3,0,angleToPulse(0 + i4L2));
    //s3.write(60 + i4L2);
  }
}

void moveLeg1Right() {
 if (i1L1 <= 10) {
    pwm.setPWM(s18,0,angleToPulse(50 - i1L1 * 2));
    pwm.setPWM(s17,0,angleToPulse(90 - i1L1 * 3));
    //delay(500);
    //s18.write(60 - i1L1 * 2);
    //s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    pwm.setPWM(s16,0,angleToPulse(70 + i2L1));
    //s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm.setPWM(s18,0,angleToPulse(30 + i3L1 * 2));
    pwm.setPWM(s17,0,angleToPulse(60 + i3L1 * 3));
    //delay(500);
    //s18.write(40 + i3L1 * 2);
    //s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    pwm.setPWM(s16,0,angleToPulse(100 - i4L1));
    //s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Right() {
  if (i1L2 <= 10) {
    pwm.setPWM(s21,0,angleToPulse(40 - i1L2 * 2));
    pwm.setPWM(s20,0,angleToPulse(78 - i1L2 * 3));
    //delay(500);
    //s21.write(50 - i1L2 * 2);
    //s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    pwm.setPWM(s19,0,angleToPulse(75 + i2L2));
    //s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    pwm.setPWM(s21,0,angleToPulse(20 + i3L2 * 2));
    pwm.setPWM(s20,0,angleToPulse(50 + i3L2 * 3));
    //delay(500);
    //s21.write(30 + i3L2 * 2);
    //s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    pwm.setPWM(s19,0,angleToPulse(105 - i4L2));
    //s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Right() {
  if (i1L1 <= 10) {
    pwm.setPWM(s24,0,angleToPulse(40 - i1L1 * 2));
    pwm.setPWM(s23,0,angleToPulse(80 - i1L1 * 3));
    //s24.write(50 - i1L1 * 2);
    //s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    pwm.setPWM(s22,0,angleToPulse(110 + i2L1));
    //s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm.setPWM(s24,0,angleToPulse(20 + i3L1 * 2));
    pwm.setPWM(s23,0,angleToPulse(50 + i3L1 * 3));
    //s24.write(30 + i3L1 * 2);
    //s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    pwm.setPWM(s22,0,angleToPulse(140 - i4L1));
    //s22.write(80 - i4L1);
  }
}

void moveLeg4Left() {
  if (i1L2 <= 10) {
    pwm2.setPWM(s10,0,angleToPulse(75 + i1L2 * 2));
    pwm2.setPWM(s11,0,angleToPulse(40 + i1L2 * 3));
    //s10.write(65 + i1L2 * 2);
    //s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    pwm2.setPWM(s12,0,angleToPulse(70 - i2L2));
    //s12.write(60 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    pwm2.setPWM(s10,0,angleToPulse(95 - i3L2 * 2));
    pwm2.setPWM(s11,0,angleToPulse(70 - i3L2 * 3));
    //s10.write(85 - i3L2 * 2);
    //s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    pwm2.setPWM(s12,0,angleToPulse(40 + i4L2));
    //s12.write(30 + i4L2);
  }
}

void moveLeg5Left() {
   if (i1L1 <= 10) {
    pwm2.setPWM(s7,0,angleToPulse(90 + i1L1 * 2));
    pwm2.setPWM(s8,0,angleToPulse(70 + i1L1 * 3));
    //s7.write(80 + i1L1 * 2);
    //s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    pwm2.setPWM(s9,0,angleToPulse(30 - i2L1));
    //s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    pwm2.setPWM(s7,0,angleToPulse(110 - i3L1 * 2));
    pwm2.setPWM(s8,0,angleToPulse(100 - i3L1 * 3));
    //s7.write(100 - i3L1 * 2);
    //s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    pwm2.setPWM(s9,0,angleToPulse(0 + i4L1));
    //s9.write(30 + i4L1);
  }
}

void moveLeg6Left() {
  if (i1L2 <= 10) {
    pwm2.setPWM(s1,0,angleToPulse(100 + i1L2 * 2));
    pwm2.setPWM(s2,0,angleToPulse(55 + i1L2 * 3));
    //s1.write(90 + i1L2 * 2);
    //s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    pwm2.setPWM(s3,0,angleToPulse(30 - i2L2));
    //s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    pwm2.setPWM(s1,0,angleToPulse(120 - i3L2 * 2));
    pwm2.setPWM(s2,0,angleToPulse(85 - i3L2 * 3));
    //s1.write(110 - i3L2 * 2);
    //s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    pwm2.setPWM(s3,0,angleToPulse(0 + i4L2));
    //s3.write(60 + i4L2);
  }
}


void initialPosition() {
 
  m = 0;
  l1status = LOW;
  
  pwm.setPWM(s18,0,angleToPulse(50));
  pwm.setPWM(s17,0,angleToPulse(90));
  pwm.setPWM(s16,0,angleToPulse(70));//rot
  // Leg 2
  pwm.setPWM(s21,0,angleToPulse(40));
  pwm.setPWM(s20,0,angleToPulse(78));
  pwm.setPWM(s19,0,angleToPulse(75));//rot
  // Leg 3
  pwm.setPWM(s24,0,angleToPulse(40));
  pwm.setPWM(s23,0,angleToPulse(80));
  pwm.setPWM(s22,0,angleToPulse(110));//rot
  // Leg 4
  pwm2.setPWM(s10,0,angleToPulse(75));
  pwm2.setPWM(s11,0,angleToPulse(35));
  pwm2.setPWM(s12,0,angleToPulse(70));//rot
  // Leg 5
  pwm2.setPWM(s7,0,angleToPulse(90));
  pwm2.setPWM(s8,0,angleToPulse(70));
  pwm2.setPWM(s9,0,angleToPulse(25));//rot
  // Leg 6
  pwm2.setPWM(s1,0,angleToPulse(100));
  pwm2.setPWM(s2,0,angleToPulse(55));
  pwm2.setPWM(s3,0,angleToPulse(30));//rot
  i1L1 = 0;
  i2L1 = 0;
  i3L1 = 0;
  i4L1 = 0;
  i5L1 = 0;
  i6L1 = 0;

  i1L2 = 0;
  i2L2 = 0;
  i3L2 = 0;
  i4L2 = 0;
  i5L2 = 0;
  i6L2 = 0;
}


int angleToPulse(int ang){
  int pulselength = map(ang, 0, 180, 150, 575);
  return pulselength;
  }
