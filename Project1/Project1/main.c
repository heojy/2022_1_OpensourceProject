#include <stdio.h>
#include "calender.h"
#include "todolist.h"
#pragma warning(disable:4996)

int main(void) {
	int choice = 0;
	while (choice != 5) {
		printf("�޴� : 1. �޷� ����ϱ�, 2. ���θ���Ʈ �ۼ��ϱ�, 3. ����� ���� ����, 4. �����, 5. ���� !  : ");
		scanf("%d", &choice);

		// �޴� �Է¿� ���� �Լ� �۵�
		switch (choice) {
		case 1:
			calenderMode(); // Ķ���� ���
			break;
		case 2:
			todolistmode(); // ���θ���Ʈ ��� 
			break;
		case 3:
			ledgersetMode(); // ����� �ܾ� �������
			break;
		case 4:
			ledgerMode(); // ����� ��� ���
			break;
		default: // �߸� �Է½� ���Է�
			break;
		}
	}
	return 0;
}