#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// round (floor) number to 2 places 
double get_floor(double val) {
	int flag = 0;
	if (val < 0) {
		val *= -1;
		flag = 1;
	}
	double new_val = val * 100; // 1.3499 * 100 = 134.99
	new_val = floor(new_val); // 134.00
	new_val /= 100; // 134.00 / 100 = 1.34
	if (flag) {
		new_val *= -1;
	}
	return new_val;
}

// counts credit/degit interest
double get_interest (double balance, double interest, int date) {
	for (int i = 0; i < date; ++i) {
		balance += (interest/100) * balance; // gets interest % of balance
		balance = get_floor(balance);
	}
	return balance;
}

// counts balance
int get_balance (double credit, double debit) {
	printf("Zadejte transakce:\n");
	int date, prev_date = 0, diff_date = 0, start = 1;
	double deposit, balance = 0, prev_deposit = 0;
	// input for balance per deposit 
	while ( 1 )
	{
		if (scanf("%d, %lf", &date, &deposit) != 2 || date < prev_date) {
			return 1;
		}
		if (start) {
			prev_date = date;
			start = 0;
		}
		diff_date = date - prev_date; // number of days between deposits
		prev_date = date;
		balance += prev_deposit;
		if (balance >= 0) {
			balance = get_interest(balance, credit, diff_date); // gets credit interest
		}
		else {
			balance = get_interest(balance, debit, diff_date); // gets debet interest
		}
		prev_deposit = deposit;
		if (deposit==0) {
			break;
		}
	}
	printf("Zustatek: %.02lf\n", balance);
	return 0;
}

int main (void) {
	// input for credit and debit interest
	double credit, debit;
	printf("Zadejte kreditni urok [%%]:\n");
	if ( scanf(" %lf", &credit) != 1 || credit < 0 ) {
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Zadejte debetni urok [%%]:\n");
	if ( scanf(" %lf", &debit) != 1 || debit < 0 ) {
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	// return 1 if balance can't be counted
	if ( get_balance(credit, debit) ) {
		printf("Nespravny vstup.\n");
		return 1;
	}

	return 0;
}