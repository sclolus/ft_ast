/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 06:13:51 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/15 10:03:59 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ft_set_name_parser(t_parser *parser, char *str)
{
	if (!(parser->name = ft_strdup(str)))
		exit (EXIT_FAILURE);
}

void	ft_put_id(t_parser *parser)
{
	switch (parser->id)
	{
	case ONECHAR:
		ft_putstr("ONECHAR");
		break;
	case STRING:
		ft_putstr("STRING");
		break;
	case AND:
		ft_putstr("&&");
		break;
	case OR:
		ft_putstr("|");
		break;
	case ANY:
		ft_putstr("ANY");
		break;
	case SATISFY:
		ft_putstr("SATISFY");
		break;
	case STR_ANY:
		ft_putstr("STR_ANY");
		break;
	case PLUS:
		ft_putstr("+");
		break;
	case MULTIPLY:
		ft_putstr("*");
		break;
/*	case ONECHAR:
		ft_putstr(ONECHAR);
	case ONECHAR:
	ft_putstr(ONECHAR);*/
	default :
		ft_putnbr(parser->id);
		break;
	}
}

void	ft_put_parser(t_parser *parser)
{
	uint32_t	i;

	i = 0;
//	ft_put_id(parser);
	if (parser->id == OR)
	{
		ft_put_id(parser);
		ft_putnbr(parser->parser.or.n);
//		ft_putstr("| ");
		ft_putchar('\n');
		while (i < parser->parser.or.n)
		{
				ft_put_id(parser->parser.or.parsers[i]);
			ft_putchar('\t');
			ft_put_parser(parser->parser.or.parsers[i]);
			i++;
		}
	}
	else if (parser->id == AND)
	{
//		ft_putstr("& ");
		ft_put_id(parser);
		ft_putnbr(parser->parser.and.n);
		ft_putchar('\n');
		while (i < parser->parser.and.n)
		{
//			printf("%d \n", parser->parser.or.parsers[i]->id);
			ft_put_id(parser->parser.and.parsers[i]);
			ft_putchar('\t');
			ft_put_parser(parser->parser.or.parsers[i]);
			i++;
		}
	}
	else if (parser->id == PLUS)
	{
		ft_put_id(parser);
		ft_putchar('\t');
		ft_putchar('\n');
		ft_put_id(parser->parser.plus.parser);
		ft_putchar('\t');
		ft_put_parser(parser->parser.plus.parser);
		ft_putchar('\n');
	}
	else if (parser->id == MULTIPLY)
	{
		ft_put_id(parser);
		ft_putchar('\n');
		ft_put_id(parser->parser.multiply.parser);
		ft_put_parser(parser->parser.plus.parser);
		ft_putchar('\n');
	}
	else 
//		ft_putstr("node ");
		;
}
