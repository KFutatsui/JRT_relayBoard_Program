#include "classJRTRelayBoard.h"

static classJRTRelayBoard *spClassJRTRelayBoardInstance;

void setup() {
  spClassJRTRelayBoardInstance = &classJRTRelayBoard::getInstance();
}

void loop() {
  spClassJRTRelayBoardInstance->LedFlashing();  
