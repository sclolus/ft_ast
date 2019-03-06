/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_parser_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 20:07:39 by aalves            #+#    #+#             */
/*   Updated: 2019/03/04 20:15:05 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_parser	*ft_get_parser_str_any_of(char *charset)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = STR_ANY_OF;
	parser->parser.str_any_of.charset = charset;
	parser->parser.str_any_of.str = NULL;
	return (parser);
}

t_parser	*ft_get_parser_satisfy_str(int32_t f(char*))
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = SATISFY_STR;
	parser->parser.satisfy_str.f = f;
	return (parser);
}

t_parser	*ft_get_parser_str(char *str)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	if (!(parser->parser.string.str = ft_strdup(str)))
		exit(EXIT_FAILURE);
	parser->parser.string.len = ft_strlen(str);
	parser->id = STRING;
	return (parser);
}

t_parser	*ft_get_parser_str_any(void)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.str_any.len = 0;
	parser->parser.str_any.str = NULL;
	parser->id = STR_ANY;
	return (parser);
}
