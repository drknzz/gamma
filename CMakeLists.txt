cmake_minimum_required(VERSION 3.0)
project(Gamma C)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# Nie chcemy oglądać komunikatów o procentowym postępie kompilacji.
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

# Chcemy zobaczyć polecenia wywołane przez make.
set(CMAKE_VERBOSE_MAKEFILE ON)

# Ustawiamy wspólne opcje kompilowania dla wszystkich wariantów projektu.
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra")
# Domyślne opcje dla wariantów Release i Debug są sensowne.
# Jeśli to konieczne, ustawiamy tu inne.
#set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
#set(CMAKE_C_FLAGS_DEBUG "-g")

# Wskazujemy pliki źródłowe.
set(SOURCE_FILES
    src/gamma.c
    src/gamma.h
    src/gamma_engine_help.c
    src/gamma_engine_help.h
    src/gamma_batch.c
    src/gamma_batch.h
    src/gamma_interactive.c
    src/gamma_interactive.h
    src/gamma_io.c
    src/gamma_io.h
    src/gamma_main_extra.c
    src/gamma_main_extra.h
    src/gamma_main.c)

# Wskazujemy plik wykonywalny.
add_executable(gamma ${SOURCE_FILES})

# Wskazujemy testowe pliki źródłowe
set(TEST_SOURCE_FILES
    src/gamma.c
    src/gamma.h
    src/gamma_engine_help.c
    src/gamma_engine_help.h
    src/gamma_test.c)

# Wskazujemy plik wykonywalny dla testów silnika.
add_executable(test EXCLUDE_FROM_ALL ${TEST_SOURCE_FILES})
set_target_properties(test PROPERTIES OUTPUT_NAME gamma_test)

# Dodajemy obsługę Doxygena: sprawdzamy, czy jest zainstalowany i jeśli tak to:
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Wskazujemy lokalizacją pliku konfiguracyjnego i podajemy jego docelową lokalizację w folderze, gdzie następuje kompilacja.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    # Dodajemy cel doc: użycie make doc spowoduje wywołanie doxygena z odpowiednim plikiem konfiguracyjnym w folderze kompilacji.
    # Na wyjście zostanie wypisany odpowiedni komentarz.
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
    )
endif (DOXYGEN_FOUND)
