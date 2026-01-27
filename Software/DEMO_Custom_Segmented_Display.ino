// Custom 7 segment Display Code based on the Adafruit AW9523 library example
// Newer version, this is far from the most optimized code, but at least it's more efficient than the previous code. It's still good enough for my use cases.

#include "Adafruit_AW9523.h"

Adafruit_AW9523 awA;
Adafruit_AW9523 awB;

int brightness = 80;         // 0 to 255        255 = IMAX, should be 37mA [...]

#define LED_Neg_EN 5 //replace with whatever pin you want
#define Neg_RST 6    // here too

uint8_t pinsMatrixA [4][4] = {
  {0, 1, 2, 3},         //  C_2 [0][0]       C_3 [0][1]    E_3 [0][2]     G_3 [0][3]
  {4, 5, 6, 7},         //  G_2 [1][0]       F_3 [1][1]    B_2 [1][2]     F_2 [1][3]
  {8, 9, 10, 11},       //  ICON4 [2][0]     D_3 [2][1]    DP_2 [2][2]    D_2 [2][3]
  {12, 13, 14, 15}      //  A_2 [3][0]       A_3 [3][1]    B_3 [3][2]     ICON3 [3][3]
};

uint8_t pinsMatrixB [4][4] = {
  {0, 1, 2, 3},         //  LED_BAR_2 [0][0]    LED_BAR_1 [0][1]      ICON1 [0][2]        ICON3 [0][3]
  {4, 5, 6, 7},         //  A_1 [1][0]          F_1 [1][1]            B_1 [1][2]          G_1 [1][3]
  {8, 9, 10, 11},       //  E_1 [2][0]          LED_BAR_5 [2][1]      LED_BAR_4 [2][2]    LED_BAR_3 [2][3]
  {12, 13, 14, 15}      //  C_1 [3][0]          D_1 [3][1]            DP_1 [3][2]         E_2 [3][3]
};

bool stateMatrixA [4][4] = {
  {0, 0, 0, 0},         //  C_2 [0][0]       C_3 [0][1]    E_3 [0][2]     G_3 [0][3]
  {0, 0, 0, 0},         //  G_2 [1][0]       F_3 [1][1]    A_2 [1][2]     F_2 [1][3]
  {0, 0, 0, 0},         //  ICON4 [2][0]    D_3 [2][1]    DP3 [2][2]    D_2 [2][3]
  {0, 0, 0, 0}         //  A_2 [3][0]       A_3 [3][1]    B_3 [3][2]     ICON3 [3][3]
};

bool NstateMatrixA [4][4] = {
  {0, 0, 0, 0},         //  C_2 [0][0]       C_3 [0][1]    E_3 [0][2]     G_3 [0][3]
  {0, 0, 0, 0},         //  G_2 [1][0]       F_3 [1][1]    A_2 [1][2]     F_2 [1][3]
  {0, 0, 0, 0},         //  ICON4 [2][0]    D_3 [2][1]    DP3 [2][2]    D_2 [2][3]
  {0, 0, 0, 0}         //  A_2 [3][0]       A_3 [3][1]    B_3 [3][2]     ICON3 [3][3]
};

bool stateMatrixB [4][4] = {
  {0, 0, 0, 0},         //  LED_BAR_2 [0][0]    LED_BAR_1 [0][1]      ICON1 [0][2]        ICON2 [0][3]
  {0, 0, 0, 0},         //  A_1 [1][0]          F_1 [1][1]            B_1 [1][2]          G_1 [1][3]
  {0, 0, 0, 0},         //  E_1 [2][0]          LED_BAR_5 [2][1]      LED_BAR_4 [2][2]    LED_BAR_3 [2][3]
  {0, 0, 0, 0}         //  C_1 [3][0]          D_1 [3][1]            DP_1 [3][2]         E_2 [3][3]
};

bool NstateMatrixB [4][4] = {
  {0, 0, 0, 0},         //  LED_BAR_2 [0][0]    LED_BAR_1 [0][1]      ICON1 [0][2]        ICON2 [0][3]
  {0, 0, 0, 0},         //  A_1 [1][0]          F_1 [1][1]            B_1 [1][2]          G_1 [1][3]
  {0, 0, 0, 0},         //  E_1 [2][0]          LED_BAR_5 [2][1]      LED_BAR_4 [2][2]    LED_BAR_3 [2][3]
  {0, 0, 0, 0}         //  C_1 [3][0]          D_1 [3][1]            DP_1 [3][2]         E_2 [3][3]
};


