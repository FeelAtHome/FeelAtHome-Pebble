#include "new_section.h"
#define menu_layer_reload_data_and_mark_dirty(layer) menu_layer_reload_data(layer); layer_mark_dirty(menu_layer_get_layer(layer));
static Window *window;

// This is a menu layer
// You have more control than with a simple menu layer
static MenuLayer *menu_layer;

// Menu items can optionally have an icon drawn with them
static GBitmap *menu_icons[NUM_MENU_ICONS];

static int current_icon = 0;

// You can draw arbitrary things in a menu item such as a background
static GBitmap *menu_background;


// A callback is used to specify the amount of sections of menu items
// With this, you can dynamically add and remove sections
static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
//  	displayed = &menu_sections->item;
	return NUM_MENU_SECTIONS;
}

// Each section has a number of items;  we use a callback to specify this
// You can also dynamically add and remove items using this
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return itemlen(&menu_sections->item, 0);
}

// A callback is used to specify the height of the section header
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  // This is a define provided in pebble.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
    case 0:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, menu_sections->name);
	  break;
  }
}

static void print_item(GContext *ctx, const Layer *cell_layer, t_item **lst, int row)
{
	if (lst)
	{
		if ((unsigned int)row == (*lst)->id)
			menu_draw_option(ctx, (*lst)->name, (*lst)->value);
		else
			print_item(ctx, cell_layer, &(*lst)->next, row);
	}
}

// This is the menu item draw callback where you specify what each item should look like
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {	
	if (*menu_sections->item->name)
		print_item(ctx, cell_layer, &menu_sections->item, cell_index->row);

}


static void		change_value(t_item **lst, int row)
{
	if (!lst)
		return ;
	if ((unsigned int)row == (*lst)->id)
		(*lst)->value = strcmp((*lst)->value, "OFF") ? "OFF" : "ON";
	else
		change_value(&(*lst)->next, row);
}

// Here we capture when a user selects a menu item
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
	change_value(&menu_sections->item, cell_index->row);
	layer_mark_dirty(menu_layer_get_layer(menu_layer));
}

// This initializes the menu upon window load
void window_load(Window *window) {

  // And also load the background
  menu_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND_BRAINS);

  // Now we prepare to initialize the menu layer
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(menu_layer, window);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

void window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(menu_layer);

  // Cleanup the menu icons
  for (int i = 0; i < NUM_MENU_ICONS; i++) {
    gbitmap_destroy(menu_icons[i]);
  }

  // And cleanup the background
  gbitmap_destroy(menu_background);
}

void delete_site_to_menu(uint32_t id, char *name)
{
	
}

int main(void) {
  window = window_create();

	// initalize menus request
//	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
 // request_menus();
	init_first_section();
	// register the function used anytime a message is received
 // app_message_register_inbox_received(received_handler);
  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);

  app_event_loop();

  window_destroy(window);
}