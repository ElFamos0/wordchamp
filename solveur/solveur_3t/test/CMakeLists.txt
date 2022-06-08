add_compile_options(-g3)
add_link_options(-g3)
add_compile_options(-lm)
add_link_options(-lm)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fno-omit-frame-pointer)
add_compile_options(-fno-optimize-sibling-calls)
add_link_options(-fno-optimize-sibling-calls)

add_executable(build/solveur_3t ../src/freqsolve.c ../src/open_dict.c)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable (build/open_dict_test open_dict_test.c ../src/open_dict.c)