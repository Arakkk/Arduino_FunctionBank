// Butterwworth Filter関数
/****************************************************
 * ButterworthFilter -- 1次バタースフィルタ(BWF)    
 *                          
 * パラメータ                     
 *  data_BWF      -- フィルタリングしたい生データ      
 *  cutoff-- カットオフ周波数(Hz)
 *  
 * グローバル変数
 *  float pre_data_BWF = 0.0;     // 一つ前の生データ
 *  float pre_results_BWF = 0.0;  // 一つ前のフィルタリング結果                     
 *  
 * 戻り値                         
 *  results_BWF     // フィルタリング結果                         
 *                                                   
 * **************************************************/
float ButterworthFilter(float data_BWF, float cutoff){
    float T;         //サンプリング周期[s]
    float omega_c;   // カットオフ角周波数[rad/s]
    float a_1;
    float b_0;
    float b_1;
    float results_BWF;            // フィルタリング結果

    // サンプリング周期の設定
    T = sc/1000.0;      // sc = サンプリング周期[ms]

    // 各種パラメータを算出
    omega_c = 2.0 * PI * cutoff;
    b_0 = tan(omega_c*T/2.0)/(1 + tan(omega_c*T/2.0));
    b_1 = tan(omega_c*T/2.0)/(1 + tan(omega_c*T/2.0));
    a_1 = (1 - tan(omega_c*T/2.0))/(1 + tan(omega_c*T/2.0));

    // フィルタリング
    results_BWF = b_0 * data_BWF + b_1 * pre_data_BWF
        + a_1 * pre_results_BWF;

    // 現在の値を保存
    pre_data_BWF = data_BWF;
    pre_results_BWF = results_BWF;

    // フィルタリング結果を戻す
    return results_BWF;
}
