#pragma once

#include "Dataset.h"

class Student
{
public:
	static Dataset *dataset;	// データ集合へのポインタ

	Student();
	~Student();
	void setSnackNum(int assortPrice);

	int assortOrderNum;	// ペンペンセットを買うとき1，買わないとき0
	int* snackOrderNum;	// 各お菓子の注文数，assortが1のときはすべて0

private:
	int* snackList;
};

