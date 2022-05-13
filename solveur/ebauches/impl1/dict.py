# On ouvre le fichier pour lire chaque lignes
d = open("dict.txt")
dict = []

for line in d.readlines():
    dict.append(line.strip())

d.close()