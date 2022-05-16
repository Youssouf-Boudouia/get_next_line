/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:43:46 by yboudoui          #+#    #+#             */
/*   Updated: 2022/03/13 16:52:00 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_create_stach(t_stash **root)
{
	char	*buffer;

	(*root) = malloc(sizeof(t_stash));
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (*root && buffer)
	{
		(**root) = (t_stash){0, buffer, NULL};
		return (OK);
	}
	free(*root);
	free(buffer);
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

void	ft_add_stash_to_book(t_book *book, t_stash *stash)
{
	book->total_len += stash->readed;
	if (!book->stash)
		book->stash = stash;
	else
		book->lastStash->next = stash;
	book->lastStash = stash;
}

void	ft_strncpy(char *dst, char *src, int n)
{
	while (n--)
		*(dst++) = *(src++);
}
