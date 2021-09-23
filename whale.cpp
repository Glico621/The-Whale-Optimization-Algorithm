#include "whale.h"

//static�ϐ��̏�����
int Whale::posLen = -1;
Dataset* Whale::dataset = NULL;

//�R���X�g���N�^�ƃ��j���[���C�A�f�B�V���i�����[�g�̍����ŕ��� �A�f�B�V���i�����[�g�P���ƁC�ǉ������ƈꏏ
//����ȏ�C����ȉ��ŕ��򂷂�Ƃ�������

//�R���X�g���N�^
//argPop: �����Ă���N�W���Q
Whale::Whale(Population* argPop)
{
	int i;
	pop = argPop;

	r1 = new double[posLen];
	r2 = new double[posLen];
	A = new double[posLen];
	C = new double[posLen];


	pos = new double[posLen];
	printf("%f", pos[0]);
	newPos1 = new double[posLen];
	newPos2 = new double[posLen];
	snackOrderNum = new int[dataset->snackTypeNum];
	for (i = 0; i < dataset->snackTypeNum; i++)
	{
		pos[i] = dataset->maxAmount / dataset->snackPrice[i] * dataset->studentNum * RAND_01;
		snackOrderNum[i] = -1;
	}printf("\n");
	//!����RAND01�ǂ��ɂ�������
	pos[i] = AID_MAX * RAND_01;
	assortOrderNum = -1;

	studentList = new Student * [dataset->studentNum];
	for (i = 0; i < dataset->studentNum; i++)
	{
		studentList[i] = new Student();
	}

	
	for (i = 0; i < posLen; i++)
	{
		//printf("%d\n ", pos[i]);
	}
	printf("\n");
	
	evaluate();
}

//�f�X�g���N�^
Whale::~Whale()
{
	int i;

	delete[] r1;
	delete[] r2;
	delete[] A;
	delete[] C;
	delete[] pos;
	delete[] newPos1;
	delete[] newPos2;
	delete[] snackOrderNum;
	for (i = 0; i < dataset->studentNum; i++) {
		delete studentList[i];
	}
	delete[] studentList;
}

//�N�W�����ړ�������
void Whale::move(double aValue)
{
	int i;
	double normA, sum, normD, r;

	//r1,r2�̏������������ŏ������C�R���X�g���N�^�ɏ�����

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

		sum = 0.0;
		for (i = 0; i < dataset->snackTypeNum; i++)
		{	
			C[i] = 2 * r2[i];
			A[i] = 2 * aValue * r1[i] - aValue;
			sum += A[i] * A[i];
		}
		normA = sqrt(sum);

		//|A|��1�����Ȃ�A�^�b�N�C1�ȏ�Ȃ�l����T��
		if (normA < 1)
		{
			//�A�^�b�N
			//D�����߂�
			sum = 0.0;
			normD = 0.0;
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				sum += pow(C[i] * pop->bestPos[i] - pos[i], 2);
			}
			normD = sqrt(sum);

			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				pos[i] = pos[i] - A[i] * normD;
			}
			pos[i] = AID_MAX * RAND_01;
		}
		else
		{
			//�T�[�`
			//�A�^�b�N�ƈقȂ�_�́C�������悪�ŗǂł͂Ȃ������_���̃N�W���ł��邱��
			sum = 0.0;
			normD = 0.0;
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				sum += pow(C[i] * pop->bestPos[i] - pos[i], 2);
			}
			normD = sqrt(sum);

			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				pos[i] = pos[i] - A[i] * normD;
			}
			pos[i] = AID_MAX * RAND_01;
		}
	}
	else
	{
		//����
		r = RAND_11;
		sum = 0.0;
		normD = 0.0;
		for (i = 0; i < dataset->snackTypeNum; i++)
		{
			sum += pow(pop->bestPos[i] - pos[i], 2);
		}
		normD = sqrt(sum);

		for (i = 0; i < dataset->snackTypeNum; i++)
		{
			pos[i] = normD * exp(Spiral_Coefficient * r) * cos(2.0 * PI * r) + pop->bestPos[i];
		}
		pos[i] = AID_MAX * RAND_01;
	}


	evaluate();
}


//�]���l���Z�o����
//argPos: �@�]���Ώۂ̃R�E�����̈ʒu
//�߂�l�F�@�]���l
void Whale::evaluate()
{
	int i, j, k, diff;
	double subvalue, ave, sd, sqrSum;

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