# Reporte — Mini-Lab: Técnicas de Diseño de Algoritmos

---

## Problema A — Inversion Counter for Quality Control

### 1. Resumen del problema

Dado un arreglo `A` de `n` enteros, se debe contar el número de *inversiones*: pares
`(i, j)` con `i < j` y `A[i] > A[j]`. Este tipo de conteo mide qué tan "desordenado"
está un arreglo respecto de su orden ascendente, y aparece en contextos como control de
calidad (comparar el orden de una secuencia de mediciones contra el orden esperado) o en
métricas de similitud de rankings.

Un enfoque de fuerza bruta compara todos los pares en O(n²), lo cual es demasiado lento
para `n` hasta 2×10⁵ (hasta ~2×10¹⁰ comparaciones).

### 2. Idea del algoritmo (Divide & Conquer)

Se modifica **Merge Sort**: al ordenar el arreglo por mitades, cada vez que se hace el
*merge* de la mitad izquierda `[left, mid]` con la derecha `[mid+1, right]`, ambas ya
están ordenadas internamente. Si en algún punto `A[i] > A[j]` (elemento de la izquierda
mayor que uno de la derecha), entonces **todos** los elementos restantes de la izquierda,
desde `i` hasta `mid`, también son mayores que `A[j]` (porque la izquierda está
ordenada). Eso aporta `(mid - i + 1)` inversiones de una sola vez, sin compararlas una
por una.

El total de inversiones es la suma de las inversiones dentro de la mitad izquierda, las
de la mitad derecha, y las que "cruzan" ambas mitades durante el merge.

### 3. Pseudocódigo

```
function mergeSort(A, left, right):
    if left >= right: return 0
    mid = (left + right) / 2
    inv = mergeSort(A, left, mid)
    inv += mergeSort(A, mid+1, right)
    inv += merge(A, left, mid, right)
    return inv

function merge(A, left, mid, right):
    i = left, j = mid+1, k = left
    inv = 0
    while i <= mid and j <= right:
        if A[i] <= A[j]:
            temp[k++] = A[i++]
        else:
            inv += (mid - i + 1)   # A[i..mid] son todas > A[j]
            temp[k++] = A[j++]
    copiar restantes de A[i..mid] y A[j..right] a temp
    copiar temp[left..right] de vuelta a A
    return inv
```

### 4. Argumento de correctitud

**Invariante:** al llegar al `merge`, tanto `A[left..mid]` como `A[mid+1..right]` están
ordenados ascendentemente (por hipótesis inductiva de las llamadas recursivas).

Durante el merge, cuando se compara `A[i]` (izquierda) con `A[j]` (derecha):
- Si `A[i] <= A[j]`, no hay inversión asociada a ese par en este paso; se avanza `i`.
- Si `A[i] > A[j]`, entonces, como `A[i..mid]` está ordenado ascendentemente,
  `A[i] <= A[i+1] <= ... <= A[mid]`, por lo que **todos** esos `mid - i + 1` elementos
  son también mayores que `A[j]`. Cada uno forma una inversión con `A[j]` (su posición
  original en la izquierda es menor que la de `A[j]` en la derecha). Se suman de una vez
  y se avanza `j`.

Cada inversión del arreglo original cae en exactamente uno de tres casos: ambos índices
en la mitad izquierda, ambos en la derecha, o uno en cada mitad — por lo que sumar los
tres conteos (recursión izquierda + recursión derecha + merge) cuenta cada inversión
exactamente una vez.

### 5. Ejemplo trabajado

Entrada: `A = [2, 4, 1, 3, 5]`

- Se parte en `[2, 4]` y `[1, 3, 5]`.
- `[2, 4]` ya está ordenado, 0 inversiones internas.
- `[1, 3, 5]` ya está ordenado, 0 inversiones internas.
- Merge de `[2, 4]` con `[1, 3, 5]`:
  - Compara 2 vs 1 → 2 > 1 → suma `(mid - i + 1) = 2` inversiones (2 y 4 son ambos
    mayores que 1) → total parcial 2.
  - Compara 2 vs 3 → 2 ≤ 3 → sin inversión.
  - Compara 4 vs 3 → 4 > 3 → suma 1 inversión (solo queda el 4 en la izquierda) → total
    parcial 3.
  - Compara 4 vs 5 → 4 ≤ 5 → sin inversión.
- Total: **3 inversiones**, que corresponden a los pares `(2,1)`, `(4,1)`, `(4,3)`.

Salida del programa: `3` ✅ (coincide con la esperada).

### 6. Complejidad

**Tiempo:** cada nivel de la recursión hace un trabajo total de O(n) en los merges
(cada elemento se copia una vez por nivel), y hay O(log n) niveles. Recurrencia:

```
T(n) = 2·T(n/2) + O(n)  →  T(n) = O(n log n)   (Teorema Maestro, caso 2)
```

**Espacio:** O(n) por el arreglo auxiliar `temp` usado en cada merge (reutilizado, no
se aloja por nivel), más O(log n) de profundidad de la pila de recursión. Total: **O(n)**.

---

## Problema B — Minimum Meeting Rooms (Scheduling)

