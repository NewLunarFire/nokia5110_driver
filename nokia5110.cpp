#include "n5110.h"

extern DigitalOut led1, led2, led3, led4;
extern char surface[6][84];

n5110_t* n5110_create() {
	return (n5110_t*)malloc(sizeof(n5110_t));
}

void n5110_setPins(n5110_t* dev, PinName mosi, PinName clk, PinName cs, PinName dc, PinName rst) {
	dev->port = new SPI(mosi, NC, clk);
	dev->port->format(8, 0);
	dev->port->frequency(1000000);
	
	dev->cs = new DigitalOut(cs);
	dev->dc = new DigitalOut(dc);
	dev->rst = new DigitalOut(rst);
	
	*(dev->cs) = 1;
	*(dev->dc) = 0;
	*(dev->rst) = 1;
}

//Reset module
void n5110_reset(n5110_t* dev) {
	*(dev->rst) = 0;
	wait_us(100);
	*(dev->rst) = 1;
}


void n5110_sendCommand(n5110_t* dev, int cmd) {
	*(dev->dc) = 0;
	*(dev->cs) = 0;
	dev->port->write(cmd);
	wait_us(100);
	*(dev->cs) = 1;
}

void n5110_init(n5110_t* dev) {
	n5110_sendCommand(dev, 0x21); // Active, Horizontal, Extended Instructions
	n5110_sendCommand(dev, 0xBF); // Set LCD Vop
	n5110_sendCommand(dev, 0x04); // Set Temp coefficent
	n5110_sendCommand(dev, 0x14); // LCD bias mode 1:48 (try 0x13)
	n5110_sendCommand(dev, 0x20); // Active, Horizontal, Normal Instructions
	n5110_sendCommand(dev, 0x0C); // Set Display control, Normal Mode
}

void n5110_sendData(n5110_t* dev, char* surface) {
	*(dev->dc) = 1;
	*(dev->cs) = 0;
	
	for(int i = 0; i < N5110_SURFACE_BYTES; i++) {
		dev->port->write(surface[i]);
		wait_us(10);
	}
	
	*(dev->cs) = 1;
}
