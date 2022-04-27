#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void ledgersetMode();
void ledgerMode();

int balance = -1;  // 잔액 초기값
int choice = 0;  // 선택값 초기설정
FILE *fp = NULL;  // 파일 입출력을 위한 포인터 설정

void ledgersetMode() {
	fp = fopen("list.txt", "w");
	printf(" ======가계부=======\n");
	printf("\n현재 자산을 입력해주세요. \n");  //현재자산을 입력받는다.
	scanf("%d", &balance);
	if (balance == 0) {
		printf("자산에 0원을 입력하여 종료됩니다.\n");
	}
	else {
		printf("\n계좌 잔액 : %d 원 입력되었습니다.\n", balance);
		fprintf(fp, "\n잔액은 %d 원\n", balance);
	}
	fclose(fp);
}

void ledgerMode() {
	int line_count = 0;
	int max = 0;  //수입
	int min = 0;  //수출
	char buffer[128];

	//list.txt 파일의 마지막 줄을 분석하기 위한 if 문
	if (0 == fopen_s(&fp, "list.txt", "rt")) { 
		while (fgets(buffer, 128, fp) != NULL) {
			line_count++;
		}
		printf("%s", buffer);
		fclose(fp);
	} // 결과적으로 buffer는 마지막 줄을 가리키게 됨.

	char *comment = malloc(sizeof(char) * 20); // 수입 지출을 기록할 때 동적 메모리를 사용하기 위함
	char *ptr = strtok(buffer, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
	balance = atoi(strtok(NULL, " ")); // 잘린 문자열에서 잔액값을 읽어와 balance에 저장.

	while (choice != 4) {
		fp = fopen("list.txt", "a+"); 
		printf("\n기능 선택 (1.수입  2.지출  3.잔액 조회  4.종료) :  ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: //수입을 선택할시
			printf("수입 항목 : ");
			scanf(" %[^\n]s", comment);
			printf("수입 금액 : ");
			scanf("%d", &max);
			balance = balance + max;
			printf("\n (수입) %s : +%d", comment, max); 
			fprintf(fp,"\n (수입) %s : +%d", comment, max);
			fprintf(fp, "\n잔액은 %d 원\n", balance); // 내역을 list.txt에 저장
			printf("\n 처리 되었습니다.\n");
			printf("\n 잔액 : %d 원\n", balance); // 금액을 화면에 출력
			break;

		case 2: // 소비를 선택시
			printf("소비 항목 : ");
			scanf(" %[^\n]s", comment);
			printf("소비 금액 : ");
			scanf("%d", &min);

			if ((balance - min) >= 0) {
				balance = balance - min;
				printf("\n (소비) %s : -%d", comment, min);
				fprintf(fp, "\n (소비) %s : -%d", comment, min);
				fprintf(fp, "\n잔액은 %d 원\n", balance);// 내역을 list.txt에 저장
				printf("\n처리 되었습니다.\n");
				printf("\n잔액 : %d 원\n", balance);   //금액을 화면에 출력
			}
			else {
				printf("잔액보다 큰 금액을 소비할 수 없어 잔액만큼을 지출합니다.");
				balance = 0;
				printf("\n (소비) %s : -%d", comment, min);
				fprintf(fp, "\n (소비) %s : -%d", comment, min);
				fprintf(fp, "\n잔액은 %d 원\n", balance); // 내역을 list.txt에 저장
				printf("\n처리 되었습니다.\n");
				printf("\n잔액 : %d\n", balance);   //금액을 화면에 출력
			}
			break;

		case 3: //잔액조회 선택시
			printf("\n내 계좌 잔액 : %d 원\n", balance); //금액을 화면에  출력
			fprintf(fp, "\n잔액은 %d 원\n", balance); // 내역을 list.txt에 저장
			printf("\n처리 되었습니다.\n");
			break;

		case 4: //종료를 선택시
			fprintf(fp, "\n잔액은 %d 원\n", balance); // 내역을 list.txt에 저장
			printf("프로그램을 종료 합니다. \n");
			choice = 4;
			break;

		default:
			printf("잘못된 연산자를 입력하였습니다.\n");
			break;
		}
		fclose(fp);		
	}
	choice = 0;
	free(comment);
}


