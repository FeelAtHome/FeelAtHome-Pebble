#include "new_section.h"

t_section 				*new_section(void const *content)
{
	t_section			*new;
	
	if (!(new = (t_section*)malloc(sizeof(t_section))))
		return (NULL);
	if (!content)
		new->name = NULL;
	else
	{
		if (!(new->name = (char*)malloc(strlen(content))))
			return (NULL);
		memcpy(new->name, content, strlen(content));
	}
	new->item = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}