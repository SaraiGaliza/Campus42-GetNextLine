/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarrodri <sarrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:27:00 by sarrodri          #+#    #+#             */
/*   Updated: 2025/06/23 12:52:31 by sarrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Si no se define externamente desde la línea de comandos
//(con la flag -D BUFFER_SIZE=XX) define BUFFER_SIZE como 42
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Librerías
# include <stdlib.h> // malloc(), free()
# include <unistd.h> // read()
// # include <fcntl.h>  // open(), flags como O_RDONLY (opcional para el main)
// # include <stdio.h>  // para printf o pruebas (opcional para el main)

// Declaración de laa funciónes principales
char	*get_next_line(int fd);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);

#endif
