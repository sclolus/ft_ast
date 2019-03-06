/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_and.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 20:31:10 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:13:40 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_mpc_and_n	*get_p_and(t_parser *parser)
{
#if ASSERT
	assert(parser->id == AND);
#endif
	return (&parser->parser.and);
}

bool				ft_eval_parser_and(t_parser *parser, char **string)
{
	uint32_t		i;
	t_mpc_and_n		*inner;
	char			*save;

	i = 0;
	inner = get_p_and(parser);
	save = *string;
	while (i < inner->n)
	{
		if (!ft_eval_parser(inner->parsers[i], string))
		{
			*string = save;
			return false;
		}
		i++;
	}
	return true;
}
