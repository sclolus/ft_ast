/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_oneof.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:29:56 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 20:32:17 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_mpc_oneof	*get_p_oneof(t_parser *parser)
{
#if ASSERT
	assert(parser->id == ONEOF);
#endif
	return (&parser->parser.oneof);
}

bool	ft_eval_parser_oneof(t_parser *parser, char **string)
{
	t_mpc_oneof	*inner;

	inner = get_p_oneof(parser);
	if (ft_strchr(inner->charset, **string))
	{
		//inner->c = **string;
		(*string)++;
		return (true);
	}
	return (false);
}
