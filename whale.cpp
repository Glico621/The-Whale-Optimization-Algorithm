#include "Whale.h"

//static変数の初期化
int Whale::posLen = -1;
Dataset* Whale::dataset = NULL;

//コンストラクタ
//argPop: 属しているクジラ群
Whale::Whale(Population* argPop)
{
	int i;
	pop = argPop;

	normD = new double[posLen];
	pos = new double[posLen];

	snackOrderNum = new int[dataset->snackTypeNum];
	for (i = 0; i < dataset->snackTypeNum; i++)
	{
		pos[i] = dataset->maxAmount / dataset->snackPrice[i] * dataset->studentNum * RAND_01;
		snackOrderNum[i] = -1;	
	}		
	pos[i] = AID_MAX * RAND_01;
	assortOrderNum = -1;

	studentList = new Student * [dataset->studentNum];
	for (i = 0; i < dataset->studentNum; i++)
	{
		studentList[i] = new Student();
	}

	evaluate();
}

//デストラクタ
Whale::~Whale()
{
	int i;

	delete[] normD;
	delete[] pos;
	delete[] snackOrderNum;
	for (i = 0; i < dataset->studentNum; i++) {
		delete studentList[i];
	}
	delete[] studentList;
}

//クジラをどの方法で移動させるか決め，移動させる
//アタック，サーチ，旋回の3種類
void Whale::move(double aValue)
{
	int i, searchNum;
	double normA, sum, r, hogeA, hogeC;

	//0から1の乱数，normAによってクジラの行動を選択
	//pが0.5未満ならアタックorサーチ
	if (RAND_01 < 0.5)
	{
		hogeA = 2 * aValue * RAND_01 - aValue;
		hogeC = 2 * RAND_01;
		normA = fabs(hogeA);

		//|A|が1未満ならアタック，1以上なら獲物を探索
		if (normA < 1)
		{
			//アタック
			//normDは，ベストのposと現在のposとの距離を格納		
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				//!ここのposおｋ
				normD[i] = fabs(hogeC * pop->bestPos[i] - pos[i]);
				pos[i] = pop->bestPos[i] - hogeA * normD[i];
			}
		}
		else
		{
			//サーチ
			//アタックと異なる点：向かう先が最良ではなくランダムのクジラであること

			//クジラの添え字決定（ランダム個体）
			//予めどのクジラを目標にするかを決定
			searchNum = rand() % (POP_SIZE);
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				normD[i] = fabs(hogeC * pop->whale[searchNum]->pos[i] - pos[i]);
				pos[i] = pop->whale[searchNum]->pos[i] - hogeA * normD[i];
			}	
		}
	}
	else
	{
		//この旋回の計算でのposに問題なしおｋ，posの負数なし
		//旋回
		//ぐるぐる旋回しながら，獲物を取り囲む	
		r = RAND_11;	//-1から1の乱数 
		for (i = 0; i < dataset->snackTypeNum; i++)
		{
			sum = pow((pop->bestPos[i] - pos[i]), 2);
			normD[i] = sqrt(sum);
			pos[i] = normD[i] * exp(Spiral_Coefficient * r) * cos(2.0 * PI * r) + pop->bestPos[i];	
		}
	}

	//posの絶対値がでかくなりすぎた場合，bestPos付近にリセット
	for (i = 0; i < dataset->snackTypeNum; i++)
	{
		if (fabs(pos[i]) > (dataset->studentNum * 100))
		{
			pos[i] = pop->bestPos[i] * (RAND_01 + 0.6);
		}
	}

	evaluate();
}

//評価値を算出する
void Whale::evaluate()
{
	int i, j, k, diff;
	double subvalue, ave, sd, sqrSum;

	//pos（購入数）が負数だった場合，valueを最低評価値に
	for (j = 0; j < posLen; j++) {
		if (pos[j] < 0) {
			value = WORST_VALUE;
			break;
		}
	}

	//上のfor文で最低評価値が出なかった場合
	if (j == posLen) {
		ave = 0.0;
		sqrSum = 0.0;
		for (k = 0; k < REP_NUM; k++) {
			// 初期化
			for (j = 0; j < dataset->snackTypeNum; j++) {
				snackOrderNum[j] = 0;
			}
			assortOrderNum = 0;

			// 児童の注文決定
			//どちらかを判別して，ぐるぐる回数を減らせないかなー
			//先にassortが０か１か
			for (i = 0; i < dataset->studentNum; i++) {
				//setSnackNum(補助額＋持参額　＝　ペンペンセットの値段)
				studentList[i]->setSnackNum((int)pos[posLen - 1] + dataset->maxAmount);
				for (j = 0; j < dataset->snackTypeNum; j++) {
					//お菓子の個数を入れる配列，　i番目の児童が何個そのお菓子を注文したか
					//お菓子の添え字を動かす
					snackOrderNum[j] += studentList[i]->snackOrderNum[j];
				}
				//ペンペンセット個数
				assortOrderNum += studentList[i]->assortOrderNum;
			}

			// 損失計算
			//subvalue;　損失
			subvalue = 0;
			//お菓子の種類ごとに損失を計算
			for (j = 0; j < dataset->snackTypeNum; j++) {
				//diff:子供が注文した個数と，注文数の差		
				//printf("%f\n", pos[j]);
				diff = snackOrderNum[j] - (int)pos[j];
				if (diff > 0) {
					//お菓子の不足している分，レートをかけて損失に加算
					//不足個数　×　お菓子の値段　×　レート
					subvalue += diff * (int)(dataset->snackPrice[j] * dataset->additionalRate);
				} else if (diff < 0) {
					//児童の注文より多く仕入れてしまった場合
					//過分がそのまま損失に加算される
					subvalue += -diff * dataset->snackPrice[j];
				}
			}
			//ペンペンセットの注文数×補助額　
			//割増料金なし
			//補助額をどうするか
			subvalue += (int)pos[posLen - 1] * assortOrderNum;
			ave += subvalue;
			sqrSum += subvalue * subvalue;
		}

		//評価値の算出
		//Avei, SD
		ave /= REP_NUM;
		sd = sqrt(sqrSum / REP_NUM - ave * ave);
		value = ave + sd;
	}
}