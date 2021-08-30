#include <fDigitsSegtPin.h>
fDigitsSegtPin Display(A1, 0, 13, 8, 12, A6, 1, A4, A5, 11, A3, A2);
float Rr = 0;
float R = 0;
int pinA = 2; // Пины прерываний
int pinB = 3; // Пины прерываний

volatile long pause    = 50;  // Пауза для борьбы с дребезгом
volatile long lastTurn = 0;   // Переменная для хранения времени последнего изменения

volatile int T_ust = 0;       // Счетчик оборотов
int actualT_ust    = 0;       // Временная переменная определяющая изменение основного счетчика

volatile int state = 0;       // Статус одного шага - от 0 до 4 в одну сторону, от 0 до -4 - в другую

volatile int pinAValue = 0;   // Переменные хранящие состояние пина, для экономии времени
volatile int pinBValue = 0;   // Переменные хранящие состояние пина, для экономии времени

void A()
{
  if (micros() - lastTurn < pause) return;  // Если с момента последнего изменения состояния не прошло
  // достаточно времени - выходим из прерывания
  pinAValue = digitalRead(pinA);            // Получаем состояние пинов A и B
  pinBValue = digitalRead(pinB);

  cli();    // Запрещаем обработку прерываний, чтобы не отвлекаться
  if (state == 0  && !pinAValue &&  pinBValue || state == 2  && pinAValue && !pinBValue) {
    state += 1; // Если выполняется условие, наращиваем переменную state
    lastTurn = micros();
  }
  if (state == -1 && !pinAValue && !pinBValue || state == -3 && pinAValue &&  pinBValue) {
    state -= 1; // Если выполняется условие, наращиваем в минус переменную state
    lastTurn = micros();
  }
  setT_ust(state); // Проверяем не было ли полного шага из 4 изменений сигналов (2 импульсов)
  sei(); // Разрешаем обработку прерываний

  if (pinAValue && pinBValue && state != 0) state = 0; // Если что-то пошло не так, возвращаем статус в исходное состояние
}
void B()
{
  if (micros() - lastTurn < pause) return;
  pinAValue = digitalRead(pinA);
  pinBValue = digitalRead(pinB);

  cli();
  if (state == 1 && !pinAValue && !pinBValue || state == 3 && pinAValue && pinBValue) {
    state += 1; // Если выполняется условие, наращиваем переменную state
    lastTurn = micros();
  }
  if (state == 0 && pinAValue && !pinBValue || state == -2 && !pinAValue && pinBValue) {
    state -= 1; // Если выполняется условие, наращиваем в минус переменную state
    lastTurn = micros();
  }
  setT_ust(state); // Проверяем не было ли полного шага из 4 изменений сигналов (2 импульсов)
  sei();

  if (pinAValue && pinBValue && state != 0) state = 0; // Если что-то пошло не так, возвращаем статус в исходное состояние
}

void setT_ust(int state)
{ // Устанавливаем значение счетчика
  if (state == 4 || state == -4)
  { // Если переменная state приняла заданное значение приращения
    T_ust += (int)(state / 4);      // Увеличиваем/уменьшаем счетчик
    lastTurn = micros();            // Запоминаем последнее изменение
  }
}

void setup()
{
  pinMode(pinA, INPUT);           // Пины в режим приема INPUT
  pinMode(pinB, INPUT);           // Пины в режим приема INPUT

  attachInterrupt(0, A, CHANGE);  // Настраиваем обработчик прерываний по изменению сигнала
  attachInterrupt(1, B, CHANGE);  // Настраиваем обработчик прерываний по изменению сигнала


  Display.begin();
  Display.doPrint_lastDot = 1;
  Display.doPrint_firstZero = 0;
  Display.doReport_overRange = 0;

  TCCR1A = TCCR1A & 0xe0 | 1;
  TCCR1B = TCCR1B & 0xe0 | 0x09;

  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A3, OUTPUT);
  //pinMode(A0, INPUT);


}

void loop()
{
  Rr = analogRead(A0);
  //100/(1023*Rr - 1);
  R = (Rr*100/(1023-Rr));
 
   //Rr = Rr*0.0049;
  analogWrite(10, Rr/(0.0049*3.99609375));
  // digitalWrite(9,HIGH);
  // digitalWrite(A3,HIGH);
  // Serial.println(Rr);
  Display.print(R);
}