### 1. Resumen del problema

Dadas `m` reuniones `(s_i, e_i)`, se debe determinar el número mínimo de salas
necesarias para que ninguna sala tenga dos reuniones solapadas al mismo tiempo. Si una
reunión termina exactamente cuando otra empieza, pueden compartir sala (no se consideran
solapadas). Este es un problema clásico de asignación de recursos bajo restricciones de
tiempo.

### 2. Idea del algoritmo (Greedy)

Se procesan las reuniones **en orden de tiempo de inicio**. Para cada reunión, se intenta
reutilizar una sala que ya haya quedado libre (es decir, cuya última reunión asignada
termine en un tiempo ≤ el inicio de la reunión actual). Si ninguna sala está libre, se
abre una sala nueva. El número final de salas abiertas es la respuesta.

La *propiedad de elección greedy* es: nunca conviene abrir una sala nueva si existe una
ya libre, porque usar una sala libre nunca perjudica la asignación de reuniones futuras
(todas las salas libres son intercambiables entre sí en ese instante).

### 3. Pseudocódigo (implementación actual)

```
function minRooms(meetings):                 # asume meetings ordenado por s_i
    rooms = []                                # lista de "último fin" por sala
    for each (s, e) in meetings:
        placed = false
        for room in rooms:
            if room.lastEnd <= s:
                room.lastEnd = e
                placed = true
                break
        if not placed:
            rooms.append(new room with lastEnd = e)
    return size(rooms)
```

> **Nota:** esta es la implementación tal como está en `main.cpp`. Es correcta *siempre
> que la entrada venga ordenada por `s_i`*, pero en el peor caso recorre linealmente
> todas las salas abiertas para cada reunión (ver sección de complejidad).

### 3.1 Variante recomendada con min-heap (O(m log m))

Para garantizar eficiencia también en el peor caso, la variante estándar usa un
min-heap con los tiempos de fin de las salas ocupadas:

```
function minRoomsHeap(meetings):
    sort meetings by s_i
    heap = min-heap (vacío)                   # guarda tiempos de fin
    for each (s, e) in meetings:
        if heap not empty and heap.top() <= s:
            heap.pop()                        # se reutiliza esa sala
        heap.push(e)
    return size(heap)
```

Aquí, en cada iteración solo se consulta y opcionalmente se extrae el mínimo del heap
(O(log m)), en vez de recorrer todas las salas.

### 4. Argumento de correctitud

Al ordenar por `s_i` y procesar en ese orden, en cualquier instante las salas "libres"
son exactamente aquellas cuyo `lastEnd <= s_actual`. Asignar la reunión actual a
**cualquier** sala libre (no importa cuál) nunca es peor que abrir una nueva, porque:

- Si existe una sala libre, usarla no bloquea ninguna reunión futura que esa sala no
  hubiera bloqueado igual si estuviera libre.
- Abrir una sala nueva cuando hay una libre solo puede aumentar el conteo final sin
  necesidad.

Por inducción sobre el número de reuniones procesadas, el número de salas abiertas en
todo momento es igual al máximo número de reuniones simultáneas visto hasta ese punto,
que es exactamente la cota inferior teórica del problema (no puede haber menos salas que
el pico de solapamiento).

**Riesgo de correctitud detectado:** la implementación actual no ordena `meetings`
dentro del programa; asume que ya llega ordenado por `s_i` (ver comentario en el código
y en `problemB_rooms/README.md`). Si la entrada no viene ordenada, el resultado es
incorrecto. Ejemplo verificado:

```
Entrada (mismas reuniones del ejemplo, en otro orden):
3
15 20
0 30
5 10

Salida obtenida: 3   (la salida correcta, ordenando primero, es 2)
```

Se recomienda agregar `sort(meetings.begin(), meetings.end());` al inicio de `main()`
para eliminar esta dependencia del orden de entrada.

### 5. Ejemplo trabajado

Entrada: reuniones `(0,30), (5,10), (15,20)` (ya ordenadas por inicio).

- `(0,30)`: no hay salas → se abre Sala 1, `lastEnd = 30`.
- `(5,10)`: Sala 1 tiene `lastEnd = 30 > 5` → no está libre → se abre Sala 2,
  `lastEnd = 10`.
- `(15,20)`: se revisa Sala 1 (`lastEnd = 30 > 15`, no libre); se revisa Sala 2
  (`lastEnd = 10 <= 15`, libre) → se reutiliza Sala 2, `lastEnd = 20`.
- Salas abiertas al final: 2.

Salida del programa: `2` ✅.

### 6. Complejidad

**Implementación actual (búsqueda lineal de sala libre):**
- **Tiempo:** O(m²) en el peor caso. Cada una de las `m` reuniones puede recorrer hasta
  todas las salas abiertas hasta el momento (peor caso: todas las reuniones se
  solapan, como en el Test 3, y el número de salas crece hasta `m`).
- **Espacio:** O(m) — a lo sumo una entrada por sala abierta, y en el peor caso hay
  `m` salas.

