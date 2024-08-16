# Allocator
This is an investigation into what libc does under the hood when calling malloc and free. Most of this code is inspired from:
- https://sploitfun.wordpress.com/2015/02/10/understanding-glibc-malloc/ 
- https://www.youtube.com/watch?v=sZ8GJ1TiMdk 
- https://azeria-labs.com/heap-exploitation-part-1-understanding-the-glibc-heap-implementation/
- https://azeria-labs.com/heap-exploitation-part-2-glibc-heap-free-bins/ 
- https://youtube.com/shorts/ZbU-lokFhfY?si=qBZQYKBKGsyow7l8 
- https://developer.ibm.com/articles/pa-dalign/

Limitations Of This Project:
- The pointers to the heap can only be located in the heap and the stack.
- No packed structures that mess up the memory alignment
- No Tricks that obscure the pointers (XOR linked lists because they alter the bits of the pointers)
- Probably only works on x86_64
- Only works on machines where the heap is allocated increasingly instead of decreasingly
- Probably works when compiled with MSBUILD
