#include <fDigitsSegtPin.h>
#include "GyverPID.h"
// (коэффициент П, коэффициент И, коэффициент Д, период дискретизации dt (мс) )
GyverPID regulator(0.1, 0.05, 0.01, 10);
// или так:
//GyverPID regulator(0.1, 0.05, 0.01); // можно П, И, Д, без dt, dt будет по умолч. 100 мс
#define CLK 2
#define DT 3
#define SW 4
#include "GyverEncoder.h"
Encoder enc1(CLK, DT, SW);


fDigitsSegtPin Display(A1, 0, 13, 8, 12, A6, 1, A4, A5, 11, A3, A2);
float Rr = 0;
float R = 0;
float T_aut = 0;
float T_ust = 300;
unsigned long time;
unsigned long Pre_time;
unsigned long t_pre;
unsigned long at_pre;
int Button = 0;
int T_ust_pre=0;
int Add=0;



void setup()
{
  //Serial.begin(9600);
  attachInterrupt(0, isr, CHANGE);    // прерывание на 2 пине! CLK у энка



   regulator.setDirection(NORMAL); // направление регулирования (NORMAL/REVERSE). ПО УМОЛЧАНИЮ СТОИТ NORMAL
   regulator.setLimits(0, 255);    // пределы (ставим для 8 битного ШИМ). ПО УМОЛЧАНИЮ СТОЯТ 0 И 255
   
   regulator.tune(0.1, 0.1, 0.1);  // изменить коэффициенты можно в любое время

  Display.begin();
  Display.doPrint_lastDot = 1;
  Display.doPrint_firstZero = 0;
  Display.doReport_overRange = 0;

  TCCR1A = TCCR1A & 0xe0 | 1;
  TCCR1B = TCCR1B & 0xe0 | 0x09;

  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A3, OUTPUT);


}

void isr() {
  enc1.tick();  // отработка в прерывании
}

void loop()
{
  Rr = analogRead(A0);


  //100/(1023*Rr - 1);
  R = (Rr * 100 / (1023 - Rr));

  { //Описание кривой Т(R)
    if (R > 0 && R <= 80.3) {
      T_aut = 5.846 * R - 275;
      //Display.print(T_aut);
    }
    if (R > 80.3 && R <= 120.4) {
      T_aut = 6.09 * R - 290.2;
      // Display.print(T_aut);
    }
    if (R > 120.4 && R < 150) {
      T_aut = 6.78 * R - 370;
      //Display.print(T_aut);
    }
    if (R > 150) {
      //Display.print(000);
    }
  }

  enc1.tick();  // отработка
  if (enc1.isPress()) {
    Button++;
  }
 // else Button = 0;

if (enc1.isRight()) { // если был поворот
    T_ust++;
  }
if (enc1.isFastR()) { // если был поворот
    T_ust=T_ust+5;
  }
  
if (enc1.isLeft()) { // если был поворот
    T_ust--;
  }
if (enc1.isFastL()) { // если был поворот
    T_ust=T_ust-5;
  }












if (Button==1){
//

  if (T_ust!=T_ust_pre){
    if ((millis()-t_pre)<5000){
      Display.print(T_ust);
    
      }
      else{
       t_pre=millis();
       T_ust_pre=T_ust;
      }
  
  }
  else if (t_pre==millis() && T_ust_pre==T_ust) {
     t_pre=millis();
     }
  else {
      Display.print(T_aut);
  
       }

  }
else{
  Display.print(000);
  Button=0;
}










//if (Button==0){
//  Display.print(T_aut);
//  //Button==0;
//  }
//if (Button==1){
//  Display.print(T_ust);
//  }

//if (Button>=2){
//  Display.print(T_aut);
//  Button=0;
//}
 

  //if (enc1.isRightH()) Serial.println("Right holded"); // если было удержание + поворот
  //if (enc1.isLeftH()) Serial.println("Left holded");

  // analogWrite(10, Rr/(0.0049*3.99609375));
  // digitalWrite(9, HIGH);
  //  digitalWrite(A3,HIGH);
  // Serial.println(Rr);
regulator.setpoint = T_ust;        // сообщаем регулятору температуру, которую он должен поддерживать
  //int T_aut;                 // читаем с датчика температуру
    regulator.input = T_aut;   // сообщаем регулятору текущую температуру
  // getResultTimer возвращает значение для управляющего устройства
  // (после вызова можно получать это значение как regulator.output)
  // обновление происходит по встроенному таймеру на millis()
       analogWrite(10, regulator.getResultTimer());  // отправляем на мосфет
  // .getResultTimer() по сути возвращает regulator.output








}
