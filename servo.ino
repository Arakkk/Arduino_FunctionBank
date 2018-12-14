
// サーボモータ制御関数(角度一定)
/***************************************************
 * servo  -- サーボモータ角度制御関数
 * 
 * メモ
 *  一定時間ループすることで目標角度に到達する
 *  目標角度が予め決まっている場合に使う
 *    
 * パラメータ
 *  servo_deg   -- 回転角度
 *  
 * 戻り値
 *  なし
 ***************************************************/
void servo(int servo_deg){
  const float minPulse = 500.0;  // 最小パルス [μsec]
  const float maxPulse = 2400.0; // 最大パルス [μsec]
  const int PWMcycle = 20000;    // PWMサイクル [μsec]
  
  float midPulse = (maxPulse + minPulse) / 2.0;
  float PulseLength = midPulse;

  // 目標角度に到達するようにループさせる
  // ループ時間が長すぎるとアレクサに「(デバイス)から応答がありません」って言われる
  for(int i = 0;i <= 20;i++){
    PulseLength = midPulse + servo_deg / 90.0 * (maxPulse - minPulse) / 2.0;
      
    digitalWrite( servo_sig, HIGH );
    delayMicroseconds( (int)PulseLength );
    digitalWrite( servo_sig, LOW );
    delayMicroseconds( PWMcycle - (int)PulseLength );
  }
}
