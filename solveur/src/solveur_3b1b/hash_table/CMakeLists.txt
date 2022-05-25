add_compile_options(-g3)
add_link_options(-g3)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fno-omit-frame-pointer)
add_compile_options(-fno-optimize-sibling-calls)
add_link_options(-fno-optimize-sibling-calls)
add_executable (maintest3 dico_test.c table.c list.c dico.c)

# Format : add_executable(nom_executable fichier_main.c dependencies.c)

