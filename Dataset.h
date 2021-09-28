#pragma once

// 標準ヘッダのインクルード
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

// 定数の定義
//このAID_MAXをリストラ説
#define AID_MAX	500				// ペンペンセットの補助最高額
#define REP_NUM 10				// 評価時のシミュレーション回数
#define WORST_VALUE 1000000		// 最悪評価値
#define PI 3.14159265			//円周率

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

//-1以上1以下の乱数
#define RAND_11 ((double)rand() / RAND_MAX * 2) - 1

//0.2以上0.8未満の乱数
#define RAND_28 (((double)rand() / RAND_MAX * 6) + 2) * 0.1

class Dataset
{
public:
	Dataset(char *fileName);
	~Dataset();

	int studentNum;			// 児童数
	int maxAmount;			// 持参するお菓子の上限額
	int snackTypeNum;		// お菓子の種類数
	int* snackPrice;		// 各お菓子の価格
	double additionalRate;	// お急ぎ便の割増

private:

};
