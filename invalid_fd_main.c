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
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line;

 // Llamada con fd inválido
    line = get_next_line(42);
    if (!line) 
        printf("Test OK: El fd no es valido y la funcion devuelve NULL\n");
    else
    {
        printf("Test KO: Devolvió \"%s\"\n", line);
        free(line);
    }
    return (0);
}
