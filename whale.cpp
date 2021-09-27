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

	normD = new double[posLen];
	pos = new double[posLen];

	snackOrderNum = new int[dataset->snackTypeNum];
	for (i = 0; i < dataset->snackTypeNum; i++)
	{
		pos[i] = dataset->maxAmount / dataset->snackPrice[i] * dataset->studentNum * RAND_01;
		snackOrderNum[i] = -1;	
	}		

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

	delete[] normD;
	delete[] pos;
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
	double normA, sum, r, hogeA, hogeC;

	//01�̗���p�ɂ���Đ��񂩂���ȊO���𕪊�
	//p��0.5�����Ȃ�A�^�b�Nor�T�[�`
	if (RAND_01 < 0.5)
	{

		hogeA = 2 * aValue * RAND_01 - aValue;
		hogeC = 2 * RAND_01;

		normA = sqrt(hogeA * hogeA);

		//|A|��1�����Ȃ�A�^�b�N�C1�ȏ�Ȃ�l����T��
		if (normA < 1)
		{
			//�A�^�b�N
			//normD�́C�x�X�g��pos�ƌ��݂�pos�Ƃ̋������i�[		
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				//!������pos����
				sum = pow((hogeC * pop->bestPos[i] - pos[i]), 2);
				normD[i] = sqrt(sum);
				pos[i] = pop->bestPos[i] -  hogeA * normD[i];
			}
		}
		else
		{
			//�T�[�`
			//�A�^�b�N�ƈقȂ�_�F�������悪�ŗǂł͂Ȃ������_���̃N�W���ł��邱��

			//�N�W���̓Y��������i�����_���́j
			int	searchNum = rand() % (int)(POP_SIZE);
			
			for (i = 0; i < dataset->snackTypeNum; i++)
			{
				sum = pow((hogeC * pop->whale[searchNum]->pos[i] - pos[i]), 2);
				normD[i] = sqrt(sum);

				pos[i] = pop->whale[searchNum]->pos[i] - hogeA * normD[i];

			}
		}
	}
	else
	{
		//����
		//���邮����񂵂Ȃ���C�l�������͂�	
		r = RAND_11;	//-1����1�̗���
		for (i = 0; i < dataset->snackTypeNum; i++)
		{
			sum = pow((pop->bestPos[i] - pos[i]), 2);
			normD[i] = sqrt(sum);
			pos[i] = normD[i] * exp(Spiral_Coefficient * r) * cos(2.0 * PI * r) + pop->bestPos[i];
		}

	}

	evaluate();
}

//�]���l���Z�o����
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