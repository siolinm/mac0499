import matplotlib.pyplot as plt
import numpy as np

def GetCircle(pi, pj, pk):
    tempki = pk[0]**2 - pi[0]**2 + pk[1]**2 - pi[1]**2
    tempji = pj[0]**2 - pi[0]**2 + pj[1]**2 - pi[1]**2
    aki = 2*pk[0] - 2*pi[0]
    bki = 2*pk[1] - 2*pi[1]
    aji = 2*pj[0] - 2*pi[0]
    bji = 2*pj[1] - 2*pi[1]
    det = aki*bji - bki*aji
    if abs(det) < 1.0e-6:
        return None, None
    cx = aki*tempji - aji*tempki
    cy = bki*tempji - bji*tempki
    cx = cx/det
    cy = cy/det
    r = ((pk[0]-cx)**2 + (pk[1] - cy)**2)**0.5
    return (cx, cy), r

def define_circle(p1, p2, p3):
    """
    Returns the center and radius of the circle passing the given 3 points.
    In case the 3 points form a line, returns (None, infinity).
    """
    temp = p2[0] * p2[0] + p2[1] * p2[1]
    bc = (p1[0] * p1[0] + p1[1] * p1[1] - temp) / 2
    cd = (temp - p3[0] * p3[0] - p3[1] * p3[1]) / 2
    det = (p1[0] - p2[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p2[1])

    if abs(det) < 1.0e-6:
        return (None, np.inf)

    # Center of circle
    cx = (bc*(p2[1] - p3[1]) - cd*(p1[1] - p2[1])) / det
    cy = ((p1[0] - p2[0]) * cd - (p2[0] - p3[0]) * bc) / det

    radius = np.sqrt((cx - p1[0])**2 + (cy - p1[1])**2)
    return ((cx, cy), radius)

def PlotIllegal(D, V, il):
    plt.figure(figsize=(8,8))
    plt.ioff()
    xs, ys = zip(*V[1:])
    plt.scatter(xs, ys)
    for e in D.E:
        origin = e.Origin.Coordinates
        destiny = e.Twin.Origin.Coordinates
        if e != il and e.Twin != il:
            plt.plot([origin[0], destiny[0]], [origin[1], destiny[1]], color='black')
        else:
            plt.plot([origin[0], destiny[0]], [origin[1], destiny[1]], color='r')
            if e == il:
                PlotCircle(D, plt, e)
    plt.show()

def PlotCircle(d, plt, e):
    if not (e.IncidentFace == d.fout or e.Twin.IncidentFace == d.fout):
        pi = e.Origin.Coordinates
        pj = e.Next.Origin.Coordinates
        pk = e.Next.Next.Origin.Coordinates
        pl = e.Twin.Prev.Origin.Coordinates
        plt.scatter([pi[0], pj[0], pk[0]], [pi[1], pj[1], pk[1]], color='r')
        plt.scatter([pl[0]], [pl[1]], color='g')
        c, r = define_circle(pi, pj, pk)
        circle = plt.Circle(c, r, fill=False)
        plt.gcf().gca().add_artist(circle)

def Plot(D, V, il=None):
    plt.figure()
    xs, ys = zip(*V[1:])
    plt.scatter(xs, ys)
    for v in D.V:
        plt.annotate(v.Index, v.Coordinates)
    for e in D.E:
        if il != None and e == il or e.Twin == il:
            color = 'r'
        else:
            color = 'black'
        origin = e.Origin.Coordinates
        destiny = e.Twin.Origin.Coordinates
        dx = destiny[0] - origin[0]
        dy = destiny[1] - origin[1]
        C = 50
        R = 1/5
        norm = ((dx**2 + dy**2)**0.5)
        dx = dx/norm
        dy = dy/norm
        normvec = (dy/C, -dx/C)

        norigin = (origin[0]+normvec[0], origin[1]+normvec[1])
        ndestiny = (destiny[0]+normvec[0], destiny[1]+normvec[1])
        dx = ndestiny[0] - norigin[0]
        dy = ndestiny[1] - norigin[1]
        norm = ((dx**2 + dy**2)**0.5)
        dx = (dx/norm)*R
        dy = (dy/norm)*R
        norigin = (norigin[0] + dx, norigin[1] + dy)
        ndestiny = (ndestiny[0] - dx, ndestiny[1] - dy)

        plt.annotate(text='', xy=norigin, xytext=ndestiny,
        arrowprops=dict(arrowstyle='->', color=color))

    plt.show()

def PlotFecho(V, H, h):
    XY = []
    for i in range(1, h+1):
        XY.append(V[H[i]])
    XY.append(V[H[1]])
    xs, ys = zip(*XY)
    plt.figure()
    plt.plot(xs, ys)
    xs, ys = zip(*V[1:])
    plt.scatter(xs, ys)
    plt.show()
