# Copilot / AI エージェント向けの短い操作メモ

目的: このファイルはリポジトリ固有の設計・ワークフロー・実装パターンを素早く把握し、AIコーディングエージェントが安全に生産的に作業できるよう補助します。

- **主要目的**: ESP32 ベースのリレー/入力ボード用ファームウェア。入力（デジタル/アナログ）を定期的にパッケージして `Serial2` 経由で送信する。

- **重要ファイル**:
  - `classJRTRelayBoard.h` : プロジェクトの中心データ構造 `ControllerCommandData` とピン定義、設定値（例: `msc_u64SendcycleTime`）を定義。
  - `classJRTRelayBoard.ino` : シングルトン実装、ピン初期化、入力読み取り・送信ロジック。
  - `jrtRelayBoardProgram.ino` : `setup` / `loop` を持つ Arduino エントリポイント。`classJRTRelayBoard::getInstance()` を取得してループ内で API を呼ぶ。
  - `ReadMe.md` : プロジェクト概要（文字化けのため注意。コードが一次情報）。

- **アーキテクチャ（短く）**:
  - 単一インスタンス（Singleton） `classJRTRelayBoard` が全てのデバイス制御を担当。
  - センサ入力 -> `ControllerCommandData` に変換 -> `Serial2.write` でバイナリ送信。
  - ネットワーク（WiFi/Bluetooth）は無効化される（`WiFi.mode(WIFI_OFF)` / `btStop()`）。

- **実装パターンと命名規則**:
  - 定数ピン名は `msc_u8...`（例: `msc_u8AnalogInput1`）。型修飾（`u8`）が命名に含まれる。
  - メンバ変数は `m_sStruct...` / `u64LastSendTime` のように接頭辞付き。
  - シングルトンは `static getInstance()` + private コンストラクタ + コピー禁止パターン。
  - デバッグは `Serial`（USB）に `println`、データ送信は `Serial2` を使用。

- **動作・タイミング**:
  - 送信周期は `msc_u64SendcycleTime` による（現在 `300` ミリ秒）。
  - アナログ値は ESP32 の 12-bit ADC (0-4095) を 0-255 にスケーリングしている（例: `(analogRead(...) * 255 / 4095)）。`

- **注意事項（エージェントが注意すべき発見可能な問題）**:
  - `ControllerCommandData.u8AnalogSignalPacket` は配列長 `5` だが、`classJRTRelayBoard.ino` の `analogInputGetStatus()` で `u8AnalogSignalPacket[5]` に書き込みがある（配列越えの可能性）。2番目の要素（index 2）への書き込みが抜けている。変更を加える場合はまずここを確認すること。
  - `digitalInputGetStatus()` のビット組み立て式に乗算の順序ミスと思われる箇所がある（`* 64 * !digitalRead(msc_u8DigitalInput8) * 128` のような箇所）。ビットシフト/加算の意図をコード上で明確に修正する必要がある。
  - ReadMe は文字化けしているため、設計意図はソースが信頼できる一次情報。

- **ビルド / 実機フロー（発見可能な情報に基づく）**:
  - ターゲットは ESP32（`WiFi.h`, `btStop()` 使用、12-bit ADC スケール）。
  - IDE: Arduino IDE か PlatformIO が使える。PlatformIO での簡易手順例（エージェントが変更を出す際に README に追加する場合の参考）:
    - `pio init --board esp32dev`（既存の環境に合わせてボードを選択）
    - プロジェクトをビルド・アップロードする（PlatformIO の `Build` / `Upload` を使用）。
  - 実行時デバッグ: USB シリアル（`Serial`）を 115200 で監視。外部コントローラは `Serial2` の受信を期待している。

- **変更・拡張するときのヒント**:
  - 低レベルデータ列（`ControllerCommandData`）のフォーマットを変える場合は、`classJRTRelayBoard.h` の構造体と `Serial2.write(...)` の双方を同時に変更し、互換性を保つかバージョンを追加する。
  - ピンの追加・再配置は `classJRTRelayBoard.h` の `msc_u8...` 定数を更新し、初期化コード（`pinMode`）を `classJRTRelayBoard.ino` に反映する。

---
更新要求: この内容のどの部分を詳しく追加すべきか教えてください（PlatformIO 設定、実機テスト手順、または既知のバグ修正案など）。
