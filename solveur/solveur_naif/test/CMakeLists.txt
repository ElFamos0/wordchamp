add_compile_options(-g3)
add_link_options(-g3)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fno-omit-frame-pointer)
add_compile_options(-fno-optimize-sibling-calls)
add_link_options(-fno-optimize-sibling-calls)

add_executable (build/solveur_naif 
    ../src/game.c
    ../src/wordlist.c 
    ../src/letter.c
    ../src/word.c
    ../src/table.c 
    ../src/list.c 
)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable (build/test 
    test.c 
    ../src/wordlist.c 
    ../src/letter.c
    ../src/word.c
    ../src/table.c 
    ../src/list.c 
)