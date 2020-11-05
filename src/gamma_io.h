/** @file
 * Funkcje obsługujące wejście do gry gamma
 *
 * @author Kamil Jankowski <kj418271@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */
#ifndef GAMMA_GAMMA_IO_H
#define GAMMA_GAMMA_IO_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "gamma_interactive.h"

/** @brief Wczytuje znak z wejścia bez echo.
 * @return Znak z wejścia.
 */
int getche(void);

/** @brief Czyta znaki z wejścia, aż do znaku '\n' lub końca danych.
 */
void read_end_of_line();

/** @brief Sprawdza czy znak @p c jest biały.
 * @param[in] c   – znak,
 * @return Wartość @p true, jeżeli znak jest biały,
 * wartość @p false w przeciwnym wypadku.
 */
bool isWhiteCharacter(char c);

/** @brief Wczytuje biale znaki z wejscia.
 * @return Wartość @p true, jeżeli wystąpił conajmniej 1 biały znak,
 * wartość @p false w przeciwnym wypadku.
 */
bool skip_white_char();

/** @brief Czyta wartość typu uint32_t z wejścia.
 * Czyta znaki z wejścia, dopóki są z przedziału '0' - '9' i wynik
 * mieści się w zakresie uint32_t. Wynik ustawia w wartości @p result.
 * @param[in] result  – wynik wczytywania liczby,
 * @return Wartość @p true, jeśli pojawiła się jakaś cyfra,
 * wartość @p false, jeżeli na wejścu nie było cyfry, lub liczba przekroczyła
 * zakres uint32_t.
 */
bool read_uint(uint32_t *result);

/** @brief Czyta białe znaki oraz liczbę typu uint32_t z wejścia.
 * Wynik zapisuje w zmiennej @p result.
 * @param[in] result  – wynik wczytywania liczby,
 * @return Wartość @p true, jeśli wystąpił chociaż 1 biały znak oraz
 * udało się wczytać liczbę typu uint32_t, wartość @p false w przeciwnym wypadku.
 */
bool read_next_uint(uint32_t *result);

#endif //GAMMA_GAMMA_IO_H
