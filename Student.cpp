#include "Student.h"

// static変数の初期化
Dataset* Student::dataset = NULL;

// コンストラクタ
Student::Student()
{
	int i;

	assortOrderNum = -1;
	//要素数　＝　お菓子の種類数
	snackOrderNum = new int [dataset->snackTypeNum];
	snackList = new int [dataset->snackTypeNum];
	for(i = 0; i < dataset->snackTypeNum; i++) {
		snackOrderNum[i] = -1;
	}
}

// デストラクタ
Student::~Student()
{
	delete [] snackOrderNum;
	delete [] snackList;
}

//児童ごとにどのお菓子を買うか決める
void Student::setSnackNum(int assortPrice)
{
	int i, listNum, residue, select;

	//o1の乱数より，右辺の確率が大きくなれば，ペンペンセットを買う
	if(RAND_01 < 1 / (1 + exp(-0.023 * (assortPrice - dataset->maxAmount - 250))))
	   assortOrderNum = 1;//買う
	else
	   assortOrderNum = 0;//買わない

	for(i = 0; i < dataset->snackTypeNum; i++) {
		snackOrderNum[i] = 0;
	}
	//ペンペンセットを注文しない児童のみ実行
	//セットを購入する児童は，単品で購入できない
	if(assortOrderNum == 0) {
		//residue:　児童の持参額の残り
		residue = dataset->maxAmount;
		//残額で買えるお菓子がなくなるまでループ
		do {
			listNum = 0;
			//forループ　お菓子の種類
			//if　　　　　residueでそのお菓子が買えれば　snackListにお菓子のナンバーを記録
			for (i = 0; i < dataset->snackTypeNum; i++) {
				if (dataset->snackPrice[i] <= residue) {
					snackList[listNum++] = i;
				}
			}
			//買えるお菓子が無ければ終了
			if (listNum == 0) {
				break;
			}

			//select:0 ～(listNum -1)
			//残額で買えるお菓子のうち，ランダムでいずれか一つの購入を決定
			//残額からそのお菓子の値段を引く
			select = rand() % listNum;
			snackOrderNum[snackList[select]]++;
			residue -= dataset->snackPrice[snackList[select]];
		} while(residue > 0);
	}
}
