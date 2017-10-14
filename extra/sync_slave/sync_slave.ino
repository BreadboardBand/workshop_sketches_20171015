#include <TimerOne.h>

// 同期信号を入力するピン (ピン2なります)
#define SYNC_IN_PIN 2

// ピン2からの割りこみをうけたい
#define INTERRUPT_CH 0

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

// 同期信号が来たらこの関数が実行されます。
// シーケンサーのサンプルの loop 内とほぼ同じです。(delayがない)
void syncSignalReceived()
{
    if (step++ >= MAXSTEP) {
      step = 0;
    }

   auto output = sequencerSteps[step];
   OCR2A = output;
}

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

  pinMode(SYNC_IN_PIN, INPUT_PULLUP);
  attachInterrupt(INTERRUPT_CH, RISING, syncSignalReceived); // 割り込みの登録(同期信号が来たら syncSignalReceived()が呼ばれます)
}

void loop() {
  // loopでは何もしません。
}
