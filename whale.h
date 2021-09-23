#pragma once

#include "Student.h"
#include "population.h"
class Population;

//定数の定義
#define TIME_MAX 500			//繰り返し数
#define POP_SIZE 10				//クジラの個体数
#define DECRESE 0.001			//変数aの減少値（前半はランダム移動，後半は獲物に向かう）（aの以降速度）
#define Spiral_Coefficient 	1	//対数螺旋の係数（大きいほど，大きく旋回）


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
	double* r1;							//位置生成用乱数配列１
	double* r2;							//位置生成用乱数２
	double* A;							//ランダム係数ベクトル
	double* C;							//ランダム係数ベクトル
	//double* D;							//アタック用ベクトル

private:
	void evaluate();					//評価値を算出する
	double* newPos1;						//新しい位置（良いコウモリの近く）
	double* newPos2;						//新しい位置（ランダム）

	Student** studentList;				//児童の集合
	int* snackOrderNum;					//お菓子ごとの注文数
	int assortOrderNum;					//ペンペンセットの注文数
};