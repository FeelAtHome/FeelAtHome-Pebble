#include "new_section.h"
	
void add_item_to_section(uint32_t id, char *name)
{
	t_item			*new;
	t_item			*tmp;
	
	tmp = menu_sections->item;
	new = new_item(name, id);
	while (tmp->name)
		tmp = tmp->next;
	tmp = new;
}