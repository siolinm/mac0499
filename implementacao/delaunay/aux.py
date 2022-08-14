def Esq(V, i, j, k):
    a = V[i]
    b = V[j]
    c = V[k]
    x = ((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0]))
    return x > 0

def Dir(V, i, j, k):
    a = V[i]
    b = V[j]
    c = V[k]
    x = ((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0]))
    return x < 0

def esq(a, b, c):
    return ((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0])) > 0

def direita(a, b, c):
    return ((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0])) < 0
