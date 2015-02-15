#include "new_section.h"

// ask to the phone application for the different items from the menus

void request_menus(void)
{
  DictionaryIterator *it;

  app_message_outbox_begin(&it);
  dict_write_uint8(it, 0, REQUEST_SITES);
  dict_write_end(it);
  app_message_outbox_send();
}