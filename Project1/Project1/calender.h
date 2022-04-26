#ifndef CALENDER_H_
#define CALENDER_H_
#include <stdio.h>

void calenderMode();

void printMonth(int year, int month);
void printMonthTitle(int year, int month);
void printMonthName(int month);
void printMonthBody(int year, int month);
int getStartDay(int year, int month);
int getTotalNumberOfDays(int year, int month);
int getNumberOfDaysInMonth(int year, int month);
int isLeapYear(int year);

#endif