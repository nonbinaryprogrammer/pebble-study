#include <windows/start_studying_window.h>
#include <windows/mark_as_complete_window.h>
#include <todo.h>

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

typedef enum {
  ScrollDirectionDown,
  ScrollDirectionUp,
} ScrollDirection;

static Window *s_main_window;
static TextLayer *s_text_layer;

static int s_inum;
static int s_itot;
static ToDo item_arr[] = {
  {"Lab #6", "Chapter 16, #1, 3, 5a", "321", "MTH", 2, 0, 0, 0, 0},
  {"Homework #3", "Chapter 12, #3, 4b, 5de, 6, 7, 11", "321", "MTH", 2, 30, 0, 0, 0},
  {"OTP Implementation", "OTP and Socket communication implementation in C", "344", "CS", 6, 0, 0, 0, 0}
};

static void scroll(ScrollDirection direction) {
  static char s_card_text[200] = "";
  int delta = direction == ScrollDirectionUp ? -1 : +1;
  
  do {
    s_inum += delta;

    if (s_inum == s_itot) {
      s_inum = 0;
    }
    else if(s_inum == -1) {
      s_inum = s_itot-1;
    }
  } while(item_arr[s_inum].compl == 1);

  snprintf(s_card_text, sizeof(char)*200, "%s\n%s", item_arr[s_inum].title, item_arr[s_inum].descr);
  
  text_layer_set_text(s_text_layer, s_card_text);
}

static void mark() {
  mark_as_complete_window_push(s_inum);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  scroll(ScrollDirectionUp);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  scroll(ScrollDirectionDown);
}

static void center_click_handler(ClickRecognizerRef recognizer, void *context) {
  mark();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, center_click_handler);
}

static void window_load(Window *window) {
  static char s_card_text[200] = "";
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  snprintf(s_card_text, sizeof(char)*200, "%s\n%s", item_arr[s_inum].title, item_arr[s_inum].descr);

  s_text_layer = text_layer_create((GRect) { .origin = {0, 44}, .size = {bounds.size.w, 60}});
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentLeft);
  text_layer_set_text(s_text_layer, s_card_text);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);

  window_destroy(window);
  s_main_window = NULL;
}

void start_studying_window_push() {
  s_inum = 0;
  s_itot = sizeof(item_arr)/sizeof(ToDo);
  
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
