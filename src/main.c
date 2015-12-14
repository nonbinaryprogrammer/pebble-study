#include <pebble.h>

static Window *s_main_window;
static MenuLayer *s_menu_layer;

static TextLayer *s_error_text_layer;

typedef struct {
  char title[35];
  char descr[100];
  int class;
  char subje[5];
  float t_est;
  int compl;
  float actua;
} ToDo;

ToDo item_arr[] = {
  {"Lab #6", "Chapter 16, #1, 3, 5a", 321, "MTH", 2.0, 0, 0},
  {"Homework #3", "Chapter 12, #3, 4b, 5de, 6, 7, 11", 321, "MTH", 2.5, 0, 0},
  {"OTP Implementation", "OTP and Socket communication implementation in C", 344, "CS", 6.0, 0, 0}
};

static char* menu_arr[] = {"start studying", "view to-do list", "view holds", "view stats"};

static void select_callback(struct MenuLayer *s_menu_layer, MenuIndex *cell_index, void *callback_context) {
  if(!layer_get_hidden(text_layer_get_layer(s_error_text_layer))) {
    layer_set_hidden(text_layer_get_layer(s_error_text_layer), true);
  }
  return;
}

static uint16_t get_section_count_callback(struct MenuLayer *menulayer, uint16_t section_index, void *callback_context) {
  return 4;
}

static void draw_row_handler(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
  char* txt = menu_arr[cell_index->row];
  
  menu_cell_basic_draw(ctx, cell_layer, txt, NULL, NULL);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_rows = get_section_count_callback,
    .draw_row = draw_row_handler,
    .select_click = select_callback
  });
  menu_layer_set_click_config_onto_window(s_menu_layer, s_main_window);
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
  
  s_error_text_layer = text_layer_create((GRect) { .origin = {0, 44}, .size = {bounds.size.w, 60}});
  text_layer_set_text(s_error_text_layer, "cannot\nget list");
  text_layer_set_text_alignment(s_error_text_layer, GTextAlignmentCenter);
  text_layer_set_font(s_error_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_color(s_error_text_layer, GColorWhite);
  text_layer_set_background_color(s_error_text_layer, GColorBlack);
  layer_set_hidden(text_layer_get_layer(s_error_text_layer), true);
  layer_add_child(window_layer, text_layer_get_layer(s_error_text_layer));
}

static void main_window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
}

static void init() {
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}