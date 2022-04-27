#include <stdio.h>
#include "calender.h"
#include "todolist.h"
#pragma warning(disable:4996)

int main(void) {
	int choice = 0;
	while (choice != 5) {
		printf("메뉴 : 1. 달력 출력하기, 2. 투두리스트 작성하기, 3. 가계부 시작 설정, 4. 가계부, 5. 멈춰 !  : ");
		scanf("%d", &choice);

		// 메뉴 입력에 따른 함수 작동
		switch (choice) {
		case 1:
			calenderMode(); // 캘린더 기능
			break;
		case 2:
			todolistmode(); // 투두리스트 기능 
			break;
		case 3:
			ledgersetMode(); // 가계부 잔액 설정기능
			break;
		case 4:
			ledgerMode(); // 가계부 사용 기능
			break;
		default: // 잘못 입력시 재입력
			break;
		}
	}
	return 0;
}