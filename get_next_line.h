/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:51:38 by yboudoui          #+#    #+#             */
/*   Updated: 2022/06/14 15:13:53 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# define OK 1
# define NOK 0
# define ERROR 0

typedef struct s_stash {
	int				readed;
	char			*buffer;
	struct s_stash	*next;
}	t_stash;

typedef struct s_book {
	int				fd;
	int				len;
	t_stash			*read;
	t_stash			*last;
	t_stash			*stash;
	struct s_book	*next;
	struct s_book	*prev;
}	t_book;

int		ft_create_stach(t_stash **root);
void	ft_delete(t_stash **root);
void	ft_delete_book(t_book **root);

void	ft_add_stash_to_book(t_book *book, t_stash *stash);
void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*get_next_line(int fd);

#endif
