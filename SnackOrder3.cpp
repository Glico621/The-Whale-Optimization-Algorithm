// SnackOrder3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "Population.h"


//課題点
//additionalRateへの依存が高すぎる
//bestPosがばけものみたいな値になる



int main()
{
	clock_t start = clock();

	int t;
	char dataFname[] = "data.csv";
	char resultFname[] = "result.csv";
	Population* pop;

	//疑似乱数の生成
	//実行するたびに異なる乱数を生成するため
	//乱数の種はエポック秒
	srand((unsigned int)time(NULL));

	//data.csvの内容をpopにぶち込む
	pop = new Population(dataFname);

	//この時点でwhaleが読み込めてないのがおかしい
	pop->aValue = 2.0;
	for (t = 1; t <= TIME_MAX; t++) {
		pop->move(pop->aValue);
		//ステップごとにaを減少させる
		pop->aValue = pop->decrease(pop->aValue);
		printf("%d回目：最良評価値%f\n", t, pop->bestValue);
	}

	//お菓子ごとの個数，最大補助をresult.csvに書き込む
	pop->printResult(resultFname);
	delete pop;

	clock_t end = clock();
	printf("time = %f sec.\n", (double)(end - start) / CLOCKS_PER_SEC);
	
}



