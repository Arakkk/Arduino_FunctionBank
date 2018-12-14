// サーボモータ角度制御関数
/***************************************************
 * servo_AngleControl  -- サーボモータ角度制御関数
 *    
 * パラメータ
 *  servo_deg   -- 回転角度
 *  
 * 戻り値
 *  なし
 *  
 * メモ
 *  制御角-90～90deg用．
 *  制御パルスの範囲を設定する．
 ***************************************************/
void servo_AngleControl(float servo_deg){
  const float minPulse = 500.0;  // 最小パルス [μsec]
  const float maxPulse = 2400.0; // 最大パルス [μsec]
  const int PWMcycle = 20000;    // PWMサイクル [μsec]
  
  float midPulse = (maxPulse + minPulse) / 2.0;
  float PulseLength = midPulse;

  PulseLength = midPulse + servo_deg / 90.0 * (maxPulse - minPulse) / 2.0;
    
  digitalWrite( servo_sig, HIGH );
  delayMicroseconds( (int)PulseLength );
  digitalWrite( servo_sig, LOW );
  delayMicroseconds( PWMcycle - (int)PulseLength );
}
