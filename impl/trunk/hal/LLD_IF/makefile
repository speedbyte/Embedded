include ../makeopts

# we assume that a file called all or clean is never present in the folder.
# if something like this is available, then one can use .PHONY: all to still
# be able to run the recipe.

OBJS=LLD_I2C.obj LLD_UART.obj
LIBRARY=LLD_IF.lib

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
