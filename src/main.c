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

int check_response(char *buffer)
{
    char **response;

    if (buffer == NULL)
        return (0);
    response = my_str_to_wordtab(buffer, ':');
    if (strcmp(response[1], "OK") != 0) {
        return (0);
    }
    return (1);
}


int main(void)
{
    if (send_command(START) == 84)
        return (84);
    if (send_info() == 84)
        return (84);
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