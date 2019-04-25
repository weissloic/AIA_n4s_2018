/*
** EPITECH PROJECT, 2018
** get_next_line.c
** File description:
** get_next_line.c
*/

#include "my.h"

int my_str_len(char *str)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++);
    return (i);
}

static char *fill_buffer(char *buffer, int fd)
{
    int reader = 0;

    buffer = malloc(sizeof(char) * (READ_SIZE + 1));
    if (buffer == NULL)
        return (NULL);
    reader = read(fd, buffer, READ_SIZE);
    if (reader == -1)
        return (NULL);
    buffer[reader] = '\0';
    return (buffer);
}

static int have_result(char **line, char **buffer)
{
    int i = 0;

    (*line) = malloc(sizeof(char) * (READ_SIZE + 1));
    if ((*line) == NULL)
        return (-1);
    while (**buffer != '\0' && (i == 0 || *(*buffer - 1) != '\n')) {
        (*line)[i] = **buffer;
        (*buffer)++;
        i++;
    }
    return (i);
}

char *my_strncat_buff(char *buffer, char *add)
{
    char *result = NULL;
    int j;
    int i;

    if (buffer == NULL)
        return (add);
    if (add == NULL)
        return (buffer);
    result = malloc(sizeof(char) * (my_str_len(buffer) + my_str_len(add) + 1));
    if (result == NULL)
        return (NULL);
    for (i = 0; buffer[i] != '\0'; i++)
        result[i] = buffer[i];
    j = i;
    for (i = 0; add[i] != '\0'; i++, j++)
        result[j] = add[i];
    result[j] = '\0';
    return (result);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line = NULL;
    int length = 0;

    if (fd == -1)
        return (NULL);
    if (buffer == NULL || buffer[0] == '\0')
        buffer = fill_buffer(buffer, fd);
    if (buffer == NULL || buffer[0] == '\0')
        return (NULL);
    length = have_result(&line, &buffer);
    if (length == -1)
        return (NULL);
    line[length] = '\0';
    if (length != 0 && line[length - 1] == '\n')
        line[length - 1] = '\0';
    else
        line = my_strncat_buff(line, get_next_line(fd));
    return (line);
}