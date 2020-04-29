/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:52:48 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 12:52:48 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t		i;
	char		*cast_s;

	i = 0;
	cast_s = (char *)s;
	while (cast_s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int			i;
	char		*cast_src;

	cast_src = (char*)src;
	i = 0;
	while (cast_src[i])
	{
		dest[i] = cast_src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	dest = (char*)malloc(sizeof(char) * len + 1);
	if (dest == 0)
		return (0);
	while (i < len)
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_tolower(int word)
{
	if (word >= 'A' && word <= 'Z')
		return (word + 32);
	else
		return (word);
}
