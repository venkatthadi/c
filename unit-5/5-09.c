#include <stdio.h>

int days_per_month[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int *year, int *month, int *day){
        int i, leap = *year % 4 == 0 && *year % 100 != 0 || *year % 400 == 0;
        if(*year < 0 || *month < 1 || *day < 1 || *day > days_per_month[leap][*month]|| *month > 12)
                return -1;
        for(i = 1; i < *month; i++)
                *day += days_per_month[leap][i];
        return *day;
}

void month_day(int *year, int *days, int *pmonth, int *pday){
        int i, leap = *year % 4 == 0 && *year % 100 != 0 || *year % 400 == 0;
        if(*year < 0 || *days < 1 || *days > (leap ? 366 : 365))
                return;
        for(i = 1; *days > days_per_month[leap][i]; i++){
                *days -= days_per_month[leap][i];
        }
        *pmonth = i;
        *pday = *days;
}

int main(){
	int year = 2003, month = 3, day = 11;
        printf("day of the year - %d\n", day_of_year(&year, &month, &day));
        int m = 0, d = 0, y = 2003, days = 51;
        month_day(&y, &days, &m, &d);
        printf("%d %d %d\n", d, m, y);
        return 0;
}

