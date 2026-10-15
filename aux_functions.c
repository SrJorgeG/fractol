/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:09:38 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = -1;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (++i < n && (ss1[i] || ss2[i]))
		if (ss1[i] != ss2[i])
			return ((int)(ss1[i] - ss2[i]));
	return (0);
}

size_t	ft_strlen(const char *s)
{
	const char	*z;

	z = s;
	while (*z)
		z++;
	return (z - s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;
	size_t			i;

	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		str[i++] = 0;
	return (str);
}

double	re_scale(int num, double zoom, double inc, double scale)
{
	return (((num * scale) - 2.0) / zoom + inc);
}
