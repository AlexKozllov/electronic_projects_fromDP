#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>                       // Импортируем бмблиотеку

int Address_Value_1 = 0;                          // Переменная для хранения адреса
byte EValue_1; 
int Address_Value_2 = 1;                          // Переменная для хранения адреса
byte EValue_2; 
int Address_Value_3 = 2;                          // Переменная для хранения адреса
byte EValue_3; 
int Address_Value_4 = 3;                          // Переменная для хранения адреса
byte EValue_4; 
int Address_Value_5= 4;                          // Переменная для хранения адреса
byte EValue_5; 
int Address_dV_1 = 5;                          // Переменная для хранения адреса
byte EdV_1; 
int Address_dV_2 = 6;                          // Переменная для хранения адреса
byte EdV_2; 
int Address_dV_3 = 7;                          // Переменная для хранения адреса
byte EdV_3; 
int Address_dV_4 = 8;                          // Переменная для хранения адреса
byte EdV_4; 
int Address_dV_5 = 9;                          // Переменная для хранения адреса
byte EdV_5; 

LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей

int BATTON_SET=A0;
int BATTON_MORE=A1;
int BATTON_LESS=A2;
int BATTON_OK=A3;
int SET=0;
int MORE=0;
int LESS=0;
int OK=0;
int Value_1;
int ValueM_1;
int Value_2;
int ValueM_2;
int Value_3;
int ValueM_3;
int Value_4;
int ValueM_4;
int Value_5;
int ValueM_5;
int dV_1;
int dV_2;
int dV_3;
int dV_4;
int dV_5;
unsigned long last_time;

