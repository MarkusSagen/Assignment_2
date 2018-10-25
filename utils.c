#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"


bool not_empty(char *str)
{
  return strlen(str) > 0;
}

bool is_shelf(char *str)
{
return str[0] >= 'A' && str[0] <= 'Z' && str[1] >= '0' && str[1] <= '9'  && str[2] >= '0' && str[2] <= '9' && str[3] == '\0'; 
}

bool is_number(char *str)
{
  bool k = false;
  for (int i = 0; str[i] != '\0'; ++i)
    {
      int j = str[i] - '0';
      if (k && i>0) k = false;
      if (str[i] == '-' && i == 0) {j=0;k=true;};
      if (j < 0 || j > 9) return false;
    }
  if (k) return false;    
  return true;
}

/*int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n' && c != EOF);
    }
  while (conversions < 1);
  return result;
  }*/

char *read_string()
{
  int buf_siz = 50;
  char buf[buf_siz];
  int i = 0;
  while (i<buf_siz)
    {
      buf[i] = getchar();
  if (buf[i] == '\n')
    {
      buf[i] = '\0';
      return strdup(buf);
    }
  ++i;
    }
  return strdup(buf);
}

/*
char *ask_question_string(char *question, char *buf, int buf_siz)
{
  printf("%s\n", question);
  for (int len = 0; len==0;)
  len = read_string(buf, buf_siz);
  return buf;
}
*/


char* ask_question(char *question, char *error_msg, check_func check)
{
  printf("%s", question);
  int buf_siz = 50;
  char buf[buf_siz];
  int i = 0;
  while (i<buf_siz)
    {
      buf[i] = getchar();
  if (buf[i] == '\n')
    {
      buf[i] = '\0';
      if (check(buf)) return strdup(buf);
      else return ask_question(error_msg, error_msg, check);
    }
  ++i;
    }
  if (check(buf)) return strdup(buf);
      else return ask_question(error_msg, error_msg, check);
}

bool yes_no() {
  char *str_in = read_string();
  float score = str_cmp(str_in, "y");
  if (score>=3 || str_in[0]=='\0') return true; 
  else return false;
}
bool check_true() {
  return true;
}
answer_t make_float(char *str)
{
  return (answer_t) { .float_value = atof(str) };
}

/*int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}

char *ask_question_shelf(char *question)
{
  return ask_question(question, is_shelf, (convert_func) strdup).string_value;
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}*/

static float char_match (char in, char cmp) {
  if (in == cmp) {return 1;}
  if  ((cmp>='a' && cmp<='z' && in == cmp - 'a' + 'A') || (cmp>='A' && cmp<='Z' && in == cmp + 'a' - 'A')) {return 1;}
  return 0;
}


float str_cmp(char *in, char *cmp) {
  float result = 0;
  int in_p = 0;
  int cmp_p = 0;
  bool c = true;
  float mult = 1;
  float result_tmp;
  while (in[in_p] != '\0' && cmp[cmp_p] != '\0') {
    if (c) mult = 1; else mult = 0.5;
    c = false;
    result_tmp = char_match(in[in_p], cmp[cmp_p]);
    if (result_tmp > 0) {++in_p; result += result_tmp * mult; c = true;}
    if (cmp_p==0 && result_tmp > 0) {result += 2;}
    if (cmp[cmp_p] == ' ') c = true;
    ++cmp_p;
    }
  return result;
}
