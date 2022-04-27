from setup import *
from utils.motValide import motValide

@app.route('/motValideDebug', methods=['GET'])
def motValideDebug():
    return motValide("AAAAA")