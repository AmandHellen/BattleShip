#include "utils.h"

void delay(int secs){
    int ms = 1000 * 1000 * secs;
    clock_t start_time = clock();
    while (clock() < start_time + ms)
        ;
}

unsigned char * serialize_int(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value >> 24;
  buffer[1] = value >> 16;
  buffer[2] = value >> 8;
  buffer[3] = value;
  return buffer + 4;
}

unsigned char * serialize_char(unsigned char *buffer, char value)
{
  buffer[0] = value;
  return buffer + 1;
}
