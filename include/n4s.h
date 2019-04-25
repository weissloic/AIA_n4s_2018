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
#define FORWARD(n) "CAR_FORWARD:"n
#define BACKWARD(n) "CAR_BACKWARD:"n

typedef struct s_car {
    float speed;
    float wheels_dir;
} car_t;

char *get_next_line(int fd);

// SEND
int send_command(char *str);
int send_info(void);
int check_response(char *buffer);
 
#endif /* !BOOTSTRAP_H_ */
