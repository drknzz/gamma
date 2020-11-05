/** @file
 * Funkcje obsługujące tryb batch gry gamma
 *
 * @author Kamil Jankowski <kj418271@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */
#ifndef GAMMA_GAMMA_BATCH_H
#define GAMMA_GAMMA_BATCH_H

#include "gamma.h"
#include "gamma_io.h"

/** @brief Parsuje wejście i wywołuje @ref gamma_move.
 *  @param[in] g     – wskaźnik na strukturę przechowującą stan gry.
 *  @return Wartość @p true, jeżeli udało się wywołać @ref gamma_move,
 *  wartość @p false w przeciwnym wypadku.
 */
bool batch_m(gamma_t *g);

/** @brief Parsuje wejście i wywołuje @ref gamma_golden_move.
 *  @param[in] g     – wskaźnik na strukturę przechowującą stan gry.
 *  @return Wartość @p true, jeżeli udało się wywołać @ref gamma_golden_move,
 *  wartość @p false w przeciwnym wypadku.
 */
bool batch_g(gamma_t *g);

/** @brief Parsuje wejście i wywołuje @ref gamma_busy_fields.
 *  @param[in] g     – wskaźnik na strukturę przechowującą stan gry.
 *  @return Wartość @p true, jeżeli udało się wywołać @ref gamma_busy_fields,
 *  wartość @p false w przeciwnym wypadku.
 */
bool batch_b(gamma_t *g);

/** @brief Parsuje wejście i wywołuje @ref gamma_free_fields.
 *  @param[in] g     – wskaźnik na strukturę przechowującą stan gry.
 *  @return Wartość @p true, jeżeli udało się wywołać @ref gamma_free_fields,
 *  wartość @p false w przeciwnym wypadku.
 */
bool batch_f(gamma_t *g);

/** @brief Parsuje wejście i wywołuje @ref gamma_golden_possible.
 *  @param[in] g     – wskaźnik na strukturę przechowującą stan gry.
 *  @return Wartość @p true, jeżeli udało się wywołać @ref gamma_golden_possible,
 *  wartość @p false w przeciwnym wypadku.
 */
bool batch_q(gamma_t *g);

/** @brief Parsuje wejście i wywołuje @ref gamma_board.
 *  @param[in] g     – wskaźnik na strukturę przechowującą stan gry.
 *  @return Wartość @p true, jeżeli udało się wywołać @ref gamma_board,
 *  wartość @p false w przeciwnym wypadku.
 */
bool batch_p(gamma_t *g);

/** @brief Rozpoznaje i wywołuje funkcję w zależności od @p c.
 *  Jeżeli wywołana funkcja zwróciła @p false, wypisuje błąd.
 *  @param[in] g          – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] c          – znak funkcji,
 *  @param[in] lineCount  – numer linii.
 */
void batch_detect(gamma_t *g, char c, int *lineCount);

/** @brief Obsługuje input w trybie batch.
 *  @param[in] g          – wskaźnik na strukturę przechowującą stan gry,
 *  @param[in] lineCount  – numer linii.
 */
void batch_mode(gamma_t *g, int *lineCount);

#endif //GAMMA_GAMMA_BATCH_H
