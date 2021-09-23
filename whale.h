#pragma once

#include "Student.h"
#include "population.h"
class Population;

//�萔�̒�`
#define TIME_MAX 500			//�J��Ԃ���
#define POP_SIZE 10				//�N�W���̌̐�
#define DECRESE 0.001			//�ϐ�a�̌����l�i�O���̓����_���ړ��C�㔼�͊l���Ɍ������j�ia�̈ȍ~���x�j
#define Spiral_Coefficient 	1	//�ΐ������̌W���i�傫���قǁC�傫������j


class Whale
{
public:
	static int posLen;					//�ʒu�x�N�g���̒���
	static Dataset* dataset;			//�f�[�^�W���ւ̃|�C���^

	Whale(Population* argPop);
	~Whale();

	void move(double aValue);						//�N�W�����ړ�����

	Population* pop;					//�����Ă���N�W���Q
	double* pos;						//�ʒu
	double value;						//�]���l
	double* r1;							//�ʒu�����p�����z��P
	double* r2;							//�ʒu�����p�����Q
	double* A;							//�����_���W���x�N�g��
	double* C;							//�����_���W���x�N�g��
	//double* D;							//�A�^�b�N�p�x�N�g��

private:
	void evaluate();					//�]���l���Z�o����
	double* newPos1;						//�V�����ʒu�i�ǂ��R�E�����̋߂��j
	double* newPos2;						//�V�����ʒu�i�����_���j

	Student** studentList;				//�����̏W��
	int* snackOrderNum;					//���َq���Ƃ̒�����
	int assortOrderNum;					//�y���y���Z�b�g�̒�����
};