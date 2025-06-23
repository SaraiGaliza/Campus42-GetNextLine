# Campus42-GetNextLine
El objetivo de este proyecto es simple: programar una función que devuelva una línea leída de un file descriptor.

CONCEPTOS CLAVE:
🔹 Variables estaticas
Se declara con la palabra clave static. Ejemplo: static int contador = 0;
Se inicializa solo una vez, la primera vez que se ejecuta su declaración.
Cuando declaras una variable como static dentro de una función, esta mantiene su valor entre llamadas. Es decir, no se reinicia cada vez que se llama a la función.
Tiene una vida útil que dura toda la ejecución del programa, incluso si su ámbito es local a una función.
Estas variables se almacenan en el segmento de datos del programa, que se define en tiempo de compilación. Por lo que solo pueden inicializarse con valores constantes (el valor debe ser conocido en tiempo de compilación, es decir, antes de ejecutar el programa)

Cuando declaras una variable global como static, su ámbito se limita al archivo en el que se define. Esto significa que no puede ser accedida desde otros archivos, lo cual es útil para encapsular datos y evitar conflictos de nombres.
Tanto las varables estaticas como las variables globales si no se inicializan explícitamente, el compilador la inicializa automáticamente a cero.
Varaibles locales: Solo existen dentro de esa función. Se crean cuando entras en la función y se destruyen cuando sales. Si no las inicializas, su contenido será indefinido (lo que haya en memoria, literalmente basura).

🔹 ¿Qué es un File Descriptor?
Un file descriptor (descriptor de archivo) es un número entero que el sistema operativo asigna para identificar un archivo abierto, un socket (comunicación por red), un pipe (comunicación entre procesos), o incluso la entrada/salida estándar (la pantalla o el teclado). Basicamente, todo puede ser un descriptor de archivo.
⚠️ No es el archivo en sí, ni los datos. Es un número que representa ese archivo en el sistema.
En C y en la mayoria de sistemas de Unix hay 3 File Descriptors por defecto:
- 0: stdin - Entrada estándar (teclado) // scanf, read(0, ...)
- 1: stdout - Salida estándar (pantalla) // printf, write(1, ...)
- 2: stderr - Salida de errores estándar // fprintf(stderr, ...), write(2, ...)

📊 Tablas internas del sistema
El sistema operativo guarda la información de los archivos abiertos en "tablas". Cuando tu programa abre un archivo, el sistema necesita organizar esa información, y lo hace usando 3 estructuras (o "tablas").
- File Descriptor Table (tabla de descriptores de archivo): Lo usa solo el programa y sirve para que sepas a qué archivos estás accediendo.
- File Table Entry (entrada de archivo): Sirve para guardar información del uso del archivo.
- Global File Table (tabla global de archivos): Lo usa todo el sistema	y sirve para encontrar físicamente el archivo.
Lo que pasa internamente cuando usas por ejemplo open():
1. El sistema busca el archivo en la Global File Table.
2. Si lo encuentra, crea una File Table Entry para el archivo.
3. En tu programa, se agrega un nuevo índice en tu File Descriptor Table (por ejemplo, el número 3).
4. Cuando usas write(fd, ...), se sigue esa cadena para encontrar el archivo real y escribir en él.

🔹 Open() and Read() functions
Estas funciones forman parte de la API del sistema Unix/Linux. Sirven para abrir y leer archivos a bajo nivel (más directo que fopen() y fread() de stdio).
No forman parte del lenguaje C estándar, pero sí están disponibles en sistemas Unix/Linux.
Se llaman "llamadas al sistema" (system calls), y permiten que tu programa hable directamente con el sistema operativo.
🔧 Están definidas en cabeceras como:
#include <fcntl.h>    // para open()
#include <unistd.h>   // para read(), write(), close()

OPEN: 
int open(const char *pathname, int flags); // int fd = open("archivo.txt", O_RDONLY);
Devuelve un file descriptor (fd), un número que representa el archivo. Si falla, devuelve -1.
Cuando usas la función open(), no solo le pasas el nombre del archivo, también debes decirle cómo lo quieres abrir:
Todo esto se indica usando banderas, que son constantes con nombres en mayúsculas.
Flag | Significado | Ejemplo práctico
- O_RDONLY | Abrir solo para leer | Leer un archivo de texto
- O_WRONLY | Abrir solo para escribir | Escribir logs o resultados
- O_RDWR | Abrir para leer y escribir | Leer/modificar el contenido
- O_CREAT | Crear el archivo si no existe | Crear un archivo nuevo si aún no está
- O_EXCL | Solo crear el archivo si no existe ya | Útil junto con O_CREAT para evitar sobrescribir
Se combinan con el operador | (OR bit a bit), así: int fd = open("archivo.txt", O_WRONLY | O_CREAT, 0644);

READ: 
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
- fd: El file descriptor, o sea, el "número" que representa el archivo abierto con open()
- buf: puntero al espacio en memoria donde se guardarán los datos leídos
- count: cuántos bytes leer.

