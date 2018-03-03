#ifndef N5110_H
#define N5110_H

#define N5110_ROWS 84
#define N5110_COLS 48
#define N5110_BANKS (N5110_COLS / 8)
#define N5110_SURFACE_BYTES (N5110_ROWS * N5110_BANKS)
#define N5110_SURFACE_SIZE (N5110_SURFACE_BYTES * sizeof(char))

#include "mbed.h"

typedef struct {
	SPI* port;
	DigitalOut* dc;
	DigitalOut* cs;
	DigitalOut* rst;
} n5110_t;

n5110_t* n5110_create();
void n5110_setPins(n5110_t* dev, PinName mosi, PinName clk, PinName cs, PinName dc, PinName rst);
void n5110_reset(n5110_t* dev);
void n5110_init(n5110_t* dev);
void n5110_sendData(n5110_t* dev, char* surface);

//void n5110_sendCommand(n5110_t* dev, int cmd);

#endif
