import numpy as np


def circle(p1, p2, p3):
    points = {
        "a": (-2, 1),
        "b": (-1, 3),
        "c": (1, 1),
        "d": (1, 2),
        "e": (2, 0),
        "f": (2, -2),
        "g": (3, 4),
        "h": (4, 2)
    }

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
    "abc": ["bcd", "aec"],
    "bcd": ["abc", "bdg", "ced"],
    "bdg": ["dhg", "bcd"],
    "dhg": ["bdg", "deh"],
    "ced": ["bcd", "deh", "aec"],
    "deh": ["dhg", "ced", "fhe"],
    "fhe": ["deh", "afe"],
    "afe": ["fhe", "aec"],
    "aec": ["abc", "afe", "ced"]
}


for key, value in P.items():
    a, b, c = [*key]
    print(f"\\node ({key}) at {circle(a, b, c)} {{\\textbullet}}; % {a}-{b}-{c}")


