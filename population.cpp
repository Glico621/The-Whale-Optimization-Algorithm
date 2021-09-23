#include "population.h"

//�R���X�g���N�^
Population::Population(char* filename)
{
	int i, best;

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
	//newWhale = new Whale(this);
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
	int i, best;

	//���ׂẴN�W�����ړ�����
	for (i = 0; i < POP_SIZE; i++)
	{
		whale[i]->move(aValue);
	}

	//�ŗǂ��L�^����
	best = -1;
	for (i = 0; i < POP_SIZE; i++)
	{
		if (bestValue > whale[i]->value)
		{
			best = i;
		}
	}
	if (best != -1)
	{
		for (i = 0; i < Whale::posLen; i++)
		{
			bestPos[i] = whale[best]->pos[i];
		}
		bestValue = whale[best]->value;
	}
}

//�X�e�b�v���Ƃ�a�����炷
double Population::decrease(double aValue)
{
	aValue -= 0.005;
	if (aValue < 0)
	{
		aValue = 0;
	}

	return aValue;
}

void Population::saveBestPos()
{
	int i, best;

	//���ǂ�value�̂���i���L�^
	best = -1;
	for (i = 0; i < POP_SIZE; i++) {
		if (bestValue > whale[i]->value) {
			best = i;
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