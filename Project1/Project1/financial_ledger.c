#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void ledgersetMode();
void ledgerMode();

int balance = -1;  //�ܾ�
int choice = 0;  //���û���
FILE *fp = NULL;

void ledgersetMode() {
	fp = fopen("list.txt", "w");
	printf(" ======�����=======\n");
	printf("\n���� �ڻ��� �Է����ּ���. \n");  //�����ڻ��� �Է¹޴´�.
	scanf("%d", &balance);
	if (balance == 0) {
		printf("�ڻ꿡 0���� �Է��Ͽ� ����˴ϴ�.\n");
	}
	else {
		printf("\n�ڻ� %d �� �ԷµǾ����ϴ�.\n", balance);
		fprintf(fp, "\n�ܾ��� %d ��\n", balance);
	}
	fclose(fp);
}

void ledgerMode() {
	int line_count = 0;
	int max = 0;  //����
	int min = 0;  //����
	char buffer[128];

	if (0 == fopen_s(&fp, "list.txt", "rt")) {
		while (fgets(buffer, 128, fp) != NULL) {
			line_count++;
		}
		printf("%s", buffer);
		fclose(fp);
	}
	char *ptr = strtok(buffer, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
	 balance= atoi(strtok(NULL, " "));

	while (choice != 4) {
		fp = fopen("list.txt", "a+");
		//balance = atoi(buffer);
		printf("\n��� ���� (1.����  2.����  3.�ܾ� ��ȸ  4.����) :  ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: //������ �����ҽ�
			printf("���� �ݾ� : ");
			scanf("%d", &max);
			balance = balance + max;
			fprintf(fp, "\n�ܾ��� %d ��\n", balance);
			printf("\n�ܾ� : %d\n", balance);
			printf("ó�� �Ǿ����ϴ�.\n");
			break;

		case 2: // ������ ���ý�
			printf("����  �ݾ� : ");
			scanf("%d", &min);
			if ((balance - min) >= 0) {
				balance = balance - min;
				fprintf(fp, "\n�ܾ��� %d ��\n", balance);
				printf("\n�ܾ� : %d\n", balance);   //�ݾ��� ȭ�鿡 ���
				printf("ó�� �Ǿ����ϴ�.\n");
			}
			else {
				printf("�ܾ׺��� ū �ݾ��� ������ �� ���� �ܾ׸�ŭ�� �����մϴ�.");
				balance = 0;
				fprintf(fp, "\n�ܾ��� %d ��\n", balance);
				printf("\n�ܾ� : %d\n", balance);   //�ݾ��� ȭ�鿡 ���
				printf("ó�� �Ǿ����ϴ�.\n");
			}
			break;

		case 3: //�ܾ���ȸ ���ý�
			fprintf(fp, "\n�ܾ��� %d ��\n", balance);
			printf("\n �ܾ� ��ȸ : %d\n", balance);//�ݾ��� ȭ�鿡  ���
			printf("ó�� �Ǿ����ϴ�.\n");
			break;

		case 4: //���Ḧ ���ý�
			fprintf(fp, "\n�ܾ��� %d ��\n", balance);
			printf("���α׷��� ���� �մϴ�. \n");
			choice = 4;
			break;

		default:
			printf("�߸��� �����ڸ� �Է��Ͽ����ϴ�.\n");
			break;
		}
		//fprintf(fp, "\n%d", balance);
		fclose(fp);
	}
	choice = 0;
}


