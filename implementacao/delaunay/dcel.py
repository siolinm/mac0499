class DCEL():
    def __init__(self, V=None, E=None, F=None, fout=None):
        if V == None:
            self.V = []
        else:
            self.V = V
        if E == None:
            self.E = []
        else:
            self.E = E
        if F == None:
            self.F = []
        else:
            self.F = F
        self.fout = fout

    def AddVertex(self, v):
        self.V.append(v)

    def AddFace(self, f):
        self.F.append(f)

    def AddEdge(self, e):
        self.E.append(e)


class Vertex():
    def __init__(self, Coordinates=None, IncidentEdge=None, Index=None):
        self.Coordinates = Coordinates
        self.IncidentEdge = IncidentEdge
        self.Index = Index

    def __str__(self):
        return f"{self.Coordinates}"

    def __repr__(self):
        return str(self)


class Face():
    def __init__(self, OuterComponent=None, InnerComponents=None):
        self.OuterComponent = OuterComponent
        self.InnerComponents = InnerComponents


class Edge():
    def __init__(self, Origin=None, Twin=None, IncidentFace=None,
                 Next=None, Prev=None):
        self.Origin = Origin
        if Origin != None:
            self.Origin.IncidentEdge = self
        self.Twin = Twin
        if Twin != None:
            Twin.Twin = self
        self.IncidentFace = IncidentFace
        self.Next = Next
        if Next != None:
            Next.Prev = self
        self.Prev = Prev
        if Prev != None:
            Prev.Next = self

    def __str__(self):
        return "\\draw " + str(self.Origin) + " -- " + str(self.Twin.Origin) + ";"

    def __repr__(self):
        return str(self)
