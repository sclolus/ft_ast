/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 00:55:46 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/24 15:04:01 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_parser_onechar(t_parser *parser, char **string)
{
	if (parser->parser.onechar.c == **string)
	{
		(*string)++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_str(t_parser *parser, char **string)
{
	if (!(ft_memcmp(parser->parser.string.str
					, *string, parser->parser.string.len)))
	{
		*string += parser->parser.string.len;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_any(t_parser *parser, char **string)
{
	if (**string != '\0')
	{
		parser->parser.any.matched = **string;
		(*string)++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_str_any(t_parser *parser, char **string)
{
	uint32_t	ret;
	uint32_t	count;

	ret = 0;
	count = 0;
	if (parser->parser.str_any.end)
	{
		parser->parser.str_any.str = *string;
		while (**string && !(ret = (ft_eval_parser(parser->parser.str_any.end, string))))
		{
			(*string)++;
			count++;
		}
		if (ret)
			(*string)--;
		parser->parser.str_any.len = count;
		parser->parser.str_any.str = ft_strndup(parser->parser.str_any.str, count);
	}
	else
	{
		parser->parser.str_any.str = *string;
		parser->parser.str_any.len = ft_strlen(*string);
		(*string) += parser->parser.str_any.len;
	}
	return (1);
}

uint32_t		ft_eval_parser_char_range(t_parser *parser, char **string)
{
	if (**string >= parser->parser.range.start
		&& **string <= parser->parser.range.end)
	{
		parser->parser.range.matched = **string;
		(*string)++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_or(t_parser	*parser, char **string)
{
	uint32_t	ret;
	uint32_t	i;

	ret = 0;
	i = 0;
	while (!ret && i < parser->parser.or.n)
	{
			if (parser->parser.or.parsers[i]->id == STR_ANY)
				parser->parser.or.parsers[i]->parser.str_any.end
					= i + 1 < parser->parser.or.n ? parser->parser.or.parsers[i + i]
					: NULL;
			ret |= ft_eval_parser(parser->parser.or.parsers[i], string);
		i++;
	}
	return (ret);
}


uint32_t		ft_eval_parser_and(t_parser	*parser, char **string)
{
	uint32_t	ret;
	uint32_t	i;

	ret = 1;
	i = 0;
	while (ret && i < parser->parser.and.n)
	{
		if (parser->parser.and.parsers[i]->id == STR_ANY)
			parser->parser.and.parsers[i]->parser.str_any.end
				= i + 1 < parser->parser.and.n ? parser->parser.and.parsers[i + i]
				: NULL;
		ret &= ft_eval_parser(parser->parser.and.parsers[i], string);
		i++;
	}
	return (ret);
}

uint32_t		ft_eval_parser_not(t_parser	*parser, char **string)
{
	return (!ft_eval_parser(parser, string));
}

uint32_t		ft_eval_parser_undefined(t_parser *parser, char **string)
{
	if (parser)
		;
	ft_putstr_fd("error: undefined parser\n", 2);
	ft_putstr_fd("current string: ", 2);
	ft_putstr_fd(*string, 2);
	exit (EXIT_FAILURE);
}

uint32_t		ft_eval_parser_satisfy(t_parser *parser, char **string)
{
	if (parser->parser.satisfy.f(**string))
	{
		(*string)++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_satisfy_str(t_parser *parser, char **string)
{
	uint32_t	ret;

	if ((ret = parser->parser.satisfy_str.f(*string)))
	{
		(*string) += ret;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_plus(t_parser *parser, char **string)
{
	t_list		*head;
	t_list		*link;
	uint32_t	n;
	uint32_t	i;
	n = 0;
	i = 0;
	head = NULL;
	while (1)
	{
		if (!(link = ft_lstnew(NULL, sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		link->content = ft_dup_parser(parser->parser.multiply.parser);
		// ft_put_parser_tree(link->content);
		if (!ft_eval_parser(link->content, string))
		{
			free(link); //free le parser
			break;
		}
		ft_lstadd(&head, link);
		++n;
	}
	if (n)
	{
		parser->parser.plus.n = n;
		if (!(parser->parser.multiply.parsers = (t_parser**)malloc(n * sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		i = n - 1;
		while (head)
		{
			parser->parser.multiply.parsers[i] = head->content;
			link = head;
			head = head->next;
			free(link);
			--i;
		}
	}
	return (n != 0);
}

uint32_t		ft_eval_parser_multiply(t_parser *parser, char **string)
{
	t_list		*head;
	t_list		*link;
	uint32_t	n;
	uint32_t	i;

	n = 0;
	i = 0;
	head = NULL;
	while (1)
	{
		if (!(link = ft_lstnew(NULL, sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		link->content = ft_dup_parser(parser->parser.multiply.parser);
		if (!ft_eval_parser(link->content, string))
		{
			free(link); //free le parser
			break;
		}
		ft_lstadd(&head, link);
		++n;
	}
	if (n)
	{
		parser->parser.multiply.n = n;
		if (!(parser->parser.multiply.parsers = (t_parser**)malloc(n * sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		i = n - 1;
		while (head)
		{
			parser->parser.multiply.parsers[i] = head->content;
			link = head;
			head = head->next;
			free(link);
			--i;
		}
	}
	return (1);
}

uint32_t		ft_eval_parser_oneof(t_parser *parser, char **string)
{
	if (ft_strchr(parser->parser.oneof.charset, **string))
	{
		parser->parser.oneof.c = **string;
		(*string)++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_invocations(t_parser *parser, char **string)
{
	uint32_t	i;

	i = 0;
	while (i < 3)
	{
		if (!ft_eval_parser(parser->parser.and.parsers[i], string))
			return (0);
		i++;
	}
	parser->parser.and.parsers[i] = ft_get_parser_expression();
	while (i < 8)
	{
		if (!(ft_eval_parser(parser->parser.and.parsers[i], string)))
			return (0);
		i++;
	}
	return (1);
}

uint32_t		ft_eval_delayed(t_parser *parser, char **string)
{
	return (ft_eval_parser(parser, string));
}

uint32_t		ft_eval_input(t_parser *parser, char **string)
{
	if (ft_eval_parser(parser, string) && !**string)
		return (1);
	return (0);
}

uint32_t		ft_eval_parser_func(t_parser *parser, char **string)
{
	parser->parser.func.parser = parser->parser.func.gene();
	return (parser->parser.func.f(parser->parser.func.parser, string));
}

uint32_t		ft_eval_parser(t_parser *parser, char **string)
{
	static const t_eval_parser	eval_parsers[17] = {
		{&ft_eval_parser_undefined},
		{&ft_eval_parser_undefined},
		{&ft_eval_parser_onechar},
		{&ft_eval_parser_str},
		{&ft_eval_parser_undefined},
		{&ft_eval_parser_char_range},
		{&ft_eval_parser_any},
		{&ft_eval_parser_satisfy},
		{&ft_eval_parser_satisfy_str},
		{&ft_eval_parser_str_any},
		{&ft_eval_parser_oneof},
		{&ft_eval_parser_func},
		{&ft_eval_parser_and},
		{&ft_eval_parser_or},
		{&ft_eval_parser_not},
		{&ft_eval_parser_plus},
		{&ft_eval_parser_multiply}};
	char		*base;
	uint32_t	ret;

	base = *string;
	ret = eval_parsers[parser->id].f(parser, string);
	if (ret)
		parser->retained = RETAINED;
	parser->retained = UNRETAINED;
	return (ret);
}
