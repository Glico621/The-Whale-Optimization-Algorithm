#pragma once

#include "Whale.h"
class Whale;

class Population
{
public:
	Population(char* fileNmae);
	~Population();

	void move(double aValue);				//クジラを移動
	double decrease(double aValue);			//aのカウントを減らす
	void saveBestPos();						//最良食料源を記録する
	void printResult(char* fileName);		//結果を表示する


	Dataset* dataset;		//データセット
	Whale** whale;			//食料源の集合メンバ
	double* bestPos;		//最良食料源の位置
	double bestValue;		//最良食料源の評価値
	double aValue;			//noemA(クジラの行動選択)に用いる変数，ステップごとに減少

private:

};
