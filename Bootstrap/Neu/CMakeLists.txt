project (Neu)

add_executable(neu
    main.cpp
    Parser/NeuParser.cpp
    Tokenizer/NeuTokenizer.cpp)

target_link_libraries(neu core)