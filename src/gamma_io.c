#include "gamma_io.h"

int getche(void) {
    struct termios x, y;
    if (tcgetattr(STDIN_FILENO, &x) == -1) {
        clear_screen();
        cursor_to_home();
        printf("Broken input.\n");
        exit(1);
    }
    y = x;
    y.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &y) == -1) {
        clear_screen();
        cursor_to_home();
        printf("Broken input.\n");
        exit(1);
    }
    int c = getchar();
    if (tcsetattr(STDIN_FILENO, TCSANOW, &x) == -1) {
        clear_screen();
        cursor_to_home();
        printf("Broken input.\n");
        exit(1);
    }
    return c;
}

void read_end_of_line() {
    char c = getchar();

    while (c != '\n' && !feof(stdin)) {
        c = getchar();
    }
}

bool isWhiteCharacter(char c) {
    return (c == 32 || c == 9 || c == 11 || c == 12 || c == 13);
}

bool skip_white_char() {
    char c = getchar();

    if (!isWhiteCharacter(c)) {
        ungetc(c, stdin);
        return false;
    }

    do {
        c = getchar();
    } while (isWhiteCharacter(c));

    ungetc(c, stdin);

    return true;
}

bool read_uint(uint32_t *result) {
    char c = getchar();
    bool hasNumber = false;
    uint32_t num = 0;
    *result = 0;

    while (c >= '0' && c <= '9') {
        hasNumber = true;
        num = c - '0';

        if ((UINT32_MAX - num) / 10 >= *result) {
            (*result) *= 10;
            (*result) += num;
        }
        else {
            return false;
        }

        c = getchar();
    }

    ungetc(c, stdin);

    if (hasNumber) {
        return true;
    }

    return false;
}

bool read_next_uint(uint32_t *result) {
    if (skip_white_char()) {
        if (read_uint(result)) {
            return true;
        }
    }

    return false;
}