#include <MozziGuts.h>
#include <Oscil.h> // オシレータのテンプレート
#include <tables/sin2048_int8.h> // オシレータ用のサイン波テーブル
//#include <tables/triangle2048_int8.h> //オシレータ用の三角波テーブル

// use: Oscil <table_size, update_rate> oscilName (wavetable)
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA); 
//Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> aTri(TRIANGLE2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // コントロールレートを64に設定

void setup(){
  startMozzi(CONTROL_RATE); //Mozziの初期設化、処理開始
  aSin.setFreq(440) ; //周波数440Hzの設定
}

void updateControl(){
  // 制御処理コードをここに書く
}

int updateAudio(){
  return aSin.next(); //aSinのwavetableが繰り返し読み込まれる
}

void loop(){
  audioHook(); //音を出力するためのバッファ処理
}
