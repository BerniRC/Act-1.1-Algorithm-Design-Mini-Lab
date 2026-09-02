# Problema A — Inversion Counter for Quality Control

Cuenta el número de inversiones de un arreglo de `n` enteros. Un par `(i, j)` es una
inversión si `i < j` y `A[i] > A[j]`.

## Técnica utilizada

**Divide & Conquer** — Merge Sort modificado: durante el paso de "merge" se cuentan las
inversiones que cruzan la mitad izquierda con la derecha.

## Formato de entrada

```
n
a1 a2 ... an
```

## Formato de salida

```
inv
```

## Compilación

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Ejecución

```bash
./main < entrada.txt
```

## Casos de prueba

### Test 1 — Caso general
Entrada:
```
5
2 4 1 3 5
```
Salida:
```
3
```

### Test 2 — Arreglo ya ordenado (caso borde: 0 inversiones)
Entrada:
```
5
1 2 3 4 5
```
Salida:
```
0
```

### Test 3 — Arreglo en orden inverso (caso borde: máximo de inversiones)
Entrada:
```
4
4 3 2 1
```
Salida:
```
6
```

### Test 4 — Elementos duplicados (caso borde)
Entrada:
```
6
5 5 5 1 1 1
```
Salida:
```
9
```
(los tres `5` no forman inversión entre sí porque `A[i] <= A[j]` no cuenta como inversión;
cada uno de los tres `5` forma inversión con cada uno de los tres `1` → 3×3 = 9)

## Complejidad

- **Tiempo:** O(n log n) — recurrencia T(n) = 2T(n/2) + O(n).
- **Espacio:** O(n) — arreglo auxiliar `temp` de tamaño `n`, más O(log n) de pila de
  recursión.

Ver el detalle completo (pseudocódigo y justificación) en `../report.md`.
