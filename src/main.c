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

int main(void)
{
    car_t *car = malloc(sizeof(car_t));
    if (send_command(START, car) == 84)
        return (84);
    if (send_info(car) == 84)
        return (84);
    while (compare_response(car, "Track Cleared") == 1) {
        send_info(car);
        send_command("CAR_FORWARD:1\n", car);
    }
    /*while (1) {
        if (count == 1) {
            if (write(1, "START_SIMULATION\n", 18) < 0) {
                printf("Error xD");
            }
            response = get_next_line(0);
            if (check_response(response) == 0)
                return (84);
        }
        if (write(1, "CAR_FORWARD:0.5\n", 16) < 0) {
            printf("Error xD");
        }
        if (write(1, "CYCLE_WAIT:10\n", 14) < 0) {
            printf("Error xD");
        }
        if (count > 13) {
            write(1, "CAR_FORWARD:0\n", 16);
            break;
        }
        count++;
    }*/
    return (0);
}