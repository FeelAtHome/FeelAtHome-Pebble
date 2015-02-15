#include "new_section.h"
	
void		add_new_section_to_menu(t_section **menu, t_section *new)
{
	if (!new || !menu)
		return ;
	new->next = *menu;
	*menu = new;
}