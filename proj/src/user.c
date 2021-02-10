#include "user.h"

User* high[3];
long int high_sc[3]={0};


User *create_user(char n[5],char d[10], long int sc)
{
  User *u = (User *) malloc ( sizeof(User));
  for(int it=0;it<5;it++)
  {
    u->name[it]=n[it];
  }
  for(int it=0;it<10;it++)
  {
    u->date[it]=d[it];
  }
  u-> sc = sc;
  return u;
}

void destroy_user(User *u){
  if( u == NULL )
    return;
  free(u);
  u = NULL;
}
