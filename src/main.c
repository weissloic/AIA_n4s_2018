/*
** EPITECH PROJECT, 2019
** Delivery
** File description:
** ai
*/

#include "n4s.h"
#include "my.h"

// 1:OK:No erros so far:Track Cleared:
// 0:KO:

// GET INFO LIDAR
// Track Cleared a la fin = FIN DE LA COURSE CIAO
// LES NOMBRES = distance entre les murs et la voiture

int len_tab(char **tab)
{
    int i = 0;

    while (tab[i])
        i++;
    return (i);
}

int check_response(char *buffer, car_t *car)
{
    if (buffer == NULL)
        return (0);
    car->response = my_str_to_wordtab(buffer, ':');
    if (len_tab(car->response) < 2)
        return (84);
    if (strcmp(car->response[1], "OK") != 0) {
        return (0);
    }
    return (1);
}

int compare_response(car_t *car, char *response)
{
    for (int i = 0; car->response[i] != NULL; i++) {
        if (strcmp(car->response[i], response) == 0) {
            send_command(STOP, car);
            return (0);
        }
    }
    return (1);
}

char **check_lidar(car_t *car)
{
    char **check = NULL;

    send_command("GET_INFO_LIDAR\n", car);
    check = my_str_to_wordtab(car->check_str, ':');
    if (len_tab(check) < 2)
        return (NULL);
    free(car->check_str);
    return (check);
}

int main(void)
{
    car_t *car = malloc(sizeof(car_t));
    char **check = NULL;

    if (send_command(START, car) == 84)
        return (84);
    if (send_info(car) == 84)
        return (84);
    while (compare_response(car, "Track Cleared") == 1) {
        if (game_loop(check, car) == 84)
            return 84;
    }
    fprintf(stderr, "Track Cleared\n");
    if (send_command(STOP, car) == 84)
        return (84);
    return (0);
}