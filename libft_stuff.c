/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:31:14 by ztoptas           #+#    #+#             */
/*   Updated: 2025/11/19 08:31:14 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	getting_sign(const char **str)
{
	int	sign;

	sign = 1;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	double	res;
	double	power;
	int		sign;
	double	decimal_part;

	res = 0.0;
	power = 1.0;
	decimal_part = 0.0;
	sign = getting_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		power /= 10.0;
		decimal_part += (*str - '0') * power;
		str++;
	}
	return (sign * (res + decimal_part));
}

void	ft_putstr(char *s)
{
	int		i;
	ssize_t	ret;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ret = write(1, &s[i], 1);
		if (ret == -1)
			return ;
		i++;
	}
}
