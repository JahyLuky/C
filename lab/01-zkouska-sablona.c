/*
 * Simulace zkouškové úlohy:
 * - Vaším úkolem je implementovat funkci add(),
 *   která sečte dvě čísla zadaná jako spojové seznamy.
 *   od nejméně významné číslice v soustavě o základu BASE.
 * - Funkce musí testovat validitu vstupů, tedy:
 *     - Nejvyšší číslice nesmí být 0, vyjma seznamu reprezentujícího
 *       nulu.
 *     - Žádná číslice nesmí být >= BASE.
 *     - Pokud vstup není validní vraťte NULL;
 * - Neměňte nic v #ifndef __PROGTEST__ (krom přidání
 *   více testů do mainu).
 * - Program musí fungovat pro libovolnou 2 <= BASE <= 1000.
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#define BASE 2

typedef struct Digit Digit;
typedef Digit *Number;

struct Digit {
  Digit *next;
  uint32_t digit;
};

Digit* create_number(unsigned x) {
  if (!x) return NULL;
  
  Digit *d = (Digit*)malloc(sizeof(*d));
  d->next = create_number(x / BASE);
  d->digit = x % BASE;
  return d;
}

void free_number(Digit* x) {
  if (!x) return;
  free_number(x->next);
  free(x);
}
#endif

void print_list (Digit * a) {
  while (a) {
    printf("%d", a->digit);
    a = a->next;
  }
  printf("\n");
}

Digit *add (Digit *a, Digit *b) {
  if (a == NULL) {
    return b;
  }
  if (b == NULL) {
    return a;
  }

  //print_list(a);
  //print_list(b);

  Digit * c = NULL;
  uint32_t cnt = 0;
  int flag = 0;
  uint32_t i = 1;
  while (a || b) {
    // flag == 1, isnt first number
    if (flag) {
      if (a == NULL) {
        if (b->next == NULL && b->digit == 0) {
          return NULL;
        }
        if (b->digit >= BASE) {
          return NULL;
        }

        cnt += (b->digit) * (BASE * i);
        i *= BASE;
        printf("1b: %d, cnt: %d, i: %d\n", b->digit, cnt, i);

      } else if (b == NULL) {
        if (a->next == NULL && a->digit == 0) {
          return NULL;
        }
        if (a->digit >= BASE) {
          return NULL;
        }

        cnt += (a->digit) * (i * BASE);
        i *= BASE;
        printf("2a: %d, cnt: %d, i: %d\n", a->digit, cnt, i);

      // a isnt NULL, b isnt NULL
      } else {  
        if (a->next == NULL && a->digit == 0) {
          return NULL;
        }
        if (b->next == NULL && b->digit == 0) {
          return NULL;
        }
        if (b->digit >= BASE || a->digit >= BASE) {
          return NULL;
        }

        cnt += (a->digit + b->digit) * (i * BASE);
        i *= BASE;
        printf("3a: %d, b: %d, cnt: %d, i: %d\n", a->digit, b->digit, cnt, i);

      }
    } else {
        if (a == NULL) {
          if (b->digit >= BASE) {
            return NULL;
          }

          cnt += (b->digit);
          printf("1b: %d, cnt: %d, i: %d\n", b->digit, cnt, i);

      } else if (b == NULL) {
        if (a->digit >= BASE) {
          return NULL;
        }

        cnt += (a->digit);
        printf("2a: %d, cnt: %d, i: %d\n", a->digit, cnt, i);
        
      } else {
        if (a->next == NULL && a->digit == 0) {
          return NULL;
        }

        cnt += (a->digit + b->digit);
        printf("3a: %d, b: %d, cnt: %d, i: %d\n", a->digit, b->digit, cnt, i);

      }
      flag = 1;
    }

    // iteration in a and b
    if (a != NULL && b == NULL) {
      a = a->next;
    }
    if (b != NULL && a == NULL) {
      b = b->next;
    }
    if (a != NULL && b != NULL) {
      a = a->next;
      b = b->next;
    }
  }

  c = create_number(cnt);
  print_list(c);
  return c;
}

#ifndef __PROGTEST__
bool equal(Digit *a, Digit *b) {
  if (!a || !b) return a == b;
  if (a->digit != b->digit) return false;
  return equal(a->next, b->next);
}

int main() {
  /*
  Digit *aa = create_number(999);
  Digit *bb = create_number(1);
  Digit *cc = add(aa, bb);
  Digit *expp = create_number(1 + 999);
  //printf("Final: ");
  //print_list(exp);
  assert(equal(cc, expp));
  free_number(aa);
  free_number(bb);
  free_number(cc);
  free_number(expp);

  Digit *a = create_number(1001);
  Digit *b = create_number(123);
  Digit *c = add(a, b);
  Digit *exp = create_number(123 + 1001);
  //printf("Final: ");
  //print_list(exp);
  assert(equal(c, exp));
  
  Digit *d = add(c, c);
  Digit *tmp = add(exp, b);
  free_number(exp);
  exp = add(a, tmp);
  free_number(tmp);
  assert(equal(exp, d));
  free_number(d);
  free_number(exp);

  a->digit = BASE + 1;
  assert(add(a, b) == NULL);
  assert(add(b, a) == NULL);

  a->digit = 2;
  b->next->next->digit = 0;
  assert(add(a, b) == NULL);
  assert(add(b, a) == NULL);

  free_number(b);
  free_number(a);
  free_number(c);
  */
  
  
  Digit *a = create_number(1000);
  Digit *b = create_number(1000);
  Digit *c = add(a, b);
  Digit *exp = create_number(1000 + 1000);
  Digit *expp = create_number(2000);
  printf("Final: ");
  print_list(exp);
  assert(equal(c, expp));

  free_number(b);
  free_number(a);
  free_number(c);
  free_number(exp);
  free_number(expp);

 return 0;
}
#endif