#include "new_section.h"

void			items_iter(t_item *item, void (*f)(t_item *elem))
{
	if (!item || !f)
		return ;
	(*f)(item);
	items_iter(item->next, f);
}