Folder structure:
Parent folder: trunk
doc - Automatic code documentation via Doxygen
hal - Hardware Abstraction layer
kern - custom linux lernel modules
app - Application software
matlab - network connection to matlab
sig - signal processing layer software

Kernel structure
Parent folder: rpi
linux-3.18.16
linux-latest
linux-rt-rpi
patches
tools

 

rpi - preconfigured firmware for raspberry Pi B+
tst - contains test data and codde to test the module. this folder is under each and every driver module.

To regenerate the code documentation to the latest version, run doxygen in the folder impl/trunk/doc/

Zauber commands:
Enter directory to compare: cd blah
find ./ -name *.c -exec  diff -U0 {} ../helikopter-raspberry-ChrisWork/{} \;

This will give you all the details of the file currently differing from master.