void setup() {
  pinMode (LED_Neg_EN, OUTPUT);
  digitalWrite (LED_Neg_EN, HIGH);
  Serial.begin(115200);
  while (!Serial) delay(1);  // wait for serial port to open

  Serial.println("Custom Segmented Display ready to use");

  if (! awA.begin(0x5B)) { // or 0x59
    Serial.println("AW9523-A not found...");
    while (1) delay(10);  // halt forever
  }

  if (! awB.begin(0x58)) { // or 0x5B
    Serial.println("AW9523-B not found...");
    while (1) delay(10);  // halt forever
  }

  Serial.println("Custom Segmented display ready to go!");

  for (int PIN = 0; PIN <= 15; PIN++) {
    awA.pinMode(PIN, AW9523_LED_MODE); // set to constant current drive
    awB.pinMode(PIN, AW9523_LED_MODE); // set to constant current drive
  }
  delay (2000);
  digitalWrite (LED_Neg_EN, LOW);     // Enable VCC.LEDs

}

void loop() {
  clearALL();
  for (int b = 0; b <= 100; b++) {    // two dots gradually lighting up
    brightness = b;
    NstateMatrixB[3][2] = 1;    // DP_1
    NstateMatrixA[2][2] = 1;    // DP_2
    forcedRefreshDisplay();
    delay (100);
  }
  clearALL();
  for (int level = 0; level <= 5; level++) {    // light Bar test
    LightBar (level);
    delay (1000);
  }

  for (int b = 0; b <= 80; b++) {
    brightness = b;
    litALL();
    forcedRefreshDisplay();
    delay (100);
  }
  clearALL();
  NstateMatrixB[0][2] = 1;    // Icon 1
  delay (800);
  refreshDisplay();
  NstateMatrixB[0][3] = 1;    // Icon 2
  delay (800);
  refreshDisplay();
  NstateMatrixA[3][3] = 1;    // Icon 3
  delay (800);
  refreshDisplay();
  NstateMatrixA[2][0] = 1;    // Icon 4
  delay (800);
  refreshDisplay();
  delay (2000);
  clearALL();

  for (int num = 0; num <= 999; num++) {    // counts up to 999
    displayNumber (num);
    delay (150);
  }
  clearALL();
}

