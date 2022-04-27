from setup import *
from utils.isMot import isMot

@app.route('/motValide/<mot>', methods=['GET'])
def motValide(mot):
    return isMot(mot)