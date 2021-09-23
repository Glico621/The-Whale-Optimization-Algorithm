#include "Dataset.h"

// コンストラクタ
// fileName: データセットのファイル名
Dataset::Dataset(char *fileName)
{
	char *pos1, *pos2;
	char line[1024], paraName[32];
	int snackPriceCount = 0;
	FILE *fp;

	// 読込みエラー発見のための初期化
	studentNum = -1;
	maxAmount = -1;
	snackTypeNum = -1;
	snackPrice = NULL;
	additionalRate = -1;

	// 読込み
	if((fp = fopen(fileName, "r")) == NULL) {
		printf("ファイル%sが開けません．\n", fileName);
		exit(-1);
	}

	//fgets関数　ファイルから文字列を一行取得
		//第一引数 　文字配列のポインタ
		//第二 　　　一行の最大文字数
		//第三 　　　ファイルポインタ
	//ファイルから取得できる文字列がある限りループ
	while(fgets(line, 1024, fp)) {
		pos1 = line;
		pos2 = strchr(pos1, ',');
		*pos2 = '\0';
		strcpy(paraName, line);
		pos1 = pos2 + 1;
		pos2 = strchr(pos1, ',');
		if(!pos2) {
			pos2 = strchr(pos1, '\n');
		}
		*pos2 = '\0';
		if(!strcmp(paraName, "studentNum")) {
			if(studentNum != -1) {
				printf("%sが複数定義されています．\n", paraName);
				exit(-1);
			}
			studentNum = atoi(pos1);
		} else if(!strcmp(paraName, "maxAmount")) {
			if(maxAmount != -1) {
				printf("%sが複数定義されています．\n", paraName);
				exit(-1);
			}
			maxAmount = atoi(pos1);
		} else if(!strcmp(paraName, "snackTypeNum")) {
			if(snackTypeNum != -1) {
				printf("%sが複数定義されています．\n", paraName);
				exit(-1);
			}
			snackTypeNum = atoi(pos1);
			snackPrice = new int [snackTypeNum];
		} else if(!strcmp(paraName, "snackPrice")) {
			if(!snackPrice) {
				printf("お菓子の価格(snackPrice)より前にお菓子の種類数(snackTypeNum)を定義してください．\n");
				exit(-1);
			} else if(snackPriceCount == snackTypeNum) {
				printf("お菓子の価格(snackPrice)がお菓子の種類数(snackTypeNum)より多く定義されています．\n");
				exit(-1);
			}
			snackPrice[snackPriceCount++] = atoi(pos1);
		} else if(!strcmp(paraName, "additionalRate")) {
			if(additionalRate != -1) {
				printf("%sが複数定義されています．\n", paraName);
				exit(-1);
			}
			additionalRate = atof(pos1);
		}
	}
	fclose(fp);
	if(snackPriceCount != snackTypeNum) {
		printf("お菓子の価格(snackPrice)がお菓子の種類数(snackTypeNum)より少なく定義されています．\n");
		exit(-1);
	}
}

// デストラクタ
Dataset::~Dataset()
{
	delete [] snackPrice;
}
