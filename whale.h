#pragma once

#include "Student.h"
#include "Population.h"
class Population;

//�萔�̒�`
#define TIME_MAX 200			//�J��Ԃ���
#define POP_SIZE 40				//�N�W���̌̐�
#define DECRESE 0.002			//�ϐ�aValue�̌����l�i�O���̓����_���ړ��C�㔼�͊l���E�ŗǂɌ������悤�ɂȂ�j�iaValue�̈ڍs���x�j
#define Spiral_Coefficient 1.0	//�ΐ������̌W���i�傫���قǁC�傫������j


class Whale
{
public:
	static int posLen;					//�ʒu�x�N�g���̒���
	static Dataset* dataset;			//�f�[�^�W���ւ̃|�C���^

	Whale(Population* argPop);
	~Whale();

	void move(double aValue);			//�N�W�����ړ�����

	Population* pop;					//�����Ă���N�W���Q
	double* pos;						//�ʒu
	double value;						//�]���l
	double* normD;						//best�ƌ��݂�pos�Ԃ̋���

private:
	void evaluate();					//�]���l���Z�o����

	Student** studentList;				//�����̏W��
	int* snackOrderNum;					//���َq���Ƃ̒�����
	int assortOrderNum;					//�y���y���Z�b�g�̒�����
};