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
Un file descriptor (descriptor de archivo) es un número entero que el sistema operativo asigna para identificar un archivo abierto, un socket (comunicación por red), un pipe (comunicación entre procesos), o incluso la entrada/salida estándar (la pantalla o el teclado).
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

- Open() and Read() functions
