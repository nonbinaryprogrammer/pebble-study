#include <pebble.h>
#include <windows/completed_message_window.h>
#include <todo.h>

static Window *s_main_window;
static TextLayer *s_message_layer;
static int s_item_number;
static ToDo item_arr[] = {
  {"Lab #6", "Chapter 16, #1, 3, 5a", "321", "MTH", 2, 0, 0, 0, 0},
  {"Homework #3", "Chapter 12, #3, 4b, 5de, 6, 7, 11", "321", "MTH", 2, 30, 0, 0, 0},
  {"OTP Implementation", "OTP and Socket communication implementation in C", "344", "CS", 6, 0, 0, 0, 0}
};

static void window_load(Window *window) {
  ToDo item = item_arr[s_item_number];
  static char s_message_contents[200];
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  snprintf(s_message_contents, sizeof(char)*200, "completed!\n%s%s\n%s\n%dh %dm", item.subje, item.clnum, item.title, item.e_hrs, item.e_min);

  s_message_layer = text_layer_create((GRect) { .origin = {0, 44}, .size = {bounds.size.w, 60}});
  text_layer_set_text_alignment(s_message_layer, GTextAlignmentCenter);
  text_layer_set_text(s_message_layer, s_message_contents);
  layer_add_child(window_layer, text_layer_get_layer(s_message_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_message_layer);

  window_destroy(window);
  s_main_window = NULL;
}

void completed_message_window_push(int n) {
  s_item_number = n;
  
  if(!s_main_window) {
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
  }
  window_stack_push(s_main_window, true);
}