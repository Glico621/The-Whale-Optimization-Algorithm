#include "Population.h"

//コンストラクタ
Population::Population(char* filename)
{
	int i, best;
	aValue = 0.0;
	dataset = new Dataset(filename);
	Whale::dataset = dataset;
	Whale::posLen = dataset->snackTypeNum + 1;
	Student::dataset = dataset;

	whale = new Whale* [POP_SIZE];
	best = 0;
	for (i = 0; i < POP_SIZE; i++)
	{
		whale[i] = new Whale(this);
		if (whale[best]->value > whale[i]->value)
		{
			best = i;
		}
	}


	bestPos = new double[Whale::posLen];

	for (i = 0; i < Whale::posLen; i++)
	{
		bestPos[i] = whale[best]->pos[i];

	}

	bestValue = whale[best]->value;
}

//デストラクタ
Population::~Population()
{
	int i;

	for (i = 0; i < POP_SIZE; i++)
	{
		delete whale[i];
	}
	delete[] whale;
	delete[] bestPos;
	delete dataset;
}

//クジラをどの方法で移動させるか決定する
void Population::move(double aValue)
{
	int i, best, check;
	
	//すべてのクジラを移動する
	for (i = 0; i < POP_SIZE; i++)
	{
		whale[i]->move(aValue);
	}

	//より良いvalueのあるiを記録
	best = -1;
	for (i = 0; i < POP_SIZE; i++) {
		if ((bestValue > whale[i]->value) && (whale[i]->value >= 0)) {
			if (best == -1)
			{
				best = i;
			}
			else if (whale[best]->value > whale[i]->value)
			{
				best = i;
			}
		}
	}


	/*
	best = -1;
	for (i = 0; i < POP_SIZE; i++) {
		if ((bestValue > whale[i]->value) && (whale[i]->value >= 0)) {
			best = i;
		}
	}
	*/

	/*
	best = -1;
	for (i = 0; i < POP_SIZE; i++) {
		if ((bestValue > whale[i]->value) && (whale[i]->value >= 0)) {
			if (best != -1)
			{
				if (whale[best]->value > whale[i]->value)
				{
					best = i;
				}
			}
			else
			{
				best = i;
			}
		}
	}
	*/

	//バグ対処
	//bestPosの値が8桁くらいの負数になるときがある
	//!このバグは，posがnanになってるため
	/*
	check = -1;
	for (i = 0; i < Whale::posLen; i++)
	{
		if ((best != -1) && (whale[best]->pos[i] < 0.0))
		{
			check = i;
		}
	}
	*/

	//!bestPos にnanが発生してる

	//bestが更新されていれば，そのクジラのpos,valueをbestPos,bestValueに記録
	if (best != -1) {
		for (i = 0; i < Whale::posLen; i++) 
		{
			bestPos[i] = whale[best]->pos[i];
			//printf("%f\n", whale[best]->pos[i]);
		}
		bestValue = whale[best]->value;
	}
	//bestPosの算出はおｋ
}

//ステップごとにaを減らす
double Population::decrease(double aValue)
{
	aValue -= DECRESE;
	if (aValue < 0)
	{
		aValue = 0.0;
	}
	return aValue;
}

//初期のループはおｋ
//最良評価値を記録する
/*
void Population::saveBestPos()
{
	int i, best;

	//より良いvalueのあるiを記録

	best = -1;
	for (i = 0; i < POP_SIZE; i++) {
		if ((bestValue > whale[i]->value) && (whale[i]->pos[i] >= 0) ) {
			if (best != -1)
			{
				if (whale[best]->value > whale[i]->value)
				{
					best = i;
				}
			}
			else
			{
				best = i;
			}
		}
	}
	//bestが更新されていれば，そのflowerのpos,valueをbestPos,bestValueに記録
	if (best != -1) {
		for (i = 0; i < Whale::posLen; i++) {
			bestPos[i] = whale[best]->pos[i];
		}
		bestValue = whale[best]->value;
	}

}
*/

// 結果を表示する
// fileName: 結果を書き込むファイルの名前
void Population::printResult(char* fileName)
{
	FILE* fp;
	int i;

	// 書込み
	//エラー
	if ((fp = fopen(fileName, "w")) == NULL) {
		printf("ファイル%sが開けません．\n", fileName);
		exit(-1);
	}
	//菓子毎に最良食料源の位置を書き込む
	for (i = 0; i < dataset->snackTypeNum; i++) {
		fprintf(fp, "%d,", (int)bestPos[i]);
	}
	//最後尾はペンペンセットの値段
	fprintf(fp, "%d,", (int)bestPos[i] + dataset->maxAmount);
	fclose(fp);
}