/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:02 by hallison          #+#    #+#             */
/*   Updated: 2025/10/02 19:59:55 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static size_t	get_token_count(char const *s)
{
	size_t	i;
	size_t	token_count;

	i = 0;
	token_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
			token_count++;
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\0')
			i++;
	}
	return (token_count);
}

char	*alloc_cp_token(const char *s, int len)
{
	int		i;
	char	*token;

	token = malloc((len + 1) * sizeof(char));
	if (!token)
		exit (1);
	i = 0;
	while (i < len)
	{
		token[i] = s[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

void	create_tokens(char **tokens, const char *s)
{
	int	i;
	int	t_i;
	int	word_start;
	int	word_len;

	i = 0;
	t_i = 0;
	while (s[i] != '\0')
	{
		word_len = 0;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (s[i] == '\0')
			break ;
		word_start = i;
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\0')
			i++;
		word_len = i - word_start;
		tokens[t_i] = alloc_cp_token(s + word_start, word_len);
		t_i ++;
	}
}

char	**get_element_tokens(char const *s)
{
	char	**tokens;
	size_t	token_count;

	if (!s || s[0] == '\0' || s[0] == '\n' || s[0] == '*')
		return (NULL);
	token_count = get_token_count(s);
	if (token_count == 0)
		return (NULL);
	tokens = ft_calloc(token_count + 1, sizeof(char **));
	if (tokens == NULL)
		exit (1);
	create_tokens(tokens, s);
	return (tokens);
}
