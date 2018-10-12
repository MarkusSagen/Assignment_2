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
  scanf("%c", buf + i);
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


answer_t ask_question(char *question, check_func check, convert_func convert)
{
  int buf_siz = 255;
  char buf[buf_siz];
  bool valid = true;
  while (valid)
    {
      printf("%s\n",question);
      read_string();
      valid = check(buf)==false;
    }
  return convert(buf);
}

answer_t make_float(char *str)
{
  return (answer_t) { .float_value = atof(str) };
}

int ask_question_int(char *question)
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
}
