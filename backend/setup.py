from flask import Flask
from flask_cors import CORS
from flask_sqlalchemy import SQLAlchemy

# configuration
DEBUG = True

# instantiate the app
app = Flask(__name__)
app.config.from_object(__name__)

# instantiate the db
db = SQLAlchemy(app)

# enable CORS
CORS(app, resources={r'/*': {'origins': '*'}})