from setup import *
from routes import *
import misc.dev_database_setup as dbsetup
from models import *
        
db.create_all()

if setup:
    dbsetup.load_all()

if __name__ == '__main__':
    app.run()