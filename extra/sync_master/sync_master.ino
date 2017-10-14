#include <TimerOne.h>

// 同期信号を出力するピン
#define SYNC_OUT 4

// シーケンサーのステップ数
#define MAXSTEP (16)

// シーケンサーの出力したい値をならべます。(0 ~ 255)
const uint8_t sequencerSteps[MAXSTEP] = {  
  10, 30, 80, 40,
  10, 80, 30, 20,
   0, 30, 80, 50,
 200, 40, 100, 0,
};

// いまどのステップか?
int step = 0;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
void setup() {
  
 // Timer2 PWM を高速にする
  cbi (TCCR2A, COM2A0);
  sbi (TCCR2A, COM2A1);
  sbi (TCCR2A, WGM20);
  sbi (TCCR2A, WGM21);
  cbi (TCCR2B, WGM22);
  sbi (TCCR2B, CS20);
  cbi (TCCR2B, CS21);
  cbi (TCCR2B, CS22);
  sbi(DDRB,3);    

  pinMode(SYNC_OUT, OUTPUT);
}

void loop() {

   auto output = sequencerSteps[step];
   OCR2A = output;

   digitalWrite(SYNC_OUT, HIGH); //同期信号(HIGH)を出す
   delay(100);
   digitalWrite(SYNC_OUT, LOW); //同期信号を元に戻す
   
   // テンポはA1のノブで操作します。
   delay(analogRead(1));
   
   if (step++ >= MAXSTEP) {
    step = 0;
   }
}
