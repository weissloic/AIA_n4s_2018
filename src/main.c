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
    free(car->salut);
    return (check);
}

void choose_direction(char **check, car_t *car)
{
    //fprintf(stderr, "%s\n", check[17]);
    fprintf(stderr, "check3 = %s\n", check[3]);
    fprintf(stderr, "check34 = %s\n", check[34]);
    int value = atof(check[3]) - atof(check[34]);
    if (atof(check[17]) >= 1500) {
        if (value < 0) {
            send_command("WHEELS_DIR:-0.1", car);
        } else {
            send_command("WHEELS_DIR:0.1", car);
        }
    } else if (atof(check[17]) >= 1000) {
        if (value < 0) {
            send_command("WHEELS_DIR:-0.1", car);
        } else {
            send_command("WHEELS_DIR:0.1", car);
        }
    } else if (atof(check[17]) >= 600) {
        fprintf(stderr, "600");
        if (value < 0) {
            send_command("WHEELS_DIR:-1", car);
        } else {
            send_command("WHEELS_DIR:1", car);
        }
    } else if (atof(check[17]) >= 400) {
        fprintf(stderr, "400");
        if (value < 0) {
            send_command("WHEELS_DIR:-1", car);
        } else {
            send_command("WHEELS_DIR:1", car);
        }
    }
}

void choose_speed(char *tab, car_t *car)
{
    float value = atof(tab);

    //if (value >= 2000)
    send_command("CAR_FORWARD:1\n", car);
    if (value < 2000) {
        fprintf(stderr, "sssssss");
        send_command("CAR_FORWARD:0\n", car);
    }
    /*} else if (value < 1000 && value > 500) {
        send_command("CAR_FORWARD:0\n", car);
    } else if  (value < 500 && value > 100) {
        send_command("CAR_FORWARD:0", car);
    } else if (value <= 100) {
        send_command("CAR_FORWARD:0", car);
    }*/
}

int main(void)
{
    car_t *car = malloc(sizeof(car_t));
    char **check;
    int value;
    if (send_command(START, car) == 84)
        return (84);
    if (send_info(car) == 84)
        return (84);
    while (compare_response(car, "Track Cleared") == 1) {
        send_info(car);
        check = check_lidar(car);
        choose_speed(check[17], car);
        //choose_direction(check, car);
    }
    fprintf(stderr, "Track Cleared\n");
    if (send_command(STOP, car) == 84)
        return (84);
    return (0);
}