void displayDIGIT (int number, int digit) {
  
  bool  A_1 = NstateMatrixB[1][0];
  bool  A_2 = NstateMatrixA[3][0];
  bool  A_3 = NstateMatrixA[3][1];

  bool B_1 = NstateMatrixB[1][2];
  bool B_2 = NstateMatrixA[1][2];
  bool B_3 = NstateMatrixA[3][2];

  bool C_1 = NstateMatrixB[3][0];
  bool C_2 = NstateMatrixA[0][0];
  bool C_3 = NstateMatrixA[0][1];

  bool D_1 = NstateMatrixB[3][1];
  bool D_2 = NstateMatrixA[2][3];
  bool D_3 = NstateMatrixA[2][1];

  bool E_1 = NstateMatrixB[2][0];
  bool E_2 = NstateMatrixB[3][3];
  bool E_3 = NstateMatrixA[0][2];

  bool F_1 = NstateMatrixB[1][1];
  bool F_2 = NstateMatrixA[1][3];
  bool F_3 = NstateMatrixA[1][1];

  bool G_1 = NstateMatrixB[1][3];
  bool G_2 = NstateMatrixA[1][0];
  bool G_3 = NstateMatrixA[0][3];

  bool DP_1 = NstateMatrixB[3][2];
  bool DP_2 = NstateMatrixA[2][2];

  switch (digit) {
    case 1 :
      switch (number) {
        case 0:
          A_1 = 1;
          B_1 = 1;
          C_1 = 1;
          D_1 = 1;
          E_1 = 1;
          F_1 = 1;
          G_1 = 0;
          break;
        case 1:
          A_1 = 0;
          B_1 = 1;
          C_1 = 1;
          D_1 = 0;
          E_1 = 0;
          F_1 = 0;
          G_1 = 0;
          break;
        case 2:
          A_1 = 1;
          B_1 = 1;
          C_1 = 0;
          D_1 = 1;
          E_1 = 1;
          F_1 = 0;
          G_1 = 1;
          break;
        case 3:
          A_1 = 1;
          B_1 = 1;
          C_1 = 1;
          D_1 = 1;
          E_1 = 0;
          F_1 = 0;
          G_1 = 1;
          break;
        case 4:
          A_1 = 0;
          B_1 = 1;
          C_1 = 1;
          D_1 = 0;
          E_1 = 0;
          F_1 = 1;
          G_1 = 1;
          break;
        case 5:
          A_1 = 1;
          B_1 = 0;
          C_1 = 1;
          D_1 = 1;
          E_1 = 0;
          F_1 = 1;
          G_1 = 1;
          break;
        case 6:
          A_1 = 1;
          B_1 = 0;
          C_1 = 1;
          D_1 = 1;
          E_1 = 1;
          F_1 = 1;
          G_1 = 1;
          break;
        case 7:
          A_1 = 1;
          B_1 = 1;
          C_1 = 1;
          D_1 = 0;
          E_1 = 0;
          F_1 = 0;
          G_1 = 0;
          break;
        case 8:
          A_1 = 1;
          B_1 = 1;
          C_1 = 1;
          D_1 = 1;
          E_1 = 1;
          F_1 = 1;
          G_1 = 1;
          break;
        case 9:
          A_1 = 1;
          B_1 = 1;
          C_1 = 1;
          D_1 = 1;
          E_1 = 0;
          F_1 = 1;
          G_1 = 1;
          break;
      }
      break;

    case 2 :
      switch (number) {
        case 0:
          A_2 = 1;
          B_2 = 1;
          C_2 = 1;
          D_2 = 1;
          E_2 = 1;
          F_2 = 1;
          G_2 = 0;
          break;
        case 1:
          A_2 = 0;
          B_2 = 1;
          C_2 = 1;
          D_2 = 0;
          E_2 = 0;
          F_2 = 0;
          G_2 = 0;
          break;
        case 2:
          A_2 = 1;
          B_2 = 1;
          C_2 = 0;
          D_2 = 1;
          E_2 = 1;
          F_2 = 0;
          G_2 = 1;
          break;
        case 3:
          A_2 = 1;
          B_2 = 1;
          C_2 = 1;
          D_2 = 1;
          E_2 = 0;
          F_2 = 0;
          G_2 = 1;
          break;
        case 4:
          A_2 = 0;
          B_2 = 1;
          C_2 = 1;
          D_2 = 0;
          E_2 = 0;
          F_2 = 1;
          G_2 = 1;
          break;
        case 5:
          A_2 = 1;
          B_2 = 0;
          C_2 = 1;
          D_2 = 1;
          E_2 = 0;
          F_2 = 1;
          G_2 = 1;
          break;
        case 6:
          A_2 = 1;
          B_2 = 0;
          C_2 = 1;
          D_2 = 1;
          E_2 = 1;
          F_2 = 1;
          G_2 = 1;
          break;
        case 7:
          A_2 = 1;
          B_2 = 1;
          C_2 = 1;
          D_2 = 0;
          E_2 = 0;
          F_2 = 0;
          G_2 = 0;
          break;
        case 8:
          A_2 = 1;
          B_2 = 1;
          C_2 = 1;
          D_2 = 1;
          E_2 = 1;
          F_2 = 1;
          G_2 = 1;
          break;
        case 9:
          A_2 = 1;
          B_2 = 1;
          C_2 = 1;
          D_2 = 1;
          E_2 = 0;
          F_2 = 1;
          G_2 = 1;
          break;
      }
      break;


    case 3 :
      switch (number) {
        case 0:
          A_3 = 1;
          B_3 = 1;
          C_3 = 1;
          D_3 = 1;
          E_3 = 1;
          F_3 = 1;
          G_3 = 0;
          break;
        case 1:
          A_3 = 0;
          B_3 = 1;
          C_3 = 1;
          D_3 = 0;
          E_3 = 0;
          F_3 = 0;
          G_3 = 0;
          break;
        case 2:
          A_3 = 1;
          B_3 = 1;
          C_3 = 0;
          D_3 = 1;
          E_3 = 1;
          F_3 = 0;
          G_3 = 1;
          break;
        case 3:
          A_3 = 1;
          B_3 = 1;
          C_3 = 1;
          D_3 = 1;
          E_3 = 0;
          F_3 = 0;
          G_3 = 1;
          break;
        case 4:
          A_3 = 0;
          B_3 = 1;
          C_3 = 1;
          D_3 = 0;
          E_3 = 0;
          F_3 = 1;
          G_3 = 1;
          break;
        case 5:
          A_3 = 1;
          B_3 = 0;
          C_3 = 1;
          D_3 = 1;
          E_3 = 0;
          F_3 = 1;
          G_3 = 1;
          break;
        case 6:
          A_3 = 1;
          B_3 = 0;
          C_3 = 1;
          D_3 = 1;
          E_3 = 1;
          F_3 = 1;
          G_3 = 1;
          break;
        case 7:
          A_3 = 1;
          B_3 = 1;
          C_3 = 1;
          D_3 = 0;
          E_3 = 0;
          F_3 = 0;
          G_3 = 0;
          break;
        case 8:
          A_3 = 1;
          B_3 = 1;
          C_3 = 1;
          D_3 = 1;
          E_3 = 1;
          F_3 = 1;
          G_3 = 1;
          break;
        case 9:
          A_3 = 1;
          B_3 = 1;
          C_3 = 1;
          D_3 = 1;
          E_3 = 0;
          F_3 = 1;
          G_3 = 1;
          break;
      }
      break;
  }

  NstateMatrixB[1][0] = A_1;
  NstateMatrixA[3][0] = A_2;
  NstateMatrixA[3][1] = A_3;

  NstateMatrixB[1][2] = B_1;
  NstateMatrixA[1][2] = B_2;
  NstateMatrixA[3][2] = B_3;

  NstateMatrixB[3][0] = C_1;
  NstateMatrixA[0][0] = C_2;
  NstateMatrixA[0][1] = C_3;

  NstateMatrixB[3][1] = D_1;
  NstateMatrixA[2][3] = D_2;
  NstateMatrixA[2][1] = D_3;

  NstateMatrixB[2][0] = E_1;
  NstateMatrixB[3][3] = E_2;
  NstateMatrixA[0][2] = E_3;

  NstateMatrixB[1][1] = F_1;
  NstateMatrixA[1][3] = F_2;
  NstateMatrixA[1][1] = F_3;

  NstateMatrixB[1][3] = G_1;
  NstateMatrixA[1][0] = G_2;
  NstateMatrixA[0][3] = G_3;

  NstateMatrixB[3][2] = DP_1;
  NstateMatrixA[2][2] = DP_2;

  refreshDisplay();

}

