#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//-----CZUJNIKI TEMP-----
#define T1 A0
#define T2 A1
#define T3 A2
#define T4 A3
#define T5 A4
#define T6 A5
#define T7 A6
#define T8 A7

//-----TablicaTEMP----
int tabP[8] = {0,0,0,0,11,11,11,11};
int tabR[8] = {0,1,2,3,0,1,2,3};
//-----BUZZER-----
#define BUZZ 6

//-----RESET ALARMU-----
//#define BUTTON 10

float tempAlarm = 40.00;

//-----RYSUNKI-----
byte degree[8] =
  {
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte arrow[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};

byte arrow2[] = {
  B00000,
  B01100,
  B00110,
  B11111,
  B11111,
  B00110,
  B01100,
  B00000
};

void setup() {
  Serial.begin(9800);
  lcd.begin (20,4);
  lcd.createChar(1, degree);
  lcd.createChar(2, arrow);
  lcd.createChar(3, arrow2);
  
  pinMode(BUZZ, OUTPUT);
//  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  //if (BUTTON, LOW){
 //   digitalWrite(BUZZ, LOW);
 // }
  
  float tab[8];
  tab[0] = ((analogRead(T1) * 5.0) / 1024.0) * 100;
  tab[1] = ((analogRead(T2) * 5.0) / 1024.0) * 100;
  tab[2] = ((analogRead(T3) * 5.0) / 1024.0) * 100;
  tab[3] = ((analogRead(T4) * 5.0) / 1024.0) * 100;
  tab[4] = ((analogRead(T5) * 5.0) / 1024.0) * 100;
  tab[5] = ((analogRead(T6) * 5.0) / 1024.0) * 100;
  tab[6] = ((analogRead(T7) * 5.0) / 1024.0) * 100;
  tab[7] = ((analogRead(T8) * 5.0) / 1024.0) * 100;

  printTemp(0, 0, tab[0], "1. ");
  printTemp(0, 1, tab[1], "2. ");
  printTemp(0, 2, tab[2], "3. ");
  printTemp(0, 3, tab[3], "4. ");
  printTemp(11, 0, tab[4], "5. ");
  printTemp(11, 1, tab[5], "6. ");
  printTemp(11, 2, tab[6], "7. ");
  printTemp(11, 3, tab[7], "8. ");

 // bool riseAlarm = false;
 // size_t length = sizeof(tab) / sizeof(tab[0]);
  for (int i=0; i < 8; i++)
        {
          if (tab[i] > tempAlarm)
          {
            RizeAlarm(tabP[i],tabR[i]);
           }
        }
 
   delay(1000);     

}

void printTemp(int point, int row, float temp, String ind)
  {  
  lcd.setCursor(point, row);
  lcd.print(ind);
  lcd.print(temp);
  lcd.write(1);
  }   
  void RizeAlarm(int point, int row)
  {  
    digitalWrite(BUZZ, HIGH);
    lcd.setCursor(point, row);
    lcd.print("  ");
    delay(200);
    digitalWrite(BUZZ, LOW);
    lcd.setCursor(point, row);
    lcd.write(2);
    lcd.write(3);
    delay(200);
  } 
