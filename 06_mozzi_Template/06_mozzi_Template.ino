#include <MozziGuts.h>        // Mozzi用ライブラリ
#define CONTROL_RATE 64   //コントロールレートの定義(64がデフォルト)

void setup() {
  startMozzi(CONTROL_RATE);//Mozziの初期設化、処理開始
}

void updateControl() {
  // 制御処理コードをここに書く
}

int updateAudio() {
  // オーディオ処理コードをここに書く
  return 0;
}

void loop() {
  audioHook(); //音を出力するためのバッファ処理
}
