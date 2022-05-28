add_compile_options(-g3)
add_link_options(-g3)
add_compile_options(-lm)
add_link_options(-lm)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fno-omit-frame-pointer)
add_compile_options(-fno-optimize-sibling-calls)
add_link_options(-fno-optimize-sibling-calls)

add_executable (build/solveur_3b1b ../src/solv_3b1b_main.c ../src/solv_3b1b.c ../src/open_dict.c ../src/table.c ../src/list.c ../src/dico.c)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable (build/solveur_3b1b_test solv_3b1b_test.c ../src/solv_3b1b.c ../src/open_dict.c ../src/table.c ../src/list.c ../src/dico.c)
