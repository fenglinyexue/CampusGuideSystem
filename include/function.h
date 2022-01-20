#ifndef FUNCTION_H
#define FUNCTION_H

#include "../include/custom_err_msg.h"
#include <stdio.h>

#define ROOT "root"
#define NORMAL "normal"
#define VERIFY_COUNT 3

int login(FILE *, FILE *, char **, char **);

char *local_time();

#endif