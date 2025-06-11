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
 *   Extrae la siguiente línea de rem (incluye '\\n' si existe).
 */

static  char  *extract_line(char *rem)
{
  size_t  i;
  char  *line;

  i = 0;
  while (rem[i] && rem[i] != '\n')
    i++;
  if (rem[i] == '\n')
    i++;
  line = malloc((i + 1) * sizeof *line);
  if (!line)
    return (NULL);
i = 0;
  while (rem[i] && rem[i] != '\0')
    {
      line[i] = rem[i];
      i++;
    }
  line[i] = '\0';
  return (line);
}

/*
 *   Tras extraer la línea, devuelve la parte sobrante de rem.
 *   Libera rem original.
 */

static char  *update_remainder(char *rem)
{
    size_t  i;      /* índice de inicio de lo que queda */
    size_t  len;    /* tamaño de la nueva cadena */
    char    *new;   /* puntero a la nueva remainder */

    i = 0;
    while (rem[i] && rem[i] != '\n')
        i++;
    if (!rem[i])     /* si no hay '\n', no queda nada */
        return (free(rem), (char *)NULL);
    i++;             /* saltar '\n' */
    len = 0;
    while (rem[i + len])  /* calcular longitud restante */
        len++;
    new = malloc(len + 1);
    if (!new)
        return (free(rem), (char *)NULL);
    len = 0;
    while (rem[i + len])  /* copiar carácter a carácter */
        new[len++] = rem[i + len];
    new[len] = '\0';
    free(rem);
    return (new);
}

/* get_next_line: lee de fd hasta '\n' o EOF y devuelve la línea */
char *get_next_line(int fd)
{
    static char *rem;
    char        buffer[BUFFER_SIZE + 1];
    char        *line;
    ssize_t     br;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    br = 1;
    while (!(rem && ft_strchr(rem, '\n')) && br > 0)
    {
        br = read(fd, buffer, BUFFER_SIZE);
        if (br < 0)
            return (NULL);
        buffer[br] = '\0';
        rem = ft_strjoin(rem, buffer);
        if (!rem)
            return (NULL);
    }
    if (!rem || !*rem)
        return (free(rem), rem = NULL, (char *)NULL);
    line = extract_line(rem);
    rem = update_remainder(rem);
    return (line);
}
