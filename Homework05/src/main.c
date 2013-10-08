#define GPIO_PIN_INA 30 // 0:30
#define GPIO_PIN_INB 31 // 0:31
#define GPIO_PIN_OUTA 16 // 1:48
#define GPIO_PIN_OUTB 3 // 0:3

#define GPIO0_START_ADDR 0x44e07000
#define GPIO0_END_ADDR 0x44e09000
#define GPIO0_SIZE (GPIO0_END_ADDR - GPIO0_START_ADDR)

#define GPIO1_START_ADDR 0x4804C000
#define GPIO1_END_ADDR 0x4804e000
#define GPIO1_SIZE (GPIO1_END_ADDR - GPIO1_START_ADDR)

#define GPIO_OE 0x134
#define GPIO_DATAIN 0x138
#define GPIO_SETDATAOUT 0x194
#define GPIO_CLEARDATAOUT 0x190

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>    // Defines signal-handling functions (i.e. trap Ctrl-C)

int keepgoing = 1;
void signal_handler(int sig)
{
    printf( "\nCtrl-C pressed, cleaning up and exiting...\n" );
    keepgoing = 0;
}

int main()
{
    volatile void *gpio0_addr;
    volatile unsigned int *gpio0_oe_addr;
    volatile unsigned int *gpio0_datain;
    volatile unsigned int *gpio0_setdataout_addr;
    volatile unsigned int *gpio0_cleardataout_addr;

    // Set the signal callback for Ctrl-C
    signal(SIGINT, signal_handler);

    int fd0 = open("/dev/mem", O_RDWR);

    printf("Mapping %X - %X (size: %X)\n", GPIO0_START_ADDR, GPIO0_END_ADDR,
                                           GPIO0_SIZE);

    gpio0_addr = mmap(0, GPIO0_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd0,
                        GPIO0_START_ADDR);

    gpio0_oe_addr           = gpio0_addr + GPIO_OE;
    gpio0_datain            = gpio0_addr + GPIO_DATAIN;
    gpio0_setdataout_addr   = gpio0_addr + GPIO_SETDATAOUT;
    gpio0_cleardataout_addr = gpio0_addr + GPIO_CLEARDATAOUT;

    if(gpio0_addr == MAP_FAILED) {
        printf("Unable to map GPIO\n");
        exit(1);
    }

    volatile void *gpio1_addr;
    volatile unsigned int *gpio1_oe_addr;
    volatile unsigned int *gpio1_datain;
    volatile unsigned int *gpio1_setdataout_addr;
    volatile unsigned int *gpio1_cleardataout_addr;

    // Set the signal callback for Ctrl-C
    signal(SIGINT, signal_handler);

    int fd1 = open("/dev/mem", O_RDWR);

    printf("Mapping %X - %X (size: %X)\n", GPIO1_START_ADDR, GPIO1_END_ADDR,
                                           GPIO1_SIZE);

    gpio1_addr = mmap(0, GPIO1_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd1,
                        GPIO1_START_ADDR);

    gpio1_oe_addr           = gpio1_addr + GPIO_OE;
    gpio1_datain            = gpio1_addr + GPIO_DATAIN;
    gpio1_setdataout_addr   = gpio1_addr + GPIO_SETDATAOUT;
    gpio1_cleardataout_addr = gpio1_addr + GPIO_CLEARDATAOUT;

    if(gpio1_addr == MAP_FAILED) {
        printf("Unable to map GPIO\n");
        exit(1);
    }

#define ReadGPIO(_bus, _pin) (*(_bus##_datain) & _pin)
#define SetGPIOHigh(_bus, _pin) (*(_bus##_setdataout_addr) = _pin)
#define SetGPIOLow(_bus, _pin) (*(_bus##_cleardataout_addr) = _pin)

    while (keepgoing)
    {
        if (ReadGPIO(gpio1, GPIO_PIN_INA))
            SetGPIOHigh(gpio0, GPIO_PIN_OUTA);
        else SetGPIOLow(gpio0, GPIO_PIN_OUTA);

        if (ReadGPIO(gpio0, GPIO_PIN_INB))
            SetGPIOHigh(gpio0, GPIO_PIN_OUTB);
        else SetGPIOLow(gpio0, GPIO_PIN_OUTB);
    }

    return 0;
}