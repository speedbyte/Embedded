include ../makeopts-host

# we assume that a file called all or clean is never present in the folder.
# if something like this is available, then one can use .PHONY: all to still
# be able to run the recipe.

IMAGE-HOST=READ-UDP
OBJS-HOST=read-udp-host.o

all-host:elf

elf:$(IMAGE-HOST).elf

%.elf:$(OBJS-HOST)
	$(LD) $(LDFLAGS) $(OBJS-HOST) $(LIBS-HOST)  -o $@
	
.PHONY : $(OBJS-HOST)
$(OBJS-HOST): %.o : %.c
	$(CC) $(CFLAGS) $(CINC) -o $@ $<

clean-host:
	@echo Cleaning	
	rm -f $(OBJS-HOST)
	rm -f $(IMAGE-HOST).elf


