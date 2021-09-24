#pragma once

#include "Student.h"
#include "Population.h"
class Population;

//�萔�̒�`
#define TIME_MAX 100			//�J��Ԃ���
#define POP_SIZE 30				//�N�W���̌̐�
#define DECRESE 0.008			//�ϐ�a�̌����l�i�O���̓����_���ړ��C�㔼�͊l���Ɍ������悤�ɂȂ�j�ia�̈ȍ~���x�j
#define Spiral_Coefficient 	1	//�ΐ������̌W���i�傫���قǁC�傫������j


class Whale
{
public:
	static int posLen;					//�ʒu�x�N�g���̒���
	static Dataset* dataset;			//�f�[�^�W���ւ̃|�C���^

	Whale(Population* argPop);
	~Whale();

	void move(double aValue, int base);						//�N�W�����ړ�����

	Population* pop;					//�����Ă���N�W���Q
	double* pos;						//�ʒu
	double value;						//�]���l
	double* r1;							//�ʒu�����p�����z��P
	double* r2;							//�ʒu�����p�����Q
	double* randA;						//�����_���W���x�N�g��
	double* randC;						//�����_���W���x�N�g��
	double* normD;						//best�ƌ��݂�pos�Ԃ̋���

private:
	void evaluate();					//�]���l���Z�o����

	Student** studentList;				//�����̏W��
	int* snackOrderNum;					//���َq���Ƃ̒�����
	int assortOrderNum;					//�y���y���Z�b�g�̒�����
};