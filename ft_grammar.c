/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grammar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 03:13:00 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/10 05:58:11 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int32_t	ft_count_rules(char *grammar)
{
	uint32_t	i;
	uint32_t	count;
	uint32_t	quotes;
	uint32_t	semi_colon;

	semi_colon = 0;
	count = 0;
	quotes = 0;
	i = 0;
	while (grammar[i])
	{
		if (grammar[i] == '\'')
			quotes ^= 0b01;
		else if (grammar[i] == '\"')
			quotes ^= 0b10;
		else if (grammar[i] == ':' && !semi_colon && !quotes)
		{
			count++;
			semi_colon ^= 1;
		}
		else if (grammar[i] == ':')
			return (-1);
		else if (grammar[i] == ';' && semi_colon && !quotes)
			semi_colon ^= 1;
		else if (grammar[i] == ';')
			return (-1);
		i++;
	}
	return (count);
}

/*
/** Not safe, need checks on rule existence
*/

uint32_t		ft_count_metachar(char *start, char *end)
{
	uint32_t	count;

	count = 0;
	while (start < end)
		if (ft_strchr(MPC_PARSING_METACHAR, *start++))
			count++;
	return (count);
}

int32_t			ft_fill_metachar_stack(char *stack, char *start
									   , char *end)
{
	uint32_t	i;
	uint32_t	quotes;

	i = 0;
	quotes = 0;
	while (start < end)
	{
		if (*start == '\'' && quotes != 0b10)
			quotes ^= 0b01;
		else if (*start == '\"' && quotes != 0b01)
			quotes ^= 0b10;
		if (ft_strchr(MPC_PARSING_METACHAR, *start) && !quotes)
		{
			stack[i].c = *start;
			stack[i++].offset = end - start;
		}
		start++;
	}
	stack[i] = 0;
	if (quotes)
		return (-1);
	return (i);
}

t_parser		*ft_get_next_rule(char *grammar)
{
	static char	metachar_stack[METACHAR_STACKSIZE];
	t_parser	*parser;
	char		*name;
	char		*definition;

	parser = ft_get_parser_or_n(1, NULL);
	name = ft_strchr(grammar, ':');
	definition = ft_strstr(grammar, ";\n");
	ft_fill_metachar_stack(metachar_stack, name, definition);
	
}

t_parser	*ft_grammar(char *grammar)
{
	int32_t		count;
	t_parser	**parsers;

	if ((count = ft_count_rules(grammar)) == -1)
		return (NULL);
	if (!(parsers = (t_parser**)malloc(sizeof(t_parser*) * (count + 1))))
		exit (EXIT_FAILURE);
	ft_putnbr(count);
	parsers[count] = NULL;
	while (--count >== 0)
		parsers[count] = ft_get_next_rule(grammar);
	return ((void*)1);
}
