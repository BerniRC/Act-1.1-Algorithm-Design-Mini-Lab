# Act-1.1-Algorithm-Design-Mini-Lab

Este repositorio contiene la solución a tres problemas de programación, cada uno alineado
con una técnica de diseño de algoritmos distinta:

A - Inversion Counter for Quality Control - Divide & Conquer (Merge Sort modificado)
B - Minimum Meeting Rooms (Scheduling) - Greedy
C - Budgeted Study Plan (0/1 Knapsack Variant) - Programación Dinámica

El análisis detallado de cada solución (pseudocódigo, ejemplo trabajado y complejidad)
está en [`report.md`](./report.md).

## Estructura del repositorio

```
/problemA_inversions
    main.cpp
    README.md
/problemB_rooms
    main.cpp
    README.md
/problemC_knapsack
    main.cpp
    README.md
report.md
README.md
```

## Requisitos

- Compilador con soporte de C++17 (g++ recomendado).
- Sistema operativo: cualquiera con g++ (probado en Linux).

## Compilación

Cada problema se compila de forma independiente con la siguiente recomendación:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

```bash
# Problema A
cd problemA_inversions
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main

# Problema B
cd problemB_rooms
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main

# Problema C
cd problemC_knapsack
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Ejecución

Todos los programas leen desde `stdin` y escriben en `stdout` (no hay entrada interactiva).

```bash
./main < entrada.txt
```

O bien, de forma manual (Linux/macOS):

```bash
echo "5
2 4 1 3 5" | ./main
```

Ver el formato exacto de entrada/salida y ejemplos de prueba en el README de cada
subcarpeta y en `report.md`.

## Supuestos generales

- Todas las entradas son válidas y respetan los rangos indicados en el enunciado (no se
  valida entrada malformada).
- Se usan enteros de 64 bits (`long long`) para conteos/valores que pueden exceder 32 bits.
- **Problema B:** el programa asume que las reuniones se reciben ya ordenadas por tiempo
  de inicio (`s_i`). Ver nota de correctitud en `problemB_rooms/README.md` y en
  `report.md`.

## Pruebas

Cada subcarpeta incluye al menos 3 casos de prueba (entrada/salida) en su propio
`README.md`, cubriendo casos base y casos borde (arreglo ordenado/invertido, reuniones
consecutivas/superpuestas, presupuesto ajustado, etc.).
