#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

/**
* struct malloc_header - stores info about malloc'd block
* @span: distance to next header
* @stored: bytes currently stored in this header
*/
typedef struct malloc_header
{
	size_t span;
	size_t stored;
} m_header;

void *naive_malloc(size_t size);

void *_malloc(size_t size);

void _free(void *ptr);

void *_calloc(size_t nmemb, size_t size);

#endif /* _MALLOC_H_ */
