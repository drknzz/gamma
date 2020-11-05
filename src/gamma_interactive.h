/** @file
 * Funkcje obsługujące tryb interaktywny gry gamma
 *
 * @author Kamil Jankowski <kj418271@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */

#ifndef GAMMA_GAMMA_INTERACTIVE_H
#define GAMMA_GAMMA_INTERACTIVE_H

#include "gamma.h"
#include "gamma_io.h"
#include "gamma_engine_help.h"

#define YLLW "\e[43m"       /**< żółty kolor tła */
#define BLK "\e[1;30m"      /**< czarny kolor */
#define BHRED "\e[1;91m"    /**< czerwony kolor */
#define BHGRN "\e[1;92m"    /**< zielony kolor */
#define BHYEL "\e[1;93m"    /**< żółty kolor */
#define BHBLU "\e[1;94m"    /**< niebieski kolor */
#define BHMAG "\e[1;95m"    /**< magenta kolor */
#define BHCYN "\e[1;96m"    /**< cyan kolor */
#define DFLT "\e[0m"        /**< domyślny kolor */
#define TEXT_HEIGHT 10      /**< wysokość wypisywanego tekstu */
#define TEXT_WIDTH 26       /**< szerokość wypisywanego tekstu */
#define ESC '\033'          /**< escape */
#define BRT '['             /**< kwadratowy nawias otwierający */
#define ARW_UP 'A'          /**< strzałka w górę */
#define ARW_DWN 'B'         /**< strzałka w dół */
#define ARW_RGHT 'C'        /**< strzałka w prawo */
#define ARW_LFT 'D'         /**< strzałka w lewo */

/** @brief Oblicza wymiary okna terminalu.
 *  Zapisuje wymiary okna terminalu do parametrów wejściowych.
 *  @param[in] width   – wskaźnik na szerokość okna terminalu,
 *  @param[in] height  – wskaźnik na szerokość okna terminalu.
 */
void get_terminal_size(int *width, int *height);

/** @brief Oblicza dodatkową szerokość tekstu pod planszą.
 *  Oblicza szerokość potrzebną do zapisu liczb znajdujących się w gammie.
 *  @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 *  @return Dodatkowa szerokość tekstu pod planszą.
 */
int bonus_text_width(gamma_t *g);

/** @brief Sprawdza czy plansza wraz z napisami pod nią zmieszczą się w oknie terminalu.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry.
 *  @return Wartość @p true, jeżeli plansza z napisami zmieszczą się w
 *  oknie terminalu, wartość @p false w przeciwnym wypadku.
 */
bool board_fits_in_terminal(gamma_t *g);

/** @brief Zmienia kolor tekstu / tła.
 *  @param[in] color   – kolor w kodzie ANSI.
 */
void set_text_color(char *color);

/** @brief Wypisuje białą ścianę.
 *  Zmienia kolor tekstu na biały i wypisuje białą ścianę na wyjście.
 */
void print_white_wall();

/** @brief Porusza kursorem w górę / dół.
 *  W zależności od @p down zmienia pozycję kursora na
 *  planszy o @p count komórek w górę / dół.
 *  @param[in] count       – ilość komórek,
 *  @param[in] down        – flaga oznaczająca poruszenie
 *                           w dół dla wartości @p true,
 *                           w górę dla wartości @p false.
 */
void cursor_up_down(uint32_t count, bool down);

/** @brief Porusza kursorem w lewo / prawo.
 *  W zależności od @p right zmienia pozycję kursora na
 *  planszy o @p count komórek w lewo / prawo.
 *  @param[in] count       – ilość komórek,
 *  @param[in] right       – flaga oznaczająca poruszenie
 *                           w prawo dla wartości @p true,
 *                           w lewo dla wartości @p false.
 */
void cursor_left_right(uint32_t count, bool right);

/** @brief Czyści terminal.
 */
void clear_screen();

/** @brief Ustawia kursor w lewym górnym rogu terminalu.
 */
