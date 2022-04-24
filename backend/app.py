from setup import *
from routes import *
import misc.dev_database_setup as dbsetup
from models import *

listemot = word.Word.query.all()
if len(listemot) == 0:
    setup = True

if setup:
    dbsetup.load_all()

if __name__ == '__main__':
    app.run()