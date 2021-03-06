/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:52:06 by bede-fre          #+#    #+#             */
/*   Updated: 2017/11/23 16:08:33 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	size_t	i2;

	i = 0;
	i2 = -1;
	while (s1[i] != '\0')
		i++;
	while (s2[++i2] != '\0' && (i2 < n))
		s1[i + i2] = s2[i2];
	s1[i + i2] = '\0';
	return (s1);
}
