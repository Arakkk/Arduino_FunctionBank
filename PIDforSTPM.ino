// ステモのPID制御関数
/***************************************************
 * PIDforSTPM  -- ステモのPID制御関数
 *    
 * パラメータ
 *    Kp                  -- 比例ゲイン
 *    Ki                  -- 積分ゲイン
 *    Kd                  -- 微分ゲイン
 *    PIDforSTPM_value    -- 制御量
 *    PIDforSTPM_target   -- 目標値
 *    
 * グローバル変数
 *    float PIDforSTPM_error_i     -- 積分偏差
 *    float PIDforSTPM_error_pre   -- 1ループ前の制御偏差
 *    int ControlCycle             -- 制御周期[ms] （#defineでもOK）
 *  
 * 戻り値
 *    なし
 ***************************************************/
void PIDforSTPM(float Kp, float Ki, float Kd, float PIDforSTPM_value, float PIDforSTPM_target){
  float Step;               // ステップ数
  int Direction_StepMotor;  // +1：正転 -1：逆転
  float PIDforSTPM_error;
  float PIDforSTPM_error_d;

  // 制御偏差を計算する
  PIDforSTPM_error = PIDforSTPM_target - PIDforSTPM_value;
  
  // 制御偏差を微分する
  PIDforSTPM_error_d = (PIDforSTPM_error_pre - PIDforSTPM_error) / ControlCycle / 0.01;
  
  // 制御偏差を積分する
  PIDforSTPM_error_i += PIDforSTPM_error;
  
  if(PIDforSTPM_error >= 0.0)  Direction_StepMotor = +1;
  else if(PIDforSTPM_error < 0.0) Direction_StepMotor = -1;
  
  Step = abs(Kp * PIDforSTPM_error + Ki * PIDforSTPM_error_i + Kd * PIDforSTPM_error_d)
            * (float)Direction_StepMotor;

  if(Step >= 5.0) Step = 5.0;
  else if(Step <= -5.0) Step = -5.0;
  stepper.step((int)Step);

  // 今回の制御偏差を保存する
  PIDforSTPM_error_pre = PIDforSTPM_error;
}
