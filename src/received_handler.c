#include "new_section.h"
	
// determine what to do dependings on the key
void received_handler(DictionaryIterator *it, void *context)
{
  t_msgtypes type = dict_read_next(it)->value->uint8;
  switch (type)
  {
	case ADD_SITE:
	  add_item_to_section(dict_read_next(it)->value->uint32, dict_read_next(it)->value->cstring);
	  break;
	case DELETE_SITE:
	  del_item_from_section(dict_read_next(it)->value->uint32);
    default:
	  break;
  }
}