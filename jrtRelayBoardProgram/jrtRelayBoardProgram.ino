#include "classJRTRelayBoard.h"  /// 必ずこのコードを書く]


static classJRTRelayBoard *spClassJRTRelayBoardInstance;  /// 必ずこのコードを書く

void setup() {
  spClassJRTRelayBoardInstance = &classJRTRelayBoard::getInstance();  /// 必ずsetup関数でこのコードを書く
}

void loop() {
  spClassJRTRelayBoardInstance->digitalInputGetStatus();
  spClassJRTRelayBoardInstance->analogInputGetStatus();

  spClassJRTRelayBoardInstance->sendInputStatus();
}
