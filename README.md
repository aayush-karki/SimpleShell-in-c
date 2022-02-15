# SimpleShell-in-c

For simplicity, this shell only executes one program which prints a message to the screen. This program takes 3 parameters from users: first parameter ‘n’ is the number of times the message should be printed, second parameter ‘qt’ is the time in microsecond between each print, and finally the type of process—background process or a foreground process. Again, for simplicity, the background process is executed a little differently, which will be discussed in the later section. Furthermore, this shell implements the first-come-first-serve (fsfs) scheduling which is implemented using a linked-list-based queue.
This shell implements and supports the following command:
- ver: Shows details about the shell version
- help: Shows the help
- ps: Shows the living process with the given PID
- kill(PID): Ends the process with the given PID
- exec p1(n1,qt1) p2(n2,qt2) ...: Executes the programs p1, p2 ... Each program types a message for n times and it is given a time quantum of qt msec. If the parameter (&) is      given the program will be executed in the background
- exit: Exits the program


In the comming future I plan to develope this into a fullfledge shell program with a funciton to pipe, redirect, and execute external program.
