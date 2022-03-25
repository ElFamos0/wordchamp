from setup import *
from routes import *
import misc.load_dev_wordlist as dbsetup

if __name__ == '__main__':
    app.run()

if env == "development":
    dbsetup.load_all()