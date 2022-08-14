Todo
===

- [x] Documentação
- [x] Adicionar EPS em operações que envolvem tempo e distância (falta splay_tree.c)
- [x] Desempate de eventos na fila de prioridade: DOWN -> HORIZONTAL -> UP
    - [x] checar
- [x] Desenhar lcandp na tela
- [x] Adicionar desenhos de debug para os eventos (com textos)
- [x] Repensar os desempates na splay_tree (provavelmente agora também envolvendo o eixo y)
- [x] Fazer mais testes envolvendo casos degenerados e refazer os testes normais

Bugs
===

- [x] Bugs nos cones em casos degenerados (pontos muito próximos) h/h1.in, r/r1.in
- [x] No torneio em d/h0.in: par p -- c é duplicado em algum momento. Provável erro em: insertTourn ou deleteTourn. Motivo: certificados de pares deletados no torneio não eram deletados, bem como certificados de pares inseridos.
- [x] Em d/h1.in os cones up estão completamente errados. Erro: no instante 0 p pertence a Cands(a) mas na lista p está à esquerda de a, como p continua se movendo para esquerda, uma troca horizontal não é chamada e as estruturas não são atualizadas.
  - [x] Solução: forçar eventos quando os pontos empatam. (comentar na reunião)

Testes
====

Horizontal
---

- [x] tests/h/h0.in
- [x] tests/h/h1.in
- [x] tests/h/d0.in
- [x] tests/h/d1.in
- [x] tests/h/u0.in
- [x] tests/h/u1.in

Down
---

- [x] tests/d/h0.in
- [x] tests/d/h1.in
- [x] tests/d/d0.in
- [x] tests/d/d1.in
- [x] tests/d/u0.in
- [x] tests/d/u1.in

Up
---

- [x] tests/u/h0.in
- [x] tests/u/h1.in
- [x] tests/u/d0.in
- [x] tests/u/d1.in
- [x] tests/u/u0.in
- [x] tests/u/u1.in
    - [x] erros no torneio, em casos onde o par empata no instante 0, mas a
      partir de um momento o outro passa a vencer. O melhor a se fazer seria dar
      um jeito de colocar esses pares vencendo logo de cara.

Random
---

- [x] tests/r/r0.in
- [x] tests/r/r1.in
    - [x] erros no evento do cone up entre q e a, possivelmente alguma query
      chamada errada que deu certo por conta da quantidade de pontos utilizada.
      Problema no empate, resolvido através de alterações em compareS.

Random
---
- [x] tests/degenerate/1.in
  - swap in all orders não está sendo identificado. A função updateListCert não
    é chamada durante a construção da lista ordenada, logo se existe um ALL_CERT
    logo de cara ele não é marcado, mas colocar updateListCert na construção não
    resolve, porque os pontos são inseridos um a um.
- [x] tests/degenerate/2.in
- [x] tests/degenerate/3.in
- [x] tests/degenerate/4.in
- [x] tests/degenerate/5.in
  - Erro na ordem de quem chamar ou em determinar p e q.
- [x] tests/degenerate/circle.in