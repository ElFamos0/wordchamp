def classLeters(guess,solution) :

    miss = []
    found = []
    misplace = []

    for elm in guess :
        i = 0
        while i < len(elm) :
            l = elm[i]
            if l in solution :
                if l == solution[i] :
                    if l not in found :
                        found.append(l)
                    if l in misplace :
                        misplace.remove(l)
                elif l not in misplace and l not in found:
                    misplace.append(l)               
            elif l not in miss :
                miss.append(l)
            i+=1

    return miss,found,misplace


