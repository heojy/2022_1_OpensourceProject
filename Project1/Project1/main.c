#include <stdio.h>
#include "calender.h"
#include "todolist.h"
#pragma warning(disable:4996)

int main(void) {
	int choice = 0;
	while (choice != 5) {
		printf("메뉴 : 1. 달력 출력하기, 2. 투두리스트 작성하기, 3. 가계부 시작 설정, 4. 가계부, 5. 멈춰 !  : ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			calenderMode();
			break;
		case 2:
			runLoop();
			break;
		case 3:
			ledgersetMode();
			break;
		case 4:
			ledgerMode();
			break;
		default:
			break;
		}
	}
	return 0;
}