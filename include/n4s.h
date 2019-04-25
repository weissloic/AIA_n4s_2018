/*
** EPITECH PROJECT, 2019
** bootstrap.h
** File description:
** bootstrap.h
*/

#ifndef BOOTSTRAP_H_
#define BOOTSTRAP_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define START "START_SIMULATION\n"
#define INFO "GET_INFO_LIDAR\n"
#define STOP "STOP_SIMULATION\n"
#define FORWARD(n) "CAR_FORWARD:"n"\n"
#define BACKWARD(n) "CAR_BACKWARD:"n

typedef struct s_car {
    float speed;
    float wheels_dir;
    char **response;
    char *salut;
} car_t;

char *get_next_line(int fd);

// SEND
int send_command(char *str, car_t *car);
int send_info(car_t *car);
int check_response(char *buffer, car_t *car);
void choose_direction(char **tab, car_t *car);
char **check_lidar(car_t *car);
 
#endif /* !BOOTSTRAP_H_ */
