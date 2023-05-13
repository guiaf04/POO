## @032 Estressados C: Transformações

![cover](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/032/cover.jpg)

[](toc)

- [Intro](#intro)
  - [filter](#filter)
  - [sort](#sort)
  - [reverse](#reverse)
  - [set](#set)
- [Guide](#guide)
- [Shell](#shell)
[](toc)

***

## Intro

### filter

- **get_men**: retorne uma lista com os homens.
- **get_calm_women**: retorne uma lista com as mulheres stress menor que 10.

### sort

- **sort**: ordene a lista pelo valor real
- **sort_stress**: ordene a lista por nível de stress

### reverse

- **reverse**: faça uma função que não altere a lista original, mas retorne uma nova lista invertida

### set

- **unicos**: retorne uma nova lista sem repetição de valores
- **repetidos**: retorne uma nova lista apenas com os valores repetidos

___

## Guide

- [solver.cpp](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/032/.cache/draft.cpp)
- [solver.ts](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/032/.cache/draft.ts)

## Shell

```sh
#__case get_men
$get_men [1,2,-3,4]
[1, 2, 4]
$get_men [1,-2,3,5]
[1, 3, 5]
$get_men [-1,-2,-5,-9]
[]
$end
```

```sh
#__case get_calm_women
$get_calm_women [-10,-5,6,-90]
[-5]
$get_calm_women [-1,5,-11,-99,-8]
[-1, -8]
$end
```

```sh
#__case sort
$sort [5,3,-1,-50,-1,-99]
[-99, -50, -1, -1, 3, 5]
$sort [-1,-50,12,8,-1,-99,-444]
[-444, -99, -50, -1, -1, 8, 12]
$end
```

```sh
#__case sort_stress
$sort_stress [5,3,-1,-50,-1,-99]
[-1, -1, 3, 5, -50, -99]
$sort_stress [-1,-50,12,8,-1,-99,-444]
[-1, -1, 8, 12, -50, -99, -444]
$end
```

```sh
#__case reverse
$reverse [5,3,-1,-50,-1,-99]
[-99, -1, -50, -1, 3, 5]
$reverse []
[]
$end
```

```sh
#__case unique
$unique [1,1,1]
[1]
$unique [5,3,1,1,3,2]
[5, 3, 1, 2]
$unique [5,4,3,2,1]
[5, 4, 3, 2, 1]
$end
```

```sh
#__case repeated
$repeated [1,1,1]
[1, 1]
$repeated [5,3,1,1,3,2]
[1, 3]
$repeated [5,4,3,2,1]
[]
$end
```
