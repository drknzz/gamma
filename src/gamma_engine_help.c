#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamma_engine_help.h"

uint32_t get_length(uint32_t number) {
    uint32_t result = 0;

    while (number > 0) {
        number /= 10;
        result++;
    }

    return result;
}

void dfs(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    g->visited[x][y] = true;

    //sprawdzamy przed wywołaniem za każdym razem, ponieważ x, y są typu uint32_t
    if (x > 0) {
        if (g->board[x-1][y] == player && !g->visited[x-1][y]) {
            dfs(g, player, x-1, y);
        }
    }
    if (y > 0) {
        if (g->board[x][y-1] == player && !g->visited[x][y-1]) {
            dfs(g, player, x, y-1);
        }
    }
    if (x < g->width - 1) {
        if (g->board[x+1][y] == player && !g->visited[x+1][y]) {
            dfs(g, player, x+1, y);
        }
    }
    if (y < g->height - 1) {
        if (g->board[x][y+1] == player && !g->visited[x][y+1]) {
            dfs(g, player, x, y+1);
        }
    }
}

bool is_adjacent(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    if (x > 0) {
        if (g->board[x-1][y] == player) {
            return true;
        }
    }
    if (y > 0) {
        if (g->board[x][y-1] == player) {
            return true;
        }
    }
    if (x < g->width-1) {
        if (g->board[x+1][y] == player) {
            return true;
        }
    }
    if (y < g->height-1) {
        if (g->board[x][y+1] == player) {
            return true;
        }
    }
    return false;
}

bool legal_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    if (g->board[x][y] != 0) {
        return false;
    }

    if (g->areasTaken[player] == g->areas) {
        if (!is_adjacent(g, player, x, y)) {
            return false;
        }
    }

    return true;
}

uint32_t count_areas(gamma_t *g, uint32_t player) {
    for (uint32_t i = 0; i < g->width; i++) {
        for (uint32_t j = 0; j < g->height; j++) {
            g->visited[i][j] = false;
        }
    }

    uint32_t areaCount = 0;
    for (uint32_t i = 0; i < g->width; i++) {
        for (uint32_t j = 0; j < g->height; j++) {
            if (g->board[i][j] == player) {
                if (!g->visited[i][j]) {
                    dfs(g, player, i, j);
                    areaCount++;
                }
            }
        }
    }

    return areaCount;
}

char* gamma_board_many_players(gamma_t *g) {
    uint64_t size = (uint64_t)g->height * ((uint64_t)g->width * (uint64_t)g->gridSize + 1) + 1;

    char *out = malloc(sizeof(char)*size);
    if (!out) return NULL;

    int k = 0;
    for (uint32_t i = g->height; i > 0; i--) {
        for (uint32_t j = 0; j < g->width; j++) {
            if (g->board[j][i-1] == 0) {
                for (uint32_t l = 1; l < g->gridSize; l++) {
                    out[k++] = ' ';
                }
            }
            else {
                int length = snprintf(NULL, 0, "%u", g->board[j][i-1]);
                char* number = malloc(length + 1);
                if (!number) {
                    free(out);
                    return NULL;
                }
                snprintf(number, length + 1, "%u", g->board[j][i-1]);

                for (int l = 0; l < length; l++) {
                    out[k++] = number[l];
                }
                for (uint32_t l = 1; l < g->gridSize - length; l++) {
                    out[k++] = ' ';
                }

                free(number);
            }
            out[k++] = '|';
        }
        out[k++] = '\n';
    }
    out[k] = '\0';

    return out;
}

bool check_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    if (g->board[x][y] == 0 && g->board[x][y] == player) {
        return false;
    }

    uint32_t enemy, enemyAreas, playerAreas;

    if (is_adjacent(g, player, x, y)) {
        enemy = g->board[x][y];
        enemyAreas = g->areasTaken[enemy];
        playerAreas = g->areasTaken[player];

        if (gamma_golden_move(g, player, x, y)) {
            g->board[x][y] = enemy;

            g->areasTaken[player] = playerAreas;
            g->areasTaken[enemy] = enemyAreas;

            g->busyFields[player]--;
            g->busyFields[enemy]++;

            g->goldenMove[player] = true;

            return true;
        }
    }

    return false;
}

bool find_golden_move(gamma_t *g, uint32_t player) {
    for (uint32_t i = 0; i < g->width; i++) {
        for (uint32_t j = 0; j < g->height; j++) {
            if (check_golden_move(g, player, i, j)) {
                return true;
            }
        }
    }

    return false;
}