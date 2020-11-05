#include "gamma_batch.h"

bool batch_m(gamma_t *g) {
    char c;
    uint32_t player, x, y;

    if (read_next_uint(&player) && read_next_uint(&x) && read_next_uint(&y)) {
        skip_white_char();
        c = getchar();

        if (c == '\n') {
            if (gamma_move(g, player, x, y)) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }

            return true;
        }

        ungetc(c, stdin);
    }

    return false;
}

bool batch_g(gamma_t *g) {
    char c;
    uint32_t player, x, y;

    if (read_next_uint(&player) && read_next_uint(&x) && read_next_uint(&y)) {
        skip_white_char();
        c = getchar();

        if (c == '\n') {
            if (gamma_golden_move(g, player, x, y)) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }

            return true;
        }

        ungetc(c, stdin);
    }

    return false;
}

bool batch_b(gamma_t *g) {
    char c;
    uint32_t player;

    if (read_next_uint(&player)) {
        skip_white_char();
        c = getchar();

        if (c == '\n') {
            printf("%lu\n", gamma_busy_fields(g, player));

            return true;
        }

        ungetc(c, stdin);
    }

    return false;
}

bool batch_f(gamma_t *g) {
    char c;
    uint32_t player;

    if (read_next_uint(&player)) {
        skip_white_char();
        c = getchar();

        if (c == '\n') {
            if (player <= g->players) {
                printf("%lu\n", gamma_free_fields(g, player));
            }
            else {
                printf("0\n");
            }

            return true;
        }

        ungetc(c, stdin);
    }

    return false;
}

bool batch_q(gamma_t *g) {
    char c;
    uint32_t player;

    if (read_next_uint(&player)) {
        skip_white_char();
        c = getchar();

        if (c == '\n') {
            if (player <= g->players && gamma_golden_possible(g, player)) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }

            return true;
        }

        ungetc(c, stdin);
    }

    return false;
}

bool batch_p(gamma_t *g) {
    char *b;

    skip_white_char();
    char c = getchar();

    if (c == '\n') {
        b = gamma_board(g);

        if (!(*b)) {
            return false;
        }
        else {
            printf("%s", b);
            free(b);

            return true;
        }
    }

    return false;
}

void batch_detect(gamma_t *g, char c, int *lineCount) {
    bool flag = true;

    switch (c) {
        case 'm':
            if (!batch_m(g)) flag = false;
            break;
        case 'g':
            if (!batch_g(g)) flag = false;
            break;
        case 'b':
            if (!batch_b(g)) flag = false;
            break;
        case 'f':
            if (!batch_f(g)) flag = false;
            break;
        case 'q':
            if (!batch_q(g)) flag = false;
            break;
        case 'p':
            if (!batch_p(g)) flag = false;
            break;
        default:
            flag = false;
            break;
    }

    if (!flag) {
        fprintf(stderr, "ERROR %d\n", *lineCount);
        read_end_of_line();
    }
}

void batch_mode(gamma_t *g, int *lineCount) {
    printf("OK %d\n", *lineCount);

    char c = getchar();

    while (!feof(stdin)) {
        (*lineCount)++;

        if (c == '#' || c == '\n') {
            ungetc(c, stdin);
            read_end_of_line();
        }
        else {
            batch_detect(g, c, lineCount);
        }

        c = getchar();
    }
}