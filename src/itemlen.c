#include "new_section.h"

size_t			itemlen(t_item **lst, size_t nb)
{
	return (!*lst ? nb : itemlen(&(*lst)->next, nb + 1));
}