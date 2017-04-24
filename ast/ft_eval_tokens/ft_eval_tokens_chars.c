/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:51:51 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 10:55:50 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_tokens_oneof(t_parser *parser, char **tokens, uint32_t index)
{
	if (ft_strchr(parser->parser.oneof.charset, *tokens[index]))
	{
		parser->parser.oneof.c = *tokens[index];
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_tokens_onechar(t_parser *parser, char **tokens, uint32_t index)
{
	if (parser->parser.onechar.c == tokens[index][0])
		return (1);
	else
		return (0);
}

uint32_t		ft_eval_tokens_any(t_parser *parser, char **tokens, uint32_t index)
{
	if (**tokens != '\0')
	{
		parser->parser.any.matched = **tokens;
		(*tokens)++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_tokens_char_range(t_parser *parser, char **tokens, uint32_t index)
{
	if (*tokens[index] >= parser->parser.range.start
		&& *tokens[index] <= parser->parser.range.end)
	{
		parser->parser.range.matched = *tokens[index];
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_tokens_satisfy(t_parser *parser, char **tokens, uint32_t index)
{
	if (parser->parser.satisfy.f(*tokens[index]))
		return (1);
	else
		return (0);
}
