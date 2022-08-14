from aux import Dir

def Menor(V, i, j):
    return Dir(V, 1, j, i)

def Intercala(V, A, p, q, r):
    B = list(A)
    for i in range(p, q+1):
        B[i] = A[i]
    for j in range(q+1, r+1):
        B[r + q + 1 - j] = A[j]
    i = p
    j = r
    for k in range(p, r+1):
        if Menor(V, B[i], B[j]):
            A[k] = B[i]
            i = i + 1
        else:
            A[k] = B[j]
            j = j-1

def MergeSort(V, A, p, r):
    if p < r:
        q = (p + r)//2
        MergeSort(V, A, p, q)
        MergeSort(V, A, q+1, r)
        Intercala(V, A, p, q, r)

def Ordena(V):
    n = len(V)-1
    O = list(range(0, n+1))
    i = O[1]
    for j, o in enumerate(O):
        if j == 0:
            continue
        if V[o][1] < V[i][1]:
            i = o
    V[i], V[1] = V[1], V[i]
    MergeSort(V, O, 2, n)

    return O