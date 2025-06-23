/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarrodri <sarrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:21:25 by sarrodri          #+#    #+#             */
/*   Updated: 2025/06/23 14:55:46 by sarrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> /* open, O_RDONLY */
#include <stdio.h> /* printf, perror */
#include <stdlib.h> /* free, exit */
#include <unistd.h> /* close */

int	main(int argc, char **argv)
{
	int		fd; /* Descriptor de archivo que usaremos */
	char	*line; /* Puntero donde get_next_line devuelve cada línea */

	if (argc < 2) // No hay argumento
		fd = 0; // Usamos stdin
	else // Hay argumento
	{
		fd = open(argv[1], O_RDONLY); // Lo abrimos en modo lectura
		if (fd < 0)
		{
			perror("open"); // Si falla imprimimos el error
			return (1);
		}
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line); // Imprimimos linea 
		free(line); // Liberamos memoria
	}
	if (argc >= 2) // Si abrimos un fichero
		close(fd); // Lo cerramos
	return (0);
}
