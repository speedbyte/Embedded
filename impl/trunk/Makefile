# Invoke this file by using the command make MAKECMDGOALS=target

# Default target.
all: begin makeversion gccversion product end


begin:
	@echo
	@echo "----------------- geht los ----------------------"

end:
	@echo
	@echo "----------------- fertig ----------------------"

# Display compiler version information.
gccversion : 
	@$(CC) --version
	
# Display make version information.
makeversion : 
	@make --version


product:ADC BATTERY GPS IMU LASER LLD_IF MOTOR MATLAB SIG MAIN

MAIN:FORCE
	cd MAIN; make all

ADC:FORCE
	cd hal/ADC; make all

BATTERY:FORCE
	cd hal/BATTERY; make all

GPS:FORCE
	cd hal/GPS; make all

IMU:FORCE
	cd hal/IMU; make all

LASER:FORCE
	cd hal/LASER; make all

LLD_IF:FORCE
	cd hal/LLD_IF; make all
	
MOTOR:FORCE
	cd hal/MOTOR; make all

MATLAB:FORCE
	cd matlab; make all

SIG:FORCE
	cd sig; make all

FORCE:

clean:
	cd hal/ADC; make clean
	cd hal/BATTERY; make clean
	cd hal/GPS; make clean
	cd hal/IMU; make clean
	cd hal/LASER; make clean
	cd hal/LLD_IF; make clean
	cd hal/MOTOR; make clean
	cd matlab; make clean
	cd sig; make clean
	cd MAIN; make clean
	