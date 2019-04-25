/*
** EPITECH PROJECT, 2019
** Delivery
** File description:
** ai
*/
#include "include/my.h"

int main(void)
{
    char *response;
    int count = 0;
    while (1) {
        if (count == 1) {
            if (write(1, "START_SIMULATION\n", 18) < 0) {
                my_printf("Error xD");
            }
        }
        if (write(1, "CAR_FORWARD:0.5\n", 16) < 0) {
            my_printf("Error xD");
        }
        if (write(1, "CYCLE_WAIT:10\n", 14) < 0) {
            my_printf("Error xD");
        }
        if (count > 13) {
            write(1, "CAR_FORWARD:0\n", 16);
        }
        count++;
    }
    fprintf(stderr, "%d", count);
}