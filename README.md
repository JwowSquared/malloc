# malloc
malloc is a project for Holberton which emulates the glibc `malloc`, `free`, `calloc`, and `realloc`.
the `naive_malloc` function included was a stepping stone task working towards a fully functional malloc.
Here is how the other 4 work.

## `_malloc`
`void *_malloc(size_t size);`
Taking a given size, `_malloc` will return a pointer to a memory area of the desired size, or NULL on failure.
This is accomplished by using `sbrk` to move the program break, effectively giving the program more memory to hold the requested area. However, there is no reason to call `sbrk` with every `_malloc` call, and so the program break is moved forward in increments of 4096 bytes, and a pseudo linked list is maintained to parse through the heap. `_malloc` will look through this list to see if there is an available region of memory for the request. The program break is only incrememted by a further 4096 bytes if a new entry in the list is required, and that entry is too big to fit in the remaining space.

## `_free`
`void _free(void *ptr);`
`_free` accepts memory addresses that have been previously malloc'd (with `_malloc` only). `_free` will ignore a NULL pointer, but if a valid pointer is passed that has not been previously malloc'd, behavior is undefined (but likely catastrophic). `_free` simply updates the malloc header associated with that memory region in the malloc list, marking that region as available. This allows for a new `_malloc` call to potentially use this memory region again.

## `_calloc`
`void  *_calloc(size_t nmemb, size_t size);`
`_calloc` is built using `_malloc`. All this function does is calls `_malloc` with nmemb * size, and then calls `memset` on the memory region, setting all bytes to 0.

## `_realloc`
`void *_realloc(void *ptr, size_t size);`
`_realloc` is build using `_malloc` and `_free`. If ptr is NULL, `_realloc` is equivalent to `_malloc(size)`. If size is 0, `_realloc` is equivalent to `_free(ptr)`. Otherwise, this function checks the malloc header to see if the current region referred to by ptr has enough space to hold the new size. If yes, the header is updated, and `_realloc` returns. If no, then a new region is defined with `_malloc` with the new size, and then `memcpy` is used to move the old memory to the new location, before finally calling `_free` on the old region and returning a pointer to the new region.

## Why don't `_malloc` memory leaks appear on valgrind?
Good question. Valgrind has a specific relationship with glibc malloc and free, and a "memory leak" according to valgrind is simply a malloc'd area that has not been free'd. This may sound obvious, but this means that even though you may have written an example program using `_malloc` and `_free` that you would expect to leak memory, valgrind is unable to detect this by default. There is a lengthy process of informing valgrind of our custom `_malloc` and our custom heap, but this is beyond the scope of my malloc project. If you want to test for memory leaks in a project, just use the real malloc. However, if your program leaks memory, what that means for `_malloc` is the program break will extend and extend until it cannot extend anymore, causing `_malloc` to return NULL, which can be easily tested.

## Thank You
Thanks for checking out my malloc project. I had fun, and I hope you learned a thing or two.
