# 概要
- このプログラムは改良版中継基板に設置するESP32に書き込むためのプログラムである。

# プログラム構成
- JRT_relayBoard_Program_main.ino
  - 後述するclassJRTRelayBoardを呼び出して実際の処理内容を記述するためのプログラム
  - プログラムの処理内容をいじる場合はこのファイルのプログラムを触る
- classJRTRelayBoard.h
  - classJRTRelayBoardのクラスの構成について定義しているファイル
  - classJRTRelayBoardはシングルトンクラスのため扱いには注意
    - JRT_relayBoard_Program_main.inoではインスタンスを作らないようにするなど
- classJRTRelayBoard.ino
  - classJRTRelayBoardの実際の処理内容を記述しているファイル