/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:20:00 by codex              #+#    #+#             */
/*   Updated: 2025/09/05 21:20:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"

double ft_atof(const char *str)
{
    char *end;
    if (!str)
        return 0.0;
    return strtod(str, &end);
}

void    free_split(char **arr)
{
    size_t i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

