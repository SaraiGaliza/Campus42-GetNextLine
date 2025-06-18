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
 * extract_line:
 *   Extrae la siguiente línea de store (incluye '\\n' si existe).
 */

static  char  *extract_line(char *store)
{
  size_t  i;
  char  *line;

  i = 0;
  while (store[i] && store[i] != '\n')
    i++;
  if (store[i] == '\n')
    i++;
  line = malloc((i + 1) * sizeof *line);
  if (!line)
    return (NULL);
i = 0;
  while (store[i] && store[i] != '\0')
    {
      line[i] = store[i];
      i++;
    }
  line[i] = '\0';
  return (line);
}

/*
 *   Tras extraer la línea, devuelve la parte sobrante de store.
 *   Libera store original.
 */

static char  *update_store(char *store)
{
    size_t  i;      /* índice de inicio de lo que queda */
    size_t  len;    /* tamaño de la nueva cadena */
    char    *new;   /* puntero a la nueva store */

    i = 0;
    while (store[i] && store[i] != '\n')
        i++;
    if (!store[i])     /* si no hay '\n', no queda nada */
        return (free(store), (char *)NULL);
    i++;             /* saltar '\n' */
    len = 0;
    while (store[i + len])  /* calcular longitud restante */
        len++;
    new = malloc(len + 1);
    if (!new)
        return (free(store), (char *)NULL);
    len = 0;
    while (store[i + len])  /* copiar carácter a carácter */
        new[len++] = store[i + len];
    new[len] = '\0';
    free(store);
    return (new);
}

/* 
Get_next_line:
 - Lee desde el descriptor 'fd' bloque a bloque, buscando la siguiente línea.
 - Devuelve una cadena dinámica con la línea (incluyendo '\n' si existe)
 - Devuelve NULL al llegar al EOF o en caso de error.
 */

char *get_next_line(int fd)
{
    static char *store; // Puntero estático (conserva su valor entre llamadas). Se almacena todo lo que se ha leído pero que aún no se ha devuelto.
    char        read_buffer[BUFFER_SIZE + 1]; // Buffer temporal donde 'read' deposita hasta BUFFER_SIZE bytes. El +1 es para añadir el '\0' al final y que sea un array.
    char        *returned_line; // Puntero a la línea final que se devuelve.
    ssize_t     bytes_read; // Almacena el nº de bytes leídos por read. Si =0 es EOF, si es <0 es error. Usamos 'ssize_t' para representar también -1.

    if (fd < 0 || BUFFER_SIZE <= 0) // Manejo de errores; comprobamos que el file descriptor y el tamaño de buffer sean válidos.
        return (NULL);
    bytes_read = 1; // Iniciamos bytes_read en 1 para entrar en el bucle.
    while (!(store && ft_strchr(store, '\n')) && bytes_read > 0) // Mientras no haya un '\n' en store y no hayamos llegado a EOF (bytes_read > 0) entramos al bucle.
    {
        bytes_read = read(fd, read_buffer, BUFFER_SIZE); // Leemos hasta hasta BUFFER_SIZE bytes y lo asignamos a bytes_read.
        if (bytes_read < 0) // Manejo de errores; si la lectura falla se retorna null.
            return (NULL);
        read_buffer[bytes_read] = '\0'; // Convertimos el buffer en un array añadiendo el terminador nulo al final.
        store = ft_strjoin(store, read_buffer); // Concatenamos el resutlado de buffer con lo que había en store usando ft_strjoin.
        if (!store) // Manejo de errores; si hay algun error con store devolvemos null.
            return (NULL);
    }
    if (!store || !*store) // Si 'store' está vacío o es NULL, no queda nada por leer (EOF).
        return (free(store), store = NULL, (char *)NULL); // Liberamos memoria y devolvemos NULL para indicar EOF
    returned_line = extract_line(store); // Extraemos la línea completa (hasta '\n' o final) en 'returned_line'.
    store = update_store(store); // Actualizamos 'store' con lo que quede tras la línea extraída.
    return (returned_line);  // Devolvemos la línea al usuario; él debe liberarla con free().
}
