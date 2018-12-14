// リレー制御関数
/***************************************************
 * relay_priodical  -- リレー周期駆動関数
 * 
 * メモ
 *  指定する間隔でリレーをON・OFFする
 *    
 * パラメータ
 *  Pulse_length  -- 半周期
 *    
 * グローバル変数
 *  int Count_relay   -- カウント数
 *  
 * 戻り値
 *  なし
 ***************************************************/
void relay_priodical(int Pulse_length){
  
  // 関数に入った回数をカウント
  // これを使ってON/OFFを切り替える
  Count_relay++;    // グローバル変数

  // ON
  if (Count_relay <= Pulse_length){
    digitalWrite(sigOut_relay,HIGH);

  // OFF
  } else if (Count_relay > Pulse_length){
    digitalWrite(sigOut_relay,LOW);
  }

  // １周期が終わったらカウントをクリア
  if(Count_relay >= Pulse_length * 2) Count_relay = 0;
}
