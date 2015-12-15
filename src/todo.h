/*******************************************
Define todo list item struct
*******************************************/
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