#include <iostream>



int main()
{
	time_t t; //секунды с 1970г
	tm tm; //локальное время

	time(&t); //текущее кол-во секунд
	localtime_s(&tm, &t);

	printf(
		"%d.%d.%d %d:%d:%d",
		tm.tm_mday,
		tm.tm_mon + 1,
		tm.tm_year + 1900,
		tm.tm_hour,
		tm.tm_min,
		tm.tm_sec
	);
}