void clearNumbers() {

  NstateMatrixB[1][0] = 0;
  NstateMatrixB[1][1] = 0;
  NstateMatrixB[1][2] = 0;
  NstateMatrixB[1][3] = 0;
  NstateMatrixB[2][0] = 0;
  NstateMatrixB[3][0] = 0;
  NstateMatrixB[3][1] = 0;
  NstateMatrixB[3][2] = 0;
  NstateMatrixB[3][3] = 0;

  NstateMatrixA[0][0] = 0;
  NstateMatrixA[0][1] = 0;
  NstateMatrixA[0][2] = 0;
  NstateMatrixA[0][3] = 0;
  NstateMatrixA[1][0] = 0;
  NstateMatrixA[1][1] = 0;
  NstateMatrixA[1][2] = 0;
  NstateMatrixA[1][3] = 0;
  NstateMatrixA[2][1] = 0;
  NstateMatrixA[2][2] = 0;
  NstateMatrixA[2][3] = 0;
  NstateMatrixA[3][0] = 0;
  NstateMatrixA[3][1] = 0;
  NstateMatrixA[3][2] = 0;

  refreshDisplay();
}

void clearALL() {

  for (int l = 0; l <= 3; l++) {
    for (int c = 0; c <= 3; c++) {
      NstateMatrixA[l][c] = 0;
      NstateMatrixB[l][c] = 0;
    }
  }
  refreshDisplay();
}

