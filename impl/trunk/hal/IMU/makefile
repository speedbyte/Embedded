include ../makeopts

# we assume that a file called all or clean is never present in the folder.
# if something like this is available, then one can use .PHONY: all to still
# be able to run the recipe.

OBJS=accMag/accMag.o barometer/barometer.o gyro/Gyro.o Lib/Hal_Lib.o imu.o
LIBRARY=IMU.lib

all:$(LIBRARY)

.PHONY : $(LIBRARY)
$(LIBRARY):$(OBJS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJS)	
	
.PHONY : $(OBJS)
$(OBJS): %.obj : %.c
	$(CC) $(CFLAGS) $(CINC) -o $@ $<

clean:
	@echo Cleaning	
	rm -f $(OBJS)
	rm -f $(LIBRARY)