char buffer[100];
int bytes_leidos = read(fd, buffer, 100);
Esta función intenta leer hasta 100 bytes desde el archivo asociado al file descriptor fd, y los guarda en el array buffer.
Devuelve el número real de bytes que se leyeron. Esto es importante.
Si el archivo tiene 50 caracteres, read() leerá solo 50.
Si hay un error, devuelve -1.
Si se llega al final del archivo, devuelve 0.

BUFFER_SIZE es simplemente una constante que define cuántos bytes vas a leer de golpe en cada llamada a read(). -D BUFFER_SIZE=xx?
La opción -D es una flag del compilador gcc que significa: Define una macro desde la línea de comandos. // Es como si escribieras esto directamente en tu código: #define BUFFER_SIZE 42
Ejemplo de compilación: cc -Wall -Wextra -Werror -D BUFFER_SIZE=64 get_next_line.c main.c

___________

PASOS IMPORTANTES PARA LA CORRECCION:

- Comprobar el nombre de los archivos.
- Comprobar el archivo .h y que está la macro BUFFER_SIZE
- Pasar la norminette.
- Revisar que no haya fugas de memoria. (leaks check??)

PRUEBAS BÁSICAS:
Con BUFF_SIZE fijado a 8, compile un programa de prueba que lea desde la entrada estándar usando get_next_line. Realice al menos las siguientes pruebas:
- Leer y devolver una línea de 8 caracteres (incluyendo \n) desde la entrada estándar.
- Leer y devolver dos líneas de 8 caracteres (incluyendo \n) desde la entrada estándar.
- Leer y devolver cualquier número de líneas de 8 caracteres (incluyendo \n) desde la entrada estándar.

A continuación, añada un open(argv[1]) en main y realice:
- Leer y devolver una línea de 8 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver dos líneas de 8 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver cualquier número de líneas de 8 caracteres (incluyendo \n) desde un fichero.

PRUEBAS INTERMEDIAS:
Con BUFF_SIZE fijado a 16, realice las mismas pruebas que en la sección anterior:
- Leer y devolver una línea de 16 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver dos líneas de 16 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver cualquier número de líneas de 16 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver una línea de 16 caracteres (incluyendo \n) desde la entrada estándar.
- Leer y devolver dos líneas de 16 caracteres (incluyendo \n) desde la entrada estándar.
- Leer y devolver cualquier número de líneas de 16 caracteres (incluyendo \n) desde la entrada estándar.

PRUEBAS AVANZADAS:
Con BUFF_SIZE fijado a 4, compruebe:
- Leer y devolver una línea de 4 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver dos líneas de 4 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver cualquier número de líneas de 4 caracteres (incluyendo \n) desde un fichero.
- Leer y devolver una línea de 4 caracteres (incluyendo \n) desde la entrada estándar.
- Leer y devolver dos líneas de 4 caracteres (incluyendo \n) desde la entrada estándar.
- Leer y devolver cualquier número de líneas de 4 caracteres (incluyendo \n) desde la entrada estándar.
- Leer y devolver una línea de 4 caracteres sin \n desde un fichero.
- Leer y devolver una línea de 8 caracteres sin \n desde un fichero.
- Leer y devolver una línea de 16 caracteres sin \n desde un fichero. (Recordatorio: el fin de fichero debe comportarse como fin de línea para get_next_line.)
- Leer y devolver una línea vacía desde un fichero.

GESTION DE ERRORES:
Realice AL MENOS las siguientes pruebas para evaluar la gestión de errores:
- Pasar un descriptor de archivo arbitrario a get_next_line en el que no sea posible leer (por ejemplo, 42). La función debe devolver -1.
- Fijar BUFF_SIZE a 1, 32, 9999 y luego a 10000000. Este último valor no debería funcionar (aunque no se considera un error durante la defensa). ¿Sabe alguno de los dos por qué? Si defines algo como char buf[10000000]; dentro de la función, eso ya son 10 MB en la pila y supera el límite antes incluso de empezar. intenta reservar más de 10 MB en la pila de tu hilo principal, cuyo límite por defecto es 8 MB, y por eso explota con un “stack overflow”. ese array se aloja en la pila (stack) de tu función. Cada llamada a get_next_line reserva esos megas en la pila, y como el límite por defecto es 8 MB (en Linux suele ser eso), al pedir 10 MB la pila se “desborda” y el sistema no puede ampliar más el segmento de stack, provocando el SIGSEGV que ves con Valgrind. En cambio, cuando usas ""static char read_buffer[BUFFER_SIZE + 1];""
ese array deja de ser una variable local “sobre la marcha” y pasa a formar parte de tu sección de datos estáticos (la BSS, o .data si lo inicializas). Eso significa:
No crece ni encoge con las llamadas a la función. Sólo hay una única copia de read_buffer durante toda la ejecución.
Se reserva cuando el programa se carga en memoria, dentro de tu segmento de datos estáticos, cuyo tamaño no está limitado a 8 MB como el stack. Suele gestionarse contra toda la memoria virtual disponible, de modo que dos o tres decenas de megas aquí no dan problema (mientras tengas RAM/paginación suficiente).


  





