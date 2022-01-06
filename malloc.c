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
		while (out <= end)
		{
			current = (m_header *)out;
			if (current->stored == 0)
				break;
			out += h_size + current->span;
		}
		end = out;
	}
	else
		end = out;

	current = (m_header *)out;
	if (out == end)
		current->span = size;
	current->stored = size;
	avail_bytes = avail_bytes - size - h_size;
	return (out + h_size);
}
