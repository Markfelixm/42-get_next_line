#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char    *get_next_line(int fd);
char	*ft_strldup(const char *s1, size_t size);
size_t  ft_strlen(const char *s);

#endif