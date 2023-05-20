#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "arch/io.h"

struct {
    const char* name;
    const uint16_t port;
    struct {
        const char* name;
        const char* on;
        const char* off;
        const uint16_t mask_test;
    } bit_meaning[16];
} stuff[] = {
    { 
        "U8" , 0x2003, {
            { "VER0", "on", "off", 0xf0 },
            { "VER1", "on", "off", 0xf0 },
            { "VER2", "on", "off", 0xf0 },
            { "Button", "pressed", "not pressed", (1 << 3) },
            { "JP1", "closed", "open", (1 << 1) },
            { NULL, NULL, NULL, 0 } /* sentinel */
        }
    },
    { 
        "U4 (dip switch block U34)" , 0x2001, {
            { "SW2", "off", "on", (1 << 1) },
            { "3", "EX. ON", "EX. OFF", (1 << 2) },
            { "4", "PRA", "D2048U/S", (1 << 3) },
            { "5", "TRAN", "N. TRAN", (1 << 4) },
            { "6", "FRM", "UNFRM", (1 << 5) },
            { "7", "NTU", "LTU", (1 << 6) },
            { "8", "HRD", "SFT", (1 << 7) },
            { NULL, NULL, NULL, 0 } /* sentinel */
        }
    },
    { 
        "U20" , 0x2004, {
            { "JP11 pin 22", "on", "off", (1 << 1) },
            { NULL, NULL, NULL, 0 } /* sentinel */
        }
    },
};

int main (int argc, char **argv)
{
    printf("OR566 PCB information\n");

    for (size_t i = 0; i < 2; i++)
    {
        uint16_t value = inw(stuff[i].port);

        printf("* %s (@ 0x%x = 0x%x):\n", stuff[i].name, stuff[i].port, value);

        for (size_t bit = 0; i < 16; bit++)
        {
            if (stuff[i].bit_meaning[bit].name == NULL)
            {
                break;
            }

            printf("  - %s (0x%x): ", stuff[i].bit_meaning[bit].name, stuff[i].bit_meaning[bit].mask_test);
            if (value & stuff[i].bit_meaning[bit].mask_test)
            {
                printf("%s\n", stuff[i].bit_meaning[bit].on);
            }
            else
            {
                printf("%s\n", stuff[i].bit_meaning[bit].off);
            }
        }
    }

    return 0;
}