#include "gamma_interactive.h"

void get_terminal_size(int *width, int *height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *width = w.ws_col;
    *height = w.ws_row;
}

int bonus_text_width(gamma_t *g) {
    int result = 0;
    uint64_t fields = (uint64_t)g->width * (uint64_t)g->height;

    result += get_length(fields) * 2;
    result += get_length(g->areas) * 2;

    return result;
}

bool board_fits_in_terminal(gamma_t *g) {
    int width = 0;
    int height = 0;
    int bonusTextWidth = bonus_text_width(g);

    get_terminal_size(&width, &height);

    if ((uint64_t)width < (g->gridSize * (uint64_t)g->width)) {
        return false;
    }

    if (width < TEXT_WIDTH + bonusTextWidth) {
        return false;
    }

    if ((uint64_t)height < (uint64_t)g->height + TEXT_HEIGHT) {
        return false;
    }

    return true;
}

void set_text_color(char *color) {
    printf("%s", color);
}

void print_white_wall() {
    set_text_color(DFLT);
    printf(" | ");
}

void cursor_up_down(uint32_t count, bool down) {
    char arr[5] = {ESC, BRT, '1', ARW_UP, '\0'};

    if (down) {
        arr[3] = ARW_DWN;
    }

    for (uint32_t i = 0; i < count; i++) {
        printf("%s", arr);
    }
}

void cursor_left_right(uint32_t count, bool right) {
    char arr[5] = {ESC, BRT, '1', ARW_LFT, '\0'};

    if (right) {
        arr[3] = ARW_RGHT;
    }

    for (uint32_t i = 0; i < count; i++) {
        printf("%s", arr);
    }
}

void clear_screen() {
    char arr[5] = {ESC, BRT, '2', 'J', '\0'};
    printf("%s", arr);
}

void cursor_to_home() {
    char arr[4] = {ESC, BRT, 'H', '\0'};
    printf("%s", arr);
}

void move_cursor(gamma_t *g, uint32_t *cursor_x, uint32_t *cursor_y, char c) {
    switch (c) {
        case ARW_UP:
            if (*cursor_y < g->height - 1) {
                cursor_up_down(1, 0);
                (*cursor_y)++;
            }
            break;
        case ARW_DWN:
            if (*cursor_y > 0) {
                cursor_up_down(1, 1);
                (*cursor_y)--;
            }
            break;
        case ARW_RGHT:
            if (*cursor_x < g->width - 1) {
                cursor_left_right(g->gridSize, 1);
                (*cursor_x)++;
            }
            break;
        case ARW_LFT:
            if (*cursor_x > 0) {
                cursor_left_right(g->gridSize, 0);
                (*cursor_x)--;
            }
            break;
    }
}

void interactive_print_board(gamma_t *g, uint32_t player) {
    clear_screen();
    cursor_to_home();

    char *b = gamma_board(g);

    uint64_t row = g->width * g->gridSize + 1;
    uint64_t size = g->height * row + 1;

    uint32_t width = 0, height = g->height - 1, counter = -1;
    bool newline = false;

    for (uint64_t i = 0; i < size; i++) {
        if (newline) {
            newline = false;
            printf("%c", b[i]);
            continue;
        }

        counter++;
        if (counter == g->gridSize) {
            counter = 0;
            width++;
            if (width == g->width) {
                width = 0;
                newline = true;
                if (height > 0) {
                    height--;
                }
            }
        }

        if ((g->board[width][height] == player || player == 0) && b[i] != '|' && b[i] != '.') {
            set_text_color(YLLW);
            set_text_color(BLK);
            if (player == 0 && g->board[width][height] == 0) {
                set_text_color(DFLT);
            }
        }
        else {
            set_text_color(DFLT);
        }

        printf("%c", b[i]);
    }

    set_text_color(DFLT);
    free(b);
}

void interactive_end(gamma_t *g) {
    interactive_print_board(g, 0);

    set_text_color(BHRED);
    printf("SCORES\n");

    uint32_t spaces = 0;

    for (uint32_t i = 1; i <= g->players; i++) {
        set_text_color(BHGRN);
        printf("PLAYER %u", i);

        set_text_color(DFLT);
        spaces = g->gridSize - get_length(i);
        for (uint32_t j = 0; j < spaces; j++) {
            printf(" ");
        }

        printf(" - ");

        set_text_color(BHRED);
        printf("%lu\n", gamma_busy_fields(g, i));
    }

    set_text_color(DFLT);
}

