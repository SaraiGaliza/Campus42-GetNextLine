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
 * extract_line:
 *   Extrae la siguiente línea de 'store', incluyendo '\n' si está presente.
 *   - Cuenta caracteres hasta '\n' o hasta el fin de la cadena.
 *   - Reserva memoria para la línea y copia los caracteres.
 *   - Devuelve un puntero dinámico a la línea, o NULL si falla malloc.
 */
static char	*extract_line(char *store)
{
    size_t	i;       /* índice para medir longitud de línea */
    size_t	j;       /* índice para copiar caracteres */
    char	*line;   /* buffer donde se guarda la línea */

    i = 0;
    /* Buscar el final de la línea */
    while (store[i] && store[i] != '\n')
        i++;
    if (store[i] == '\n')
        i++;  /* incluir '\n' en la longitud */
    /* Reservar espacio para la línea + terminador nulo */
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    /* Copiar caracteres */
    j = 0;
    while (j < i)
    {
        line[j] = store[j];
        j++;
    }
    line[j] = '\0';  /* cerrar cadena */
    return (line);
}

/*
 * update_store:
 *   Después de extraer una línea, actualiza 'store' para descartar
 *   la parte ya leída.
 *   - Avanza tras el '\n' para definir el inicio del remanente.
 *   - Copia lo que queda a un nuevo buffer, libera el viejo.
 *   - Devuelve el nuevo apuntador o NULL si no queda remanente.
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
 * get_next_line:
 *   Lee del descriptor 'fd' hasta encontrar una línea completa o EOF.
 *   - Utiliza un buffer estático 'read_buffer' para llamadas a read().
 *   - Acumula los datos en 'store' entre llamadas.
 *   - Devuelve una línea dinámica o NULL en EOF/error.
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
