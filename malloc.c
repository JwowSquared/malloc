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
	size_t h_size = sizeof(m_header), p_size = 4096;
	char *out;
	m_header *current;

	size += 8 - size % 8;

	if (start == NULL)
	{
		start = sbrk(0);
		end = start;
	}

	out = start;
	while (out < end)
	{
		current = (m_header *)out;
		if (current->stored == 0 && current->span >= size)
			break;
		out += h_size + current->span;
	}

	current = (m_header *)out;
	if (out == end)
	{
		while (avail_bytes < size + h_size)
		{
			if (sbrk(p_size) == (void *)-1)
				return (NULL); /* not enough memory */
			avail_bytes += p_size;
		}
		current->span = size;
		end = out + size + h_size;
		avail_bytes = avail_bytes - size - h_size;
	}
	current->stored = size;
	return (out + h_size);
}
