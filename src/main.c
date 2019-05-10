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
    //fprintf(stderr, "check3 = %s\n", check[3]);
    //fprintf(stderr, "check34 = %s\n", check[34]);
    int value = atof(check[4]) - atof(check[33]);
    if (atof(check[17]) >= 1500) {
        if (value < 0) {
            send_command("WHEELS_DIR:-0.15", car);
        } else {
            send_command("WHEELS_DIR:0.15", car);
        }
    } else if (atof(check[17]) >= 1000) {
        if (value < 0) {
            send_command("WHEELS_DIR:-0.5", car);
        } else {
            send_command("WHEELS_DIR:0.5", car);
        }
    } else if (atof(check[17]) >= 600) {
        //fprintf(stderr, "600");
        if (value < 0) {
            send_command("WHEELS_DIR:-1.5", car);
        } else {
            send_command("WHEELS_DIR:1.5", car);
        }
    } else if (atof(check[17]) >= 400) {
        //fprintf(stderr, "400");
        if (value < 0) {
            send_command("WHEELS_DIR:-1.5", car);
        } else {
            send_command("WHEELS_DIR:1.5", car);
        }
    }
}

void choose_speed(int value, car_t *car)
{
    if (value >= 2000)
        send_command("CAR_FORWARD:1\n", car);
    else if (value < 2000) {
        send_command("CAR_FORWARD:0\n", car);
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
        check = check_lidar(car);
        float value = atof(check[20]);
        //fprintf(stderr, "%.2f\n", value);
        choose_speed(value, car);
        if (atof(check[17]) >= 1500) {
            if (value < 0) {
                //send_command("WHEELS_DIR:-0.7", car);
            } else {
                //send_command("WHEELS_DIR:0.7", car);
            }
        }/* else if (atof(check[17]) >= 1000) {
            if (value < 0) {
                send_command("WHEELS_DIR:-0.5", car);
            } else {
                send_command("WHEELS_DIR:0.5", car);
            }
        } else if (atof(check[17]) >= 600) {
            //fprintf(stderr, "600");
            if (value < 0) {
                send_command("WHEELS_DIR:-0.7", car);
            } else {
                send_command("WHEELS_DIR:0.7", car);
            }
        } else if (atof(check[17]) >= 400) {
            //fprintf(stderr, "400");
            if (value < 0) {
                send_command("WHEELS_DIR:-0.7", car);
            } else {
                send_command("WHEELS_DIR:0.7", car);
            }
        }*/
        fprintf(stderr, "salut");
        for (int i = 0; check[i]; i++) {
            free(check[i]);
        }
        car->salut = NULL;
        free(check);
        //free(car->salut);
    }
    fprintf(stderr, "Track Cleared\n");
    if (send_command(STOP, car) == 84)
        return (84);
    return (0);
}

/*    float value = atof(tab[16]) + atof(tab[17]) + atof(tab[18]) / 3;

    fprintf(stderr, "%.2f\n", value);
    if (value >= 10000)
    fprintf(stderr, "eeeeee\n");
        send_command("CAR_FORWARD:1\n", car);
    if (value < 10000) {
        fprintf(stderr, "sssssss\n");
        send_command("CAR_FORWARD:0\n", car);
    }*/