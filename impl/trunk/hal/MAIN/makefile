include ../makeopts

# we assume that a file called all or clean is never present in the folder.
# if something like this is available, then one can use .PHONY: all to still
# be able to run the recipe.

IMAGE=HELIKOPTER
OBJS=main.obj

all:$(IMAGE)

.PHONY : $(LOUT)
$(IMAGE):$(OBJS)
	@echo Start Linking
	@echo $(CURDIR)	
	$(LN) $(LIBS) $(OBJS) -o $(IMAGE).out
	
.PHONY : $(OBJS)
$(OBJS): %.obj : %.c
	$(CC) $(CFLAGS) $(CINC) -o $@ $<

clean:
	@echo Cleaning	
	rm -f $(OBJS)
	rm -f $(IMAGE).map
	rm -f $(IMAGE).out


#	$(RL) $(LIBRARY)
#$(@:.obj=.c)
#-MT"$@"
