/**
 * @file classJRTRelayBoard.ino
 * @brief JRTで使用する新中継基板のプログラム
 * @author ka-futatsui
 * @date 2025/11/10 
 */

#include "classJRTRelayBoard.h" // 修正後のクラス名に合わせて適宜変更してください


/**
 * @brief classJRTRelayBoardのインスタンスを取得する
 * @detail C++11以降の静的ローカル変数によるスレッドセーフなシングルトン実装
 */
classJRTRelayBoard& classJRTRelayBoard::getInstance(void)
{
    // 関数が最初に呼び出されたときに一度だけ初期化される
    // プログラム終了時に自動的に破棄されるため、メモリリークの心配がない
    static classJRTRelayBoard instance; 
    return instance;
}

/**
 * @brief classJRTRelayBoardのコンストラクタ
 * @detail ピンの初期設定をここで行う
 */
classJRTRelayBoard::classJRTRelayBoard()
{
    // ピンの初期設定
    pinMode(2, OUTPUT);     // デジタルピン2をOutput指定
}

/**
 * @brief LEDチカチカ（Lチカ）を実行する
 */
void classJRTRelayBoard::LedFlashing(void)
{
    digitalWrite(2, HIGH);  // LED ON (ピン2：HIGH出力)
    delay(500);             // 100ms wait
    digitalWrite(2, LOW);   // LED OFF (ピン2：LOW出力)
    delay(1000);             // 100ms wait
}