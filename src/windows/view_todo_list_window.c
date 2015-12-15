#include <stdio.h>
#include <windows/view_todo_list_window.h>
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
static MenuLayer *s_menu_layer;

/**************************************************
Define list of todo items
**************************************************/
ToDo item_arr[] = {
  {"Lab #6", "Chapter 16, #1, 3, 5a", "321", "MTH", 2, 0, 0, 0, 0},
  {"Homework #3", "Chapter 12, #3, 4b, 5de, 6, 7, 11", "321", "MTH", 2, 30, 0, 0, 0},
  {"OTP Implementation", "OTP and Socket communication implementation in C", "344", "CS", 6, 0, 0, 0, 0}
};

/**************************************************
Hides error layer if visible and selects menu
**************************************************/
static void select_callback(struct MenuLayer *s_menu_layer, MenuIndex *cell_index, void *callback_context) {
  view_full_item_window_push(item_arr[cell_index->row]);

  return;
}

/**************************************************
Returns number of rows in main menu
**************************************************/
static uint16_t get_section_count_callback(struct MenuLayer *menulayer, uint16_t section_index, void *callback_context) {
  int rows = sizeof(item_arr) / sizeof(ToDo);
  
  return rows;
}

/**************************************************
Draws list rows
**************************************************/
static void draw_row_handler(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
  static char s_fulltxt[20] = "";
  
  snprintf(s_fulltxt, sizeof(char)*20, "%s %s - %s", item_arr[cell_index->row].subje, item_arr[cell_index->row].clnum, item_arr[cell_index->row].title);
  
  menu_cell_basic_draw(ctx, cell_layer, NULL, s_fulltxt, NULL);
}

/**************************************************
Creates main window layers
**************************************************/
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_rows = get_section_count_callback,
    .draw_row = draw_row_handler,
    .select_click = select_callback
  });
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

/**************************************************
Destroys main window layers
**************************************************/
static void window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
  
  window_destroy(window);
  s_menu_window = NULL;
}

/**************************************************
create main window if it doesn't exist
**************************************************/
void view_todo_list_window_push(void) {
  if(!s_menu_window) {
    s_menu_window = window_create();
    window_set_background_color(s_menu_window, GColorWhite);
    window_set_window_handlers(s_menu_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload
    });
  }
  window_stack_push(s_menu_window, true);
}
