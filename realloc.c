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

	current = (m_header *)ptr;
	current--;
	old_size = current->stored;

	_free(ptr);

	out = _malloc(size);
	if (out == NULL)
		return (NULL);

	return (memcpy(out, ptr, old_size));
}
