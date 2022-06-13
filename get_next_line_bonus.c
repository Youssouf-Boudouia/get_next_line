/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.41.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:42:36 by yboudoui          #+#    #+#             */
/*   Updated: 2022/06/11 16:12:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_have_newline(t_book book)
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
	ft_memcpy(
		book->last.read->buffer,
		book->last.read->buffer + new->readed,
		book->last.read->readed);
	return (OK);
}

static char	*ft_find_line(t_book book)
{
	char	*out;
	int		offset;

	if (!ft_have_newline(book))
		return (NULL);
	offset = 0;
	out = malloc((book->len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (book->stash)
	{
		ft_memcpy(out + offset, book->stash->buffer, book->stash->readed);
		offset += book->stash->readed;
		ft_delete(&book->stash);
	}
	out[offset] = '\0';
	book->len = 0;
	return (out);
}

static t_book	ft_get_book(int fd)
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

static int	ft_reader(t_book book)
{
	int		readed;
	char	*buffer;

	buffer = book->last.read->buffer;
	readed = read(book->fd, buffer, BUFFER_SIZE);
	book->last.read->readed = readed;
	if (readed < 0)
		return (ERROR);
	if (!readed && book->stash == NULL)
		return (NOK);
	return (OK);
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
		if (!ft_reader(book))
			break ;
		line = ft_find_line(book);
	}
	return (line);
}
