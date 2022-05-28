add_compile_options(-g3)
add_link_options(-g3)
add_compile_options(-lm)
add_link_options(-lm)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fno-omit-frame-pointer)
add_compile_options(-fno-optimize-sibling-calls)
add_link_options(-fno-optimize-sibling-calls)


add_executable (solv_3b1b_test solv_3b1b_test.c ../solv_3b1b.c ../../open_dict.c ../hash_table/table.c ../hash_table/list.c ../hash_table/dico.c)

add_executable (solv_3b1b solv_3b1b_main.c solv_3b1b.c ../open_dict.c ./hash_table/table.c ./hash_table/list.c ./hash_table/dico.c)
