#include "Whale.h"

//static�ϐ��̏�����
int Whale::posLen = -1;
Dataset* Whale::dataset = NULL;

//�R���X�g���N�^�ƃ��j���[���C�A�f�B�V���i�����[�g�̍����ŕ��� �A�f�B�V���i�����[�g�P���ƁC�ǉ������ƈꏏ
//����ȏ�C����ȉ��ŕ��򂷂�Ƃ�������

//�ŏ���move()����evaluate()�ւ�pos�̎󂯓n����
//�R���X�g���N�^�͋��炭���v

//�R���X�g���N�^
//argPop: �����Ă���N�W���Q
Whale::Whale(Population* argPop)
{
	int i;
	pop = argPop;

	r1 = new double[posLen];
	r2 = new double[posLen];
	randA = new double[posLen];
	randC = new double[posLen];
	normD = new double[posLen];
	pos = new double[posLen];

	snackOrderNum = new int[dataset->snackTypeNum];
	for (i = 0; i < dataset->snackTypeNum; i++)
	{
		pos[i] = dataset->maxAmount / dataset->snackPrice[i] * dataset->studentNum * RAND_01;
		snackOrderNum[i] = -1;	
	}		
	//printf("%f\n", pos[0]);

	//!����RAND01�ǂ��ɂ�������
	pos[i] = AID_MAX * RAND_01;
	assortOrderNum = -1;

	studentList = new Student * [dataset->studentNum];
	for (i = 0; i < dataset->studentNum; i++)
	{
		studentList[i] = new Student();
	}

	evaluate();
}

//�f�X�g���N�^
Whale::~Whale()
{
	int i;

	delete[] r1;
	delete[] r2;
	delete[] randA;
	delete[] randC;
	delete[] normD;
	delete[] pos;
	delete[] snackOrderNum;
	for (i = 0; i < dataset->studentNum; i++) {
		delete studentList[i];
	}
	delete[] studentList;
}

//�N�W�����ړ�������
void Whale::move(double aValue, int base)
{
	int i;
	double normA, sum, r;

	for (i = 0; i < posLen; i++)
	{
		pos[i] = pop->whale[base]->pos[i];
	}

	//01�̗���p�ɂ���Đ��񂩂���ȊO���𕪊�
	//p��0.5�����Ȃ�A�^�b�Nor�T�[�`
	if (RAND_01 < 0.5)
	{
		//r1, r2, A, C, |A|�̎Z�o
		for (i = 0; i < dataset->snackTypeNum; i++)
		{
			r1[i] = RAND_01;
			r2[i] = RAND_01;
		}

		//���̗��������z��ɂ��Ă��ꂼ��l�ւ���K�v����H
		//�ǂ����ł�邩�͗v����

		sum = 0.0;
		for (i = 0; i < dataset->snackTypeNum; i++)
		{	
			//01����02�ɂ��Ă邩�񂶂���
			randC[i] = 2 * r2[i];
			randA[i] = 2 * aValue * r1[i] - aValue;
			sum += randA[i] * randA[i];
		}
		normA = sqrt(sum);	//����


		double newC = 2 * RAND_01;


		//|A|��1�����Ȃ�A�^�b�N�C1�ȏ�Ȃ�l����T��
		if (normA < 1)
		{
			//�A�^�b�N
			//D�����߂�
			//normD�́Ci���Ƃ̋������i�[�����z��

			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				//!������pos����
				sum = pow((randC[i] * pop->bestPos[i] - pos[i]), 2);
				//sum = pow((newC * pop->bestPos[i] - pos[i]), 2);
				normD[i] = sqrt(sum);
			}

			double r4 = RAND_01;
			//!pos���}�C�i�X�ɂȂ����Ƃ��C��Βl���Ƃ邩0�ɂ��邩
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				//pos[i] -= ( 2 * aValue * r4 - aValue) * normD[i];
				pos[i] -= randA[i] * normD[i];
				//printf("������%f\n", pos[i]);
			}
			//���ꂢ��Hpos[i] = AID_MAX * RAND_01;
		}
		else
		{
			//�T�[�`
			//�A�^�b�N�ƈقȂ�_�́C�������悪�ŗǂł͂Ȃ������_���̃N�W���ł��邱��
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				sum = 0.0;
				sum += pow(randC[i] * pop->bestPos[i] - pos[i], 2);
				normD[i] = sqrt(sum);
			}

			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				pos[i] -= randA[i] * normD[i];
			}
			//pos[i] = AID_MAX * RAND_01;
		}
	}
	else
	{
		//����
		r = RAND_11;
		sum = 0.0;
		for (i = 0; i < dataset->snackTypeNum; i++)
		{
			sum = 0.0;
			sum += pow(pop->bestPos[i] - pos[i], 2);
			normD[i] = sqrt(sum);
		}


		for (i = 0; i < dataset->snackTypeNum; i++)
		{
			pos[i] = normD[i] * exp(Spiral_Coefficient * r) * cos(2.0 * PI * r) + pop->bestPos[i];

		}
		//pos[i] = AID_MAX * RAND_01;
	}


	evaluate();
}

