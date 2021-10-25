#include "header/Accelerometer/Acelerometro.h"
#include <stdint.h>


static accel_t accelerations = {1, -1, 3};

void Accelerometro_Init(void)
{
    printf("Acelerometro iniciado!\n");
}

void Acelerometro_enable(void)
{
    printf("Acelerometro activado!\n");
}

void Acelerometro_disable(void)
{
    printf("Acelerometro desactivado!\n");
}


uint16_t Acelerometro_getXint(void)
{
    return accelerations.accel_x;
}
uint16_t Acelerometro_getYint(void)
{
    return accelerations.accel_y;
}
uint16_t Acelerometro_getZint(void)
{
    return accelerations.accel_z;
}


accel_t get_accelerations(void)
{
    return accelerations;
}