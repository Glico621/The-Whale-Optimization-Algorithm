#pragma once

#include "Student.h"
#include "Population.h"
class Population;

//�萔�̒�`
#define TIME_MAX 100			//�J��Ԃ���
#define POP_SIZE 25				//�N�W���̌̐�
#define DECRESE 0.013			//�ϐ�aValue�̌����l�i�O���̓����_���ړ��C�㔼�͊l���Ɍ������悤�ɂȂ�j�iaValue�̈ڍs���x�j
#define Spiral_Coefficient 	1	//�ΐ������̌W���i�傫���قǁC�傫������j

//TIME_MAX * DECREASE = 2.0  ���ƁC�I���^�C�~���O��aValue��0�ɂȂ�@
//�������C2����1���x���Ǐ����Ɋׂ�₷����K�X
//����������ƁC�悳�����ȏꏊ���\���ɒT���ł��Ȃ�

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
	double* normD;						//best�ƌ��݂�pos�Ԃ̋���

private:
	void evaluate();					//�]���l���Z�o����

	Student** studentList;				//�����̏W��
	int* snackOrderNum;					//���َq���Ƃ̒�����
	int assortOrderNum;					//�y���y���Z�b�g�̒�����
};