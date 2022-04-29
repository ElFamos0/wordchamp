def set_difficulte(word,freq) :

        diff = 1

        if len(word) <= 4 :
            diff = -1
            return diff

        def eval_freq(freq) :

            if freq >= 500 :

                modif = 0.06

            elif freq >= 50 :

                modif = 4.61834-4.11052*(freq**0.0162095)

            elif freq >= 10 :

                modif = 32.5759-30.6157*(freq**0.0143586)
        
            elif freq > 5 :

                modif = 2
            
            elif freq > 1.67 :

                modif = 0.298879+14.9173/(freq**1.32219)

            elif freq > 1 :

                modif = 14.6

            elif freq > 0.01 :

                modif = 10.1673-4.03133*(freq**0.3745)
            
            else :

                modif = 50

            return modif*250
        

        modif_freq = eval_freq(freq)
    
        dico_apparition =  {"A" :7.45,"B" :1.14,"C" :3.24,"D" :3.67,"E" :14.44,"F" :1.11,
                            "G" :1.23,"H" :1.11,"I" :6.63,"J" :0.34,"K" :0.29,"L" :4.96,
                            "M" :2.62,"N" :6.39,"O" :5.06,"P" :2.49,"Q" :0.65,"R" :6.07,
                            "S" :6.51,"T" :5.92,"U" :4.54,"V" :1.11,"W" :0.17,"X" :0.38,
                            "Y" :0.46,"Z" :0.15}

        moyenne_apparition = 0
        for l in word :
            moyenne_apparition += dico_apparition[l]
        
        moyenne_apparition /= len(word)
                
        def eval_app(moy_app) :

            if moy_app < 0.012 :
                return 3
            elif moy_app > 0.06 :
                return -0.36
            else :
                return 1728.07*(moy_app**2)-191.311*moy_app+4.89096

        diff += eval_app(moyenne_apparition/100)

        coeff_doublons = sum([word.count(l) for l in word])/len(word)

        def eval_doublons(coeff) :

            if coeff < 1 :
                return 0
            elif coeff > 2.25 :
                return 2
            else :
                return 0.662585*(coeff**2)-0.524984*coeff-0.161711


        diff += eval_doublons(coeff_doublons)


        return round(diff*modif_freq,2)