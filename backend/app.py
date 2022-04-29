from setup import *
from routes import *
import misc.dev_database_setup as dbsetup
from models import *

listemot = word.Word.query.all()
if len(listemot) == 0:
    setup = True

if setup:
    dbsetup.load_all()

    newGameNormal = game_carriere.Game_carriere(user_id,False)       
    db.session.add(newGameNormal)
    newGameId = newGameNormal.id
    maxtry = newGameNormal.maxtry
    length = newGameNormal.length
    solution = newGameNormal.solution
    

    if length == 5 :

        db.session.add(tries.Tries(newGameId,"BOIRE",1))
    
    elif length == 6 :

        db.session.add(tries.Tries(newGameId,"MAISON",1))
    
    elif length == 7 :

        db.session.add(tries.Tries(newGameId,"MAISONS",1))
    
    elif length == 8 :

        db.session.add(tries.Tries(newGameId,"SOLUTION",1))
    
    elif length == 9 :

        db.session.add(tries.Tries(newGameId,"TENDRESSE",1))
    
    elif length == 10 :

        db.session.add(tries.Tries(newGameId,"CHOCOLATEES",1))


    db.session.add(tries.Tries(newGameId,solution,2))

    db.session.commit()

    newGameNormal.endGame(True,False)

    db.session.commit()

if __name__ == '__main__':
    app.run()