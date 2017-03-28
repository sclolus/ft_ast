/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_string_concat_len.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 01:51:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/28 04:23:24 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_t_string_concat_len(t_string *string
									, char *str, uint32_t str_len)
{
	uint64_t	total_len;

	if (!str || !string)
		return (NULL);
	total_len = string->len + str_len;
	if (total_len >= string->capacity)
	{
		ft_t_string_expand(string);
		return (ft_t_string_concat(string, str));
	}
	else
	{
		ft_strncat(string->string, str, str_len);
		string->len = total_len;
	}
	return (string);
}

