#include "malloc.h"

/**
* _malloc - malloc replica
* @size: bytes to allocate
*
* Return: address of new memory location
*/
void *_malloc(size_t size)
{
	static char *start, *end;
	static size_t avail_bytes;
	size_t h_size = sizeof(size_t), p_size = 4096;
	char *out;

	if (start == NULL)
		start = sbrk(0);

	size += 8 - size % 8;

	while (avail_bytes < size + h_size)
	{
		if (sbrk(p_size) == (void *)-1)
			return (NULL); /* not enough memory */
		avail_bytes += p_size;
	}

	out = start;
	if (end != NULL)
	{
		while (out != end)
		{
			/* check previously malloc'd sections for viability */
			out += h_size + *(size_t *)out;
		}
		if (out == end)
		{
			out += h_size + *(size_t *)out;
			end = out;
		}
	}
	else
		end = out;

	*(size_t *)out = size;
	return (out + h_size);
}
