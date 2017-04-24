/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:54:29 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 10:55:17 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_tokens_str(t_parser *parser, char **tokens, uint32_t index)
{
	if (!(ft_memcmp(parser->parser.string.str
					, tokens[index], parser->parser.string.len)))
		return (1);
	else
		return (0);
}

uint32_t		ft_eval_tokens_str_any(t_parser *parser, char **tokens, uint32_t index)
{
	uint32_t	ret;
	uint32_t	count;

	ret = 0;
	count = 0;
	if (parser->parser.str_any.end)
	{
		parser->parser.str_any.str = *tokens;
		while (**tokens && !(ret = (ft_eval_tokens(parser->parser.str_any.end, tokens))))
		{
			(*tokens)++;
			count++;
		}
		if (ret)
			(*tokens)--;
		parser->parser.str_any.len = count;
		parser->parser.str_any.str = ft_strndup(parser->parser.str_any.str, count);
	}
	else
	{
		parser->parser.str_any.str = *tokens;
		parser->parser.str_any.len = ft_strlen(*tokens);
		(*tokens) += parser->parser.str_any.len;
	}
	return (1);
}


uint32_t		ft_eval_tokens_satisfy_str(t_parser *parser, char **tokens, uint32_t index)
{
	uint32_t	ret;

	if ((ret = parser->parser.satisfy_str.f(tokens[index])))
		return (1);
	else
		return (0);
}

uint32_t		ft_eval_tokens_str_any_of(t_parser *parser, char **tokens, uint32_t index)
{
	uint32_t			bool;
	static char			buf[4096];
	uint32_t			offset;
	t_tokens			*str;

	bool = 0;
	offset = 0;
	str = ft_t_string_new(32);
	while (**tokens)
	{
		if (ft_strchr(parser->parser.str_any_of.charset, **tokens))
		{
			bool |= 1;
			if (offset < 4096)
			{
				buf[offset++] = **tokens;
				(*tokens)++;
			}
			else
			{
				ft_t_string_concat_len(str, buf, 4096);
				offset = 0;
			}
		}
		else
			break ;
	}
	if (offset)
		ft_t_string_concat_len(str, buf, offset);
	parser->parser.str_any_of.str = str->string;
	free(str);
	return (bool);
}
