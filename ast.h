/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:06:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/10 06:14:04 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AST_H__
# define __AST_H__
# include "libft.h"
# include <unistd.h>

typedef uint32_t	t_id;

# define UNRETAINED 0
# define RETAINED 1

# define MPC_PARSING_METACHAR "\"\'|*+()/<>[]"
# define METACHAR_STACKSIZE 4096

typedef struct	s_metachar_stack
{
	char		c;
	uint32_t	offset;
}				t_metachar_stack;

typedef struct	s_parser t_parser;
typedef enum	e_id
{
	UNDEFINED = 0,
	ONECHAR = 1,
	STRING  = 2,
	REGEXP = 3,
	AND = 4,
	OR = 5,
	RANGE = 6,
	ANY = 7,
	SATISFY = 8,
	SATISFY_STR = 9,
	NOT = 10,
}				t_e_id;

typedef struct	s_mpc_onechar
{
	char	c;
}				t_mpc_onechar;

typedef struct	s_mpc_any
{
	char	padding[8];
}				t_mpc_any;

typedef struct	s_mpc_str
{
	char	*str;
}				t_mpc_str;

typedef struct	s_mpc_regexp
{
	char	*regexp;
}				t_mpc_regexp;

typedef struct	s_mpc_and_n
{
	uint32_t	n;
	t_parser	**parsers;
}				t_mpc_and_n;

typedef struct	s_mpc_or_n
{
	uint32_t	n;
	t_parser	**parsers;
}				t_mpc_or_n;

typedef struct	s_mpc_not
{
	t_parser	*parser;
}				t_mpc_not;

typedef struct	s_mpc_char_range
{
	char	start;
	char	end;
}				t_mpc_char_range;

typedef struct	s_mpc_satisfy
{
	int32_t	(*f)(char);
}				t_mpc_satisfy;

typedef struct	s_mpc_satisfy_str
{
	int32_t	(*f)(char*);
}				t_mpc_satisfy_str;

typedef union	s_mpc
{
	t_mpc_onechar		onechar;
	t_mpc_str			string;
	t_mpc_regexp		regexp;
	t_mpc_and_n			and;
	t_mpc_or_n			or;
	t_mpc_char_range	range;
	t_mpc_any			any;
	t_mpc_satisfy		satisfy;
	t_mpc_satisfy_str	satisfy_str;
	t_mpc_not			not;
}				t_mpc;

typedef struct	s_parser
{
	char	*name;
	t_e_id	id;
	char	retained;
	t_mpc	parser;
}				t_parser;


t_parser		*ft_get_undefined_parser(void);
t_parser		*ft_get_parser_onechar(char c);
t_parser		*ft_get_parser_str(char *str);
t_parser		*ft_get_parser_range(char start, char end);
t_parser		*ft_get_parser_and_n(uint32_t n, t_parser **parsers);
t_parser		*ft_get_parser_or_n(uint32_t n, t_parser **parsers);
t_parser		*ft_get_parser_any(void);
t_parser		*ft_get_parser_satisfy(int32_t (*f)(char));
t_parser		*ft_get_parser_satisfy_str(int32_t (*f)(char*));
t_parser		*ft_get_parser_not(t_parser *parser);

t_parser		*ft_grammar(char *grammar);
uint32_t		ft_count_metachar(char *start, char *end);
int32_t			ft_count_rules(char *grammar);
#endif