void setup()
{
  lcd.init();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
 // pinMode(13, OUTPUT);
  // ШИМ 8 разрядов, 32.25 кГц
  TCCR0A = TCCR0A & 0b11111000  | 1;
  TCCR0B = TCCR0B & 0b11111000  | 0x01; 
  TCCR1A = TCCR1A & 0xe0 | 1;
  TCCR1B = TCCR1B & 0xe0 | 0x01; 
  TCCR2A = TCCR2A & 0xe0 | 1;
  TCCR2B = TCCR2B & 0xe0 | 0x01;  

  
}
void loop()
{ 
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
 // lcd.print("Channel #1");
  //lcd.setCursor(0, 1);
 // Serial.begin(9600);
 // lcd.print("Value ");
  
 // while(true)

  BATTON_SET = !digitalRead(A0);
  BATTON_MORE = !digitalRead(A1);
  BATTON_LESS = !digitalRead(A2);
  BATTON_OK = !digitalRead(A3);

 

if (BATTON_SET == 1)
  { 
    if (millis()-last_time>10000)
   {
      last_time=millis();
      SET=SET+1;
    }
  }

if (BATTON_MORE == 1)
  { 
    if (millis()-last_time>10000)
   {
      last_time=millis();
      MORE=1;
    }
  }
if (BATTON_MORE != 1)
 {MORE=0;
  }
  
if (BATTON_LESS == 1)
  { 
    if (millis()-last_time>10000)
   {
      last_time=millis();
      LESS=1;
    }
    else 
    {LESS=0;}
  }
if (BATTON_LESS != 1)
 {LESS=0;
  }
  
if (BATTON_OK == 1)
  { 
    if (millis()-last_time>10000)
   {
      last_time=millis();
      OK=1;
    }
    else 
    {OK=0;}
  }
if (BATTON_OK != 1)
 {OK=0;
  }


  
if (SET>10)
  {
    SET=0;
  }
if (SET == 1)
  {
   // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Group #1");
    lcd.setCursor(0, 1);
    lcd.print("Value ");
    lcd.setCursor(6, 1);
    lcd.print(ValueM_1);
  }
  if (SET==2)
  {lcd.setCursor(0, 0);
    lcd.print("Group #1");
    lcd.setCursor(0, 1);
    lcd.print("dV_1 ");
    lcd.setCursor(5, 1);
    lcd.print(dV_1);
    }
  if (SET == 3)
  {
   // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Group #2");
    lcd.setCursor(0, 1);
    lcd.print("Value ");
    lcd.setCursor(6, 1);
    lcd.print(ValueM_2);
  }
  if (SET==4)
  {lcd.setCursor(0, 0);
    lcd.print("Group #2");
    lcd.setCursor(0, 1);
    lcd.print("dV_2 ");
    lcd.setCursor(5, 1);
    lcd.print(dV_2);
    }
  if (SET == 5)
  {
   // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Group #3");
    lcd.setCursor(0, 1);
    lcd.print("Value ");
    lcd.setCursor(6, 1);
    lcd.print(ValueM_3);
  }
  if (SET==6)
  {lcd.setCursor(0, 0);
    lcd.print("Group #3");
    lcd.setCursor(0, 1);
    lcd.print("dV_3 ");
    lcd.setCursor(5, 1);
    lcd.print(dV_3);
    }
  if (SET == 7)
  {
   // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Group #4");
    lcd.setCursor(0, 1);
    lcd.print("Value ");
    lcd.setCursor(6, 1);
    lcd.print(ValueM_4);
  }
  if (SET==8)
  {lcd.setCursor(0, 0);
    lcd.print("Group #4");
    lcd.setCursor(0, 1);
    lcd.print("dV_4 ");
    lcd.setCursor(5, 1);
    lcd.print(dV_4);
    }
  if (SET == 9)
  {
   // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Group #5");
    lcd.setCursor(0, 1);
    lcd.print("Value ");
    lcd.setCursor(6, 1);
    lcd.print(ValueM_5);
  }
  if (SET==10)
  {lcd.setCursor(0, 0);
    lcd.print("Group #5");
    lcd.setCursor(0, 1);
    lcd.print("dV_5 ");
    lcd.setCursor(5, 1);
    lcd.print(dV_5);
    }
  if (SET==0)
  {
    lcd.setCursor(0, 0);
    lcd.print("G:");
    lcd.setCursor(3, 0);
    lcd.print("1");
    lcd.setCursor(6, 0);
    lcd.print("2");
    lcd.setCursor(9, 0);
    lcd.print("3");
    lcd.setCursor(12, 0);
    lcd.print("4");
    lcd.setCursor(15, 0);
    lcd.print("5");
    lcd.setCursor(0, 1);
    lcd.print("V:");
    lcd.setCursor(3, 1);
    lcd.print(ValueM_1);
    lcd.setCursor(6, 1);
    lcd.print(ValueM_2);
    lcd.setCursor(9, 1);
    lcd.print(ValueM_3);
    lcd.setCursor(12, 1);
    lcd.print(ValueM_4);
    lcd.setCursor(15, 1);
    lcd.print(ValueM_5);

    
   }

   if (MORE==1 && SET==1)
   {ValueM_1=Value_1+1;}
   if (MORE==1 && SET==2)
   {dV_1=dV_1+1;}
   if (dV_1>10)
   {dV_1=10;}
   if ((Value_1)>=ValueM_1)
   {Value_1=ValueM_1;}
   if ((Value_1)<=ValueM_1)
   {Value_1=Value_1+dV_1;}
   
   if (MORE==1 && SET==3)
   {Value_2=Value_2+dV_2;}
   if (MORE==1 && SET==4)
   {dV_2=dV_2+1;}
   if (dV_2>10)
   {dV_1=10;}
   if ((Value_2+dV_2)>255)
   {Value_2=255;}
   
   if (MORE==1 && SET==5)
   {Value_3=Value_3+dV_3;}
   if (MORE==1 && SET==6)
   {dV_3=dV_3+1;}
   if (dV_3>10)
   {dV_3=10;}
   if ((Value_3+dV_3)>255)
   {Value_3=255;}
   
   if (MORE==1 && SET==7)
   {Value_4=Value_4+dV_4;}
   if (MORE==1 && SET==8)
   {dV_4=dV_4+1;}
   if (dV_4>10)
   {dV_4=10;}
   if ((Value_4+dV_4)>255)
   {Value_4=255;}
   
   if (MORE==1 && SET==9)
   {Value_5=Value_5+dV_5;}
   if (MORE==1 && SET==10)
   {dV_5=dV_5+1;}
   if (dV_5>10)
   {dV_5=10;}
   if ((Value_5+dV_5)>255)
   {Value_5=255;}


   if (OK==1)
   {SET=0;
   EValue_1=Value_1*2.55;
   EValue_2=Value_2*2.55;
   EValue_3=Value_3*2.55;
   EValue_4=Value_4*2.55;
   EValue_5=Value_5*2.55;
   EdV_1=dV_1*2.55;
   EdV_2=dV_2*2.55;
   EdV_3=dV_3*2.55;
   EdV_4=dV_4*2.55;
   EdV_5=dV_5*2.55;
   EEPROM.update(Address_Value_1,EValue_1); 
   EEPROM.update(Address_Value_2,EValue_2); 
   EEPROM.update(Address_Value_3,EValue_3); 
   EEPROM.update(Address_Value_4,EValue_4); 
   EEPROM.update(Address_Value_5,EValue_5); 
   EEPROM.update(Address_dV_1,EdV_1); 
   EEPROM.update(Address_dV_2,EdV_2); 
   EEPROM.update(Address_dV_3,EdV_3); 
   EEPROM.update(Address_dV_4,EdV_4); 
   EEPROM.update(Address_dV_5,EdV_5);  
   }

  if (LESS==1)
  {
  dV_1=EEPROM.read(Address_dV_1)/2.55;
  dV_2=EEPROM.read(Address_dV_2)/2.55;
  dV_3=EEPROM.read(Address_dV_3)/2.55;
  dV_4=EEPROM.read(Address_dV_4)/2.55;
  dV_5=EEPROM.read(Address_dV_5)/2.55;
  Value_1=EEPROM.read(Address_Value_1)/2.55;
  Value_2=EEPROM.read(Address_Value_2)/2.55;
  Value_3=EEPROM.read(Address_Value_3)/2.55;
  Value_4=EEPROM.read(Address_Value_4)/2.55;
  Value_5=EEPROM.read(Address_Value_5)/2.55;
    }
   
  
//  Serial.print(a);
//  delay(10);
 // analogWrite(3, 20); // на выводе 9 ШИМ=10%
 // analogWrite(5, 20); // на выводе 9 ШИМ=10%
 // analogWrite(6, 20); // на выводе 9 ШИМ=10%
 // analogWrite(9, 20); // на выводе 9 ШИМ=10%
 // analogWrite(10, 20); // на выводе 9 ШИМ=10%
 // analogWrite(11, 20); // на выводе 9 ШИМ=10%
  
//}
}
