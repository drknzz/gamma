/** @file
 * Funkcje pomocnicze do silnika gry gamma
 *
 * @author Kamil Jankowski <kj418271@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */

#ifndef GAMMA_ENGINE_HELP_H
#define GAMMA_ENGINE_HELP_H

#include "gamma.h"

/** @brief Oblicza ilość cyfr w danej liczbie.
 * @param[in, out] number   – liczba nieujemna.
 * @return Ilość cyfr w liczbie @p number.
 */
uint32_t get_length(uint32_t number);

/** @brief Odwiedza sąsiadujące pionki danego gracza od pola (@p x, @p y).
 * Ustawia pole na odwiedzone. Przechodzi po nieodwiedzonych
 * sąsiadujących polach. Jeżeli jest na nich pionek gracza @p player,
 * wywołuje się rekurencyjnie dla danego pola.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 */
void dfs(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Sprawdza czy pole (@p x, @p y) sąsiaduje z graczem @p player.
 * Sprawdza czy istnieje sąsiadujące pole i jeżeli tak - czy na tym polu
 * jest pionek gracza @p player.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeżeli pole (@p x, @p y) sąsiaduje
 * z graczem @p player, wartość @p false w przeciwnym wypadku.
 */
bool is_adjacent(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Sprawdza czy ruch gracza @p player na pole (@p x, @p y) jest legalny.
 * Sprawdza czy pole (@p x, @p y) jest zajęte. Jeżeli gracz posiada
 * maksymalną liczbę obszarów sprawdza czy utworzy nowy obszar.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeżeli ruch gracza @p player na pole (@p x, @p y)
 * jest legalny, wartośc @p false w przeciwnym wypadku.
 */
bool legal_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Oblicza ilość obszarów zajętych przez gracza @p player.
 * Przechodzi po tablicy visited ze struktury gamma, wywołując funkcję dfs.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new.
 * @return Ilość obszarów zajętych przez gracza @p player.
 */
uint32_t count_areas(gamma_t *g, uint32_t player);

/** @brief Daje napis opisujący stan planszy dla liczby graczy większej od 9.
 * Alokuje w pamięci bufor, w którym umieszcza napis zawierający tekstowy
 * opis aktualnego stanu planszy. Funkcja wywołująca musi zwolnić ten bufor.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 * @return Wskaźnik na zaalokowany bufor zawierający napis opisujący stan
 * planszy lub NULL, jeśli nie udało się zaalokować pamięci.
 */
char* gamma_board_many_players(gamma_t *g);

/** @brief Sprawdza, czy na danym polu można wykonać złoty ruch.
 *  Sprawdza, czy na danym polu można wykonać złoty ruch dla przypadku,
 *  kiedy ilość obszarów gracza jest maksymalna.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] player      – numer gracza,
 *  @param[in] x           – współrzędna x,
 *  @param[in] y           – współrzędna y.
 *  @return Wartość @p true, jeżeli na danym polu można wykonać złoty ruch,
 *  wartość @p false w przeciwnym wypadku.
 */
bool check_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Szuka możliwego złotego ruchu na planszy.
 *  Przechodzi po planszy wywołując na każdym polu funkcję @ref check_golden_move.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] player      – numer gracza,
 *  @return Wartość @p true, jeżeli istnieje złoty ruch,
 *  wartość @p false w przeciwnym wypadku.
 */
bool find_golden_move(gamma_t *g, uint32_t player);

#endif /* GAMMA_ENGINE_HELP */