void refreshDisplay() {
  for (int l = 0; l <= 3; l++) {
    for (int c = 0; c <= 3; c++) {
      if (stateMatrixA[l][c] != NstateMatrixA[l][c]) {
        awA.analogWrite (pinsMatrixA [l][c], brightness * NstateMatrixA[l][c]); // br * 0 = 0 or br * 1 = br
      }
      stateMatrixA[l][c] = NstateMatrixA[l][c];
      if (stateMatrixB[l][c] != NstateMatrixB[l][c]) {
        awB.analogWrite (pinsMatrixB [l][c], brightness * NstateMatrixB[l][c]);
      }
      stateMatrixB[l][c] = NstateMatrixB[l][c];
    }
  }
}

void forcedRefreshDisplay() {
  for (int l = 0; l <= 3; l++) {
    for (int c = 0; c <= 3; c++) {
      awA.analogWrite (pinsMatrixA [l][c], brightness * NstateMatrixA[l][c]); // br * 0 = 0 or br * 1 = br
      stateMatrixA[l][c] = NstateMatrixA[l][c];
      awB.analogWrite (pinsMatrixB [l][c], brightness * NstateMatrixB[l][c]);
      stateMatrixB[l][c] = NstateMatrixB[l][c];
    }
  }
}
void litALL() {
  for (int l = 0; l <= 3; l++) {
    for (int c = 0; c <= 3; c++) {
      NstateMatrixA[l][c] = 1;
      NstateMatrixB[l][c] = 1;
    }
  }
  refreshDisplay();
}

void displayNumber (int value) {          // Displays value from 0 to 999

  value = constrain(value, 0, 999);
  int firstDigit  = value / 100;
  int secondDigit = (value / 10) % 10;
  int thirdDigit  = value % 10;

  //clearNumbers();

  displayDIGIT (firstDigit, 1);
  displayDIGIT (secondDigit, 2);
  displayDIGIT (thirdDigit, 3);

}

void LightBar (int value) {

  switch (value) {
    case 0:
      NstateMatrixB[0][1] = 0; //LED BAR 1
      NstateMatrixB[0][0] = 0; //LED BAR 2
      NstateMatrixB[2][3] = 0; //LED BAR 3
      NstateMatrixB[2][2] = 0; //LED BAR 4
      NstateMatrixB[2][1] = 0; //LED BAR 5
      break;
    case 1:
      NstateMatrixB[0][1] = 1; //LED BAR 1
      NstateMatrixB[0][0] = 0; //LED BAR 2
      NstateMatrixB[2][3] = 0; //LED BAR 3
      NstateMatrixB[2][2] = 0; //LED BAR 4
      NstateMatrixB[2][1] = 0; //LED BAR 5
      break;
    case 2:
      NstateMatrixB[0][1] = 1; //LED BAR 1
      NstateMatrixB[0][0] = 1; //LED BAR 2
      NstateMatrixB[2][3] = 0; //LED BAR 3
      NstateMatrixB[2][2] = 0; //LED BAR 4
      NstateMatrixB[2][1] = 0; //LED BAR 5
      break;
    case 3:
      NstateMatrixB[0][1] = 1; //LED BAR 1
      NstateMatrixB[0][0] = 1; //LED BAR 2
      NstateMatrixB[2][3] = 1; //LED BAR 3
      NstateMatrixB[2][2] = 0; //LED BAR 4
      NstateMatrixB[2][1] = 0; //LED BAR 5
      break;
    case 4:
      NstateMatrixB[0][1] = 1; //LED BAR 1
      NstateMatrixB[0][0] = 1; //LED BAR 2
      NstateMatrixB[2][3] = 1; //LED BAR 3
      NstateMatrixB[2][2] = 1; //LED BAR 4
      NstateMatrixB[2][1] = 0; //LED BAR 5
      break;
    case 5:
      NstateMatrixB[0][1] = 1; //LED BAR 1
      NstateMatrixB[0][0] = 1; //LED BAR 2
      NstateMatrixB[2][3] = 1; //LED BAR 3
      NstateMatrixB[2][2] = 1; //LED BAR 4
      NstateMatrixB[2][1] = 1; //LED BAR 5
      break;
  }

  refreshDisplay();
}
