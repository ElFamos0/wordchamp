FROM python:3.10-buster as build

# On se met dans le bon dossier
WORKDIR /app

# On copie tout les fichiers de l'application
COPY . .

# On installe les dépendances
RUN python -m pip install -r requirements.txt

# On publie le port 5000
EXPOSE 5000

# On lance la commande python
CMD [ "python", "-m" , "flask", "run", "--host=0.0.0.0", "--port=5000"]