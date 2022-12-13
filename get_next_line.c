#include "get_next_line.h"

size_t  ft_strlen(const char *s)
{
    size_t  len;

    if (!s)
        return (0);
    len = 0;
    while (*s)
    {
        len++;
        s++;
    }
    return (len);
}

char	*ft_strldup(const char *str, size_t size)
{
	char	*dup;
	size_t	s_len;

    if (!str)
        return (NULL);
	s_len = ft_strlen(str);
    if (s_len > size)
        s_len = size;
	dup = (char *)malloc(s_len + 1);
	if (!dup)
		return (NULL);
	while (*str && size-- > 0)
		*(dup++) = *(str++);
	*dup = '\0';
	return (dup - s_len);
}

char    *get_next_line(int fd)
{
    static char *stat;
    char        *buffer;
    char        *line;
    size_t      read_bytes;
    size_t      cursor;

    if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
        return (NULL);
    if (stat == NULL)
    {
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!buffer)
            return (NULL);
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (read_bytes <= 0)
        {
            free(buffer);
            return (NULL);
        }
        buffer[read_bytes] = '\0';
        stat = ft_strldup(buffer, BUFFER_SIZE);
        free(buffer);
    }
    while (stat != NULL)
    {
        cursor = 0;
        while (stat[cursor] != '\0'
            && stat[cursor] != '\n')
        cursor++;
        if (stat[cursor] == '\n')
        {
            cursor++;
            read_bytes = ft_strlen(stat);
            buffer = ft_strldup(stat, read_bytes);
            free(stat);
            stat = ft_strldup(buffer + cursor, read_bytes);
            line = ft_strldup(buffer, cursor);
            free(buffer);
            return (line);
        }
        if (stat[cursor] == '\0')
        {
            buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
            if (!buffer)
                return (NULL);
            read_bytes = read(fd, buffer, BUFFER_SIZE);
            if (read_bytes < 0)
            {
                free(buffer);
                return (NULL);
            }
            buffer[read_bytes] = '\0';
            if (read_bytes == 0)
            {
                if (ft_strlen(stat) == 0)
                {
                    free(stat);
                    stat = NULL;
                }
                free(buffer);
                line = ft_strldup(stat, ft_strlen(stat));
                free(stat);
                stat = NULL;
                return (line);
            }
            line = ft_strldup(stat, ft_strlen(stat));
            free(stat);
            cursor = 0;
            stat = malloc(sizeof(char) * (ft_strlen(line) + read_bytes + 1));
            if (!stat)
                return (NULL);
            while (line[cursor] != '\0')
            {
                stat[cursor] = line[cursor];
                cursor++;
            }
            free(line);
            read_bytes = 0;
            while (buffer[read_bytes] != '\0')
                stat[cursor++] = buffer[read_bytes++];
            stat[cursor] = '\0';
            free(buffer);
        }
    }
    return (NULL);
}

/////////////////////// MAIN /////////////////////////
// #include <stdio.h>
// #include <fcntl.h>

// int main(void)
// {
//     int fd = open("example.txt", O_RDONLY);
//     char *one = get_next_line(fd);
//     char *two = get_next_line(fd);
//     char *three = get_next_line(fd);
//     char *four = get_next_line(fd);
//     close(fd);
//     printf("1: %s_\n", one);
//     printf("2: %s_\n", two);
//     printf("3: %s_\n", three);
//     printf("4: %s_\n", four);
// }