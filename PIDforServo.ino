// サーボモータのPID制御関数
/***************************************************
 * PIDforServo  -- サーボモータのPID制御関数
 *    
 * パラメータ
 *    Kp                  -- 比例ゲイン
 *    Ki                  -- 積分ゲイン
 *    Kd                  -- 微分ゲイン
 *    PIDforServo_value   -- 制御量
 *    PIDforServo_target  -- 目標値
 *    
 * グローバル変数
 *    float PIDforServo_error_i     -- 積分偏差
 *    float PIDforServo_error_pre   -- 1ループ前の制御偏差
 *    int ControlCycle          -- 制御周期[ms] （#defineでもOK）
 *  
 * 戻り値
 *    なし
 ***************************************************/
void PIDforServo(float Kp, float Ki, float Kd, float PIDforServo_value, float PIDforServo_target){
  float PIDforServo_error;
  float PIDforServo_error_d;
  float deg = 90.0;

  // 制御偏差を計算する
  PIDforServo_error = PIDforServo_target - PIDforServo_value;
  
  // 制御偏差を微分する
  PIDforServo_error_d = (PIDforServo_error_pre - PIDforServo_error) / ControlCycle / 0.01;
  
  // 制御偏差を積分する
  PIDforServo_error_i += PIDforServo_error;
  
  deg += Kp * PIDforServo_error + Ki * PIDforServo_error_i + Kd * PIDforServo_error_d;

  if(deg >= 180.0) deg = 180.0;
  else if(deg <= 0.0) deg= 0.0;
  servo_AngleControl(deg);

  // 今回の制御偏差を保存する
  PIDforServo_error_pre = PIDforServo_error;
}
