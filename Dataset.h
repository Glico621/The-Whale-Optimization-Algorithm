#pragma once

// �W���w�b�_�̃C���N���[�h
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

// �萔�̒�`
//����AID_MAX�����X�g����
#define AID_MAX	500				// �y���y���Z�b�g�̕⏕�ō��z
#define REP_NUM 10				// �]�����̃V�~�����[�V������
#define WORST_VALUE 1000000		// �ň��]���l
#define PI 3.14159265			//�~����

// 0�ȏ�1�ȉ��̎�������
#define RAND_01 ((double)rand() / RAND_MAX)

//-1�ȏ�1�ȉ��̗���
#define RAND_11 ((double)rand() / RAND_MAX * 2) - 1

//0.2�ȏ�0.8�����̗���
#define RAND_28 (((double)rand() / RAND_MAX * 6) + 2) * 0.1

class Dataset
{
public:
	Dataset(char *fileName);
	~Dataset();

	int studentNum;			// ������
	int maxAmount;			// ���Q���邨�َq�̏���z
	int snackTypeNum;		// ���َq�̎�ސ�
	int* snackPrice;		// �e���َq�̉��i
	double additionalRate;	// ���}���ւ̊���

private:

};
