#include <pebble.h>
#include <windows/completed_message_window.h>
#include <todo.h>

static Window *s_main_window;
static TextLayer *s_list_message_layer;
static int s_num;
static ToDo item_arr[] = {
  {"Lab #6", "Chapter 16, #1, 3, 5a", "321", "MTH", 2, 0, 0, 0, 0},
  {"Homework #3", "Chapter 12, #3, 4b, 5de, 6, 7, 11", "321", "MTH", 2, 30, 0, 0, 0},
  {"OTP Implementation", "OTP and Socket communication implementation in C", "344", "CS", 6, 0, 0, 0, 0}
};

static void all_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_remove(s_main_window, true);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, all_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, all_click_handler);
}

static void window_load(Window *window) {
  ToDo item = item_arr[s_num];
  static char s_message_text[200];
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  item.e_hrs = item.t_hrs;
  item.e_min = item.t_min;
  snprintf(s_message_text, sizeof(char)*200, "completed!\n%s%s\n%s\n%dh %dm", item.subje, item.clnum, item.title, item.e_hrs, item.e_min);
  item_arr[s_num].compl = 1;

  s_list_message_layer = text_layer_create((GRect) { .origin = {0, 44}, .size = {bounds.size.w, 60}});
  text_layer_set_text_alignment(s_list_message_layer, GTextAlignmentCenter);
  text_layer_set_text(s_list_message_layer, s_message_text);
  layer_add_child(window_layer, text_layer_get_layer(s_list_message_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_list_message_layer);

  window_destroy(window);
  s_main_window = NULL;
}

void completed_message_window_push(int inum) {
  s_num = inum;
  
  if(!s_main_window) {
    s_main_window = window_create();
    window_set_click_config_provider(s_main_window, click_config_provider);
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
  }
  window_stack_push(s_main_window, true);
}
