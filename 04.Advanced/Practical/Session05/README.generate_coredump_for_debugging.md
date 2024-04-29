- Compile your library with -g option to add debugging information
- mkdir -p ~/.config/apport/
- vim ~/.config/apport/settings
- add the following lines in the file:
[main]
unpackaged=true

- ulimit -c unlimited
- sudo systemctl restart apport
- Run any program with your library as follows:
LD_PRELOAD=/tmp/SysProg_Linux_STM_Tasks/HMM/libabokhalil.so ls
# This will run ls and set LD_PRELOAD variable in the environment of ls only to avoid running every thing with your library


When it crashes, run:
- ls -l /var/crash/ # you will find a file with the process name like _usr_bin_ls.1000.crash
- apport-unpack /var/crash/_usr_bin_ls.1000.crash ./ls_dump # This will unpack the core dump

The ls_dump folder will contain alot of useful information about the process at the time of the crash

run:
- gdb ls ./ls_dump/CoreDump # this will open gdb with the process coredump to view the state of the process at the crash time

run "bt" to see the backtrace of the process at the crash time


