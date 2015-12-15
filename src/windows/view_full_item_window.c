#include <stdio.h>
#include <windows/view_full_item_window.h>

/*********************HINT*************************
typedef struct {
  char title[35];
  char descr[100];
  char clnum[5];
  char subje[5];
  int t_hrs;
  int t_min;
  int compl;
  int e_hrs;
  int e_min;
} ToDo;
**************************************************/

/**************************************************
Define windows
**************************************************/
static Window *s_menu_window;

/**************************************************
Define layers
**************************************************/
static TextLayer *s_text_layer;

static ToDo todoitem;

/**************************************************
Creates main window layers
**************************************************/
static void window_load(Window *window) {
  static char s_txt[200] = "";
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  snprintf(s_txt, sizeof(char)*200, "%s %s\n%s\n\n%s\n\n%dh %dm", todoitem.subje, todoitem.clnum, todoitem.title, todoitem.descr, todoitem.t_hrs, todoitem.t_min);
  
  s_text_layer = text_layer_create(bounds);
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentLeft);
  text_layer_set_text(s_text_layer, s_txt);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

/**************************************************
Destroys main window layers
**************************************************/
static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
  
  window_destroy(window);
  s_menu_window = NULL;
}

/**************************************************
create main window if it doesn't exist
**************************************************/
void view_full_item_window_push(ToDo item) {
  todoitem = item;
  
  if(!s_menu_window) {
    s_menu_window = window_create();
    window_set_background_color(s_menu_window, GColorWhite);
    window_set_window_handlers(s_menu_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload
    });
  }
  window_stack_push(s_menu_window, true);
  
  return;
}