//!�]���l�͂����Ƌ��߂��Ă�
//�]���l���Z�o����
//argPos: �@�]���Ώۂ̃R�E�����̈ʒu
//�߂�l�F�@�]���l
void Whale::evaluate()
{
	int i, j, k, diff;
	double subvalue, ave, sd, sqrSum;
	//printf("%f\n",pos[0]);
	//pos�i�w�����j�������������ꍇ�Cvalue���Œ�]���l��
	for (j = 0; j < posLen; j++) {
		if (pos[j] < 0) {
			value = WORST_VALUE;
			break;
		}
	}

	//���for���ōŒ�]���l���o�Ȃ������ꍇ
	if (j == posLen) {
		ave = 0.0;
		sqrSum = 0.0;
		for (k = 0; k < REP_NUM; k++) {
			// ������
			for (j = 0; j < dataset->snackTypeNum; j++) {
				snackOrderNum[j] = 0;
			}
			assortOrderNum = 0;

			// �����̒�������
			//�ǂ��炩�𔻕ʂ��āC���邮��񐔂����点�Ȃ����ȁ[
			//���assort���O���P��
			for (i = 0; i < dataset->studentNum; i++) {
				//setSnackNum(�⏕�z�{���Q�z�@���@�y���y���Z�b�g�̒l�i)
				studentList[i]->setSnackNum((int)pos[posLen - 1] + dataset->maxAmount);
				for (j = 0; j < dataset->snackTypeNum; j++) {
					//���َq�̌�������z��C�@i�Ԗڂ̎����������̂��َq�𒍕�������
					//���َq�̓Y�����𓮂���
					snackOrderNum[j] += studentList[i]->snackOrderNum[j];
				}
				//�y���y���Z�b�g��
				assortOrderNum += studentList[i]->assortOrderNum;
			}

			// �����v�Z
			//subvalue;�@����
			subvalue = 0;
			//���َq�̎�ނ��Ƃɑ������v�Z
			for (j = 0; j < dataset->snackTypeNum; j++) {
				//diff:�q���������������ƁC�������̍�		
				diff = snackOrderNum[j] - (int)pos[j];
				if (diff > 0) {
					//���َq�̕s�����Ă��镪�C���[�g�������đ����ɉ��Z
					//�s�����@�~�@���َq�̒l�i�@�~�@���[�g
					subvalue += diff * (int)(dataset->snackPrice[j] * dataset->additionalRate);
				}
				else if (diff < 0) {
					//�����̒�����葽���d����Ă��܂����ꍇ
					//�ߕ������̂܂ܑ����ɉ��Z�����
					subvalue += -diff * dataset->snackPrice[j];
				}
			}
			//�y���y���Z�b�g�̒������~�⏕�z�@
			//���������Ȃ�
			//�⏕�z���ǂ����邩
			subvalue += (int)pos[posLen - 1] * assortOrderNum;
			ave += subvalue;
			sqrSum += subvalue * subvalue;
		}

		//�]���l�̎Z�o
		//Avei, SD
		ave /= REP_NUM;
		sd = sqrt(sqrSum / REP_NUM - ave * ave);
		value = ave + sd;
	}
}