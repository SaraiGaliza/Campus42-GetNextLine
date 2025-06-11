/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarrodri <sarrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:27:00 by sarrodri          #+#    #+#             */
/*   Updated: 2025/04/15 15:57:29 by sarrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Si no se define externamente, define BUFFER_SIZE como 42
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Librerías necesarias
# include <unistd.h>  // read()
# include <stdlib.h>  // malloc(), free()
// # include <fcntl.h>  // open(), flags como O_RDONLY (opcional para el main)
// # include <stdio.h>  // para printf o pruebas (opcional para el main)

// Declaración de la función principal
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char  *ft_strjoin(char *s1, const char *s2);
size_t	ft_strlen(const char *s)

#endif
