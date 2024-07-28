def incomodam(n):
    
    if n <= 0:
        return ""
    else:
        return "incomodam " + incomodam(n-1)
    
#print(incomodam(3))

def elefantes(n):
    
    if n < 1:
        return ""
    elif n == 1:
        return f"Um elefante incomoda muita gente\n"
    else:
        return str(elefantes(n-1)) + f"{n} elefantes {incomodam(n)}muito mais\n{n} elefantes incomodam muita gente\n"
    
print(elefantes(4))
        
    