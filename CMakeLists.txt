cmake_minimum_required(VERSION 2.4)

project( Allocator )

set( compile main.c heap.c )

add_executable( Allocator ${compile} )