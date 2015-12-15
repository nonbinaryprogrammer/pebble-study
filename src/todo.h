/*******************************************
Define todo list item struct
*******************************************/
typedef struct {
  char title[35];
  char descr[100];
  char class[5];
  char subje[5];
  float t_est;
  int compl;
  float actua;
} ToDo;