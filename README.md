Hi, this is an investigation into what GLIBCHEAP does under the hood when calling malloc and free. Most of this code is inspired from:
https://sploitfun.wordpress.com/2015/02/10/understanding-glibc-malloc/ 
https://www.youtube.com/watch?v=sZ8GJ1TiMdk 
https://azeria-labs.com/heap-exploitation-part-1-understanding-the-glibc-heap-implementation/
https://azeria-labs.com/heap-exploitation-part-2-glibc-heap-free-bins/ 
https://youtube.com/shorts/ZbU-lokFhfY?si=qBZQYKBKGsyow7l8 
https://developer.ibm.com/articles/pa-dalign/