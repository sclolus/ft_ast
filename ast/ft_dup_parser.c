/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 06:35:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/21 03:54:31 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"


static t_parser		*ft_assign_parsers(t_parser *parser, t_parser *new_parser);
static t_parser		*ft_assign_parser_data(t_parser *parser, t_parser *new_parser);

static uint32_t	ft_count_parsers(t_parser *parser)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	if (!parser)
		return (0);
	if (parser->id >= FUNC)
	{
		if (parser->id == FUNC)
			return (ft_count_parsers(parser->parser.func.parser) + 1);
		else if (parser->id == AND || parser->id == OR)
		{
			while (i < parser->parser.and.n)
			{
				count += ft_count_parsers(parser->parser.and.parsers[i]);
				i++;
			}
			return (count + 1);
		}
		else
			return (ft_count_parsers(parser->parser.not.parser) + 1);
	}
	else
		return (1);
}

static t_parser		*ft_assign_parser_data(t_parser *parser, t_parser *new_parser)
{
	uint32_t	i;
	t_parser	*tmp;

	i = 0;
	if (!parser)
	{
		printf("lol ntm\n");
		return (NULL);
	}
	if (parser->id == FUNC)
	{
		new_parser->parser.func.parser = new_parser + 1;
			return (ft_assign_parsers(parser->parser.func.parser, new_parser + 1));
	}
	else if (parser->id == AND || parser->id == OR)
	{
		if (!(new_parser->parser.and.parsers = (t_parser**)malloc(sizeof(t_parser*) * parser->parser.and.n)))
			exit(EXIT_FAILURE);
		tmp = new_parser;
		while (i < parser->parser.and.n)
		{
			new_parser->parser.and.parsers[i] = tmp + 1;
			tmp = ft_assign_parsers(parser->parser.and.parsers[i++], tmp + 1);
		}
		return (tmp);
	}
	else if (parser->id == NOT || parser->id == PLUS || parser->id == MULTIPLY)
	{
		new_parser->parser.not.parser = new_parser + 1;
		return (ft_assign_parsers(parser->parser.not.parser, new_parser + 1));
	}
	else
	{
		printf("wtf\n");
		ft_put_id(parser);
		return (ft_assign_parsers(parser->parser.not.parser, new_parser + 1));
	}

}

static t_parser		*ft_assign_parsers(t_parser *parser, t_parser *new_parser)
{
	uint32_t	i;

	i = 0;
	if (!parser)
	{
		printf("try again\n");
		return (new_parser + 1); // or change the implematation of +/*
	}
	// ft_put_id(parser);
	// ft_putchar('\n');
	ft_memcpy(new_parser, parser, sizeof(t_parser));
	if (parser->id >= FUNC)
		return (ft_assign_parser_data(parser, new_parser));
	else
	{
		if (parser->id == STRING)
		{
			if (!(new_parser->parser.string.str = ft_strdup(parser->parser.string.str)))
				exit (EXIT_FAILURE);
		}
		else if (parser->id == ONEOF)
		{
			if (!(new_parser->parser.oneof.charset = ft_strdup(parser->parser.oneof.charset)))
				exit(EXIT_FAILURE);
		}
		else if (parser->id == REGEXP)
		{
			if (!(new_parser->parser.regexp.regexp = ft_strdup(parser->parser.regexp.regexp)))
				exit(EXIT_FAILURE);
		}
		return (new_parser);
	}
}

t_parser		*ft_dup_parser(t_parser *parser)
{
	t_parser	*new_parser;
	uint32_t	size;

	size = ft_count_parsers(parser);
	ft_put_id(parser);
	printf(" allocated, size = %u\n", size);
	if (!(new_parser = (t_parser*)malloc(size * sizeof(t_parser))))
		exit (EXIT_FAILURE);
	ft_assign_parsers(parser, new_parser);
	return (new_parser);
}
