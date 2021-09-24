#pragma once

#include "Whale.h"
class Whale;

class Population
{
public:
	Population(char* fileNmae);
	~Population();

//	void encircle();						//旋回する
//	void attack();							//獲物に近づく
//	void search();							//獲物を探す
	void move(double aValue);				//クジラを移動
	double decrease(double aValue);			//aのカウントを減らす
	void saveBestPos();						//最良食料源を記録する
	void printResult(char* fileName);		//結果を表示する


	Dataset* dataset;		//データセット
	Whale** whale;			//食料源の集合メンバ
	double* bestPos;		//最良食料源の位置
	double bestValue;		//最良食料源の評価値
	double aValue;

private:

};
