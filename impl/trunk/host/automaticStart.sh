#! /bin/sh
### BEGIN INIT INFO

# Short-Description: Starts myProgramm
# Description:
### END INIT INFO

case "$1" in
start)
echo "noip wird gestartet"
# Starte Programm
/usr/local/bin/myProgramm
;;
stop)
echo "myProgramm wird beendet"
# Beende Programm
killall myProgramm 
;;
*)
echo "Benutzt: /etc/init.d/myAutostartScript {start|stop}"
exit 1
;;
esac

exit 0
