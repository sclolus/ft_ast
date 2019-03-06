/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_multiply.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:42:51 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 20:48:23 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* static void		ft_get_multiply_parsers(t_parser *parser, uint32_t n */
/* 										, t_list *head) */
/* { */
/* 	uint32_t	i; */
/* 	t_list		*link; */

/* 	parser->parser.multiply.n = n; */
/* 	if (!(parser->parser.multiply.parsers = (t_parser**)malloc(n */
/* 										* sizeof(t_parser*)))) */
/* 		exit(EXIT_FAILURE); */
/* 	i = n - 1; */
/* 	while (head) */
/* 	{ */
/* 		parser->parser.multiply.parsers[i] = head->content; */
/* 		link = head; */
/* 		head = head->next; */
/* 		free(link); */
/* 		--i; */
/* 	} */
/* } */

/* uint32_t		ft_eval_parser_multiply(t_parser *parser, char **string) */
/* { */
/* 	t_list		*head; */
/* 	t_list		*link; */
/* 	uint32_t	n; */

/* 	n = 0; */
/* 	head = NULL; */
/* 	while (1) */
/* 	{ */
/* 		if (!(link = ft_lstnew(NULL, sizeof(t_parser*)))) */
/* 			exit(EXIT_FAILURE); */
/* 		link->content = ft_dup_parser(parser->parser.multiply.parser); */
/* 		if (!ft_eval_parser(link->content, string)) */
/* 		{ */
/* 			ft_free_parser(link->content); */
/* 			free(link); */
/* 			break ; */
/* 		} */
/* 		ft_lstadd(&head, link); */
/* 		++n; */
/* 	} */
/* 	if (n) */
/* 		ft_get_multiply_parsers(parser, n, head); */
/* 	return (1); */
/* } */

static inline t_mpc_multiply	*get_p_multiply(t_parser *parser)
{
#if ASSERT
	assert(parser->id == MULTIPLY);
#endif
	return (&parser->parser.multiply);
}

bool		ft_eval_parser_multiply(t_parser *parser, char **string)
{
	t_mpc_multiply	*inner;
    char			*save;

	inner = get_p_multiply(parser);
	while (42)
	{
		save = *string;
		if (!ft_eval_parser(inner->parser, string))
		{
			*string = save;
			return (true);
		}
	}
}
