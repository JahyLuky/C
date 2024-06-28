#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

/* 
    checks if number is prime or not
    1 -> prime
    0 -> not prime
*/
int prime_number (int a) {
    // 1 isnt prime
    if (a == 1) {
        return 0;
    }
    // number is even
    if (a % 2 == 0) {
        return 0;
    }
    // checks with odd numbers
    int new_a = sqrt(a);
    for (int i = 3; i <= new_a; i+=2) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}

/*
    gets divisors for every number in interval <start, end>
    total = 1 -> prints all divisors and number of them
    total = 0 -> number of divisors
*/
void get_divisors(int start, int end, int total) {
    int sum = 0, new_start = 0, divisor_sum = 0;
    // gets all numbers in interval <start, end>
    if (start < 4) {
        start = 4;
    }
    for (int i = start; i <= end; i++) {
        new_start = sqrt(i);
        // gets all divisors
        for (int j = 1; j <= new_start; j++) {
            // j is divisor of i
            if(i % j == 0) {
                // gets first half of divisors
                divisor_sum += j;
                // skips duplicity
                if (j == 1 || i / j == j) {
                    continue;
                }
                // gets second half of divisors
                divisor_sum += (i/j);
            }
        }
        if (prime_number(divisor_sum)) {
            sum++;
            // prints divisors if needed
            if (total) {
                printf("%d\n", i);
            }
        }
        divisor_sum = 0;
    }
    printf("Celkem: %d\n", sum);
}

int main (void) {
    printf("Intervaly:\n");
    int start, end = 0, num_input;
    char input;
    // input cycle
    while (1) {
        // checks EOF (end of input)
        if (feof (stdin)) {
            break;
        }
        num_input = scanf("%c %d %d", &input, &start, &end);
        if (input == '\n') {
            continue;
        }
        if (start < 1 || end < start || num_input != 3 || (input != '?' && input != '#')) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        if (input == '?') {
            get_divisors(start, end, 1);
        }
        if (input == '#') {
            get_divisors(start,end, 0);
        }
    }
    return 0;
}