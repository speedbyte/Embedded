ifeq ($(MAKECMDGOAL),host)
include ../makeopts-host
else #ifeq ($(MAKECMDGOAL),target)
include ../makeopts
endif


# we assume that a file called all or clean is never present in the folder.
# if something like this is available, then one can use .PHONY: all to still
# be able to run the recipe.

OBJS=udpImuLib.obj udpLib.obj udpSigLib.obj
OBJS-HOST=udpImuLib.o udpLib.o udpSigLib.o

LIBRARY=MATLAB.lib
LIBRARY-HOST=MATLAB-HOST.lib

all:$(LIBRARY)

all-host:$(LIBRARY-HOST)

.PHONY : $(LIBRARY)
.PHONY : $(LIBRARY-HOST)


$(LIBRARY):$(OBJS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJS)	
	
.PHONY : $(OBJS)
$(OBJS): %.obj : %.c
	$(CC) $(CFLAGS) $(CINC) -o $@ $<

$(LIBRARY-HOST):$(OBJS-HOST)
	$(AR) $(ARFLAGS) $(LIBRARY-HOST) $(OBJS-HOST)	
	
.PHONY : $(OBJS-HOST)
$(OBJS-HOST): %.o : %.c
	$(CC) $(CFLAGS) $(CINC) -o $@ $<

clean:
	@echo Cleaning	
	rm -f $(OBJS)
	rm -f $(LIBRARY)

clean-host:
	@echo Cleaning host files	
	rm -f $(OBJS-HOST)
	rm -f $(LIBRARY-HOST)

