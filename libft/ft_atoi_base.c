/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:11:42 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/24 10:17:58 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_str_lowercase(const char *s)
{
	int		i;
	char	*tp;

	if (!(tp = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (s[++i])
		tp[i] = ft_tolower(s[i]);
	return (tp);
}

static int	ft_check(char *s, int *i, int base, int *neg)
{
	while (ft_isspace(s[*i]))
		(*i)++;
	if ((s[*i] == '-' || s[*i] == '+') && s[*i + 1] == '0')
		return (0);
	if ((s[*i] == '-' || s[*i] == '+') && base == 10)
	{
		*neg = (s[*i] == '-') ? 1 : 0;
		i++;
	}
	else if (s[*i] == '0')
	{
		if ((s[*i + 1] == 'x' && base != 16) || s[*i + 1] != 'x')
			return (0);
		*i += 2;
	}
	while (s[*i])
	{
		if ((s[*i] >= '0' && s[*i] < ('0' + base))
			|| (s[*i] >= 'a' && s[*i] < ('a' + base - 10)))
			(*i)++;
		else
			return (0);
	}
	(*i)--;
	return (1);
}

int			ft_atoi_base(const char *s, int base)
{
	int				p;
	int				neg;
	int				i;
	unsigned int	ret;
	char			*str;

	i = 0;
	neg = 0;
	ret = 0;
	p = 0;
	str = ft_str_lowercase(s);
	if ((base < 2 || base > 16) || ft_check(str, &i, base, &neg) == 0)
		return (0);
	while (i > 1 && (str[i] != '-' && str[i] != '+' && str[i] != 'x'))
	{
		if (str[i] >= '0' && str[i] < ('0' + base))
			ret += (str[i--] - '0') * ft_power(base, p++);
		else if (str[i] >= 'a' && (str[i] < ('a' + (base - 10))))
			ret += (str[i--] + 10 - 'a') * ft_power(base, p++);
	}
	free(str);
	if (neg == 1)
		return (-ret);
	return (ret);
}
