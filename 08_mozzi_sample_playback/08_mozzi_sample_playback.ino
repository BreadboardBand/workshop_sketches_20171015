#include <MozziGuts.h>
#include <Sample.h>

// 使用するサンプルのファイルをここに並べて書きます。
#include "Hat_int8.h"
#include "Kick_int8.h"
#include "OH_int8.h"
#include "Snare_int8.h"


// mozziの制御スピードを決めます。
// 64サンプルに1回動きます。
#define CONTROL_RATE 64

// 使用するサンプルの実体を作ります。
// Kick_NUM_CELLSなどの値はそれぞれの .hファイルに書かれています。
Sample <Kick_NUM_CELLS, AUDIO_RATE> kick(Kick_DATA);
Sample <Hat_NUM_CELLS, AUDIO_RATE> hat(Hat_DATA);
Sample <Snare_NUM_CELLS, AUDIO_RATE> snare(Snare_DATA);
Sample <OH_NUM_CELLS, AUDIO_RATE> oh(OH_DATA);

// スイッチの設定です。Mozzi Shieldでは2, 3, 4, 5のピンにスイッチがついています。
enum {
  NUMBER_OF_BUTTONS = 4,
  Open_Hihat = 2,
  Close_Hihat = 3,
  Snare = 4,
  Kick = 5,
  
  ONOFF_KICK = 0,
  ONOFF_SNARE = 1,
  ONOFF_CH = 2,
  ONOFF_OH = 3,
};

// スイッチのピンを指定します。
static const uint8_t switchPins[NUMBER_OF_BUTTONS] = {
  Open_Hihat,
  Close_Hihat,
  Snare,
  Kick
};

// 「1回Offにしたら再生できる」を実現するためにOn/Offを覚えておくところ
bool canPlayback[NUMBER_OF_BUTTONS] = { true, true, true, true}; 


void setup()
{
  // mozziの開始
  startMozzi(CONTROL_RATE);

  // サンプルの再生スピードを設定します。
  kick.setFreq((float) Kick_SAMPLERATE / (float)Kick_NUM_CELLS);
  hat.setFreq((float) Hat_SAMPLERATE / (float)Hat_NUM_CELLS);
  snare.setFreq((float) Snare_SAMPLERATE / (float)Snare_NUM_CELLS);
  oh.setFreq((float) OH_SAMPLERATE / (float)OH_NUM_CELLS);
  
}

void updateControl()
{
  // スイッチを読み、Onになっていたらサンプルを再生します。1回Offになったら再度再生できます。

  // Kick
  if (digitalRead(Kick)) { //スイッチを読んで、Onだったら、
    if (canPlayback[ONOFF_KICK]) { //押しっぱなしではない場合は
      canPlayback[ONOFF_KICK] = false; // 押しっぱなしで何度も再生されないようにして
      kick.start(); // サンプルを再生する
    }
  } else { // スイッチがオフになったら、スイッチを押すと再生できるようにする。
    canPlayback[ONOFF_KICK] = true;
  }
  
  
  // Snare
  if (digitalRead(Snare)) { 
    if (canPlayback[ONOFF_SNARE]) {
      canPlayback[ONOFF_SNARE] = false; 
      snare.start();
    }
  } else {
    canPlayback[ONOFF_SNARE] = true;
  }
  
  // CH
  if (digitalRead(Close_Hihat)) { 
    if (canPlayback[ONOFF_CH]) {
      canPlayback[ONOFF_CH] = false; 
      hat.start();
    }
  } else {
    canPlayback[ONOFF_CH] = true;
  }
  
  // OH
  if (digitalRead(Open_Hihat)) { 
    if (canPlayback[ONOFF_OH]) {
      canPlayback[ONOFF_OH] = false; 
      oh.start();
    }
  } else {
    canPlayback[ONOFF_OH] = true;
  }
}

int updateAudio()
{
  return (int) kick.next() + hat.next() + snare.next() + oh.next();
}

void loop()
{
  audioHook();
}

