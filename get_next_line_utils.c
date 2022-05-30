/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:52:01 by yboudoui          #+#    #+#             */
/*   Updated: 2022/05/30 16:52:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_create_stach(t_stash **root)
{
	(*root) = malloc(sizeof(t_stash));
	if (!(*root))
		return (ERROR);
	(**root) = (t_stash){.buffer = malloc(BUFFER_SIZE * sizeof(char))};
	if ((**root).buffer)
		return (OK);
	free((*root)->buffer);
	return (ERROR);
}

void	ft_delete(t_stash **root)
{
	t_stash	*out;
	t_stash	*old;

	old = (*root);
	out = (*root)->next;
	free(old->buffer);
	free(old);
	(*root) = out;
}

void	ft_add_stash_to_book(t_book book, t_stash *stash)
{
	book->len += stash->readed;
	if (!book->stash)
		book->stash = stash;
	else
		book->last.stash->next = stash;
	book->last.stash = stash;
}

void	ft_strncpy(char *dst, char *src, int n)
{
	while (n--)
		*(dst++) = *(src++);
}
