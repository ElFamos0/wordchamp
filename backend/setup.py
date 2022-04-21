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