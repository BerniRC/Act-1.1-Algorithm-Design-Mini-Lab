# Problema B — Minimum Meeting Rooms (Scheduling)

Dado un conjunto de `m` reuniones `(s_i, e_i)`, calcula el número mínimo de salas
necesarias para que ninguna reunión se solape con otra en la misma sala. Si una reunión
termina en `t` y otra empieza en `t`, no se consideran solapadas (pueden compartir sala).

## Técnica utilizada

**Greedy**: se procesan las reuniones en orden de tiempo de inicio y, para cada una, se
le asigna la primera sala que ya quedó libre (cuyo último `end` ≤ el `start` actual); si
ninguna sala está libre, se abre una sala nueva.

## Formato de entrada

```
m
s1 e1
s2 e2
...
sm em
```

## Formato de salida

```
rooms
```

## ⚠️ Supuesto importante sobre el orden de entrada

La implementación actual **asume que las reuniones llegan ya ordenadas por tiempo de
inicio (`s_i`)**. Si la entrada no viene ordenada, el resultado puede ser incorrecto.

Ejemplo de fallo con entrada desordenada (mismas 3 reuniones del Test 1, en otro orden):

```
Entrada:
3
15 20
0 30
5 10

Salida obtenida: 3   (la correcta es 2)
```

**Recomendación:** si no se puede garantizar el orden de la entrada, agregar al inicio de
`main()`:
```cpp
sort(meetings.begin(), meetings.end());
```
antes de procesar las reuniones. Todos los casos de prueba incluidos abajo ya vienen
ordenados por `s_i`, por lo que producen el resultado esperado con el código tal cual
está.

## Compilación

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Ejecución

```bash
./main < entrada.txt
```

## Casos de prueba
(todas las entradas están ordenadas por tiempo de inicio, según el supuesto de la
implementación)

### Test 1 — Caso general
Entrada:
```
3
0 30
5 10
15 20
```
Salida:
```
2
```

### Test 2 — Reuniones consecutivas, sin solape (caso borde)
Entrada:
```
3
0 10
10 20
20 30
```
Salida:
```
1
```

### Test 3 — Todas se solapan (caso borde: máximo de salas)
Entrada:
```
4
1 10
2 9
3 8
4 7
```
Salida:
```
4
```

### Test 4 — Muchos inicios idénticos (caso borde)
Entrada:
```
3
5 20
5 15
5 10
```
Salida:
```
3
```

## Complejidad

- **Tiempo:** O(m²) en el peor caso. Para cada una de las `m` reuniones se recorre
  linealmente la lista de salas abiertas hasta encontrar una libre (o abrir una nueva),
  y en el peor caso (todas se solapan) el número de salas crece hasta `m`.
- **Espacio:** O(m) — el vector `rooms2` guarda a lo sumo una entrada por sala abierta
  (máximo `m`).

> **Nota de eficiencia:** para `m` hasta 2×10⁵, O(m²) puede no ser suficientemente
> rápido en el peor caso (todas las reuniones solapadas). La alternativa clásica es usar
> un min-heap sobre los tiempos de finalización de las salas ocupadas, lo que baja la
> complejidad a **O(m log m)**. Ver la sección de Problema B en `../report.md` para el
> pseudocódigo de ambas variantes y la comparación.