void cursor_to_home();

/** @brief Porusza kursorem o jedną komórkę.
 *  W zależności od @p c zmienia pozycję kursora na planszy.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] cursor_x    – współrzędna x kursora,
 *  @param[in] cursor_y    – współrzędna y kursora,
 *  @param[in] c           – znak rozróżniający strzałki.
 */
void move_cursor(gamma_t *g, uint32_t *cursor_x, uint32_t *cursor_y, char c);

/** @brief Czyści terminal i wypisuje planszę.
 *  Wypisana plansza ma zaznaczone pola aktualnego gracza kolorem.
 *  Jeżeli gracz jest równy 0, to koloruje wszystkich graczy na planszy.
 *  @param[in] g        – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] player   – numer aktualnego gracza.
 */
void interactive_print_board(gamma_t *g, uint32_t player);

/** @brief Wypisuje stan gry po jej zakończeniu.
 *  Wypisuje planszę i każdego gracza z ilością zajętych przez niego pól.
 *  @param[in] g    – wskaźnik na strukturę przechowującą stan gry,
 */
void interactive_end(gamma_t *g);

/** @brief Wypisuje aktualny stan gry.
 *  Wypisuje planszę i dodatkowe informacje - numer gracza, ilość zajętych
 *  oraz wolnych pól, ilość zajętych i maksymalnych obszarów,
 *  możliwość złotego ruchu, instrukcję obsługi.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] player      – numer gracza,
 *  @param[in] golden      – możliwość wykonania złotego ruchu.
 */
void interactive_print_game_state(gamma_t *g, uint32_t player, bool golden);

/** @brief Ustawia kursor na środku planszy.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] cursor_x    – współrzędna x kursora,
 *  @param[in] cursor_y    – współrzędna y kursora.
 */
void interactive_cursor_to_middle(gamma_t *g, uint32_t *cursor_x, uint32_t *cursor_y);

/** @brief Ustawia kursor na współrzędnych (@p cursor_x, @p cursor_y).
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] cursor_x    – współrzędna x kursora,
 *  @param[in] cursor_y    – współrzędna y kursora.
 */
void interactive_cursor_to_cords(gamma_t *g, uint32_t cursor_x, uint32_t cursor_y);

/** @brief Aktualizuje pozycję kursora.
 *  Jeżeli @p first ma wartość @p true, ustawia kursor na środku planszy.
 *  W przeciwnym wypadku ustawia kursor na współrzędnych
 *  (@p cursor_x, @p cursor_y).
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] cursor_x    – współrzędna x kursora,
 *  @param[in] cursor_y    – współrzędna y kursora,
 *  @param[in] first    – flaga pierwszego wywołania funkcji.
 */
void update_cursor(gamma_t *g, uint32_t *cursor_x, uint32_t *cursor_y, bool *first);

/** @brief Sprawdza czy istnieje jakikolwiek ruch.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] player      – numer gracza.
 *  @return Wartość @p true, jeżeli istnieje ruch,
 *  wartość @p false w przeciwnym wypadku.
 */
bool check_for_moves(gamma_t *g, uint32_t *player);

/** @brief Parsuje wejście w trybie interaktywnym.
 *  @param[in] g           – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] player      – numer gracza,
 *  @param[in] cursor_x    – współrzędna x kursora,
 *  @param[in] cursor_y    – współrzędna y kursora.
 *  @return Wartość @p false, jeżeli została przerwana gra kombinacją CTRL+D,
 *  wartość @p true w przeciwnym wypadku.
 */
bool interactive_input(gamma_t *g, uint32_t player, uint32_t *cursor_x, uint32_t *cursor_y);

/** @brief Obsługuje input w trybie interactive.
 *  @param[in] g          – wskaźnik na strukturę przechowującą stan gry,
 */
void interactive_mode(gamma_t *g);

#endif //GAMMA_GAMMA_INTERACTIVE_H
