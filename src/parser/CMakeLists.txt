# Добавим библиотеку с классом парсера
add_library(Parser STATIC parser_rules.cpp)

target_include_directories(Parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})