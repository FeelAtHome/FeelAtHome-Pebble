#include <pebble.h>
#include "globals.h"
#include "libft.h"
#include "progress_bar.h"

int count;
Window *window;
TextLayer *text;
ActionBarLayer *action_bar;
ProgressBarLayer *progress_bar;

void simple_send_msg(t_message_out_type type)
{
  DictionaryIterator *iter;

  app_message_outbox_begin(&iter);
  dict_write_uint8(iter, 0, (unsigned char)type);
  app_message_outbox_send();
}

void update_mytext_layer()
{
  ProgressBarData *data = (ProgressBarData*)layer_get_data(progress_bar);
  char *str = (char*)text_layer_get_text(text);
  text_layer_set_text(text, ft_itoa(data->value));
  free(str);
}

void my_plus_click_handler(ClickRecognizerRef ref, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Next");
  ProgressBarData* data = (ProgressBarData*)layer_get_data(progress_bar);
  if (data->value >= 100)
    return;
  count = data->value;
  progress_bar_layer_set_value(progress_bar, ++count);
  update_mytext_layer();
}

void my_long_plus_click_handler(ClickRecognizerRef ref, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Next");
  ProgressBarData *data = (ProgressBarData*)layer_get_data(progress_bar);
  if (data->value >= 100)
    return;
  count = 100;
  progress_bar_layer_set_value(progress_bar, count);
  update_mytext_layer();
}

void my_minus_click_handler(ClickRecognizerRef ref, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Previous");
  ProgressBarData* data = (ProgressBarData*)layer_get_data(progress_bar);
  if (data->value <= 0)
    return;
  count = data->value;
  progress_bar_layer_set_value(progress_bar, --count);
  update_mytext_layer();
}

void my_long_minus_click_handler(ClickRecognizerRef ref, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Previous");
  ProgressBarData *data = (ProgressBarData*)layer_get_data(progress_bar);
  if (data->value <= 0)
    return;
  count = 0;
  progress_bar_layer_set_value(progress_bar, count);
  update_mytext_layer();
}

void click_config_provider(void *content) {
  //window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) my_minus_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 30, (ClickHandler) my_minus_click_handler);
  window_multi_click_subscribe(BUTTON_ID_DOWN, 3, 0, 0, false, (ClickHandler) my_long_minus_click_handler);
  //window_long_click_subscribe(BUTTON_ID_DOWN, 0, my_long_minus_click_handler, NULL);
  //window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) my_plus_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_UP, 30, (ClickHandler) my_plus_click_handler);
  window_multi_click_subscribe(BUTTON_ID_UP, 3, 0, 0, false, (ClickHandler) my_long_plus_click_handler);
  //window_long_click_subscribe(BUTTON_ID_UP, 0, my_long_plus_click_handler, NULL);
}

void set_song_info(char *title, char *artist)
{

}

void in_received_handler(DictionaryIterator *received, void *context)
{
  char *title;
  char *artist;

  switch ((t_message_in_type)dict_find(received, 0)->value->uint8)
  {
    case SONG_INFO:
      title = dict_find(received, 1)->value->cstring;
      artist = dict_find(received, 2)->value->cstring;
      set_song_info(title, artist);
      break;
  }
}

void in_dropped_handler(AppMessageResult reason, void *context) {
  // Message was d:ropped by OS (WTF WHY ?) 
}

void out_sent_handler(DictionaryIterator *sent, void *context) {
  // Out message delivered 
}

void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  // Out message failed 
}

void handle_init(void) {
	// Create a window and an action bar layer
	window = window_create();

  /*app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_sent(out_sent_handler);
  app_message_register_outbox_failed(out_failed_handler);*/

  progress_bar = progress_bar_layer_create(GRect(4, 118, 115, 8));
	progress_bar_layer_set_orientation(progress_bar, ProgressBarOrientationHorizontal);
	progress_bar_layer_set_range(progress_bar, 0, 100);
  progress_bar_layer_set_value(progress_bar, 50);
	progress_bar_layer_set_frame_color(progress_bar, GColorBlack);
	progress_bar_layer_set_bar_color(progress_bar, GColorBlack);
	layer_add_child(window_get_root_layer(window), progress_bar);

  text = text_layer_create(GRect(54, 99, 64, 16));
  //char *text_content = malloc(sizeof(char) * 3);
  char *text_content = ft_itoa(count);
  //text_content[0] = '5';
  //text_content[1] = '0';
  //text_content[2] = '\0';
	text_layer_set_text(text, text_content);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text));

  action_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(action_bar, window);
  action_bar_layer_set_click_config_provider(action_bar,
                                             click_config_provider);
  //action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, &my_icon_previous);
  //action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, &my_icon_next);

	// Push the window
	window_stack_push(window, true);
  free(text_content);
}

void handle_deinit(void) {
	// Destroy the action bar
	action_bar_layer_destroy(action_bar);
	progress_bar_layer_destroy(progress_bar);

	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}