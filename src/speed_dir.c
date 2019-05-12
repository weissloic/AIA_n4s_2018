/*
** EPITECH PROJECT, 2019
** Delivery
** File description:
** ai
*/

#include "n4s.h"
#include "my.h"

void choose_direction_two(char **check, car_t *car, float value)
{
    if (atof(check[18]) >= 400 && atof(check[18]) < 600)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.25\n", car) :
        send_command("WHEELS_DIR:0.25\n", car));
    if ((atof(check[18]) >= 200) && atof(check[18]) < 400)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.35\n", car) :
        send_command("WHEELS_DIR:0.35\n", car));
    if ((atof(check[18]) < 200))
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.85\n", car) :
        send_command("WHEELS_DIR:0.85\n", car));
}

void choose_direction(char **check, car_t *car)
{
    float value = atof(check[3]) - atof(check[33]);
    if (atof(check[18]) >= 1500)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.0055\n", car) :
        send_command("WHEELS_DIR:0.0055\n", car));
    if (atof(check[18]) >= 1000 && atof(check[18]) < 1500)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.055\n", car) :
        send_command("WHEELS_DIR:0.055\n", car));
    if (atof(check[18]) >= 600 && atof(check[18]) < 1000)
        value = ((value < 0) ? send_command("WHEELS_DIR:-0.15\n", car) :
        send_command("WHEELS_DIR:0.15\n", car));
    choose_direction_two(check, car, value);
}

void choose_speed_two(int value, car_t *car)
{
    if (value >= 600 && value < 1000)
        send_command("CAR_FORWARD:0.25\n", car);
    if (value >= 400 && value < 600)
        send_command("CAR_FORWARD:0.1\n", car);
    if (value < 400)
        send_command("CAR_FORWARD:0.05\n", car);
}

void choose_speed(int value, car_t *car)
{
    if (value >= 2000)
        send_command("CAR_FORWARD:0.9\n", car);
    if (value >= 1500 && value < 2000)
        send_command("CAR_FORWARD:0.6\n", car);
    if (value >= 1000 && value < 1500)
        send_command("CAR_FORWARD:0.33\n", car);
    choose_speed_two(value, car);
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
    car->check_str = NULL;
    free(car->check_str);
}