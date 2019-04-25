/*
** EPITECH PROJECT, 2019
** send_command.c
** File description:
** send_command.c
*/

#include "my.h"
#include "n4s.h"

int send_info(void)
{
    char *response = NULL;

    if (write(1, INFO, strlen(INFO)) < 0)
        return (84);
    response = get_next_line(0);
    fprintf(stderr, "%s\n", response);
    if (check_response(response) == 0)
        return (84);
    return (0);
}

int send_command(char *str)
{
    char *response = NULL;

    if (write(1, str, strlen(str)) < 0)
        return (84);
    if (check_response(response) == 0)
        return (84);
    return (0);
}