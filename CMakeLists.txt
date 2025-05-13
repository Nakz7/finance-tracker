cmake_minimum_required(VERSION 3.16)

# Nom du projet
project(FinanceTracker VERSION 0.1 LANGUAGES CXX)

# Utilise le standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Active le mode debug par défaut (utile pour TDD et développement)
set(CMAKE_BUILD_TYPE Debug)

# Recherche Qt5 (remplace Qt5 par Qt6 si tu préfères)
find_package(Qt5 REQUIRED COMPONENTS Widgets Charts)

# Ajout des fichiers source
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h)

# Cible principale de l'application
add_executable(finance_tracker ${SOURCES} ${HEADERS})

# Lien avec Qt5 (Widgets et Charts)
target_link_libraries(finance_tracker Qt5::Widgets Qt5::Charts)

# Ajoute le dossier include au chemin d'inclusion
target_include_directories(finance_tracker PRIVATE include)

# Partie TESTS
enable_testing()

# Crée une cible séparée pour les tests
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

# Ajouter aussi le code source de l'application utilisé dans les tests
set(TEST_DEPENDENCIES
    ${TEST_SOURCES}
    ${SOURCES}
)

add_executable(finance_tracker_tests ${TEST_DEPENDENCIES})

target_link_libraries(finance_tracker_tests
    Qt5::Widgets
    Qt5::Charts
    gtest
    gtest_main
    pthread
)

target_include_directories(finance_tracker_tests PRIVATE include)
