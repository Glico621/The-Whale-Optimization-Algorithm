#include "Population.h"

//�R���X�g���N�^
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

//�f�X�g���N�^
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

//�N�W�����ǂ̕��@�ňړ������邩���肷��
void Population::move(double aValue)
{
	int i, best, check;
	
	//���ׂẴN�W�����ړ�����
	for (i = 0; i < POP_SIZE; i++)
	{
		whale[i]->move(aValue);
	}

	//���ǂ�value�̂���i���L�^
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

	//�o�O�Ώ�
	//bestPos�̒l��8�����炢�̕����ɂȂ�Ƃ�������
	//!���̃o�O�́Cpos��nan�ɂȂ��Ă邽��
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

	//!bestPos ��nan���������Ă�

	//best���X�V����Ă���΁C���̃N�W����pos,value��bestPos,bestValue�ɋL�^
	if (best != -1) {
		for (i = 0; i < Whale::posLen; i++) 
		{
			bestPos[i] = whale[best]->pos[i];
			//printf("%f\n", whale[best]->pos[i]);
		}
		bestValue = whale[best]->value;
	}
	//bestPos�̎Z�o�͂���
}

//�X�e�b�v���Ƃ�a�����炷
double Population::decrease(double aValue)
{
	aValue -= DECRESE;
	if (aValue < 0)
	{
		aValue = 0.0;
	}
	return aValue;
}

//�����̃��[�v�͂���
//�ŗǕ]���l���L�^����
/*
void Population::saveBestPos()
{
	int i, best;

	//���ǂ�value�̂���i���L�^

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
	//best���X�V����Ă���΁C����flower��pos,value��bestPos,bestValue�ɋL�^
	if (best != -1) {
		for (i = 0; i < Whale::posLen; i++) {
			bestPos[i] = whale[best]->pos[i];
		}
		bestValue = whale[best]->value;
	}

}
*/

// ���ʂ�\������
// fileName: ���ʂ��������ރt�@�C���̖��O
void Population::printResult(char* fileName)
{
	FILE* fp;
	int i;

	// ������
	//�G���[
	if ((fp = fopen(fileName, "w")) == NULL) {
		printf("�t�@�C��%s���J���܂���D\n", fileName);
		exit(-1);
	}
	//�َq���ɍŗǐH�����̈ʒu����������
	for (i = 0; i < dataset->snackTypeNum; i++) {
		fprintf(fp, "%d,", (int)bestPos[i]);
	}
	//�Ō���̓y���y���Z�b�g�̒l�i
	fprintf(fp, "%d,", (int)bestPos[i] + dataset->maxAmount);
	fclose(fp);
}