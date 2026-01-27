// Custom 7 segment Display Code based on the Adafruit AW9523 library example
// This is far from the most optimized code, but it should be enough for testing.




// First code, it works but not efficient. just here for archive...







#include "Adafruit_AW9523.h"

Adafruit_AW9523 awA;
Adafruit_AW9523 awB;

int brightness = 80;         // 0 to 255        255 = IMAX, should be 37mA [...]

#define LED_Neg_EN 20 //replace with whatever pin you want
#define Neg_RST 21    // here too

uint8_t A_1 = 4;   //P0_4 B
uint8_t B_1 = 6;   //P0_6 B
uint8_t C_1 = 12;  //P1_4 B
uint8_t D_1 = 13;  //P1_5 B
uint8_t E_1 = 8;   //P1_0 B
uint8_t F_1 = 5;   //P0_5 B
uint8_t G_1 = 7;   //P0_7 B
uint8_t DP_1 = 14; //P1_6 B

uint8_t A_2 = 12;  //P1_4 A
uint8_t B_2 = 6;   //P0_6 A
uint8_t C_2 = 0;   //P0_0 A
uint8_t D_2 = 10;  //P1_2 A
uint8_t E_2 = 15;  //P1_7 B
uint8_t F_2 = 7;   //P0_7 A
uint8_t G_2 = 4;   //P0_4 A
uint8_t DP_2 = 11; //P1_3 A

uint8_t A_3 = 13;  //P1_5 A
uint8_t B_3 = 14;  //P1_6 A
uint8_t C_3 = 1;   //P0_1 A
uint8_t D_3 = 9;   //P1_1 A
uint8_t E_3 = 2;   //P0_2 A
uint8_t F_3 = 5;   //P0_5 A
uint8_t G_3 = 3;   //P0_3 A

uint8_t ICON1 = 2;    //P0_2 B
uint8_t ICON2 = 3;    //P0_3 B
uint8_t ICON3 = 15;   //P1_7 A
uint8_t ICON4 = 8;    //P1_0 A

uint8_t LED_BAR_1 = 1;   //P0_1 B
uint8_t LED_BAR_2 = 0;   //P0_0 B
uint8_t LED_BAR_3 = 11;  //P1_3 B
uint8_t LED_BAR_4 = 10;  //P1_2 B
uint8_t LED_BAR_5 = 9;   //P1_1 B


void setup() {
  pinMode (LED_Neg_EN, OUTPUT);
  digitalWrite (LED_Neg_EN, HIGH);
  Serial.begin(115200);
  while (!Serial) delay(1);  // wait for serial port to open

  Serial.println("Custom Segmented Display ready to use");

  if (! awA.begin(0x58)) { // or 0x59
    Serial.println("AW9523-A not found...");
    while (1) delay(10);  // halt forever
  }

  if (! awB.begin(0x5A)) { // or 0x5B
    Serial.println("AW9523-B not found...");
    while (1) delay(10);  // halt forever
  }

  Serial.println("Custom Segmented display ready to go!");

  for (int PIN = 0; PIN <= 15; PIN++) {
    awA.pinMode(PIN, AW9523_LED_MODE); // set to constant current drive
    awB.pinMode(PIN, AW9523_LED_MODE); // set to constant current drive
  }
  delay (500);
  digitalWrite (LED_Neg_EN, LOW);     // Enable VCC.LEDs

}

void loop() {
  clearALL();
  for (int br = 0; br <= brightness; br++) {    // two dots gradually lighting up
    awB.analogWrite (DP_1, br);
    awB.analogWrite (DP_2, br);
    delay (10);
  }
  clearALL();
  for (int level = 0; level <= 5; level++) {    // light Bar test
    LightBar (level);
    delay (1000);
  }
  awB.analogWrite (ICON1, brightness);    // Icons
  delay (200);
  awB.analogWrite (ICON2, brightness);
  delay (200);
  awA.analogWrite (ICON3, brightness);
  delay (200);
  awA.analogWrite (ICON4, brightness);
  delay (2000);
  clearALL();
  for (int num = 0; num <= 999; num++) {    // counts up to 999
    displayNumber (num);
    delay (250);
  }

  digitalWrite (LED_Neg_EN, HIGH);


}

