/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:12:09 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 13:23:51 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_tokens_undefined(t_parser *parser, t_tokens *tokens)
{
	if (parser)
		;
	ft_putstr_fd("error: undefined parser\n", 2);
	ft_putstr_fd("current tokens: ", 2);
	ft_putstr_fd(tokens->tokens[tokens->index], 2);
	exit (EXIT_FAILURE);
}

uint32_t		ft_eval_tokens_invocations(t_parser *parser, t_tokens *tokens)
{
	uint32_t	i;

	i = 0;
	while (i < 3)
	{
		if (!ft_eval_tokens(parser->parser.and.parsers[i], tokens))
			return (0);
		i++;
	}
	parser->parser.and.parsers[i] = ft_get_parser_expression();
	while (i < 8)
	{
		if (!(ft_eval_tokens(parser->parser.and.parsers[i], tokens)))
			return (0);
		i++;
	}
	return (1);
}

uint32_t		ft_eval_delayed(t_parser *parser, t_tokens *tokens)
{
	return (ft_eval_tokens(parser, tokens));
}

uint32_t		ft_eval_tokens_func(t_parser *parser, t_tokens *tokens)
{
	parser->parser.func.parser = parser->parser.func.gene();
	return (parser->parser.func.f(parser->parser.func.parser, tokens));
}
