/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:15:19 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:38:42 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* static t_mpc_ref *get_p_ref(t_parser *parser) { */
/* 	assert(parser->id == REF); */
/* 	return &parser->parser.ref; */
/* } */

/* static t_mpc_or_n	*get_p_or(t_parser *parser) { */
/* 	assert(parser->id == OR); */
/* 	return &parser->parser.or; */
/* } */

//Later do a real token management

/* static bool	tokens_left(char **string) { */
/* 	return **string != '\0'; */
/* } */


/* static bool	ft_eval_onechar(t_parser *parser, char **string) { */
/* 	if (!tokens_left(string)) { */
/* 		return false; */
/* 	} */
/* 	if (parser->parser.onechar.c == **string) { */
/* 		(*string)++; */
/* 		return (true); */
/* 	} */
/* 	return (false); */
/* } */

/* static bool	ft_eval_parser_or(t_parser *parser, char **string) { */
/* 	uint32_t	i = 0; */
/* 	t_mpc_or_n	*inner; */
/* 	char		*save = *string; */

/* 	inner = get_p_or(parser); */
/* 	while (i < inner->n) { */
/* 		*string = save; */
/* 		if(ft_eval_parser(inner->parsers[i], string)) { */
/* 			return true; */
/* 		} */
/* 		i++; */
/* 	} */
/* 	*string = save; // not necessary if invariant holds: good luck. */
/* 	return false; */
/* } */

/* static t_mpc_and_n *get_p_and(t_parser *parser) { */
/* 	assert(parser->id == AND); */
/* 	return &parser->parser.and; */
/* } */

/* static bool	ft_eval_parser_and(t_parser *parser, char **string) { */
/* 	uint32_t    i = 0; */
/* 	t_mpc_and_n    *inner; */
/* 	char	      *save = *string; */

/* 	inner = get_p_and(parser); */
/* 	while (i < inner->n) { */
/* 		if (!ft_eval_parser(inner->parsers[i], string)) { */
/* 			*string = save; */
/* 			return false; */
/* 		} */
/* 		i++; */
/* 	} */
/* 	return true; */
/* } */

/* static t_mpc_plus   *get_p_plus(t_parser *parser) { */
/* 	assert(parser->id == PLUS); */
/* 	return &parser->parser.plus; */
/* } */

/* static bool ft_eval_parser_plus(t_parser *parser, char **string) { */
/* 	uint32_t    i = 0; */
/* 	t_mpc_plus  *inner; */
/* 	char	    *save; */

/* 	inner = get_p_plus(parser); */
/* 	while (42) { */
/* 		save = *string; */
/* 		if (!ft_eval_parser(inner->parser, string)) { */
/* 			*string = save; */
/* 			return i != 0 ? true : false; */
/* 		} */
/* 		i++; */
/* 	} */
/* } */

/* static t_mpc_multiply *get_p_multiply(t_parser *parser) { */
/* 	assert(parser->id == MULTIPLY); */
/* 	return &parser->parser.multiply; */
/* } */

/* static bool ft_eval_parser_multiply(t_parser *parser, char **string) { */
/* 	uint32_t    i = 0; */
/* 	t_mpc_multiply  *inner; */
/* 	char	    *save; */

/* 	inner = get_p_multiply(parser); */
/* 	while (42) { */
/* 		save = *string; */
/* 		if (!ft_eval_parser(inner->parser, string)) { */
/* 			*string = save; */
/* 			return true; */
/* 		} */
/* 		i++; */
/* 	} */
/* } */

/* static t_mpc_str    *get_p_str(t_parser *parser) { */
/* 	assert(parser->id == STRING); */
/* 	return (&parser->parser.string); */
/* } */

/* static bool ft_eval_parser_str(t_parser *parser, char **string) { */
/* 	t_mpc_str   *inner = get_p_str(parser); */

/* 	if (strncmp(inner->str, *string, inner->len)) { */
/* 		*string += inner->len; */
/* 		return true; */
/* 	} */
/* 	return false; */
/* } */

/* static bool	ft_eval_parser_ref(t_parser *parser, char **string) { */
/* 	t_mpc_ref *inner = get_p_ref(parser); */

/* 	return ft_eval_parser(inner->ref, string); */
/* } */

/* static bool ft_eval_parser_undefined(t_parser *parser, char **string) { */
/* 	(void)parser; */
/* 	(void)string; */
/* 	dprintf(STDERR_FILENO, "Tried to eval undefined parser"); */
/* 	assert(false); */
/* } */

bool	ft_eval_input(t_parser *parser, char **string)
{
        uint32_t        ret;

        if ((ret = ft_eval_parser(parser, string)) && !**string)
                return (true);
        return (false);
}

bool	ft_eval_parser(t_parser *parser, char **string)
{
	bool		ret;

	static const t_eval_parser	eval_parsers[18] = {
		{&ft_eval_parser_undefined}, {&ft_eval_parser_ref},
		{&ft_eval_onechar}, {&ft_eval_parser_str},
		{NULL}, {&ft_eval_parser_char_range},
		{&ft_eval_parser_char_any}, {NULL},
		{NULL}, {NULL},
		{NULL}, {&ft_eval_parser_oneof},
		{NULL}, {&ft_eval_parser_and},
		{&ft_eval_parser_or}, {&ft_eval_parser_not},
		{&ft_eval_parser_plus}, {&ft_eval_parser_multiply}};

	ret = eval_parsers[parser->id].f(parser, string);
	return (ret);
}

bool	ft_eval(t_parser *parser, char **string)
{
	bool	ret;
	char	*save;

	save = *string;
	ret = ft_eval_parser(parser, string);
	printf("Last chars of string: %s:%ld\n", *string,strlen(*string));
	if (ret && **string == '\0') {
		*string = save;
		return true;
	}
	*string = save;
	return false;
}
