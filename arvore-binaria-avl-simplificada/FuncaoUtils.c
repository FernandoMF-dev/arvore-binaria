#include "headers/FuncaoUtils.h"

/*
 * Retorna o maior entre dois inteiros
 * */
int getMaxInt(int value1, int value2) {
    if (value1 > value2) {
        return value1;
    }
    return value2;
}