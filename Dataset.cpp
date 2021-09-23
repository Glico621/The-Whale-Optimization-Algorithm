#include "Dataset.h"

// �R���X�g���N�^
// fileName: �f�[�^�Z�b�g�̃t�@�C����
Dataset::Dataset(char *fileName)
{
	char *pos1, *pos2;
	char line[1024], paraName[32];
	int snackPriceCount = 0;
	FILE *fp;

	// �Ǎ��݃G���[�����̂��߂̏�����
	studentNum = -1;
	maxAmount = -1;
	snackTypeNum = -1;
	snackPrice = NULL;
	additionalRate = -1;

	// �Ǎ���
	if((fp = fopen(fileName, "r")) == NULL) {
		printf("�t�@�C��%s���J���܂���D\n", fileName);
		exit(-1);
	}

	//fgets�֐��@�t�@�C�����當�������s�擾
		//������ �@�����z��̃|�C���^
		//��� �@�@�@��s�̍ő啶����
		//��O �@�@�@�t�@�C���|�C���^
	//�t�@�C������擾�ł��镶���񂪂�����胋�[�v
	while(fgets(line, 1024, fp)) {
		pos1 = line;
		pos2 = strchr(pos1, ',');
		*pos2 = '\0';
		strcpy(paraName, line);
		pos1 = pos2 + 1;
		pos2 = strchr(pos1, ',');
		if(!pos2) {
			pos2 = strchr(pos1, '\n');
		}
		*pos2 = '\0';
		if(!strcmp(paraName, "studentNum")) {
			if(studentNum != -1) {
				printf("%s��������`����Ă��܂��D\n", paraName);
				exit(-1);
			}
			studentNum = atoi(pos1);
		} else if(!strcmp(paraName, "maxAmount")) {
			if(maxAmount != -1) {
				printf("%s��������`����Ă��܂��D\n", paraName);
				exit(-1);
			}
			maxAmount = atoi(pos1);
		} else if(!strcmp(paraName, "snackTypeNum")) {
			if(snackTypeNum != -1) {
				printf("%s��������`����Ă��܂��D\n", paraName);
				exit(-1);
			}
			snackTypeNum = atoi(pos1);
			snackPrice = new int [snackTypeNum];
		} else if(!strcmp(paraName, "snackPrice")) {
			if(!snackPrice) {
				printf("���َq�̉��i(snackPrice)���O�ɂ��َq�̎�ސ�(snackTypeNum)���`���Ă��������D\n");
				exit(-1);
			} else if(snackPriceCount == snackTypeNum) {
				printf("���َq�̉��i(snackPrice)�����َq�̎�ސ�(snackTypeNum)��葽����`����Ă��܂��D\n");
				exit(-1);
			}
			snackPrice[snackPriceCount++] = atoi(pos1);
		} else if(!strcmp(paraName, "additionalRate")) {
			if(additionalRate != -1) {
				printf("%s��������`����Ă��܂��D\n", paraName);
				exit(-1);
			}
			additionalRate = atof(pos1);
		}
	}
	fclose(fp);
	if(snackPriceCount != snackTypeNum) {
		printf("���َq�̉��i(snackPrice)�����َq�̎�ސ�(snackTypeNum)��菭�Ȃ���`����Ă��܂��D\n");
		exit(-1);
	}
}

// �f�X�g���N�^
Dataset::~Dataset()
{
	delete [] snackPrice;
}
