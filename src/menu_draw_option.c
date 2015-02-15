#include "new_section.h"

void menu_draw_option(GContext* ctx, char* option, char* value) 
{
	graphics_context_set_text_color(ctx, GColorBlack);
	graphics_draw_text(ctx, option, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(4, 0, 136, 28), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
	graphics_draw_text(ctx, value, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(4, 5, 136, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
}