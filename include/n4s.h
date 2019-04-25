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
#define READ_SIZE (10)
#define START "START_SIMULATION"
#define INFO "GET_INFO_LIDAR"
#define STOP "STOP_SIMULATION"
#define FORWARD(n) "CAR_FORWARD:"n
#define BACKWARD(n) "CAR_BACKWARD:"n

char *get_next_line(int fd);

#endif /* !BOOTSTRAP_H_ */
