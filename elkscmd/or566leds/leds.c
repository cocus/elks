#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "arch/io.h"

#define base 0x2002   //LPT0

int main (int argc, char **argv)
{
    uint16_t l;
	

    printf("leds: argc=%d\n", argc);

	if (argc < 2)
    {
        for (l = 0; l < 256; l++)
        {
            outb(l, base);  //set all pins hi
            printf("Outputting: %x\n", l);
            sleep(1);
        }
    }
    else
    {
        l = atoi(argv[1]);
        outb(l, base);
    }

    return 0;
}