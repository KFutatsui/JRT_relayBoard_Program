#ifndef JRTRELAYBOARDLIB_H_
#define JRTRELAYBOARDLIB_H_

/**
 * @brief JRTで使用するリレーボードのシングルトンクラス
 * * NOTE: クラス名から冗長な 'class' プレフィックスを削除し、JRTRelayBoardとしています。
 */
class classJRTRelayBoard 
{
public:
    /**
     * @brief JRTRelayBoardの唯一のインスタンスへの参照を取得する
     * @return JRTRelayBoardクラスのインスタンスへの参照
     * * NOTE: ポインタではなく参照を返し、静的ローカル変数で安全なシングルトンを実現
     */
    static classJRTRelayBoard& getInstance(void);
    
    /**
     * @brief LEDチカチカ（Lチカ）を実行する
     */
    void LedFlashing(void);

    /**
     * @brief アナログ入力の
     * @return 処理結果(成功:true,失敗:false)
     * * NOTE: ポインタではなく参照を返し、静的ローカル変数で安全なシングルトンを実現
     */

private:
    /**
     * @brief コンストラクタ（外部からの直接生成を禁止）
     */
    classJRTRelayBoard();
    
    /**
     * @brief コピーコンストラクタと代入演算子を削除し、シングルトン性を保証
     */
    classJRTRelayBoard(const classJRTRelayBoard&) = delete;
    classJRTRelayBoard& operator=(const classJRTRelayBoard&) = delete;

    //< ポートを指定するための定数を定義
};

#endif  // #ifndef JRTRELAYBOARDLIB_H_