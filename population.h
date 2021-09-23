#pragma once

#include "whale.h"
class Whale;

class Population
{
public:
	Population(char* fileNmae);
	~Population();

//	void encircle();						//���񂷂�
//	void attack();							//�l���ɋ߂Â�
//	void search();							//�l����T��
	void move(double aValue);				//�N�W�����ړ�
	void printResult(char* fileName);		//���ʂ�\������
	double decrease(double aValue);			//a�̃J�E���g�����炷
	void saveBestPos();						//�ŗǐH�������L�^����

	Dataset* dataset;		//�f�[�^�Z�b�g
	Whale** whale;			//�H�����̏W�������o
	double* bestPos;		//�ŗǐH�����̈ʒu
	double bestValue;		//�ŗǐH�����̕]���l
	double a;

private:
	//Whale* newWhale;		//�V�����H����
};
