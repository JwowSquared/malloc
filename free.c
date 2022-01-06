#include "malloc.h"

/**
* _free - marks malloc headers as free
* @ptr: address to mark
*/
void _free(void *ptr)
{
	m_header *target;

	if (ptr == NULL)
		return;

	target = (m_header *)ptr;

	target--;

	target->stored = 0;
}
