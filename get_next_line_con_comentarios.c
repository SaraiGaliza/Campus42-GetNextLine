/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarrodri <sarrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:31:28 by sarrodri          #+#    #+#             */
/*   Updated: 2025/04/15 15:31:33 by sarrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Extract_line: Extrae la siguiente línea de store (incluye '\n' si existe).
 - Recorre la cadena hasta encontrar '\n' o el final.
 - Reserva memoria para la línea extraída.
 - Copia carácter a carácter hasta el final de la línea.
 - Devuelve un puntero dinámico que contiene la línea.
*/

static  char  *extract_line(char *store)
{
  size_t  i; // Índice para recorrer 'store' y contar cuántos caracteres hay hasta '\n' o el final de la cadena.
  size_t  j; // Índice para copiar los caracteres de 'store' a 'line' (la cadena que vamos a devolver con la funcion).
  char  *line; // Puntero que almacenará la línea extraída.

  i = 0; // Inicializamos a 0 para comenzar a recorrer la cadena 'store'.
  while (store[i] && store[i] != '\n') // Recorremos hasta encontrar '\n' o el final de la cadena.
    i++;
  if (store[i] == '\n') // Si encontramos '\n', aumentamos 'i' para incluirlo en el conteo.
    i++;
  line = malloc((i + 1) * sizeof *line); // Reservamos memoria para la nueva cadena que vamos a devolver + el termiandor '\0'.
  if (!line) // Manejo de errores; si la asignacion de memoria falla se retorna null.
    return (NULL);
j = 0; // Inicializamos a 0 para comenzar a copiar caracteres.
  while (j < i) // Copiamos 'i' caracteres de 'store' a 'line'.
   {
      line[j] = store[j];
      j++;
   }
  line[j] = '\0'; // Añadimos el carácter nulo al final para cerrar correctamente la cadena.
  return (line); // Devolvemos la variable 'line', que contiene la nueva cadena que acabamos de extraer.
}

/*
Update_store: Actualiza el contenido de 'store' tras extraer una línea completa.
 - Encuentra el final de la línea (primer '\n') en 'store'.
 - Si no hay salto de línea, libera 'store' y devuelve NULL (no queda nada).
 - Avanza un carácter más para saltar el '\n'.
 - Calcula cuántos caracteres restan después de ese punto.
 - Reserva memoria para la nueva cadena con el resto del contenido.
 - Copia carácter a carácter la parte restante.
 - Añade el terminador '\0', libera la antigua 'store' y devuelve la nueva.
*/

static char  *update_store(char *store)
{
    size_t  i; // Índice donde termina la línea extraída (posición del '\n' o fin de cadena).
    size_t  len; // Longitud del contenido que queda tras la línea extraída.
    char    *new_store; // Puntero a la nueva cadena que contendrá ese contenido sobrante.

    i = 0; // Inicializamos a 0 para comenzar a recorrer la cadena 'store'.
    while (store[i] && store[i] != '\n') // Recorremos hasta encontrar '\n' o el final de la cadena.
        i++;
    if (!store[i]) // Si llegamos al fin sin encontrar '\n' liberamos todo y devolvemos NULL.
        return (free(store), (char *)NULL);
    i++; // Avanzamos un carácter más para no copiar el salto de línea en el nuevo buffer.
    len = 0; // Inicializamos a 0 para comenzar a recorrer lo que sobra de la cadena 'store'.
    while (store[i + len]) // Empezando en la posición i (justo después de '\n'), contamos hasta llegar a '\0'
        len++;
    new_store = malloc(len + 1); // Reservamos memoria para la nueva cadena que vamos a devolver + el termiandor '\0'. 
    if (!new_store) // Manejo de errores; si la asignacion de memoria falla liberamos store y se retorna null.
        return (free(store), (char *)NULL);
    len = 0; // Inicializamos a 0 para comenzar a copiar caracteres.
    while (store[i + len]) // Iteramos en el bucle mientras no llegemos al final de la cadena.
        new_store[len++] = store[i + len];
    new_store[len] = '\0'; // Añadimos el carácter nulo al final para cerrar correctamente la cadena.
    free(store); // Liberamos 'store' porque ya no nos hace falta.
    return (new_store); // Devolvemos la variable 'new_store' con la nueva cadena.
}

/* 
Get_next_line:
 - Lee desde el descriptor 'fd' bloque a bloque, buscando la siguiente línea.
 - Devuelve una cadena dinámica con la línea (incluyendo '\n' si existe).
 - Devuelve NULL al llegar al EOF o en caso de error.
 */

char *get_next_line(int fd)
{
    static char *store; // Puntero estático (conserva su valor entre llamadas). Se almacena todo lo que se ha leído pero que aún no se ha devuelto.
    char        read_buffer[BUFFER_SIZE + 1]; // Buffer temporal donde 'read' deposita hasta BUFFER_SIZE bytes. El +1 es para añadir el '\0' al final y que sea un array.
    char        *returned_line; // Puntero a la línea final que se devuelve.
    ssize_t     bytes_read; // Almacena el nº de bytes leídos por read. Si =0 es EOF, si es <0 es error. Usamos 'ssize_t' para representar también -1.

    if (fd < 0 || BUFFER_SIZE <= 0) // Manejo de errores; comprobamos que el file descriptor y el tamaño de buffer sean válidos.
        return (free(store), store = NULL, (char *)NULL);
    bytes_read = 1; // Iniciamos bytes_read en 1 para entrar en el bucle.
    while (!(store && ft_strchr(store, '\n')) && bytes_read > 0) // Mientras no haya un '\n' en store y no hayamos llegado a EOF (bytes_read > 0) entramos al bucle.
    {
        bytes_read = read(fd, read_buffer, BUFFER_SIZE); // Leemos hasta hasta BUFFER_SIZE bytes y lo asignamos a bytes_read.
        if (bytes_read < 0) // Manejo de errores; si la lectura falla se retorna null.
            return (free(store), store = NULL, (char *)NULL);
        read_buffer[bytes_read] = '\0'; // Convertimos el buffer en un array añadiendo el terminador nulo al final.
        store = ft_strjoin(store, read_buffer); // Concatenamos el resutlado de buffer con lo que había en 'store' usando ft_strjoin.
        if (!store) // Manejo de errores; si hay algun error con store devolvemos null.
            return (free(store), store = NULL, (char *)NULL);
    }
    if (!store || !*store) // Si 'store' está vacío o es NULL, no queda nada por leer (EOF).
        return (free(store), store = NULL, (char *)NULL); // Liberamos memoria y devolvemos NULL para indicar EOF.
    returned_line = extract_line(store); // Extraemos la línea completa (hasta '\n' o final) en 'returned_line'.
    store = update_store(store); // Actualizamos 'store' con lo que quede tras la línea extraída.
    return (returned_line);  // Devolvemos la línea al usuario; él debe liberarla con free().
}
