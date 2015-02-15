#include "new_section.h"

static void	insert_back(t_item **list, t_item *elem)
{
	if (!*list)
		*list = elem;
	else
		insert_back(&(*list)->next, elem);
}
	
static void insert_item(const char *string, const int i)
{
	insert_back(&menu_sections->item, new_item(string, i));
}

void init_first_section(void)
{
	unsigned int			i = 0;

	menu_sections = new_section("Menu Principal");
	insert_item("Lumière", i);
	insert_item("Réveil", ++i);
	insert_item("Volet", ++i);
	insert_item("Matériel", ++i);
	insert_item("Chauffage", ++i);
	insert_item("Porte", ++i);
}