**Variante con min-heap (recomendada para el peor caso a gran escala):**
- **Tiempo:** O(m log m) — O(m log m) del `sort` inicial más O(m log m) de hasta `m`
  operaciones de heap (`push`/`pop`), cada una O(log m).
- **Espacio:** O(m) — el heap guarda a lo sumo una entrada por sala/reunión activa.

> Para `m` hasta 2×10⁵, la variante O(m²) puede llegar a ~4×10¹⁰ operaciones en el peor
> caso (todas las reuniones solapadas), lo cual es demasiado lento. Si el criterio de
> eficiencia de la rúbrica evalúa el peor caso a esa escala, se recomienda migrar a la
> variante con min-heap.

---

## Problema C — Budgeted Study Plan (0/1 Knapsack Variant)

### 1. Resumen del problema

Se tienen `n` módulos de estudio, cada uno con un costo en horas `time[i]` y un
beneficio `value[i]`. Con un presupuesto total de `T` horas, y pudiendo tomar cada
módulo a lo sumo una vez, se busca el subconjunto de módulos que maximiza el valor total
sin exceder `T`. Es una instancia directa del problema de la mochila 0/1.

Con `n` hasta 2000, una búsqueda exhaustiva de subconjuntos (2ⁿ) es completamente
inviable; se necesita un enfoque polinomial.

### 2. Idea del algoritmo (Programación Dinámica)

Se define `table[j]` = máximo valor alcanzable usando a lo sumo `j` horas, considerando
los módulos procesados hasta el momento. Se recorre cada módulo una vez y, para cada uno,
se actualiza `table[j]` para todo `j` desde `T` hasta `time[i]`, **en orden
descendente**, de modo que cada módulo se use como máximo una vez (evita usar el mismo
módulo dos veces en la misma pasada, como ocurriría con un recorrido ascendente, que
correspondería a la variante de mochila con repetición).

Al final, `table[T]` contiene el valor máximo alcanzable con el presupuesto completo.

### 3. Pseudocódigo

```
function knapsack(n, T, time[], value[]):
    table = array of size (T+1), inicializado en 0
    for i = 0 to n-1:
        for j = T downTo time[i]:
            table[j] = max(table[j], table[j - time[i]] + value[i])
    return table[T]
```

### 4. Argumento de correctitud

**Invariante:** después de procesar los primeros `i` módulos, `table[j]` contiene el
máximo valor alcanzable usando **únicamente un subconjunto de los primeros `i` módulos**
con costo total ≤ `j`, para todo `j` en `[0, T]`.

Al procesar el módulo `i` (costo `time[i]`, valor `value[i]`), para cada `j >= time[i]`
hay dos opciones: no tomar el módulo `i` (se conserva `table[j]` del paso anterior) o
tomarlo (se usa `table[j - time[i]]` del paso anterior, que por invariante ya refleja
solo módulos `0..i-1`, más `value[i]`). Tomar el máximo de ambas opciones preserva la
invariante para `i+1`.

**Por qué el recorrido de `j` debe ser descendente:** si fuera ascendente, `table[j -
time[i]]` podría ya haber sido actualizado en esta misma pasada del módulo `i` (es
decir, podría ya incluir al módulo `i`), permitiendo usar el módulo `i` más de una vez —
lo cual convertiría el algoritmo en la variante de mochila **con repetición**, violando
la restricción 0/1 del problema.

### 5. Ejemplo trabajado

Entrada: módulos `(3,4), (4,5), (7,10)`, `T = 10`.

- Después de procesar `(3,4)`: `table[j] = 4` para todo `j >= 3`.
- Después de procesar `(4,5)`: para `j = 7`, se compara no tomarlo (`table[7]=4`) contra
  tomarlo (`table[3] + 5 = 9`) → `table[7] = 9`. Para `j = 10`: `table[10]` pasa a
  `max(4, table[6]+5=9) = 9`.
- Después de procesar `(7,10)`: para `j = 10`, se compara no tomarlo (`table[10] = 9`)
  contra tomarlo (`table[3] + 10 = 4 + 10 = 14`) → `table[10] = 14`.
- Resultado: `table[10] = 14`, logrado con los módulos de costo 3 y 7
  (`3 + 7 = 10 <= T`, `4 + 10 = 14`).

Salida del programa: `14` ✅.

### 6. Complejidad

**Tiempo:** O(n·T) — se recorren los `n` módulos y, para cada uno, hasta `T` posiciones
de la tabla. Con `n <= 2000` y `T <= 5000`, esto es a lo sumo ~10⁷ operaciones, muy
manejable.

**Espacio:** O(T) — se usa una sola tabla 1D `table[0..T]`, reutilizada en cada módulo
(en vez de una tabla 2D de tamaño `n × T`, que sería O(n·T) de memoria).

---

## Resumen de complejidades

| Problema | Técnica | Tiempo | Espacio |
|---|---|---|---|
| A — Inversion Counter | Divide & Conquer | O(n log n) | O(n) |
| B — Minimum Meeting Rooms | Greedy | O(m²) actual / O(m log m) con heap | O(m) |
| C — Budgeted Study Plan | Programación Dinámica | O(n·T) | O(T) |