void displayDIGIT (int number, int digit) {
  switch (digit) {
    case 1 :
      switch (number) {
        case 0:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, brightness);
          awB.analogWrite (E_1, brightness);
          awB.analogWrite (F_1, brightness);
          awB.analogWrite (G_1, 0);
          break;
        case 1:
          awB.analogWrite (A_1, 0);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, 0);
          awB.analogWrite (E_1, 0);
          awB.analogWrite (F_1, 0);
          awB.analogWrite (G_1, 0);
          break;
        case 2:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, 0);
          awB.analogWrite (D_1, brightness);
          awB.analogWrite (E_1, brightness);
          awB.analogWrite (F_1, 0);
          awB.analogWrite (G_1, brightness);
          break;
        case 3:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, brightness);
          awB.analogWrite (E_1, 0);
          awB.analogWrite (F_1, 0);
          awB.analogWrite (G_1, brightness);
          break;
        case 4:
          awB.analogWrite (A_1, 0);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, 0);
          awB.analogWrite (E_1, 0);
          awB.analogWrite (F_1, brightness);
          awB.analogWrite (G_1, brightness);
          break;
        case 5:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, 0);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, brightness);
          awB.analogWrite (E_1, 0);
          awB.analogWrite (F_1, brightness);
          awB.analogWrite (G_1, brightness);
          break;
        case 6:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, 0);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, brightness);
          awB.analogWrite (E_1, brightness);
          awB.analogWrite (F_1, brightness);
          awB.analogWrite (G_1, brightness);
          break;
        case 7:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, 0);
          awB.analogWrite (E_1, 0);
          awB.analogWrite (F_1, 0);
          awB.analogWrite (G_1, 0);
          break;
        case 8:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, brightness);
          awB.analogWrite (E_1, brightness);
          awB.analogWrite (F_1, brightness);
          awB.analogWrite (G_1, brightness);
          break;
        case 9:
          awB.analogWrite (A_1, brightness);
          awB.analogWrite (B_1, brightness);
          awB.analogWrite (C_1, brightness);
          awB.analogWrite (D_1, brightness);
          awB.analogWrite (E_1, 0);
          awB.analogWrite (F_1, brightness);
          awB.analogWrite (G_1, brightness);
          break;
      }
      break;
    case 2 :
      switch (number) {
        case 0:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, brightness);
          awB.analogWrite (E_2, brightness);
          awA.analogWrite (F_2, brightness);
          awA.analogWrite (G_2, 0);
          break;
        case 1:
          awA.analogWrite (A_2, 0);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, 0);
          awB.analogWrite (E_2, 0);
          awA.analogWrite (F_2, 0);
          awA.analogWrite (G_2, 0);
          break;
        case 2:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, 0);
          awA.analogWrite (D_2, brightness);
          awB.analogWrite (E_2, brightness);
          awA.analogWrite (F_2, 0);
          awA.analogWrite (G_2, brightness);
          break;
        case 3:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, brightness);
          awB.analogWrite (E_2, 0);
          awA.analogWrite (F_2, 0);
          awA.analogWrite (G_2, brightness);
          break;
        case 4:
          awA.analogWrite (A_2, 0);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, 0);
          awB.analogWrite (E_2, 0);
          awA.analogWrite (F_2, brightness);
          awA.analogWrite (G_2, brightness);
          break;
        case 5:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, 0);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, brightness);
          awB.analogWrite (E_2, 0);
          awA.analogWrite (F_2, brightness);
          awA.analogWrite (G_2, brightness);
          break;
        case 6:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, 0);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, brightness);
          awB.analogWrite (E_2, brightness);
          awA.analogWrite (F_2, brightness);
          awA.analogWrite (G_2, brightness);
          break;
        case 7:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, 0);
          awB.analogWrite (E_2, 0);
          awA.analogWrite (F_2, 0);
          awA.analogWrite (G_2, 0);
          break;
        case 8:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, brightness);
          awB.analogWrite (E_2, brightness);
          awA.analogWrite (F_2, brightness);
          awA.analogWrite (G_2, brightness);
          break;
        case 9:
          awA.analogWrite (A_2, brightness);
          awA.analogWrite (B_2, brightness);
          awA.analogWrite (C_2, brightness);
          awA.analogWrite (D_2, brightness);
          awB.analogWrite (E_2, 0);
          awA.analogWrite (F_2, brightness);
          awA.analogWrite (G_2, brightness);
          break;
      }
      break;
    case 3 :
      switch (number) {
        case 0:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, brightness);
          awA.analogWrite (E_3, brightness);
          awA.analogWrite (F_3, brightness);
          awA.analogWrite (G_3, 0);
          break;
        case 1:
          awA.analogWrite (A_3, 0);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, 0);
          awA.analogWrite (E_3, 0);
          awA.analogWrite (F_3, 0);
          awA.analogWrite (G_3, 0);
          break;
        case 2:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, 0);
          awA.analogWrite (D_3, brightness);
          awA.analogWrite (E_3, brightness);
          awA.analogWrite (F_3, 0);
          awA.analogWrite (G_3, brightness);
          break;
        case 3:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, brightness);
          awA.analogWrite (E_3, 0);
          awA.analogWrite (F_3, 0);
          awA.analogWrite (G_3, brightness);
          break;
        case 4:
          awA.analogWrite (A_3, 0);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, 0);
          awA.analogWrite (E_3, 0);
          awA.analogWrite (F_3, brightness);
          awA.analogWrite (G_3, brightness);
          break;
        case 5:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, 0);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, brightness);
          awA.analogWrite (E_3, 0);
          awA.analogWrite (F_3, brightness);
          awA.analogWrite (G_3, brightness);
          break;
        case 6:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, 0);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, brightness);
          awA.analogWrite (E_3, brightness);
          awA.analogWrite (F_3, brightness);
          awA.analogWrite (G_3, brightness);
          break;
        case 7:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, 0);
          awA.analogWrite (E_3, 0);
          awA.analogWrite (F_3, 0);
          awA.analogWrite (G_3, 0);
          break;
        case 8:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, brightness);
          awA.analogWrite (E_3, brightness);
          awA.analogWrite (F_3, brightness);
          awA.analogWrite (G_3, brightness);
          break;
        case 9:
          awA.analogWrite (A_3, brightness);
          awA.analogWrite (B_3, brightness);
          awA.analogWrite (C_3, brightness);
          awA.analogWrite (D_3, brightness);
          awA.analogWrite (E_3, 0);
          awA.analogWrite (F_3, brightness);
          awA.analogWrite (G_3, brightness);
          break;
      }
      break;
  }

}

