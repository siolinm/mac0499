import numpy as np
import math
from aux import *


def get_vector(p1, p2):
    return p2[0] - p1[0], p2[1] - p1[1]


def get_normal(v):
    return -v[1], v[0]


def scale(v, x):
    return v[0] * x, v[1] * x


def sig(x):
    if x > 0:
        return 1
    return -1


def soma(v, w):
    return v[0] + w[0], v[1] + w[1]


def define_line(p1, p2, p3):
    m = ((p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2)

    w = get_vector(p3, m)
    n = math.sqrt(w[0] ** 2 + w[1] ** 2)
    w = scale(w, 1/n)
    w = scale(w, 2)

    if not esq(p1, p2, p3):
        w = scale(w, -1)

    return soma(p3, w)


def line(p1, p2, p3):
    points = {'a': (-3.0, 0), 'b': (1, 1), 'c': (3.5, 4.0), 'd': (0, 3), 'e': (1, 5), 'f': (-2.0, 4), 'g': (-4, 6)}
    print(f"% {p1} -- {p2}")
    return define_line(points[p1], points[p2], p3)


def circle(p1, p2, p3):
    points = {'a': (-3.0, 0), 'b': (1, 1), 'c': (3.5, 4.0), 'd': (0, 3), 'e': (1, 5), 'f': (-2.0, 4), 'g': (-4, 6)}

    return define_circle(points[p1], points[p2], points[p3])


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
        return None, np.inf

    # Center of circle
    cx = (bc * (p2[1] - p3[1]) - cd * (p1[1] - p2[1])) / det
    cy = ((p1[0] - p2[0]) * cd - (p2[0] - p3[0]) * bc) / det

    return cx, cy


P = {
    "abd": ["afd", "dbc", "ab$"],
    "afd": ["fed", "afg"],
    "dbc": ["bc$"],
    "afg": ["ga$"],
    "fge": ["fed", "afg", "eg$"],
    "fed": [],
    "edc": ["fed", "dbc", "ce$"]
}

for key, value in P.items():
    a, b, c = [*key]
    print(f"\\node ({key}) at {circle(a, b, c)} {{\\textbullet}}; % {a}-{b}-{c}")
    for s in value:
        d, e, f = [*s]
        if f == '$':
            print(f"\\draw {circle(a, b, c)} -- {line(d, e, circle(a, b, c))};")
        else:
            print(f"\\draw {circle(a, b, c)} -- {circle(d, e, f)}; %{key}--{s}")
