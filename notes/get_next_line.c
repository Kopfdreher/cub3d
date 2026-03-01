#include "cub3d.h"
char *get_next_line(int fd)
{
    char    *line;
    char    *buffer;
    int     bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    line = NULL;
    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        line = strjoin(line, buffer); //ft_strjoin should be used here, but I am just using strjoin for now to test
        if (strchr(buffer, '\n'))
            break ;
    }
    free(buffer);
    return (line);
}