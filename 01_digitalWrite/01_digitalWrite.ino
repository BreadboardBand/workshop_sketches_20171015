// step() {}関数内は、最初の一度だけ呼び出される
void setup() {
  // setup() {}内は、基本的には変数の初期化や入出力ピンの設定などを行う
 
  pinMode(9, OUTPUT);     // Arduinoの9番ピンをデジタル出力に設定
}

// loop(){}関数内は、実行後に繰り返し呼び出される関数
void loop() {
  digitalWrite(9, HIGH);  // LEDを光らせる(出力電圧を5V(HIGH)にする)
  delay(1000);            // 1秒(1000ms)待機
  digitalWrite(9, LOW);   // LEDを消す (出力電圧を0V(LOW)にする)
  delay(1000);            // 1秒(1000ms)待機
}
