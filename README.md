# CPP-KeyLogger (meant to be used for pen testing only)
simple keylogger that sends any collected information back to the penetration tester

# Compilation instructions:

In order for the compiler to include the windows socket library, one more thing needs to be done.

In DevC++, go to "Tools", click "Compiler options" and in the bottom box type " -lws2_32"

**USAGE:

install netcat:

https://eternallybored.org/misc/netcat/

nc.exe -lvp 5555 (or the port you specified) <- For Windows

nc -lvp 5555 (or the port you specified) <- For Linux
