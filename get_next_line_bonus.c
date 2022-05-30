/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.41.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:42:36 by yboudoui          #+#    #+#             */
/*   Updated: 2022/05/30 17:43:23 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_have_newline(t_book book)
{
	t_stash	*new;
	int		index;

	if (book->last.read->readed == 0)
		return (book->stash != NULL);
	if (!ft_create_stach(&new))
		return (ERROR);
	index = -1;
	while (++index < book->last.read->readed)
	{
		new->buffer[index] = book->last.read->buffer[index];
		if (new->buffer[index] == '\n' && ++new->readed)
			break ;
	}
	new->readed += index;
	ft_add_stash_to_book(book, new);
	if (index == book->last.read->readed)
		return (NOK);
	book->last.read->readed -= new->readed;
	ft_strncpy(
		book->last.read->buffer,
		book->last.read->buffer + new->readed,
		book->last.read->readed);
	return (OK);
}

char	*ft_find_line(t_book book)
{
	char	*out;
	int		offset;
	t_stash	*old;

	if (!ft_have_newline(book))
		return (NULL);
	offset = 0;
	out = malloc((book->len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (book->stash)
	{
		ft_strncpy(out + offset, book->stash->buffer, book->stash->readed);
		offset += book->stash->readed;
		old = book->stash;
		book->stash = book->stash->next;
		free(old->buffer);
		free(old);
	}
	out[offset] = '\0';
	book->len = 0;
	return (out);
}

t_book	ft_get_book(int fd)
{
	static t_book	library = NULL;
	t_book			*book_ref;

	book_ref = &library;
	while (*book_ref)
	{
		if ((*book_ref)->fd == fd)
			return (*book_ref);
		book_ref = &(*book_ref)->next;
	}
	(*book_ref) = malloc(sizeof(t_book_data));
	if (!(*book_ref))
		return (NULL);
	(**book_ref) = (t_book_data){.fd = fd};
	if (!ft_create_stach(&((*book_ref)->last.read)))
		free(*book_ref);
	return (*book_ref);
}

char	*get_next_line(int fd)
{
	char	*line;
	t_book	book;

	book = ft_get_book(fd);
	if (!book)
		return (NULL);
	line = ft_find_line(book);
	while (!line)
	{
		book->last.read->readed = read(
				book->fd,
				book->last.read->buffer,
				BUFFER_SIZE);
		if ((book->last.read->readed < 0)
			|| (book->last.read->readed == 0 && book->stash == NULL))
			break ;
		line = ft_find_line(book);
	}
	return (line);
}
