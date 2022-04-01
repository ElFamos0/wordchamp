from flask import Flask
from flask_cors import CORS
from flask_sqlalchemy import SQLAlchemy
from os import environ, path
from models import Word

# configuration
DEBUG = True

# instantiate the app
app = Flask(__name__)
app.config.from_object(__name__)

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
    app.config['SQLALCHEMY_DATABASE_URI'] = "postgresql://{username}:{password}@{host}:5432/{database}" # Declares the database path

# instantiate the db   
db = SQLAlchemy(app)

# enable CORS
CORS(app, resources={r'/*': {'origins': '*'}})