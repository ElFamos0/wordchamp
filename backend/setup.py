from flask import Flask
from flask_cors import CORS
from flask_sqlalchemy import SQLAlchemy
from os import environ, path
from flask_jwt_extended import JWTManager
from datetime import timedelta



# configuration
DEBUG = True

# instantiate the app
app = Flask(__name__)
app.config.from_object(__name__)

app.config["JWT_ACCESS_TOKEN_EXPIRES"] = timedelta(hours=1)
app.config["JWT_REFRESH_TOKEN_EXPIRES"] = timedelta(days=30)

env = environ.get("ENVIRONMENT", "development")

# instantiate secrets and env variables
app.config['SECRET_KEY'] = 'c1155c6a351e49eba15c00ce577b259e'

setup = False
if not path.isfile("db.sqlite3"):
    open("db.sqlite3", "w")
    setup = True

if env == "development":
    app.config['SQLALCHEMY_DATABASE_URI'] = "sqlite:///db.sqlite3" # Declares the database path
else:
    # add production database
    username = environ.get("DB_USERNAME")
    password = environ.get("DB_PASSWORD")
    host = environ.get("DB_HOST")
    database = environ.get("DB_DATABASE")
    app.config['SQLALCHEMY_DATABASE_URI'] = f"postgresql://{username}:{password}@{host}:5432/{database}" # Declares the database path

# instantiate the db   
db = SQLAlchemy(app)

jwt = JWTManager(app)

# enable CORS
CORS(app, resources={r'/*': {'origins': '*'}})


from models import *

db.create_all()







##### Comment add un user
from models import *

usertest = user.User.query.all() 
if len(usertest) == 0 :
    newUser = user.User("pseudo","mdp",False)
    db.session.add(newUser)
    db.session.commit()
##### 


##### Comment add une game normale 

from sqlalchemy.orm import with_polymorphic

all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal])

all_games = db.session.query(all_games_poly)
if len(all_games.all()) == 0 :

    user = user.User.query.first()       # Juste pour récupérer un user, sinon remplacer par ce qu'il vous faut

    newGameNormal = game_normal.Game_normal(user.id,"dentifrice",6,10,"21022021")       #(last attribut = date en timestamp)
    db.session.add(newGameNormal)
    db.session.commit()

#####






##### Comment récupérer toutes les games :


all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal])

all_games = db.session.query(all_games_poly)

first_game = all_games[0]

date = first_game.date              #Pour récup la date
state = first_game.state            #Pour récup le state
id = first_game.id                  #Pour récup l'id
game_type = first_game.game_type    #Pour récup le type de game

if game_type == "game_normal" :

    id_user = first_game.id_user    #Pour récup le user_id
    solution = first_game.solution  #Pour récup la solution
    maxtry = first_game.maxtry      #Pour récup le nb de try
    length = first_game.length      #Pour récup la longeur de la soluce

#print(date,state,id,game_type,id_user,solution,maxtry,length)

########



