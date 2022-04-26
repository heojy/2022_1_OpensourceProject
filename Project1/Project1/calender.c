#include <stdio.h>
#include <Windows.h>
#include"calender.h"
#pragma warning(disable:4996)

void calenderMode() {
	int year, month;
	printf("������ �Է��ϼ��� : ");
	scanf("%d", &year);
	printf("���� �Է��ϼ��� : ");
	scanf("%d", &month);
	printf("\n");
	printMonth(year, month);
}

//year�� month�� ���� �޾� �ش� ���� ��� -> title, body
void printMonth(int year, int month) {
	printMonthTitle(year, month);
	printMonthBody(year, month);
}

//���� �⵵�� ���
void printMonthTitle(int year, int month) {
	printMonthName(month);
	printf(" %d\n", year);
	printf("-----------------------------\n");
	printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
}

//month�� ���� �޾� �ش� ���� ���� �̸��� ���
void printMonthName(int month) {
	switch (month) {
	case 1: printf("January"); break;
	case 2: printf("February"); break;
	case 3: printf("March"); break;
	case 4: printf("April"); break;
	case 5: printf("May"); break;
	case 6: printf("June"); break;
	case 7: printf("July"); break;
	case 8: printf("August"); break;
	case 9: printf("September"); break;
	case 10: printf("October"); break;
	case 11: printf("November"); break;
	case 12: printf("December"); break;
	}
}

//year�� month�� ���� �޾� ���ϰ� ���� ���
void printMonthBody(int year, int month) {
	int startday = getStartDay(year, month);
	int numberofdaysinmonth = getNumberOfDaysInMonth(year, month);
	for (int i = 1; i < startday; i++) printf("     ");
	for (int i = 1; i <= numberofdaysinmonth; i++) {
		printf("%5d", i);
		if ((i + startday-1) % 7 == 0) printf("\n");
	}
	printf("\n");
}

// �ش� ���� �����ϴ� ���� �� �������� ã�� �Լ�
int getStartDay(int year, int month) {
	int startday1800 = 3;
	int totalnumberofdays = getTotalNumberOfDays(year, month);
	return (startday1800 + totalnumberofdays) % 7+1;
}

// 1800�� 1�� 1�� ���� ��ĥ�� �Ǵ��� ���
int getTotalNumberOfDays(int year, int month) {
	int total = 0;
	for (int i = 1800; i < year; i++) {
		if (isLeapYear(i)) total += 366;
		else total += 365;
	}
	for (int i = 1; i < month; i++) total = total + getNumberOfDaysInMonth(year, i);
	return total;
}

//year�� month�� ���� �޾� �ش���� ��ĥ�� �ִ���
int getNumberOfDaysInMonth(int year, int month) {
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
	if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	if (month == 2) {
		if (isLeapYear(year) == 1) return 29;
		else return 28;
	}
}

//year�� ���޹޾� �������� Ȯ��
int isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) return 1;
	else return 0;
}