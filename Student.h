#pragma once

#include "Dataset.h"

class Student
{
public:
	static Dataset *dataset;	// �f�[�^�W���ւ̃|�C���^

	Student();
	~Student();
	void setSnackNum(int assortPrice);

	int assortOrderNum;	// �y���y���Z�b�g�𔃂��Ƃ�1�C����Ȃ��Ƃ�0
	int* snackOrderNum;	// �e���َq�̒������Cassort��1�̂Ƃ��͂��ׂ�0

private:
	int* snackList;
};

