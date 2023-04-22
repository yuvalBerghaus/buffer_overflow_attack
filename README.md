# buffer_overflow_attack

for windows run gcc -g -fno-stack-protector main.c -o auth -W -no-pie -lws2_32 //the -g is for debugging
now run the ./file_name // the exe file
b function_name // breakpoint
p var_name // print the details of the var (including address in the stack pointer)
