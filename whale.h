#pragma once

#include "Student.h"
#include "Population.h"
class Population;

//定数の定義
#define TIME_MAX 200			//繰り返し数
#define POP_SIZE 40				//クジラの個体数
#define DECRESE 0.008			//変数aValueの減少値（前半はランダム移動，後半は獲物・最良に向かうようになる）（aValueの移行速度）
#define Spiral_Coefficient 1.0	//対数螺旋の係数（大きいほど，大きく旋回）

//TIME_MAX * DECREASE = 2.0  だと，終了タイミングでaValueが0になる　
//↑局所解に陥りやすすぎるから，終盤までランダム移動の割合を一定数保っておく方針
//200 - 0.0008 40匹

//クジラの個体数は，30だと局所解ぎみ　　初期だと50あればほぼ3000代

class Whale
{
public:
	static int posLen;					//位置ベクトルの長さ
	static Dataset* dataset;			//データ集合へのポインタ

	Whale(Population* argPop);
	~Whale();

	void move(double aValue);						//クジラを移動する

	Population* pop;					//属しているクジラ群
	double* pos;						//位置
	double value;						//評価値
	double* normD;						//bestと現在のpos間の距離

private:
	void evaluate();					//評価値を算出する

	Student** studentList;				//児童の集合
	int* snackOrderNum;					//お菓子ごとの注文数
	int assortOrderNum;					//ペンペンセットの注文数
};