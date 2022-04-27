from setup import *
from utils.isMot import isMot

@app.route('/motValideDebug', methods=['GET'])
def motValideDebug():
    return isMot("AAAAA")