void clearNumbers() {
  awA.analogWrite (0, 0);
  awA.analogWrite (1, 0);
  awA.analogWrite (2, 0);
  awA.analogWrite (3, 0);
  awA.analogWrite (4, 0);
  awA.analogWrite (5, 0);
  awA.analogWrite (6, 0);
  awA.analogWrite (7, 0);
  awA.analogWrite (9, 0);
  awA.analogWrite (10, 0);
  awA.analogWrite (11, 0);
  awA.analogWrite (12, 0);
  awA.analogWrite (13, 0);
  awA.analogWrite (14, 0);

  awB.analogWrite (4, 0);
  awB.analogWrite (5, 0);
  awB.analogWrite (6, 0);
  awB.analogWrite (7, 0);
  awB.analogWrite (8, 0);
  awB.analogWrite (12, 0);
  awB.analogWrite (13, 0);
  awB.analogWrite (14, 0);
  awB.analogWrite (15, 0);


}

void clearALL() {
  for (int PIN = 0; PIN <= 15; PIN++) {
    awA.analogWrite (PIN, 0);
    awB.analogWrite (PIN, 0);
  }
}

void displayNumber (int value) {          // Displays value from 0 to 999
  
  value = constrain(value, 0, 999);
  int firstDigit  = value / 100;
  int secondDigit = (value / 10) % 10;
  int thirdDigit  = value % 10;

  clearNumbers();

  displayDIGIT (firstDigit, 1);
  displayDIGIT (secondDigit, 2);
  displayDIGIT (thirdDigit, 3);

}

void LightBar (int value) {

  switch (value) {
    case 0:
      awB.analogWrite (LED_BAR_1, 0);
      awB.analogWrite (LED_BAR_2, 0);
      awB.analogWrite (LED_BAR_3, 0);
      awB.analogWrite (LED_BAR_4, 0);
      awB.analogWrite (LED_BAR_5, 0);
      break;
    case 1:
      awB.analogWrite (LED_BAR_1, brightness);
      awB.analogWrite (LED_BAR_2, 0);
      awB.analogWrite (LED_BAR_3, 0);
      awB.analogWrite (LED_BAR_4, 0);
      awB.analogWrite (LED_BAR_5, 0);
      break;
    case 2:
      awB.analogWrite (LED_BAR_1, brightness);
      awB.analogWrite (LED_BAR_2, brightness);
      awB.analogWrite (LED_BAR_3, 0);
      awB.analogWrite (LED_BAR_4, 0);
      awB.analogWrite (LED_BAR_5, 0);
      break;
    case 3:
      awB.analogWrite (LED_BAR_1, brightness);
      awB.analogWrite (LED_BAR_2, brightness);
      awB.analogWrite (LED_BAR_3, brightness);
      awB.analogWrite (LED_BAR_4, 0);
      awB.analogWrite (LED_BAR_5, 0);
      break;
    case 4:
      awB.analogWrite (LED_BAR_1, brightness);
      awB.analogWrite (LED_BAR_2, brightness);
      awB.analogWrite (LED_BAR_3, brightness);
      awB.analogWrite (LED_BAR_4, brightness);
      awB.analogWrite (LED_BAR_5, 0);
      break;
    case 5:
      awB.analogWrite (LED_BAR_1, brightness);
      awB.analogWrite (LED_BAR_2, brightness);
      awB.analogWrite (LED_BAR_3, brightness);
      awB.analogWrite (LED_BAR_4, brightness);
      awB.analogWrite (LED_BAR_5, brightness);
      break;
  }

}

