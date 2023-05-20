#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "arch/io.h"
#include "arch/8018x.h"

struct {
    const char* name;
    const uint16_t start;
    const uint16_t stop;
} chipselects[] = {
    { "EEPROM (UCS)" , PCB_UCSST, PCB_UCSSP },
    { "RAM (LCS)" , PCB_LCSST, PCB_LCSSP },
    { "GCS0" , PCB_GCS0ST, PCB_GCS0SP },
    { "GCS1" , PCB_GCS1ST, PCB_GCS1SP },
    { "GCS2" , PCB_GCS2ST, PCB_GCS2SP },
    { "GCS3" , PCB_GCS3ST, PCB_GCS3SP },
    { "GCS4" , PCB_GCS4ST, PCB_GCS4SP },
    { "GCS5" , PCB_GCS5ST, PCB_GCS5SP },
    { "GCS6" , PCB_GCS6ST, PCB_GCS6SP },
    { "GCS7" , PCB_GCS7ST, PCB_GCS7SP },
};

struct {
    const char* name;
    const uint16_t portcon;
    const uint16_t portdir;
    const uint16_t portlatch;
    const uint16_t portpin;
} ports[] = {
    { "P1", PCB_P1CON, PCB_P1DIR, PCB_P1LTCH, PCB_P1PIN },
    { "P2", PCB_P2CON, PCB_P2DIR, PCB_P2LTCH, PCB_P2PIN },
};

#define ARRAY_SIZE(x) ((sizeof(x))/(sizeof(x[0])))

void print_chipselects(void)
{
    printf("Chip select unit configuration:\n");

    for (size_t i = 0; i < ARRAY_SIZE(chipselects); i++)
    {
        uint32_t start = inw(chipselects[i].start);
        uint32_t stop = inw(chipselects[i].stop);
        uint16_t waitstates = start & 0x0f;
        uint8_t enabled = stop & 0x08;
        uint8_t istop = stop & 0x04;
        uint8_t ismem = stop & 0x02;
        uint8_t rdy = stop & 0x01;
        uint32_t size;

        start &= 0xffc0;
        stop &= 0xffc0;

        if (ismem)
        {
            /* CS9:0 are compared with the A19:10 (memory bus cycles) */
            start <<= 4;
        }

        if (istop)
        {
            if (ismem)
            {
                stop = 0xfffff;
            }
            else
            {
                stop = 0xffff;
            }
        }
        else
        {
            if (ismem)
            {
                /* CS9:0 are compared with the A19:10 (memory bus cycles) */
                stop <<= 4;
            }
        }

        size = stop - start + 1;

        printf(" %s region %s: 0x%6lx-0x%6lx (%ld byte(s)) %s %dws %s\n",
            enabled ? "*" : " ",
            chipselects[i].name,
            start,
            stop,
            size,
            ismem ? "MEM" : "I/O",
            waitstates,
            rdy ? " RDY" : "NRDY");
    }
}

void print_ports(void)
{
    printf("Input/Output ports configuration:\n");

    for (size_t i = 0; i < ARRAY_SIZE(ports); i++)
    {
        uint16_t con = inw(ports[i].portcon);
        uint16_t dir = inw(ports[i].portdir);
        uint16_t latch = inw(ports[i].portlatch);
        uint16_t state = inw(ports[i].portpin);

        for (size_t pin = 0; pin < 8; pin++)
        {
            uint16_t is_periph = con & (1 << pin);
            uint16_t is_input = dir & (1 << pin);
            uint16_t pin_latch = latch & (1 << pin);
            uint16_t pin_state = state & (1 << pin);

            printf(" %s.%d %s %s Latch=%d State=%d\n",
                ports[i].name,
                pin,
                is_periph ? "PERI" : "GPIO",
                is_input ? "IN " : "OUT",
                pin_latch ? 1 : 0,
                pin_state ? 1 : 0);
        }
    }
}

int main (int argc, char **argv)
{
    printf("8018x information:\n");

    print_chipselects();
    print_ports();

    return 0;
}