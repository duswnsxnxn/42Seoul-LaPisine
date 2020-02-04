/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:32:40 by jko               #+#    #+#             */
/*   Updated: 2020/02/04 22:59:39 by jko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			is_charset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

unsigned int	count_words(char *str, char *charset)
{
	int i;
	int count;

	count = 0;
	i = 0;
	if (str[i] && !is_charset(str[i++], charset))
		count++;
	while (str[i])
	{
		if (is_charset(str[i], charset) && str[i + 1]
				&& !is_charset(str[i + 1], charset))
			count++;
		i++;
	}
	return (count);
}

char			*str_n_cpy(char *str, unsigned int n)
{
	unsigned int	i;
	char			*result;

	result = (char *)malloc(sizeof(char) * (n + 1));
	result[n] = 0;
	i = 0;
	while (i < n)
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

void			fill_strs(char *str, char *charset, char **result)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	if (str[i] && !is_charset(str[i], charset))
		j = i++;
	while (str[i])
	{
		if (is_charset(str[i], charset))
		{
			if (j < i)
				result[count++] = str_n_cpy(str + j, i - j);
			j = i + 1;
		}
		i++;
	}
	if (j < i)
		result[count] = str_n_cpy(str + j, i - j);
}

char			**ft_split(char *str, char *charset)
{
	unsigned int	count;
	char			**result;

	if (!charset[0])
	{
		result = (char **)malloc(sizeof(char *) * 2);
		result[0] = str;
		result[1] = 0;
		return (result);
	}
	count = count_words(str, charset);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	result[count] = 0;
	fill_strs(str, charset, result);
	return (result);
}