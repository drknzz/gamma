#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gamma.h"
#include "gamma_engine_help.h"

gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
    if (width == 0 || height == 0 || players == 0 || areas == 0) return NULL;

    gamma_t *g = NULL;
    bool ok = true;

    g = malloc(sizeof(gamma_t));
    if (!g) return NULL;

    g->width = width;
    g->height = height;
    g->players = players;
    g->areas = areas;
    g->gridSize = get_length(players);

    if (players > 9) (g->gridSize)++;

    g->board = malloc(sizeof(uint32_t*)*g->width);
    if (!g->board) ok = false;
    else {
        for (uint32_t i = 0; i < g->width; i++) {
            g->board[i] = calloc(g->height, sizeof(uint32_t));
            if (g->board[i] == NULL) {
                ok = false;
                break;
            }
        }
    }

    g->busyFields = calloc(players+1, sizeof(uint64_t));
    if (!g->busyFields) ok = false;

    g->goldenMove = malloc(sizeof(bool)*(players+1));
    if (!g->goldenMove) ok = false;
    else {
        for (uint32_t i = 1; i < players + 1; i++) {
            g->goldenMove[i] = true;
        }
    }

    g->areasTaken = calloc(players+1, sizeof(uint32_t));
    if (!g->areasTaken) ok = false;

    g->visited = calloc(g->width, sizeof(bool*));
    if (!g->visited) ok = false;
    else {
        for (uint32_t i = 0; i < g->width; i++) {
            g->visited[i] = calloc(g->height, sizeof(bool));
            if (!g->visited[i]) {
                ok = false;
                break;
            }
        }
    }

    if (!ok) {
        gamma_delete(g);
        return NULL;
    }

    return g;
}

void gamma_delete(gamma_t *g) {
    if (!g) return;
    if (g->board) {
        for (uint32_t i = 0; i < g->width; i++) {
            free(g->board[i]);
        }
    }
    if (g->visited) {
        for (uint32_t i = 0; i < g->width; i++) {
            free(g->visited[i]);
        }
    }
    free(g->board);
    free(g->visited);
    free(g->busyFields);
    free(g->goldenMove);
    free(g->areasTaken);
    free(g);
}

bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || player == 0 || player > g->players || x >= g->width || y >= g->height) {
        return false;
    }

    if (!legal_move(g, player, x, y)) {
        return false;
    }

    g->board[x][y] = player;
    g->busyFields[player]++;

    if (g->areasTaken[player] < g->areas && !is_adjacent(g, player, x, y)) {
        g->areasTaken[player]++;
    }
    else {
        g->areasTaken[player] = count_areas(g, player);
    }

    return true;
}

bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || player == 0 || player > g->players || x >= g->width || y >= g->height) {
        return false;
    }

    if (!g->goldenMove[player]) {
        return false;
    }

    if (g->board[x][y] == 0 || g->board[x][y] == player) {
        return false;
    }

    uint32_t enemy = g->board[x][y];

    g->board[x][y] = player;

    uint32_t playerAreas = count_areas(g, player);
    uint32_t enemyAreas = count_areas(g, enemy);

    if (playerAreas > g->areas || enemyAreas > g->areas) {
        g->board[x][y] = enemy;
        return false;
    }

    g->busyFields[player]++;
    g->busyFields[enemy]--;

    g->areasTaken[player] = playerAreas;
    g->areasTaken[enemy] = enemyAreas;

    g->goldenMove[player] = false;

    return true;
}

uint64_t gamma_busy_fields(gamma_t *g, uint32_t player) {
    if (!g || player == 0 || player > g->players) {
        return 0;
    }

    return g->busyFields[player];
}

uint64_t gamma_free_fields(gamma_t *g, uint32_t player) {
    if(!g || player == 0 || player > g->players) {
        return 0;
    }

    uint64_t free_fields = 0;

    if (g->areasTaken[player] < g->areas) {
        free_fields += (uint64_t)g->width * (uint64_t)g->height;
        for (uint32_t i = 0; i < g->players; i++) {
            free_fields -= g->busyFields[i+1];
        }
    }
    else {
        for (uint32_t i = 0; i < g->width; i++) {
            for (uint32_t j = 0; j < g->height; j++) {
                if (g->board[i][j] == 0) {
                    if (is_adjacent(g, player, i, j)) {
                        free_fields++;
                    }
                }
            }
        }
    }

    return free_fields;
}

bool gamma_golden_possible(gamma_t *g, uint32_t player) {
    if (!g || player == 0 || player > g->players || !g->goldenMove[player]) {
        return false;
    }

    if (g->areasTaken[player] < g->areas) {
        for (uint32_t i = 0; i < g->players; i++) {
            if (i+1 == player) {
                continue;
            }
            if (g->busyFields[i+1] > 0) {
                return true;
            }
        }
    }
    else {
        if (find_golden_move(g, player)){
            return true;
        }
    }

    return false;
}

char* gamma_board(gamma_t *g) {
    if (!g) return NULL;

    if (g->players > 9) {
        return gamma_board_many_players(g);
    }

    uint64_t size = (uint64_t)g->height * ((uint64_t)g->width + 1) + 1;

    char *out = malloc(sizeof(char) * size);
    if (!out) return NULL;

    uint32_t k = 0;
    for (uint32_t i = g->height; i > 0; i--) {
        for (uint32_t j = 0; j < g->width; j++) {
            if (g->board[j][i-1] == 0) {
                out[k] = '.';
            } else {
                out[k] = g->board[j][i-1] + '0';
            }

            k++;
        }
        out[k++] = '\n';
    }
    out[k] = '\0';

    return out;
}