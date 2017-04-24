/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 09:54:09 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 15:46:51 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#define CHARSET_WHITESPACES " \t\n"

static int32_t	ft_is_shell_reserved(char *buf, uint32_t i)
{
	if (ft_strchr("|&;<>$ \t\n", buf[i])
		&& !ft_is_quoted(buf, i))
		return (1);
	return (0);
}

void	ft_add_token_to_list(t_list **token_list
							, char *input, uint32_t start, uint32_t i)
{
	t_list	*tmp;
	char	*tmp_token;

	if (!(tmp = ft_lstnew(0, 0)))
		exit(EXIT_FAILURE);
	if (!(tmp_token = ft_strsub(input, start, i - start)))
		exit(EXIT_FAILURE);
	tmp->content = tmp_token;
	ft_lstadd(token_list, tmp);
}

char	**ft_token_list_to_tab(t_list *token_list)
{
	char		**tab;
	t_list		*tmp;
	uint32_t	i;
	uint32_t	size;

	size = ft_lstlen(token_list);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		tab[size - i - 1] = token_list->content;
		tmp = token_list;
		token_list = token_list->next;
		free(tmp);
		i++;
	}
	return (tab);
}

#define CHARSET_OP "|&;<>"

uint32_t	ft_is_part_of_op(char *input, uint32_t index)
{
	uint32_t	i;

	i = index;

	if (i > 0 && !ft_is_quoted(input, index - 1)
		&& ft_strchr("|&;<>" , input[index -1]))
		return (1);
	else
		return (0);
}

char	**ft_lexer(char *input)
{
	t_list		*token_list;
	uint32_t	i;
	uint32_t	start;
	uint32_t	last_unquoted_point;
	t_bool		bool_word;

	i = 0;
	last_unquoted_point = 0;
	start = 0;
	bool_word = 0;
	token_list = NULL;
	while (input[i])
	{
		if (!ft_is_quoted(input + last_unquoted_point, i - last_unquoted_point))
			last_unquoted_point = i;
		if (!bool_word && !ft_strchr(CHARSET_WHITESPACES, input[i]))
		{
			bool_word = 1;
			start = i;
		}
		else if (bool_word && ((ft_strchr(CHARSET_WHITESPACES, input[i]) && !ft_is_quoted(input, i))
							   || (!ft_is_shell_reserved(input, i) && ft_is_part_of_op(input, i))))
		{
			bool_word = 0;
			ft_add_token_to_list(&token_list, input, start, i);
			continue ;
		}	
		else if (bool_word && ft_is_shell_reserved(input, i) && !ft_is_part_of_op(input, i))
		{
			bool_word = 0;
			ft_add_token_to_list(&token_list, input, start, i);
			continue ;
		}
		i++;
	}
	if (bool_word)
		ft_add_token_to_list(&token_list, input, start, i);
	return (ft_token_list_to_tab(token_list));
}

void	ft_put_tokens(char **tokens)
{
	if (!tokens)
		return ;
	ft_putendl("_______");
	while (*tokens)
	{
		ft_putchar('=');
		ft_putendl(*tokens++);
		
	}
	ft_putendl("_______");
}
