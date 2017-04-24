/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:50:13 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 10:51:35 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_input_file(uint32_t fd, t_parser *parser)
{
	char		*tokens;
	char		*tmp;
	static char	buf[2048];
	int32_t		ret;

	ret = 0;
	if (!(tokens = ft_strnew(0)))
		exit (EXIT_FAILURE);
	while ((ret = read(fd, buf, 2047)) > 0)
	{
		buf[ret] = 0;
		if (!(tokens = ft_strjoin_f(tokens, buf, 0)))
			exit (EXIT_FAILURE);
	}
	tmp = tokens;
	ret = ft_eval_input(parser, &tokens);
	free(tmp);
	return (ret);
}

uint32_t		ft_eval_input(t_parser *parser, char **tokens)
{
	uint32_t	ret;
	uint32_t	index;

	index = 0;
	if ((ret = ft_eval_tokens(parser, tokens, &index)) && !index)
		return (1);
	return (0);
}

uint32_t		ft_eval_tokens(t_parser *parser, char **tokens, uint32_t index)
{
	static const t_eval_tokens	eval_tokens[18] = {
		{&ft_eval_tokens_undefined},
		{&ft_eval_tokens_undefined},
		{&ft_eval_tokens_onechar},
		{&ft_eval_tokens_str},
		{&ft_eval_tokens_undefined},
		{&ft_eval_tokens_char_range},
		{&ft_eval_tokens_any},
		{&ft_eval_tokens_str_any_of},
		{&ft_eval_tokens_satisfy},
		{&ft_eval_tokens_satisfy_str},
		{&ft_eval_tokens_str_any},
		{&ft_eval_tokens_oneof},
		{&ft_eval_tokens_func},
		{&ft_eval_tokens_and},
		{&ft_eval_tokens_or},
		{&ft_eval_tokens_not},
		{&ft_eval_tokens_plus},
		{&ft_eval_tokens_multiply}};
	char		*base;
	uint32_t	ret;

	base = *tokens;
	ret = eval_tokens[parser->id].f(parser, tokens);
	if (ret)
		parser->retained = RETAINED;
	else
	{
		parser->retained = UNRETAINED;
		*tokens = base;
	}
	return (ret);
}
