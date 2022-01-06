#include "malloc.h"

/**
* _realloc - realloc replica
* @ptr: element to re allocate
* @size: new size of element
*
* Return: address of new memory location
*/
void *_realloc(void *ptr, size_t size)
{
	char *out;
	m_header *current;
	size_t old_size;

	if (ptr == NULL)
		return (_malloc(size));

	if (size == 0)
	{
		_free(ptr);
		return (NULL);
	}

	current = (m_header *)ptr;
	current--;
	old_size = current->stored;

	if (old_size >= size)
	{
		current->stored = size;
		return (ptr);
	}

	out = _malloc(size);
	if (out == NULL)
		return (NULL);
	memcpy(out, ptr, old_size);

	_free(ptr);

	return (out);
}
