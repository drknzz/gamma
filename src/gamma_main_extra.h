/** @file
 * Funkcje obsługujące tryby gry gamma
 *
 * @author Kamil Jankowski <kj418271@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */
#ifndef GAMMA_GAMMA_MAIN_EXTRA_H
#define GAMMA_GAMMA_MAIN_EXTRA_H

#include "gamma_batch.h"
#include "gamma_interactive.h"

/** @brief Uruchamia tryb gry.
 *  Parsuje input po znaku @p mode, w przypadku złego
 *  inputu wypisuje error / ustawia @p flag na wartość false.
 *  Dla dobrego inputu włącza dany tryb gry. Po zakończeniu usuwa
 *  wskaźnik na strukturę gamma_t.
 * @param[in] mode       – tryb gry,
 * @param[in] lineCount  – numer linii wejścia,
 * @param[in] flag       – flaga dla złego inputu,
 * @return Wartość @p true, jeżeli udało się uruchomić dany tryb,
 * wartość @p false w przeciwnym wypadku.
 */
bool get_mode_start(char mode, int *lineCount, bool *flag);

/** @brief Główna funkcja gry.
 *  Uruchamia tryb gry za pomocą @ref get_mode_start.
 *  Zlicza linie, omija komentarze i puste linie.
 *  W przypadku złego inputu wypisuje błędy.
 */
void get_mode();

#endif //GAMMA_GAMMA_MAIN_EXTRA_H
