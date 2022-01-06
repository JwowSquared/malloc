#include "malloc.h"

/**
* naive_malloc - malloc that only allocates size memory
* @size: bytes to allocate
*
* Return: address of new memory location
*/
void *naive_malloc(size_t size)
{
	static void *start;
	static void *end;
	static size_t avail_bytes;
	size_t h_size = sizeof(size_t), p_size = 4096;
	void *out;

	if (start == NULL)
		start = sbrk(0);

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
			out = (char *)out + h_size + *(size_t *)out;
		}
		if (out == end)
		{
			out = (char *)out + h_size + *(size_t *)out;
			end = out;
		}
	}
	else
		end = out;

	*(size_t *)out = size;
	return ((char *)out + h_size);
}
