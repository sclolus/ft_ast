/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_onechar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:23:36 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:10:58 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static inline t_mpc_onechar	*get_p_onechar(t_parser *parser)
{
#if ASSERT
	assert(parser->id == ONECHAR);
#endif
	return (&parser->parser.onechar);
}

bool	ft_eval_onechar(t_parser *parser, char **string)
{
	t_mpc_onechar	*inner;

	if (!**string)
		return (false);
	inner = get_p_onechar(parser);
	if (inner->c == **string)
	{
		(*string)++;
		return (true);
	}
	return (false);
}
