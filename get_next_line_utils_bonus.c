/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:43:46 by yboudoui          #+#    #+#             */
/*   Updated: 2022/06/11 16:04:37 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d || !s)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}
