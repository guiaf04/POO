## @039 Estressados D: Controles

![cover](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/039/cover.jpg)

[](toc)

- [Intro](#intro)
  - [pares](#pares)
  - [proximidade](#proximidade)
  - [duplo for](#duplo-for)
  - [remoções](#remoções)
- [Guide](#guide)
- [Shell](#shell)
[](toc)

***

## Intro

### pares

- **occurr**: Faça uma contagem de quantas vezes cada nível de stress aparece e retorne essa contagem ordenado pelo nível de stress.
- **times** Uma ou mais pessoas de mesmo stress seguidas formam um time. Gere um vetor compactado indicando o nível de stress e quantas pessoas tem em cada time?

### proximidade

- **mnext**: Apresente um mapa colocando 1 nas posições que existem homens ao lado de pelo menos uma mulher.
- **alone**: quais posições existem homens que não estão do lado de nenhuma mulher?

### duplo for

- **couple**: Casais são formados quando quando um homem e uma mulher com o mesmo nível de stress se encontram. Retorne a quantidade de casais que podem ser formados.
- **subseq**: Dada uma sequência de valores, procure essa sequência na fila e retorne a primeira posição onde ela começar.

### remoções

- **erase**: dado a lista com os índices de todas as pessoas que saíram da fila, qual a fila resultante?
- **clear**: dado um valor, remova todas as vezes que esse valor aparece na lista.

___

## Guide

- [solver.cpp](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/039/.cache/draft.cpp), [help.h](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/039/help.h)
- [solver.js](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/039/.cache/draft.js)
- [solver.ts](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/039/.cache/draft.ts)

## Shell

```sh
#__case occur
$occurr [1,3,-1]
[(1, 2), (3, 1)]
$occurr [-2,1,-2,4]
[(1, 1), (2, 2), (4, 1)]
$occurr [1,2,5,9,-1,-1,5,5]
[(1, 3), (2, 1), (5, 3), (9, 1)]
$end
```

```sh
#__case teams
$teams []
[]
$teams [5]
[(5, 1)]
$teams [5,5]
[(5, 2)]
$teams [3,5,5,5]
[(3, 1), (5, 3)]
$teams [5,5,2,2,2,4,4]
[(5, 2), (2, 3), (4, 2)]
$teams [5,5,7,1,5]
[(5, 2), (7, 1), (1, 1), (5, 1)]
$end
```

```sh
#__case mnext
$mnext [5]
[0]
$mnext [5,2]
[0, 0]
$mnext [-1,-3,5]
[0, 0, 1]
$mnext [1,2,5,9,-1,-1,5,5]
[0, 0, 0, 1, 0, 0, 1, 0]
$end
```

```sh
#__case alone
$alone [5]
[1]
$alone [5,3]
[1, 1]
$alone [-1,-3,5]
[0, 0, 0]
$alone [1,-3,5]
[0, 0, 0]
$alone [-1,3,-5]
[0, 0, 0]
$alone [1,2,5,9,-1,-1,5,5]
[1, 1, 1, 0, 0, 0, 0, 1]
$end
```

```sh
#__case couple
$couple [5]
0
$couple [5,3]
0
$couple [5,-5]
1
$couple [-5,-5]
0
$couple [-5,5]
1
$couple [-5,5,-5,-5]
1
$couple [2,-2,4,2,-4,-4]
2
$couple [2,-2,4,2,-4,-4,4]
3
$end
```

```sh
#__case subseq
$subseq [1,2,4,3] [8]
-1
$subseq [1,2,4,3] [1,2]
0
$subseq [1,2,4,3] [2,4,3]
1
$subseq [3,5,5,5] [5,5]
1
$subseq [5,5,2,2,2,4,4] [2,2,4]
3
$subseq [5,5,2,2,2,4,4] [2,2,4,4,3]
-1
$subseq [5,5,2,2,2,4,4] [9]
-1
$subseq [5,5,2,2,2,4,4] [4,4,4]
-1
$end
```

```sh
#__case erase
$erase [1,2,4,3] [0,1,2,3]
[]
$erase [1,2,4,3] [1,2]
[1, 3]
$erase [1,2,4,3] [2,1,3]
[1]
$erase [3,5,5,5] [3]
[3, 5, 5]
$end
```

```sh
#__case clear
$clear [2,2,2,2,2] 2
[]
$clear [1,2,4,3] 1
[2, 4, 3]
$clear [1,2,2,3,2,2] 2
[1, 3]
$clear [5,5,3,5,5,5] 5
[3]
$end
```
