#include<iostream>
#include<iomanip>
using std::cout;
using std::cin;

//This is made to update our timestamps everyday

long int date(long int u) {
	int d;
	int year = u /10000;
	int month = u / 100 - year;
	int day=u- year*10000-month*100+1;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if (day == 31) {
			month = month + 1;
			day = 1;
		}
		else {
			day += 1;

		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day ==30) {
			month = month + 1;
			day = 1;
		}
		else {
			day += 1;

		}
	}
	if (month == 2)
	{
		if ((year % 4) == 0) {
			if (day == 29) {
				month = month + 1;
				day = 1;
			}
			else {
				day += 1;

			}

		}
		else {
			if (day == 28) {
				month = month + 1;
				day = 1;
			}
			else {
				day += 1;

			}
		}
	}
	if ((month == 12) && (day == 31)) {
		year = year + 1;
		month = 1;
		day = 1;
	}
	return d = year * 10000 + month * 100 + day;
	
}

