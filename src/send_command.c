/*
** EPITECH PROJECT, 2019
** send_command.c
** File description:
** send_command.c
*/

#include "my.h"
#include "n4s.h"

int send_info(car_t *car)
{
    car->check_str = NULL;

    if (write(1, INFO, strlen(INFO)) < 0)
        return (84);
    car->check_str = get_next_line(0);
    if (check_response(car->check_str, car) == 0)
        return (84);
    return (0);
}

int send_command(char *str, car_t *car)
{
    char *response = NULL;

    if (write(1, str, strlen(str)) < 0)
        return (84);
    response = get_next_line(0);
    if (check_response(response, car) == 0)
        return (84);
    return (0);
}