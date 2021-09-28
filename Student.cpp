#include "Student.h"

// static�ϐ��̏�����
Dataset* Student::dataset = NULL;

// �R���X�g���N�^
Student::Student()
{
	int i;

	assortOrderNum = -1;
	//�v�f���@���@���َq�̎�ސ�
	snackOrderNum = new int [dataset->snackTypeNum];
	snackList = new int [dataset->snackTypeNum];
	for(i = 0; i < dataset->snackTypeNum; i++) {
		snackOrderNum[i] = -1;
	}
}

// �f�X�g���N�^
Student::~Student()
{
	delete [] snackOrderNum;
	delete [] snackList;
}

//�������Ƃɂǂ̂��َq�𔃂������߂�
void Student::setSnackNum(int assortPrice)
{
	int i, listNum, residue, select;

	//o1�̗������C�E�ӂ̊m�����傫���Ȃ�΁C�y���y���Z�b�g�𔃂�
	if(RAND_01 < 1 / (1 + exp(-0.023 * (assortPrice - dataset->maxAmount - 250))))
	   assortOrderNum = 1;//����
	else
	   assortOrderNum = 0;//����Ȃ�

	for(i = 0; i < dataset->snackTypeNum; i++) {
		snackOrderNum[i] = 0;
	}
	//�y���y���Z�b�g�𒍕����Ȃ������̂ݎ��s
	//�Z�b�g���w�����鎙���́C�P�i�ōw���ł��Ȃ�
	if(assortOrderNum == 0) {
		//residue:�@�����̎��Q�z�̎c��
		residue = dataset->maxAmount;
		//�c�z�Ŕ����邨�َq���Ȃ��Ȃ�܂Ń��[�v
		do {
			listNum = 0;
			//for���[�v�@���َq�̎��
			//if�@�@�@�@�@residue�ł��̂��َq��������΁@snackList�ɂ��َq�̃i���o�[���L�^
			for (i = 0; i < dataset->snackTypeNum; i++) {
				if (dataset->snackPrice[i] <= residue) {
					snackList[listNum++] = i;
				}
			}
			//�����邨�َq��������ΏI��
			if (listNum == 0) {
				break;
			}

			//select:0 �`(listNum -1)
			//�c�z�Ŕ����邨�َq�̂����C�����_���ł����ꂩ��̍w��������
			//�c�z���炻�̂��َq�̒l�i������
			select = rand() % listNum;
			snackOrderNum[snackList[select]]++;
			residue -= dataset->snackPrice[snackList[select]];
		} while(residue > 0);
	}
}
