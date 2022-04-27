#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void ledgersetMode();
void ledgerMode();

int balance = -1;  // �ܾ� �ʱⰪ
int choice = 0;  // ���ð� �ʱ⼳��
FILE *fp = NULL;  // ���� ������� ���� ������ ����

void ledgersetMode() {
	fp = fopen("list.txt", "w");
	printf(" ======�����=======\n");
	printf("\n���� �ڻ��� �Է����ּ���. \n");  //�����ڻ��� �Է¹޴´�.
	scanf("%d", &balance);
	if (balance == 0) {
		printf("�ڻ꿡 0���� �Է��Ͽ� ����˴ϴ�.\n");
	}
	else {
		printf("\n���� �ܾ� : %d �� �ԷµǾ����ϴ�.\n", balance);
		fprintf(fp, "\n�ܾ��� %d ��\n", balance);
	}
	fclose(fp);
}

void ledgerMode() {
	int line_count = 0;
	int max = 0;  //����
	int min = 0;  //����
	char buffer[128];

	//list.txt ������ ������ ���� �м��ϱ� ���� if ��
	if (0 == fopen_s(&fp, "list.txt", "rt")) { 
		while (fgets(buffer, 128, fp) != NULL) {
			line_count++;
		}
		printf("%s", buffer);
		fclose(fp);
	} // ��������� buffer�� ������ ���� ����Ű�� ��.

	char *comment = malloc(sizeof(char) * 20); // ���� ������ ����� �� ���� �޸𸮸� ����ϱ� ����
	char *ptr = strtok(buffer, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
	balance = atoi(strtok(NULL, " ")); // �߸� ���ڿ����� �ܾװ��� �о�� balance�� ����.

	while (choice != 4) {
		fp = fopen("list.txt", "a+"); 
		printf("\n��� ���� (1.����  2.����  3.�ܾ� ��ȸ  4.����) :  ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: //������ �����ҽ�
			printf("���� �׸� : ");
			scanf(" %[^\n]s", comment);
			printf("���� �ݾ� : ");
			scanf("%d", &max);
			balance = balance + max;
			printf("\n (����) %s : +%d", comment, max); 
			fprintf(fp,"\n (����) %s : +%d", comment, max);
			fprintf(fp, "\n�ܾ��� %d ��\n", balance); // ������ list.txt�� ����
			printf("\n ó�� �Ǿ����ϴ�.\n");
			printf("\n �ܾ� : %d ��\n", balance); // �ݾ��� ȭ�鿡 ���
			break;

		case 2: // �Һ� ���ý�
			printf("�Һ� �׸� : ");
			scanf(" %[^\n]s", comment);
			printf("�Һ� �ݾ� : ");
			scanf("%d", &min);

			if ((balance - min) >= 0) {
				balance = balance - min;
				printf("\n (�Һ�) %s : -%d", comment, min);
				fprintf(fp, "\n (�Һ�) %s : -%d", comment, min);
				fprintf(fp, "\n�ܾ��� %d ��\n", balance);// ������ list.txt�� ����
				printf("\nó�� �Ǿ����ϴ�.\n");
				printf("\n�ܾ� : %d ��\n", balance);   //�ݾ��� ȭ�鿡 ���
			}
			else {
				printf("�ܾ׺��� ū �ݾ��� �Һ��� �� ���� �ܾ׸�ŭ�� �����մϴ�.");
				balance = 0;
				printf("\n (�Һ�) %s : -%d", comment, min);
				fprintf(fp, "\n (�Һ�) %s : -%d", comment, min);
				fprintf(fp, "\n�ܾ��� %d ��\n", balance); // ������ list.txt�� ����
				printf("\nó�� �Ǿ����ϴ�.\n");
				printf("\n�ܾ� : %d\n", balance);   //�ݾ��� ȭ�鿡 ���
			}
			break;

		case 3: //�ܾ���ȸ ���ý�
			printf("\n�� ���� �ܾ� : %d ��\n", balance); //�ݾ��� ȭ�鿡  ���
			fprintf(fp, "\n�ܾ��� %d ��\n", balance); // ������ list.txt�� ����
			printf("\nó�� �Ǿ����ϴ�.\n");
			break;

		case 4: //���Ḧ ���ý�
			fprintf(fp, "\n�ܾ��� %d ��\n", balance); // ������ list.txt�� ����
			printf("���α׷��� ���� �մϴ�. \n");
			choice = 4;
			break;

		default:
			printf("�߸��� �����ڸ� �Է��Ͽ����ϴ�.\n");
			break;
		}
		fclose(fp);		
	}
	choice = 0;
	free(comment);
}


