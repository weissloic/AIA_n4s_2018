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
    check = my_str_to_wordtab(car->salut, ':');
    if (len_tab(check) < 2)
        return (NULL);
    free(car->salut);
    return (check);
}

void choose_direction(char **check, car_t *car)
{
    float value = atof(check[3]) - atof(check[33]);
    int b;
    switch (atoi(check[18]) >= b) {
        case (1500):
            fprintf(stderr, "djhzqjhzdqjé");
            break;
    }

    if (atof(check[18]) >= 1500)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.0055\n", car) :
        send_command("WHEELS_DIR:0.0055\n", car));
    else if (atof(check[18]) >= 1000)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.055\n", car) :
        send_command("WHEELS_DIR:0.055\n", car));
    else if (atof(check[18]) >= 600)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.15\n", car) :
        send_command("WHEELS_DIR:0.15\n", car));
    else if (atof(check[18]) >= 400)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.25\n", car) :
        send_command("WHEELS_DIR:0.25\n", car));
    else if ((atof(check[18]) >= 200))
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.35\n", car) :
        send_command("WHEELS_DIR:0.35\n", car));
    else
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.85\n", car) :
        send_command("WHEELS_DIR:0.85\n", car));
}

void choose_speed(int value, car_t *car)
{
    if (value >= 2000)
        send_command("CAR_FORWARD:0.9\n", car);
    else if (value >= 1500)
        send_command("CAR_FORWARD:0.6\n", car);
    else if (value >= 1000)
        send_command("CAR_FORWARD:0.33\n", car);
    else if (value >= 600)
        send_command("CAR_FORWARD:0.25\n", car);
    else if (value >= 400)
        send_command("CAR_FORWARD:0.06\n", car);
    else
        send_command("CAR_FORWARD:0.02\n", car);
}

int game_loop(char **check, car_t *car)
{
    send_info(car);
    check = check_lidar(car);
    if (check == NULL)
        return (84);
    float value = atof(check[18]);
    choose_speed(value, car);
    choose_direction(check, car);
    for (int i = 0; check[i]; i++) {
        free(check[i]);
    }
    free(check);
    car->salut = NULL;
    free(car->salut);
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