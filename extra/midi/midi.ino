// arduino unoのUSB部分についている別のマイコン 16u2 に dualMoco.hexを書きこみます。
// mac: https://qiita.com/tadfmac/items/1ce0689ed94a92cbded3
// windows: http://www.dm9records.com/index.php/tips/arduino/moco/

// スケッチー>ライブラリをインクルード->ライブラリを管理ー>”MIDI Library”
// を選択してインストールしてください。

#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

MIDI_CREATE_DEFAULT_INSTANCE(); // USB MIDIの使用を宣言

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

void setup() {
     MIDI.begin(1);                // MIDI Channelを1に設定
     MIDI.turnThruOff();

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
}

void loop() {
  // MIDIデータを受信
   if (MIDI.read()) {
      const auto type = MIDI.getType();
      const auto data1 = MIDI.getData1();
      const auto data2 = MIDI.getData2();
      const auto channel = MIDI.getChannel();

      switch(type) {
      case midi::NoteOn:
        OCR2A = data1 * 2; // note番号 0~127を電圧 0~255に変換してVCOへ
        break;
      case midi::NoteOff:
        OCR2A = 0; // 電圧を0Vに
        break;
      default:
        break;
      }
   }
}
