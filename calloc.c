#include "malloc.h"

/**
* _calloc - calloc replica
* @nmemb: number of elements to allocate
* @size: size of element
*
* Return: address of new memory location
*/
void *_calloc(size_t nmemb, size_t size)
{
	char *out;

	out = _malloc(nmemb * size);
	if (out == NULL)
		return (NULL);

	return (memset(out, 0, nmemb * size));
}
