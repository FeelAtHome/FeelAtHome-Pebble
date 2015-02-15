#include "new_section.h"
	
t_item 				*new_item(void const *content, unsigned int id)
{
	t_item			*new;
	
	if (!(new = (t_item*)malloc(sizeof(t_item))))
		return (NULL);
	if (!content)
		new->name = NULL;
	else
	{
		if (!(new->name = (char*)malloc(strlen(content))))
			return (NULL);
		memcpy(new->name, content, strlen(content));
	}
	new->id = (id ? id : 0);
	new->value = "OFF";
	new->next = NULL;
	return (new);
}