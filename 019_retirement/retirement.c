#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution, rate_of_return;
};
typedef struct _retire_info retire_info;
double calculate(int months,
                 double balance1,
                 double return1,
                 int current_m,
                 double contribution1) {
  for (int i = 1; i <= months; i++) {
    int year = current_m / 12;
    int m = current_m - 12 * year;
    printf("age %3d month %2d you have $%.2lf\n", year, m, balance1);
    balance1 = balance1 * return1 + balance1 + contribution1;
    current_m += 1;
  }
  return balance1;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  double current = initial;
  int current_m = startAge;
  current = calculate(
      working.months, current, working.rate_of_return, current_m, working.contribution);
  current_m += working.months;
  current = calculate(
      retired.months, current, retired.rate_of_return, current_m, retired.contribution);
}
int main(void) {
  retire_info working;
  retire_info retired;
  retirement(327, 21345, working, retired);
  return 0;
}
