def ePrimo(k):
    if k<2:
        return False
    divisor=2
    while divisor*divisor<=k:
        if k%divisor==0:
            return False
        divisor+=1
    return True
    
def maior_primo(x):
    while x>=2:
        if ePrimo(x):
            return x
        x-=1
    return None