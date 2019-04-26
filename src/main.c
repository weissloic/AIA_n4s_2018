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

int check_response(char *buffer, car_t *car)
{
    if (buffer == NULL)
        return (0);
    car->response = my_str_to_wordtab(buffer, ':');
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
    int i = 0;
    char **check;
    send_command("GET_INFO_LIDAR\n", car);
    while (car->salut[i - 2] != 'f' || car->salut[i - 1] != 'a' || car->salut[i] != 'r') {
        i++;
    }
    check = my_str_to_wordtab(car->salut, ':');
    return (check);
}

void choose_direction(char **tab, car_t *car)
{
    int max = 3000;
    int angle = 0;
    int way = 16;
    for (int i = 3; tab[i + 1] != NULL; i++) {
        if (atoi(tab[i]) <= 400 && atoi(tab[i]) < max) {
            if (atoi(tab[i]) <= 200) {
                angle = 0;
            }
            max = atoi(tab[i]);
            way = i;
        }
        fprintf(stderr, "%s ", tab[i]);
    }
    fprintf(stderr, "\n");
    if (way < 5 && angle == 0) {
        send_command("WHEELS_DIR:-0.10\n", car);
    }
    if (way < 5 && angle == 1) {
        send_command("WHEELS_DIR:-0.25\n", car);
    }
    if (way >= 6 && way <= 26 && angle == 0)
        send_command("WHEELS_DIR:0\n", car);
    if (way >= 6 && way <= 26 && angle == 1)
        send_command("WHEELS_DIR:0\n", car);
    if (way > 27 && angle == 0) {
        send_command("WHEELS_DIR:0.10\n", car);
    }
    if (way > 27 && angle == 1) {
        send_command("WHEELS_DIR:0.25\n", car);
    }
}

int main(void)
{
    car_t *car = malloc(sizeof(car_t));
    char **check;
    if (send_command(START, car) == 84)
        return (84);
    if (send_info(car) == 84)
        return (84);
    while (compare_response(car, "Track Cleared") == 1) {
        send_info(car);
        send_command("CAR_FORWARD:0.8\n", car);
        check = check_lidar(car);
        choose_direction(check, car);
    }
    fprintf(stderr, "Track Cleared\n");
    if (send_command(STOP, car) == 84)
        return (84);
    return (0);
}