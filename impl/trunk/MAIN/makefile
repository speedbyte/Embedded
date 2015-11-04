include ../makeopts

# we assume that a file called all or clean is never present in the folder.
# if something like this is available, then one can use .PHONY: all to still
# be able to run the recipe.

TARGET=HELIKOPTER
OBJS=main.obj

all:sizebefore build sizeafter readelf

# Display size of file.
ELFSIZE 	= $(SIZE) -A $(TARGET).elf
BINSIZE 	= $(SIZE) --target=$(FORMAT) $(TARGET).bin

sizebefore:
	@if [ -f $(TARGET).elf ]; then echo; echo "---size before----"; $(ELFSIZE); $(BINSIZE); echo; fi

sizeafter:
	@if [ -f $(TARGET).elf ]; then echo; echo "---size after----"; $(ELFSIZE); $(BINSIZE); echo; fi

build: elf bin obd sym

elf: $(TARGET).elf
bin: $(TARGET).bin 
obd: $(TARGET).obd
sym: $(TARGET).sym

.PHONY : $(LOUT)
%.elf:$(OBJS)
	@echo Start Linking
	@echo $(CURDIR)	
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS)  -o $@
#Strip debug symbols for production code
#	$(OBJCOPY) --strip-debug  $@ $@

# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo
	@echo $(MSG_FLASH) $@
# just to show the use of patsubst
	$(OBJCOPY) -O $(FORMAT) $< $(patsubst %.bin,%.bin,$@)         

# Create extended listing file from ELF output file.
# testing: option -C
%.obd: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@
#	$(OBJDUMP) -i > $(patsubst %.obd,%.lsq,$@) 
	

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo "Creating Symbol Table" $@
	$(NM) -n $< > $@
	
.PHONY : $(OBJS)
$(OBJS): %.obj : %.c
	$(CC) $(CFLAGS) $(CINC) -o $@ $<

readelf:
	@if [ -f $(TARGET).elf ]; then echo; echo "elf file header"; $(READELF) -e $(TARGET).elf; echo; fi

clean:
	@echo Cleaning	
	rm -f $(OBJS)
	rm -f $(TARGET).map
	rm -f $(TARGET).bin
	rm -f $(TARGET).sym
	rm -f $(TARGET).obd
	rm -f $(TARGET).elf
	rm -f $(TARGET).out

#	$(RL) $(LIBRARY)
#$(@:.obj=.c)
#-MT"$@"
