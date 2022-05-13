add_compile_options(-g3)
add_link_options(-g3)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fno-omit-frame-pointer)
add_compile_options(-fno-optimize-sibling-calls)
add_link_options(-fno-optimize-sibling-calls)


add_executable (open_dict_test open_dict_test.c ../src/open_dict.c)
add_executable (array_test array_test.c ../src/array.c)
add_executable(wordle ../src/wordle.c ../src/open_dict.c)