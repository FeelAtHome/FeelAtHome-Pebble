#pragma once

#ifndef NEW_SECTION_H
# define NEW_SECTION_H
	
#include <pebble.h>	

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ICONS 1
//#define NUM_FIRST_MENU_ITEMS 2
	
typedef struct			s_item {
	char				*name;
	unsigned int		id;
	char				*value;
	struct s_item		*next;
}                   	t_item;

typedef struct			s_section {
	char				*name;
	struct s_item		*item;
	struct s_section	*prev;
	struct s_section	*next;
}						t_section;

typedef enum e_msgtypes {
  REQUEST_SITES = 0,
  ADD_SITE = 1,
  ADD_SECTION = 2,
  DELETE_SITE = 3,
  DELETE_SECTION = 4,
  FINISHED_SENDING = 5
}            t_msgtypes;

t_section			*menu_sections;
void 				menu_draw_option(GContext* ctx, char* option, char* value);
void 				add_item_to_section(uint32_t id, char *name);
void 				del_item_from_section(uint32_t id);
void 				init_first_section(void);
t_item 				*new_item(void const *content, unsigned int id);
t_section 			*new_section(void const *content);
void				add_new_section_to_menu(t_section **menu, t_section *new);
size_t				itemlen(t_item **lst, size_t nb);
void 				request_menus(void);

#endif