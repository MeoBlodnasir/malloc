#include "malloc.h"

void *reallok(void *ptr, size_t size)
{
	void *ret;
	t_area *area;
	ret = mallok(size);
	area = ret - sizeof(t_area);
	ft_memcpy(ret, ptr, area->size);
	freek(ptr);
	return ret;
}
