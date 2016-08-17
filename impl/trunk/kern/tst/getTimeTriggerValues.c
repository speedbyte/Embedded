#include <stdio.h>
#include <fcntl.h>

/* structured data delivered by the kernel module timeTrigger */
struct timedInterrupt{
    int         irqNum;
    unsigned long    timer;
};

int main( int argc, char **argv, char **envp )
{
    int fd;

    struct timedInterrupt timerStruct;
    unsigned long oldTime=0;

    fd = open( "/dev/timeTrigger10ms", O_RDONLY );
    if (fd<0) {
        perror("/dev/timeTrigger10ms");
        return -1;
    }
    while (1) {
        unsigned long recvBytes=0;

    /* read will block until a new timer tigger will arrive */
        recvBytes = read( fd, &(timerStruct), sizeof(timerStruct) );
        printf("interrupts: %d, time elapsed: %7lu us @ %10lu\n", 
        timerStruct.irqNum, 
        timerStruct.timer - oldTime, 
        timerStruct.timer);
    oldTime=timerStruct.timer;
    }
    return 0;
}
