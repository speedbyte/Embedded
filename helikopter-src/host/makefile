include ../makeopts-host

# we assume that a file called all or clean is never present in the folder.
# if something like this is available, then one can use .PHONY: all to still
# be able to run the recipe.


OBJS-HOST=read-udp-host.o

#OS='uname -o'
ifeq ($(OS),Cygwin)
	IMAGE-HOST=READ-UDP-CYGWIN
else
	IMAGE-HOST=READ-UDP-LINUX
endif


all-host:elf

elf:$(IMAGE-HOST).elf

%.elf:$(OBJS-HOST)
	$(LD) $(LDFLAGS) $(OBJS-HOST) $(LIBS-HOST)  -o $@
	
.PHONY : $(OBJS-HOST)
$(OBJS-HOST): %.o : %.c
	@echo $(OS)
	$(CC) $(CFLAGS) $(CINC) -o $@ $<

clean-host:
	@echo Cleaning	
	rm -f $(OBJS-HOST)
	rm -f $(IMAGE-HOST).elf


