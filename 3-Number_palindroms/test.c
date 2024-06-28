#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#endif /* __PROGTEST__ */

// Finds if given number and its radix is palindrom or not
// 1 -> number is palindrom
// 0 -> number isnt palindrom
int has_palindrome(unsigned long long num, unsigned long long radix) {
  unsigned long long palin = 0;
  unsigned long long tmp = num;
  while (tmp > 0) {
    // first digit of tmp + prev digits * radix
    palin = (tmp % radix) + (palin * radix);
    // lower tmp by 1 digit
    tmp /= radix;
  }
  // our number is equal to its palindrom
  if (num == palin) {
    return 1;
  }
  // our number isnt palindrom
  return 0;
}

// Finds next palindrom from interval <'from', 'maximal unsigned long long value'>
// 1 -> next palindrom was found 
// 0 -> next palindrom wasnt found
int nextPalindrome ( unsigned long long from, int radix, unsigned long long * next ) {
  // our radix is out of range <2, 36>
  if (radix < 2 || radix > 36) {
    return 0;
  }
  // 'from' is bigger than maximal unsigned long long value
  if (from >= 18446744073709551615LLu) {
    return 0;
  }

  int palin = 0;
  // looking for next palindrom, starting: 'from' + 1
  while (1) {
    from++;
    palin = has_palindrome(from, radix);
    if (palin) {
      // saves palindrom value
      *next = from;
      break;
    }
  }
  return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) {
  unsigned long long next;

  assert ( nextPalindrome ( 0, 2, &next ) == 1
           && next == 1 );
  assert ( nextPalindrome ( 1, 10, &next ) == 1
           && next == 2 );
  assert ( nextPalindrome ( 123, 10, &next ) == 1
           && next == 131 );
  assert ( nextPalindrome ( 188, 10, &next ) == 1
           && next == 191 );
  assert ( nextPalindrome ( 1441, 10, &next ) == 1
           && next == 1551 );
  assert ( nextPalindrome ( 95, 15, &next ) == 1
           && next == 96 ); /* 96 = 66 (radix 15) */
  assert ( nextPalindrome ( 45395, 36, &next ) == 1
           && next == 45431 ); /* 45431 = z1z (radix 36) */
  assert ( nextPalindrome ( 1027, 2, &next ) == 1
           && next == 1057 ); /* 1057 = 10000100001 (radix 2) */
  assert ( nextPalindrome ( 1000, 100, &next ) == 0
           && next == 1057 );
  assert ( nextPalindrome ( 18446744073709551614LLu, 2, &next ) == 1
           && next == 18446744073709551615LLu ); /* 18446744073709551615 = 1111111111111111111111111111111111111111111111111111111111111111 (radix 2) */
  assert ( nextPalindrome ( 18446744073709551615LLu, 2, &next ) == 0
           && next == 18446744073709551615LLu );
  return 0;
}
#endif /* __PROGTEST__ */