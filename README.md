# Laboratorio 3 - Procesos

En este laboratorio vamos a ver las llamadas al sistema relacionadas con procesos.

:bulb: Incluir las respuestas a las preguntas de los ejercicios en un archivo de texto con el nombre `respuestas.txt`.

:date: Fecha de entrega: 16/04

## Ejercicio 1: Crear un proceso

El programa [`fork.c`](fork.c) debe recibir como parámetros el nombre de un archivo y dos cadenas:

```sh
$ bin/fork hola.txt string1 string2
```

El programa debe abrir el archivo indicado en modo `O_APPEND`. Si el archivo no existe, debe crearlo con permisos `0644`. Luego, debe crear un proceso hijo que escribe en el archivo `Hijo: string2`, donde `string2` es el tercer parámetro. Para crear el proceso hijo, utilizar la llamada al sistema [`fork()`](http://man7.org/linux/man-pages/man2/fork.2.html). El proceso padre debe esperar a que el proceso hijo finalice y luego escribir `Padre: string1` en el archivo. Usar la llamada al sistema [`wait()`](http://man7.org/linux/man-pages/man2/wait.2.html) para esperar la finalización del proceso hijo.

Una ejecución de ejemplo sería:

```sh
$ bin/fork hola.txt hola mundo
$ cat hola.txt
Hijo: mundo
Padre: hola
$
```

Ejecutar `make check` para verificar la solución.

## Ejercicio 2: Crear multiples procesos

Completar el programa [`mfork.c`](mfork.c) para que cree *n* procesos hijos:

* El número *n* debe ser indicado como parámetro en la línea de comandos.
* Cada proceso hijo debe tener asignado un _id_ único, que es un número entero. El primer hijo creado debe tener el _id_ 1, el segundo el _id_ 2 y así sucesivamente.
* Cada proceso hijo debe imprimir por la salida estándar su *identificador de proceso* (PID) y su _id_. Para obtener el PID emplear la llamada al sistema [`getpid()`](http://man7.org/linux/man-pages/man2/getpid.2.html).
* Cada proceso debe esperar un número aleatorio de segundos, no mayor a 10, antes de terminar. Para que el proceso se suspenda ese número de segundos, utilizar la función [`sleep()`](http://man7.org/linux/man-pages/man3/sleep.3.html).
* Cada proceso hijo debe finalizar con la llamada al sistema [`exit()`](http://man7.org/linux/man-pages/man2/exit.3.html). Como parámetro debe utilizar el número de segundos que espero.
* El proceso padre debe esperar a que todos sus procesos hijos finalicen. Utilizar la llamada al sistema [`waitpid()`](http://man7.org/linux/man-pages/man2/waitpid.2.html) para esperar a que los procesos hijos terminen.
* El proceso padre debe imprimir cuantos segundos durmió cada proceso hijo. Este dato se obtiene mediante `waitpid()`.

Por ejemplo, si se ejecuta el programa indicando que se creen 3 procesos hijo, debe obtenerse una salida similar a la siguiente:

```bash
$ bin/mfork 3
Hijo 3431: id 1
Hijo 3434: id 2
Hijo 3432: id 3
Hijo 3434 durmió 4 segundos.
Hijo 3432 durmió 2 segundos.
Hijo 3431 durmió 7 segundos.
mfork: todos los hijos terminaron.
$
```

## Ejercicio 3: Ejecutar un programa

Completar el programa [`exec.c`](exec.c) para que, desde un proceso hijo, ejecute el programa indicado como parámetro. Para esto, utilizar la llamada al sistema [`exec()`](http://man7.org/linux/man-pages/man3/exec.3.html). 

Por ejemplo, para ejecutar el comando `ls -h`:

```sh
$ bin/exec ls -lh
```

El proceso padre debe esperar a que termine de ejecutar el comando indicado. Además, el valor de retorno del proceso padre debe ser el mismo que el retornado por el proceso hijo.

Ejecutar `make check` para verificar la solución.

## Ejercicio 4: Interprete de comandos

En esta parte del laboratorio se agregan varias funcionalidades al intérprete de comandos [`sh.c`](sh.c) (tomado del curso [_6.828 Operating Systems Engineering_](https://pdos.csail.mit.edu/6.828/) del MIT).

### 4.1: Ejecución de comandos

Implementar la ejecución de comandos. El parser del intérprete ya genera una estructura `execcmd` que contiene el comando a ejecutar y los parámetros que se le hayan indicado. Deben completar el caso `' '` en la función `runcmd()`. Para ejecutar el comando, utilizar la llamada a sistema [`execv()`](http://man7.org/linux/man-pages/man3/exec.3.html). Se debe imprimir un mensaje de error si `execv()` falla, utilizando la función [`perror()`](http://man7.org/linux/man-pages/man3/perror.3.html).

### 4.1: Redirección de E/S

Implementar redirección de E/S mediante los operadores `<` y `>`, de manera que el shell permita ejecutar comandos como:

```bash
$ echo "sistemas operativos" > x.txt
$ cat < x.txt
sistemas operativos
$
```

El parser implementado en el shell ya reconoce estos operadores, y genera una estructura `redircmd` con los datos necesarios para implementar la redirección. Deben completar el código necesario en la función `runcmd()`. Consultar las llamadas al sistema [`open()`](http://man7.org/linux/man-pages/man2/open.2.html) y [`close()`](http://man7.org/linux/man-pages/man2/close.2.html). Imprimir un mensaje de error si alguna de las llamadas al sistema empleadas falla con [`perror()`](http://man7.org/linux/man-pages/man3/perror.3.html). Verificar los permisos con los que se crea el archivo.

### 4.1: Tuberías (pipes)

Implementar soporte para el uso de tuberías (_pipes_), para poder ejecutar un comando como:

```
$ echo "hola" | wc
    1   1   5
$
```

El parser ya reconoce el operador `|` y guarda en la estructura `pipecmd` todos los datos requeridos para conectar dos procesos mediante una tubería. Deben agregar el código necesario en la función `runcmd()`. Las llamadas al sistema que deben utilizar son [`pipe()`](http://man7.org/linux/man-pages/man2/pipe.2.html), [`fork()`](http://man7.org/linux/man-pages/man2/fork.2.html), [`close()`](http://man7.org/linux/man-pages/man2/close.2.html) y [`dup()`](http://man7.org/linux/man-pages/man2/dup.2.html).

## Ejercicio 5: getppid() en xv6

Añadir a _xv6_ la llamada al sistema `getppid()`. Utilizar como guía la llamada al sistema `getpid()`. Agregar también un programa con el que se pruebe el funcionamiento de la llamada al sistema.

Incluir en el archivo `respuestas.txt` una explicación de cómo se implemento la nueva llamada al sistema.

---

¡Fin del Laboratorio 3!