void interactive_print_game_state(gamma_t *g, uint32_t player, bool golden) {
    interactive_print_board(g, player);

    uint64_t busy = gamma_busy_fields(g, player);
    uint64_t free = gamma_free_fields(g, player);

    set_text_color(BHMAG);
    printf("PLAYER %u\n", player);
    set_text_color(BHGRN);
    printf("FREE %lu", free);
    print_white_wall();
    set_text_color(BHRED);
    printf("SCORE %lu", busy);
    print_white_wall();
    set_text_color(BHCYN);
    printf("AREAS %u / %u\n", g->areasTaken[player], g->areas);
    if (golden) {
        set_text_color(BHYEL);
        printf("GOLDEN MOVE");
    }
    printf("\n\n");

    set_text_color(BHBLU);
    printf("     CONTROLS\n");
    printf("ARROWS   - MOVE AROUND\n");
    printf("SPACE    - PLACE PAWN\n");
    printf("G        - GOLDEN MOVE\n");
    printf("C        - SKIP TURN\n");
    printf("CTRL + D - END GAME");
    set_text_color(DFLT);
}

void interactive_cursor_to_middle(gamma_t *g, uint32_t *cursor_x, uint32_t *cursor_y) {
    cursor_to_home();

    uint32_t mid_x, mid_y;

    mid_x = g->width/2;
    if (g->width % 2 == 0) mid_x--;

    mid_y = (g->height - 1) / 2;

    *cursor_x = mid_x;
    *cursor_y = mid_y;

    cursor_up_down(g->height - mid_y - 1, 1);
    cursor_left_right(mid_x * g->gridSize, 1);
}

void interactive_cursor_to_cords(gamma_t *g, uint32_t cursor_x, uint32_t cursor_y) {
    cursor_to_home();
    cursor_up_down(g->height - cursor_y - 1, 1);
    cursor_left_right(cursor_x * g->gridSize, 1);
}

void update_cursor(gamma_t *g, uint32_t *cursor_x, uint32_t *cursor_y, bool *first) {
    if (*first) {
        interactive_cursor_to_middle(g, cursor_x, cursor_y);
        *first = false;
    }
    else {
        interactive_cursor_to_cords(g, *cursor_x, *cursor_y);
    }
}

bool check_for_moves(gamma_t *g, uint32_t *player) {
    uint32_t skipped_turns = 0;

    bool golden = gamma_golden_possible(g, *player);

    while (!gamma_free_fields(g, *player) && !golden) {
        if (++(*player) > g->players) {
            *player = 1;
        }
        skipped_turns++;

        if (skipped_turns == g->players) {
            return false;
        }

        golden = gamma_golden_possible(g, *player);
    }

    return true;
}

bool interactive_input(gamma_t *g, uint32_t player, uint32_t *cursor_x, uint32_t *cursor_y) {
    char c = getche();

    while(!feof(stdin)) {
        if (c ==  ESC) {
            c = getche();

            if (c == BRT && !feof(stdin)) {
                c = getche();

                if (!feof(stdin)) {
                    move_cursor(g, cursor_x, cursor_y, c);
                }
            }
            else {
                ungetc(c, stdin);
            }

        }
        else if (c == ' ') {
            //jezeli ruch jest legalny, wychodzi
            if (gamma_move(g, player, *cursor_x, *cursor_y)) {
                break;
            }
        }
        else if (c == 'g' || c == 'G') {
            if (gamma_golden_possible(g, player)) {
                if (gamma_golden_move(g, player, *cursor_x, *cursor_y)) {
                    break;
                }
            }
        }
        else if (c == 'c' || c == 'C') {
            break;
        }
        else if (c == 4) {
            interactive_end(g);
            return false;
        }

        if (!feof(stdin)) {
            c = getche();
        }
    }

    return true;
}

void interactive_mode(gamma_t *g) {
    bool golden, first = true;
    uint32_t player = 1, cursor_x = 0, cursor_y = 0;

    if (!board_fits_in_terminal(g)) {
        printf("Given board cannot fit in the screen.\n");
        exit(1);
    }

    while(true) {
        if (!check_for_moves(g, &player)) {
            interactive_end(g);
            return;
        }

        golden = gamma_golden_possible(g, player);

        interactive_print_game_state(g, player, golden);

        update_cursor(g, &cursor_x, &cursor_y, &first);

        if (!interactive_input(g, player, &cursor_x, &cursor_y)) {
            return;
        }

        if (++player > g->players) {
            player = 1;
        }
    }
}