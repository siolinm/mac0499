from dcel import *
import numpy as np
from ordena import *
from aux import *
from plots import *


# Referência:
# http://www.ist.tugraz.at/_attach/Publish/Da2_19/05_triangulations_handouts.pdf
# Documento da Cris e do Coelho

def AddHalfEdge(ev, en):
    """
    inserts the half-edge en between ev and its successor
    """
    en.Origin = ev.Twin.Origin
    en.IncidentFace = ev.IncidentFace
    en.Prev = ev
    en.Next = ev.Next
    ev.Next = en
    en.Next.Prev = en


def AddEdge(D, ev):
    """
    inserts two half-edges creating a new face

    ev.Next and ev.Next.Next belongs to the new face
    """
    en1 = Edge()
    en2 = Edge()
    f = Face()
    D.AddEdge(en1)
    D.AddEdge(en2)
    D.AddFace(f)

    en1.Twin = en2
    en2.Twin = en1

    en1.Origin = ev.Twin.Origin
    en1.Prev = ev
    en1.Next = ev.Next.Next.Next
    en1.IncidentFace = ev.IncidentFace

    en2.Origin = en1.Next.Origin
    en2.Next = ev.Next
    en2.Prev = en1.Next.Prev

    en2.Next.Prev = en2
    en2.Prev.Next = en2
    en1.Next.Prev = en1
    en1.Prev.Next = en1

    en2.Next.IncidentFace = f
    en2.Next.Next.IncidentFace = f
    en2.IncidentFace = f

    f.OuterComponent = en2

    return en1.Prev


def Linha(pi):
    return [pi[0], pi[1], pi[0] ** 2 + pi[1] ** 2, 1]


def InCircle(pi, pj, pk, pl):
    a = np.array([Linha(pi), Linha(pj), Linha(pk), Linha(pl)])
    return np.linalg.det(a) > 0


def Illegal(d, e):
    if e.IncidentFace == d.fout or e.Twin.IncidentFace == d.fout:
        return False

    pi = e.Origin.Coordinates
    pj = e.Next.Origin.Coordinates
    pk = e.Next.Next.Origin.Coordinates
    pl = e.Twin.Prev.Origin.Coordinates
    if not (esq(pk, pi, pl) and direita(pk, pj, pl)):
        # o quadrilatero (pi, pj, pk, pl) não é convexo?
        return False

    return InCircle(pi, pj, pk, pl)


def ChangeOrigin(e):
    if e.Origin.IncidentEdge == e:
        e.Origin.IncidentEdge = e.Prev.Twin
    e.Origin = e.Prev.Origin


def ChangeNext(e, n):
    e.Next = n
    e.Next.Prev = e


def ChangePrev(e, p):
    e.Prev = p
    e.Prev.Next = e


def ChangeFace(e, f):
    e.IncidentFace = f
    e.Next.IncidentFace = f
    e.Next.Next.IncidentFace = f
    f.OuterComponent = e


def Flip(e):
    ChangeOrigin(e)
    ChangeOrigin(e.Twin)
    f1 = e.IncidentFace
    f2 = e.Twin.IncidentFace

    enext = e.Twin.Prev
    eprev = e.Next
    tnext = e.Prev
    tprev = e.Twin.Next

    ChangeNext(e, enext)
    ChangeNext(e.Twin, tnext)
    ChangePrev(e, eprev)
    ChangePrev(e.Twin, tprev)
    ChangeNext(enext, eprev)
    ChangeNext(tnext, tprev)
    ChangeFace(e, f1)
    ChangeFace(e.Twin, f2)


def Graham(V):
    O = Ordena(V)
    d = DCEL()
    n = len(V) - 1
    H = [0] * len(V)
    E = []

    v1 = Vertex(V[O[1]], Index=O[1])
    v2 = Vertex(V[O[2]], Index=O[2])
    H[1] = (O[1], v1)
    H[2] = (O[2], v2)
    d.AddVertex(v1)
    d.AddVertex(v2)

    fout = Face()
    d.AddFace(fout)
    d.fout = fout

    e0 = Edge(v1, None, fout)
    d.AddEdge(e0)

    te0 = Edge(v2, e0, fout)
    d.AddEdge(te0)

    e0.Next = te0
    te0.Next = e0
    e0.Prev = te0
    te0.Prev = e0

    fout.OuterComponent = te0

    h = 2
    for k in range(3, n + 1):
        # O[k] -> O[1] O[1] -> H[h] H[h] -> O[k]
        # Plot(d)
        vk = Vertex(V[O[k]], Index=O[k])
        d.AddVertex(vk)

        # E.append((O[k], O[1]))
        en0 = Edge()
        AddHalfEdge(te0, en0)

        en1 = Edge(vk, en0, fout)
        AddHalfEdge(en0, en1)
        d.AddEdge(en0)
        d.AddEdge(en1)
        en0 = AddEdge(d, en0)
        # Plot(d)
        # E.append((H[h], O[k]))
        while h > 1 and Esq(V, H[h][0], H[h - 1][0], O[k]):
            h = h - 1
            # E.append((H[h], O[k]))
            en0 = AddEdge(d, en0)
            # Plot(d)
        h = h + 1
        H[h] = (O[k], vk)

    # Plot(d, V)

    return H, h, E, d


def LegalTriangulation(d, V):
    illegal = True
    c = 0
    while illegal:
        illegal = False
        c += 1
        for e in d.E:
            # if not (e.IncidentFace == d.fout or e.Twin.IncidentFace == d.fout):
            #     PlotIllegal(d, V, e)
            if Illegal(d, e):
                Flip(e)
                # PlotIllegal(d, V, e)
                illegal = True
    print(c)
    PlotIllegal(d, V, None)

def ApplyVelocity(p, v, t):
    if p is None:
        return None
    return p[0] + t * v[0], p[1] + t * v[1]

def ApplyVelocities(P, v, t):
    newP = []
    for i, p in enumerate(P):
        newP.append(ApplyVelocity(p, v[i], t))
    print(newP)
    return newP


V = [None, (-2, -1), (-1, 3), (1, 1), (1, 2), (2, 0), (2, -2), (3, 4), (4, 2)]
t = 2
v = [None, (1.25, 0.5), (0.5, -1), (1, -1), (1, 0), (0, -1), (2, -1), (2, -2), (-1.5, 1)]
# V = [None, (-2, -1), (-1, 3), (1, 1), (1, 2), (2, 0)]
# V = [None, (-2, -1), (-1, 3), (1, 1), (1, 2), (2, 0), (2, -2), (6, 4), (4, 2)]


V = ApplyVelocities(V, v, t)
H, h, E, d = Graham(V)

LegalTriangulation(d, V)

# PlotFecho(V, H)
