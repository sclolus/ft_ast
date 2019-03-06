/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:07:23 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:08:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static inline t_mpc_str	*get_p_str(t_parser *parser)
{
#if ASSERT
	assert(parser->id == STRING);
#endif
	return (&parser->parser.string);
}

bool ft_eval_parser_str(t_parser *parser, char **string)
{
	t_mpc_str   *inner;

	inner = get_p_str(parser);
	if (ft_strncmp(inner->str, *string, inner->len))
	{
		*string += inner->len;
		return (true);
	}
	return (false);
}
