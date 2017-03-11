/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 11:16:04 by aalves            #+#    #+#             */
/*   Updated: 2017/03/08 03:54:22 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_push(t_stack *stack, void *content)
{
	if (stack->n_elem <= STACK_SIZE)
		stack->content[stack->n_elem++ - 1] = content;
	else
	{
		ft_putendl("Stack limit reached");
		exit(EXIT_FAILURE);
	}
}

void		*ft_pop(t_stack *stack)
{
	if (stack->n_elem > 0)
		return(stack->content[stack->n_elem-- - 1]);
	else
		return (NULL); //exit if pop empty stack ?
}

void		*ft_peek(t_stack *stack)
{
	if (stack->n_elem > 0)
		return(stack->content[stack->n_elem]);
	else
		return (NULL);
}

uint32_t	ft_stack_empty(t_stack *stack)
{
	return(!stack->n_elem);
}
