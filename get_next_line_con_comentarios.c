/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarrodri <sarrodri@student.42barcelon>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:18:56 by sarrodri          #+#    #+#             */
/*   Updated: 2025/06/23 13:27:07 by sarrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * free_buf:
 *   Libera la memoria apuntada por ptr y devuelve NULL.
 *   Útil para reiniciar el puntero estático 'store' en caso de error.
 */
static char	*free_buf(char *ptr)
{
    free(ptr);
    return (NULL);
}

/*
Extract_line: Extrae la siguiente línea de store (incluye '\n' si existe).
 - Recorre la cadena hasta encontrar '\n' o el final.
 - Reserva memoria para la línea extraída.
 - Copia carácter a carácter hasta el final de la línea.
 - Devuelve un puntero dinámico que contiene la línea.
*/
static char	*extract_line(char *store)
{
    size_t	i; // Índice para recorrer 'store' y contar cuántos caracteres hay hasta '\n' o el final de la cadena.
    size_t	j; // Índice para copiar los caracteres de 'store' a 'line' (la cadena que vamos a devolver con la funcion).
    char	*line; // Puntero que almacenará la línea extraída.

    i = 0; // Inicializamos a 0 para comenzar a recorrer la cadena 'store'.
    while (store[i] && store[i] != '\n') // Recorremos hasta encontrar '\n' o el final de la cadena.
        i++;
    if (store[i] == '\n') // Si encontramos '\n', aumentamos 'i' para incluirlo en el conteo.
        i++;
    line = malloc(i + 1); // Reservamos memoria para la nueva cadena que vamos a devolver + el termiandor '\0'.
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
static char	*update_store(char *store)
{
    size_t	i;         /* posición de '\n' */
    size_t	len;       /* longitud del remanente */
    char	*new_store;/* buffer para el remanente */

    i = 0;
    /* Encontrar '\n' */
    while (store[i] && store[i] != '\n')
        i++;
    if (!store[i])
        return (free_buf(store));  /* no hay '\n', liberar todo */
    i++;  /* avanzar después del '\n' */
    /* Calcular cuántos caracteres quedan */
    len = ft_strlen(store + i);
    /* Reservar nuevo buffer */
    new_store = malloc(len + 1);
    if (!new_store)
        return (free_buf(store));
    /* Copiar remanente */
    ft_strlcpy(new_store, store + i, len + 1);
    free(store);
    return (new_store);
}

/* 
Get_next_line:
 - Lee desde el descriptor 'fd' bloque a bloque, buscando la siguiente línea.
 - Devuelve una cadena dinámica con la línea (incluyendo '\n' si existe).
 - Devuelve NULL al llegar al EOF o en caso de error.
 */
char	*get_next_line(int fd)
{
    static char	*store;                      /* datos pendientes */
    static char	read_buffer[BUFFER_SIZE + 1];/* buffer para read() */
    char		*returned_line;
    ssize_t		bytes_read;

    /* Validar args */
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (store = free_buf(store));
    bytes_read = 1;
    /* Leer hasta hallar '\n' o llegar a EOF */
    while (!(store && ft_strchr(store, '\n')) && bytes_read > 0)
    {
        bytes_read = read(fd, read_buffer, BUFFER_SIZE);
        if (bytes_read < 0)
            return (store = free_buf(store));
        read_buffer[bytes_read] = '\0';
        store = ft_strjoin(store, read_buffer);
        if (!store)
            return (store = free_buf(store));
    }
    /* Si no hay datos, EOF limpio */
    if (!store || !*store)
        return (store = free_buf(store));
    /* Extraer línea y actualizar store */
    returned_line = extract_line(store);
    store = update_store(store);
    return (returned_line);
}
