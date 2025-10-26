cmake_minimum_required(VERSION 3.16)

# === Projet général ===
project(FinanceTracker VERSION 0.1 LANGUAGES CXX)

# Active l'AUTOMOC indispensable pour Qt (génération signaux/slots)
set(CMAKE_AUTOMOC ON)

# Utilise le standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Recherche Qt5 (remplace Qt5 par Qt6 si besoin)
find_package(Qt5 REQUIRED COMPONENTS Widgets Charts)

# === Fichiers du projet ===
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h)

# === Librairie principale contenant toute la logique de l'application ===
add_library(finance_tracker_core ${SOURCES} ${HEADERS})
target_link_libraries(finance_tracker_core Qt5::Widgets Qt5::Charts)
target_include_directories(finance_tracker_core PUBLIC include)

# === Exécutable principal (juste le main.cpp) ===
add_executable(finance_tracker src/main.cpp)
target_link_libraries(finance_tracker finance_tracker_core)

# === Partie TESTS ===
enable_testing()
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

# Exécutable des tests unitaires
add_executable(finance_tracker_tests ${TEST_SOURCES})
target_link_libraries(finance_tracker_tests
    finance_tracker_core           # Logique commune à l'app et aux tests
    Qt5::Widgets
    Qt5::Charts
    gtest
    gtest_main
    pthread
)
target_include_directories(finance_tracker_tests PRIVATE include)

# === Conseils ===
# Nouveau .cpp/.h, il sera détecté grâce à GLOB_RECURSE
# - Tests couvrent tout le code métier, ajout dans finance_tracker_core uniquement
# - Headers ne sont ajoutés que pour l'automoc, ils ne sont pas recompilés
