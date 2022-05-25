add_compile_options(-g3)
add_link_options(-g3)
add_compile_options(-lm)
add_link_options(-lm)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fno-omit-frame-pointer)
add_compile_options(-fno-optimize-sibling-calls)
add_link_options(-fno-optimize-sibling-calls)


add_executable (solveur_naif open_dict_test.c ../src/open_dict.c)