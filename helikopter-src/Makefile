# Invoke this file by using the command make MAKECMDGOALS=target

PWD=$(shell pwd)
TOP=$(PWD)/../..
export TOP

# Default target.
all: begin makeversion gccversion product end

begin:
	@echo "----------------- geht los ----------------------"
	@echo $(TOP)

# Display make version information.
makeversion : 
	@make --version

# Display compiler version information.
gccversion : 
	@$(CC) --version

end:
	@echo
	@echo "----------------- fertig ----------------------"

product:ADC BATTERY REMOTECONTROLLER GPIO GPS IMU LASER LLD_IF MOTOR MATLAB SIG MAIN 

MAIN:FORCE
	cd MAIN; make all

ADC:FORCE
	cd hal/ADC; make all

BATTERY:FORCE
	cd hal/BATTERY; make all

REMOTECONTROLLER:FORCE
	cd hal/REMOTECONTROLLER; make all

GPIO:FORCE
	cd hal/GPIO; make all

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
	cd hal/REMOTECONTROLLER; make clean
	cd hal/GPIO; make clean
	cd hal/GPS; make clean
	cd hal/IMU; make clean
	cd hal/LASER; make clean
	cd hal/LLD_IF; make clean
	cd hal/MOTOR; make clean
	cd matlab; make clean
	cd sig; make clean
	cd MAIN; make clean
	
