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
  cbi (TIMSK0,TOIE0);      
}

void loop() {
   // 一定の時間ごとにランダムな値を作り、VCOを動かす
   auto output = random(255);
   OCR2A = output;

   // 一定時間のウェイト(TimerOneを使ってもよい)
   volatile uint32_t wait = (uint32_t)analogRead(1) * (uint32_t)500; 
   for (uint32_t i = 0; i < wait; ++i) {
         __asm__("nop\n\t"); 
   }
}
