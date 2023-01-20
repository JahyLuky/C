#include <stdio.h>
#include <stdlib.h>

/*
  Finds value in array
  cnt -> how many times it was found
  0 -> false
*/
int find_sum (int arr[], int size, int value) {
  int cnt = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] == value) {
        cnt++;
    }
  }
  if (cnt > 0)
    return cnt;
  return 0;
}

/*
  For all possible intervals determine its sum
  return: how many pairs of mutually different intervals have same sum
*/
int get_sums (int seq[], int size) {
  static int arr[200000];
  static int pairs[200000];
  int find_next = 0, find = 0, sum = 0;
  int id_intr = 0, id_sum = 0; 
  int intr_lenght = 0, result = 0;
  // left interval, <x, >
  for (int i = 0; i < size; i++) {
    // right interval, < , y>
    for (int j = i; j < size; j++) {
      // sum of interval
      for (int z = i; z <= j; z++) {
        sum += seq[z];
        intr_lenght++;
      }

      // lenght of interval
      if (intr_lenght > 1) {
        // finds duplicite in sums of every interval
        find = find_sum(arr, id_intr, sum);
        if (find > 0) {
          // finds another duplicites in intervals
          // with at least 1 duplicite sum
          find_next = find_sum(pairs, id_sum, sum); 
          if (find_next > 0) {
            // gets all combination of intervals
            result += find_next;
          }
          // first sum in interaval
          result++;
          pairs[id_sum++] = sum;
        }

        arr[id_intr++] = sum;
      }

      intr_lenght = 0;
      sum = 0;
    }
  }

  return result;
}

int main () {
  printf("Posloupnost:\n");
  static int seq[20000];
  int num = 0, size = -1, in = 0;
  while (1) {

    // checks EOF (end of input)
    if (feof (stdin)) {
      // sequence is empty
      if (size == 0) {
        printf("Nespravny vstup.\n");
        return 0;
      }
      break;
    }

    // scan number in sequence
    in = scanf("%d", &num);
    // -1 -> nothing
    if (in != -1 && in != 1) {
      printf("Nespravny vstup.\n");
      return 0;
    }
    size++;

    // sequence is larger then 2000
    if (size > 2000) {
      printf("Nespravny vstup.\n");
      return 0;
    }

    // add number to sequence
    seq[size] = num;
  }

  int pairs = 0;
  pairs = get_sums(seq, size);
  printf("Pocet dvojic: %d\n", pairs);

  return 1;
}