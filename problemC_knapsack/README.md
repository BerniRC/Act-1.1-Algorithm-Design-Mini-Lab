# Problema C — Budgeted Study Plan (0/1 Knapsack Variant)

Dado un presupuesto de tiempo `T` y `n` módulos de estudio, cada uno con `time[i]` horas
y `value[i]` puntos de beneficio, calcula el máximo valor total alcanzable sin exceder
`T`, pudiendo tomar cada módulo a lo sumo una vez.

## Técnica utilizada

**Programación Dinámica** — variante 0/1 knapsack con arreglo 1D (`table[j]` = mejor
valor usando a lo sumo `j` horas), recorriendo los tiempos de mayor a menor para
garantizar que cada módulo se use como máximo una vez.

## Formato de entrada

```
n T
t1 v1
t2 v2
...
tn vn
```

## Formato de salida

```
best
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
3 10
3 4
4 5
7 10
```
Salida:
```
14
```

### Test 2 — Nada cabe en el presupuesto (caso borde)
Entrada:
```
3 5
6 10
7 20
8 30
```
Salida:
```
0
```

### Test 3 — Presupuesto ajustado, varias combinaciones posibles
Entrada:
```
4 6
1 2
2 4
3 4
4 7
```
Salida:
```
11
```

### Test 4 — Un solo módulo, valor grande (caso borde)
Entrada:
```
1 1
1 1000000
```
Salida:
```
1000000
```

## Complejidad

- **Tiempo:** O(n·T) — un doble ciclo: `n` módulos por `T` posiciones de la tabla.
- **Espacio:** O(T) — un único arreglo `table` de tamaño `T + 1` (versión 1D del DP, no
  se guarda la tabla completa de `n × T`).

Ver el detalle completo (pseudocódigo, invariante del DP y justificación del recorrido
descendente de `j`) en `../report.md`.
