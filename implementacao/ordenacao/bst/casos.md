- O predecessor de um nó é o maior elemento da subárvore esquerda e o sucessor é o menor elemento da subárvore direita.
- Caso a subárvore esquerda não exista - o predecessor dele é o primeiro nó menor do que ele "no caminho para cima" (subo para o pai dele e checo se essa é a subárvore direita do pai dele), se eu chegar na r sem achar um nó assim, então ele não tem predecessor.
- Caso a subárvore direita não exista - o sucessor dele é o primeiro nó maior do que ele "no caminho para cima" (subo para o pai dele e checo se essa é a subárvore esquerda do pai dele), se eu chegar na r sem achar um nó assim, então ele não tem sucessor.