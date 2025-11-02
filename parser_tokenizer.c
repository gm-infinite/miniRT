/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:16:50 by emgenc            #+#    #+#             */
/*   Updated: 2025/11/02 13:27:27 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**tokenize_line(char *line)
{
	char	*trimmed;
	char	**tokens;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (NULL);
	tokens = ft_split(trimmed, ' ');
	free(trimmed);
	return (tokens);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

inline bool	check_token_count(char **tokens, int expected)
{
	return (count_tokens(tokens) == expected);
}
