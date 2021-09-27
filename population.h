#pragma once

#include "Whale.h"
class Whale;

class Population
{
public:
	Population(char* fileNmae);
	~Population();

	void move(double aValue);				//�N�W�����ړ�
	double decrease(double aValue);			//a�̃J�E���g�����炷
	void saveBestPos();						//�ŗǐH�������L�^����
	void printResult(char* fileName);		//���ʂ�\������


	Dataset* dataset;		//�f�[�^�Z�b�g
	Whale** whale;			//�H�����̏W�������o
	double* bestPos;		//�ŗǐH�����̈ʒu
	double bestValue;		//�ŗǐH�����̕]���l
	double aValue;			//noemA(�N�W���̍s���I��)�ɗp����ϐ��C�X�e�b�v���ƂɌ���

private:

};
