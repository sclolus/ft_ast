/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_or.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 20:24:15 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:13:44 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* uint32_t		ft_eval_parser_or(t_parser *parser, char **string) */
/* { */
/* 	uint32_t	ret; */
/* 	uint32_t	i; */

/* 	ret = 0; */
/* 	i = 0; */
/* 	while (!ret && i < parser->parser.or.n) */
/* 	{ */
/* 		if (parser->parser.or.parsers[i]->id == STR_ANY) */
/* 			parser->parser.or.parsers[i]->parser.str_any.end = i + 1 */
/* 				< parser->parser.or.n ? parser->parser.or.parsers[i + i] */
/* 				: NULL; */
/* 		ret |= ft_eval_parser(parser->parser.or.parsers[i], string); */
/* 		i++; */
/* 	} */
/* 	if (ret) */
/* 		parser->parser.or.matched = i - 1; */
/* 	return (ret); */
/* } */

static inline t_mpc_or_n	*get_p_or(t_parser *parser)
{
#if ASSERT
	assert(parser->id == OR);
#endif
	return (&parser->parser.or);
}

bool				ft_eval_parser_or(t_parser *parser, char **string)
{
	uint32_t	i;
	t_mpc_or_n	*inner;
	char		*save;

	i = 0;
	inner = get_p_or(parser);
	save = *string;
	while (i < inner->n)
	{
		*string = save;
		if (ft_eval_parser(inner->parsers[i], string))
			return (true);
		i++;
	}
	*string = save; // not necessary if invariant holds: good luck.
	return (false);
}
