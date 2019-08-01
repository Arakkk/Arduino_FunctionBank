// Butterwworth Filter関数
/****************************************************
 * ButterworthFilter -- 1次バタースフィルタ(BWF)    
 *                          
 * パラメータ                     
 *  ch            -- チャンネル
 *  data_BWF      -- フィルタリングしたい生データ      
 *  cutoff        -- カットオフ周波数(Hz)
 *  
 * グローバル変数
 *  float pre_data_BWF = 0.0;     // 一つ前の生データ
 *  float results_BWF;            // フィルタリング結果
 *  float pre_results_BWF = 0.0;  // 一つ前のフィルタリング結果                     
 *  
 * 戻り値                         
 *  results_BWF     // フィルタリング結果                          
 *                                                   
 * **************************************************/
float ButterworthFilter(int ch, float data_BWF, float cutoff){
    float T;         //サンプリング周期[sec]
    float omega_c;   // カットオフ角周波数[rad/s]
    float a_1;
    float b_0;
    float b_1;
    float results_BWF;     // フィルタリング結果

    // サンプリング周期の設定
    T = (float)ControlCycle/1000.0;      // サンプリング周期[sec]

    // 各種パラメータを算出
    omega_c = 2.0 * PI * cutoff;
    b_0 = tan(omega_c*T/2.0)/(1 + tan(omega_c*T/2.0));
    b_1 = tan(omega_c*T/2.0)/(1 + tan(omega_c*T/2.0));
    a_1 = (1 - tan(omega_c*T/2.0))/(1 + tan(omega_c*T/2.0));

    if(ch == 1){
      // フィルタリング
      results_BWF = b_0 * data_BWF + b_1 * BWF.pre_data_1
          + a_1 * BWF.pre_results_1;
  
      // 現在の値を保存
      BWF.pre_data_1 = data_BWF;
      BWF.pre_results_1 = results_BWF;
    }
    else if(ch == 2){
      results_BWF = b_0 * data_BWF + b_1 * BWF.pre_data_2
          + a_1 * BWF.pre_results_2;
  
      BWF.pre_data_2 = data_BWF;
      BWF.pre_results_2 = results_BWF;
    }
    else if(ch == 3){
      results_BWF = b_0 * data_BWF + b_1 * BWF.pre_data_3
          + a_1 * BWF.pre_results_3;

      BWF.pre_data_3 = data_BWF;
      BWF.pre_results_3 = results_BWF;
    }
    else if(ch == 4){
      results_BWF = b_0 * data_BWF + b_1 * BWF.pre_data_4
          + a_1 * BWF.pre_results_4;

      BWF.pre_data_4 = data_BWF;
      BWF.pre_results_4 = results_BWF;
    }

    // フィルタリング結果を戻す
    return results_BWF;
}
