#include <stdio.h>
#include <fcntl.h>

int main( int argc, char **argv, char **envp )
{
    int fd;

    /* structured data received from kernel driver output */
    struct outputStruct{
        int                                     irqNum;
        unsigned long timer_l;
        unsigned long timer_h;
    };

    struct outputStruct localOutputBlock;

    unsigned long long newTime = 0;
    unsigned long long oldTime = 0;

    /* open character file handler of kernel driver ppmDemux */
    fd = open( "/dev/gpioirq24", O_RDONLY );
    if (fd<0) {
        perror("/dev/gpioirq24");
        return -1;
    }

    while (1) {
        unsigned long recvBytes=0;

        /* evaluate only lower part of counter value (wrap around every
         * ~4.2 seconds is sufficient for this testing approach)
         */
        recvBytes = read( fd,&(localOutputBlock), sizeof(struct outputStruct) );
        newTime = (unsigned long long)localOutputBlock.timer_l;
        printf("interrupts: %d, delta: %llu us\n",localOutputBlock.irqNum, (newTime - oldTime) );
        oldTime = newTime;
    }
    return 0;
}


