def MinMax(temperaturas):
    print("A menor temperatura foi de:", minima(temperaturas),"C.")
    print("A maior temperatura foi de:", maxima(temperaturas),"C.")

def minima(temps):
    min=temps[0]
    for i in temps:
        if min>i:
            min=i
    return min

def maxima(temp):
    max=temp[0]
    for i in temp:
        if max<i:
            max=i
    return max

temperatura=[17,28,29,30,15,32,24,27]
MinMax(temperatura)
