#ifndef CVECTOR_H
#define CVECTOR_H // CVECTOR_Hの定義
/*
ベクトルクラス
ベクトルクラスを扱います
*/
class CVector {
public:
	//各軸での値の設定
	//Set(X座標,Y座標,Z座標)
	void Set(float x, float y, float z);
	//Xの値を知る
	float X() const;
	//Yの値を知る
	float Y() const;
	//Zの値を知る
	float Z() const;
private:
	//3D各軸での値を設定
	float mX, mY, mZ;

};
#endif;