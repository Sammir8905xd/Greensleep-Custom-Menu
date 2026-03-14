cmake_minimum_required(VERSION 3.25)

# Proyecto del Multiverso de OranGy
project(GreensleepCustomMenu)

# Buscamos el SDK de Geode
find_package(Geode REQUIRED)

# Añadimos el archivo de código
add_geode_mod(
    orangydev.dynamic_main_menu
    SOURCES src/main.cpp
)

# Esto asegura que se usen los encabezados correctos de Geode
target_link_libraries(orangydev.dynamic_main_menu geode::sdk)
