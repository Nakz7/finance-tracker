cmake_minimum_required(VERSION 3.16)

# Nom du projet
project(FinanceTracker VERSION 0.1 LANGUAGES CXX)

# Standard C++17 et options Qt
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Active le mode debug par défaut
set(CMAKE_BUILD_TYPE Debug)

# Recherche de Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets Charts)

# --- Définition de la librairie Core ---

# Headers
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "include/*.h")

# Sources (tous les .cpp de src/ SAUF main.cpp)
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# Création de la librairie statique
add_library(finance_tracker_core STATIC
    ${CORE_SOURCES}
    ${CORE_HEADERS}
)

# Inclusions pour la librairie
target_include_directories(finance_tracker_core PUBLIC include)

# Lien de la librairie avec Qt
target_link_libraries(finance_tracker_core PUBLIC Qt5::Widgets Qt5::Charts)


# --- Cible principale de l'application ---

add_executable(finance_tracker src/main.cpp)

# Lien de l'exécutable avec la librairie core
target_link_libraries(finance_tracker PRIVATE finance_tracker_core)


# --- Partie TESTS ---

enable_testing()

# Fichiers de test
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")

# Exécutable de test
add_executable(finance_tracker_tests
    ${TEST_SOURCES}
)

# Lien des tests avec la librairie core et gtest
target_link_libraries(finance_tracker_tests PRIVATE
    finance_tracker_core
    gtest
    gtest_main
    pthread
)
