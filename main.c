/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/10 05:07:20 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int main(int argc, char **argv)
{

	if (argc || argv)
	{};
	if (ft_grammar("number \"number\" : /[0-9]+/ ; \
expression      : <product> ((\'+\' | \'-\') <product>)* ; \
product         : <value>   ((\'*\' | \'/\')   <value>)* ; \
value           : <number> | \'(\' <expression> \')\' ; \
maths           : /^/ <expression> /$/ ;"))
		ft_putstr("valid rules");
	else
		ft_putstr("lol");
//	ft_parser(argv[1]);
	return (0);
}
