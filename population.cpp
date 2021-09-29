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

//�N�W�����̂��ƂɈړ��C�ŗǂ��L�^
void Population::move(double aValue)
{
	int i, best;
	
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

	//best���X�V����Ă���΁C���̃N�W����pos,value��bestPos,bestValue�ɋL�^
	if (best != -1) {
		for (i = 0; i < Whale::posLen; i++) 
		{
			bestPos[i] = whale[best]->pos[i];
		}
		bestValue = whale[best]->value;
	}
}

//�X�e�b�v���Ƃ�a�����炷
//a���傫����΁C�N�W���̓����_���ɓ����₷���Ȃ�@�@�@�@�@�@�@���T�[�`
//a����������΁C�N�W���͐H���i�ŗǁj�t�߂Ɍ������₷���Ȃ�@�@���A�^�b�N
double Population::decrease(double aValue)
{
	aValue -= DECRESE;
	if (aValue < 0)
	{
		aValue = 0.0;
	}
	return aValue;
}

// ���ʂ�\������
// fileName: ���ʂ��������ރt�@�C���̖��O
void Population::printResult(char* fileName)
{
	FILE* fp;
	int i;

	// ������
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