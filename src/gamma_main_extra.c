#include "gamma_main_extra.h"

bool get_mode_start(char mode, int *lineCount, bool *flag) {
    uint32_t w, h, p, a;
    char c;

    //jezeli udalo sie wczytac wszystkie wartosci
    if (read_next_uint(&w) && read_next_uint(&h) && read_next_uint(&p) && read_next_uint(&a)) {
        skip_white_char();
        c = getchar();

        if (c == '\n') {
            gamma_t *g = gamma_new(w, h, p, a);

            //jezeli udalo sie stworzyc gre
            if (g) {
                if (mode == 'B') {
                    batch_mode(g, lineCount);
                }
                else {
                    interactive_mode(g);
                }

                gamma_delete(g);

                return true;
            }
            else {
                fprintf(stderr, "ERROR %d\n", *lineCount);
            }

            gamma_delete(g);
        }
        else {
            ungetc(c, stdin);
            *flag = false;
        }
    }
    else {
        *flag = false;
    }

    return false;
}

void get_mode() {
    int lineCount = 0;
    //flaga dla zlego inputu, errora
    bool flag = true;
    char c;

    while ((c = getchar()) && !feof(stdin)) {
        flag = true;
        lineCount++;

        if (c == '#' || c == '\n') {
            ungetc(c, stdin);
            read_end_of_line();
        }
        else {
            if (c == 'B' || c == 'I') {
                if (get_mode_start(c, &lineCount, &flag)) {
                    return;
                }
            }
            else {
                flag = false;
            }

            if (!flag) {
                fprintf(stderr, "ERROR %d\n", lineCount);
                read_end_of_line();
            }
        }
    }
}