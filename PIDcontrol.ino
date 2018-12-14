// PID制御関数
/***************************************************
 * PIDcontrol  -- DCモータのPID制御関数
 *    
 * パラメータ
 *    Kp              -- 比例ゲイン
 *    Ki              -- 積分ゲイン
 *    Kd              -- 微分ゲイン
 *    Control_value   -- 制御量
 *    Control_target  -- 目標値
 *    
 * グローバル変数
 *    float PWM1_Ratio          -- duty比
 *    float Control_error       -- 制御偏差 ※グローバル変数じゃなくていい(要変更)
 *    float Control_error_i     -- 積分偏差
 *    float Control_error_d     -- 微分偏差 ※
 *    float Control_error_pre   -- 1ループ前の制御偏差
 *  
 * 戻り値
 *    なし
 ***************************************************/
void PIDcontrol(float Kp, float Ki, float Kd, float Control_value, float Control_target){
  int PWM1_Value;               //motor1のPWM値(0～254)
  float dT = 0.05;

  //if(Control_value <= 0.0)  Control_value *= -1.0;

  // 制御偏差を計算する
  Control_error = Control_target - Control_value;
  Control_error_d = (Control_error_pre - Control_error)/0.05;

  // 制御偏差を積分する
  Control_error_i += Control_error;
  
  if(Control_error >= 0.0){
    PWM1_Value = (int)Kp * (int)Control_error + (int)Ki * (int)Control_error_i
              + (int)Kd * (int)Control_error_d;
    if(PWM1_Value >= 254) PWM1_Value = 254;
    
    digitalWrite(Direction_1,HIGH);
    digitalWrite(Direction_2,LOW);
    analogWrite(PWM1,PWM1_Value);
    
  }else if(Control_error < 0.0){
    Control_error *= -1.0;
    PWM1_Value = (int)Kp * (int)Control_error + (int)Ki * (int)Control_error_i
              + (int)Kd * (int)Control_error_d;
    if(PWM1_Value >= 254) PWM1_Value = 254;
    
    digitalWrite(Direction_1,LOW);
    digitalWrite(Direction_2,HIGH);
    analogWrite(PWM1,PWM1_Value);
  }
