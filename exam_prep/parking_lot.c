/*
Úkolem je vytvořit program, který bude spravovat poplatky za parkování.

Předpokládáme parkoviště, které vybírá poplatky za parkování. Při vjezdu se zaznamená čas a registrační značka vozu, při výjezdu se podle registrační značky a času spočte doba parkování a z té i následně cena za použití parkoviště. Správu příjezdů, odjezdů a výpočtů parkovacích poplatků má na starosti Váš program.

Parkovací poplatky jsou dané celkovým časem parkování:

30 minut a méně                       zdarma
od 30 minut do 60 minut včetně        30 Kč
od 60 minut do jednoho dne včetně     40 Kč za každou započatou hodinu,
od jednoho dne                        1000 Kč za každý započatý den.

Např. pro příjezd v 10:45 a odjezd v 11:45 je doba parkování 60 minut, tedy cena 30 Kč. Pro odjezd o minutu později (v 11:46) by doba parkování byla 61 minut, tedy 1 celá a jedna načatá hodina a cena by vyšla na 2*40 Kč.

Program dostává na vstupu log příjezdů a odjezdů. Log je řazen chronologicky, začíná vždy časovým údajem (hodina a minuta). Registrační značky v logu jsou libovolné řetězce o délce nejvýše 10 znaků. Je garantováno, že neobsahují bílé znaky. Program musí rozpoznávat následující požadavky:

H:M + RZ znamená příjezd vozidla, program si informaci o vozidle uloží do svých dátových struktur. Zvláštním specifikem našeho parkoviště je, že se do něj vejde neomezený počet vozidel.
H:M - RZ znamená odjezd vozidla. Program pro dané vozidlo vypočte je parkovací poplatek a ten zobrazí. Pokud zadána RZ není známa (daný automobil aktuálne na parkovišti neparkuje), program to zobrazí a pokračuje dále ve zpracování dalších záznamů.
0:00 = znamená značku pro další den. Tato značka se v logu objeví vždy v 0:00 (nesmí se objevit s jiným časem).
Výstupem programu je reakce na zpracování jednotlivých příjezdů a odjezdů. Pokud je příjezd zpracován správně, program pouze zobrazí informaci OK. U odjezdů je zobrazena RZ a vypočtená cena za parkování. Pokud je správně přečten celý vstup, program nakonec ještě zobrazí obsazení parkoviště.
Pokud je vstup neplatný, program to musí detekovat, zobrazit chybové hlášení a ukončit se. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

je zadaný neplatný časový údaj (správně je 0:00 až 23:59, v zápisu musí být uvedená dvojtečka),
je zadaný jiný pokyn než příjezd / odjezd / značka pro nový den (tj. + / - / = ),
chybí RZ přijíždějícího nebo odjíždějícího automobilu,
časový údaj v logu klesá. Mezi dvojicí po sobě jdoucích záznamů o příjezdu/odjezdu musí čas buď růst nebo musí zůstat stejný. Výjimkou je značka pro další den, u té naopak musí být vždy uveden čas 0:00.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>

typedef struct parking_lot {
    char *name;
    int hour;
    int min;
    int day;
} park;

void freePark (park ** arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]->name);
        free(arr[i]);
    }
    free(arr);
}

int findCar (park ** arr, int size, char * str) {
    for (int i = 0; i < size; i++) {
        if (strcasecmp(arr[i]->name, str) == 0) {
            return i;
        }
    }
    return -1;
}

int countPrice (int h1, int m1, int h2, int m2) {
    int sum1 = h2 * 60 + m2;
    int sum2 = h1 * 60 + m1;
    int sum = sum1 - sum2;
    //printf("sum = %d\n", sum);
    if (sum <= 30) {
        return 0;
    }
    if (sum > 30 && sum <= 60) {
        return 30;
    }
    if (sum > 60 && sum <= (24*60)) {
        if (sum % 60 == 0) {
            return 40 * (sum / 60);
        } else {
            return 40 * ((sum / 60) + 1);
        }
    }
    return -1;
}

int main (void) {
    printf("Log:\n");
    int size = 1;
    park ** arr = (park**) malloc(size * sizeof(**arr));
    char str[10];
    char c;
    int hour = 0, min = 0, last_hour = 0, last_min = 0;
    int car_cnt = 0, car_id = 0, id = 0, price = 0;
    int add = 0, in = 0;
    while (1) {
        if (feof(stdin)) {
            printf("Pocet automobilu v garazi: %d\n", car_cnt);
            break;
        }

        in = scanf("%d:%d %c", &hour, &min, &c);
        //printf("in %d\n", in);
        if (in == -1) {
            continue;
        }

        if (hour < 0 || hour > 23 || min < 0 || min > 59) {
            printf("fail time\n");
            freePark(arr, id);
            return 1;
        }
        if (last_hour > hour && (hour != 0 && min != 0 && c != '=')) {
            printf("fail hour\n");
            freePark(arr, id);
            return 1;
        }
        if (last_hour == hour && (hour != 0 && min != 0 && c != '=')) {
            if (last_min > min) {
                printf("fail min\n");
                freePark(arr, id);
                return 1;
            }
        }
        last_hour = hour;
        last_min = min;

        if (c == '+') {
            scanf("%10s", str);
            if (size == id) {
                size *= 2;
                arr = (park**) realloc(arr, size * sizeof(**arr));
            }
            arr[id] = (park *) malloc (sizeof(park));
            arr[id]->hour = hour;
            arr[id]->min = min;
            arr[id]->day = 0;
            arr[id]->name = strdup(str);
            id++;
            printf("OK\n");
            car_cnt++;
        }
        else if (c == '-') {
            scanf("%10s", str);
            car_id = findCar(arr, id, str);
            if (car_id == -1) {
                printf("Nenalezeno\n");
                continue;
            }
            if (arr[car_id]->day == 0) {
                price = countPrice(arr[car_id]->hour, arr[car_id]->min, hour, min);
            } else {
                if (hour > arr[car_id]->hour) {
                    add = 1000;
                }

                if (hour == arr[car_id]->hour) {
                    if (min > arr[car_id]->min) {
                        add = 1000;
                    }
                }
                price = arr[car_id]->day * 1000;
                price += add;
                add = 0;
            }
            printf("RZ: %s, cena: %d\n", arr[car_id]->name, price);
            free(arr[car_id]->name);
            arr[car_id]->name = strdup(" ");
            car_cnt--;
        }
        else if (c == '=' && hour == 0 && min == 0) {
            last_hour = 0;
            last_min = 0;
            for (int i = 0; i < id; i++) {
                arr[i]->day += 1;
            }
        }
        else {
            printf("fail char\n");
            freePark(arr, id);
            return 1;
        }
    }
    freePark(arr, id);
    return 0;
}