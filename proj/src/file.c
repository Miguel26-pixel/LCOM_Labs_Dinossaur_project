#include "file.h"

extern User* high[3];
extern int high_sc[3];


void read_file() {
    FILE *users_to_read = fopen("/home/lcom/labs/proj/src/high_score.txt","r");

	if(users_to_read == NULL)
		return;
    int j=0;
    while(j<3) 
    {
        char name[5]={'\0'};
        char date[10];
        char dummy='\0';
        int day=0,month=0,year=0;
        long int score=0;
        fscanf(users_to_read, "%lu",&score);
        fscanf(users_to_read, "%d",&day);
        fscanf(users_to_read, "%d",&month);
        fscanf(users_to_read, "%d",&year);
        fscanf(users_to_read, "%c",&dummy);
        sprintf(date,"%02d %02d %d",day,month,year);
        User *u = create_user(name,date,score);
        high[j]=u;
        high_sc[j] = score;
        j++;
    }
    fclose(users_to_read);
}

void write_file() {
    FILE *users_to_write = fopen("/home/lcom/labs/proj/src/high_score.txt","w");

	if(users_to_write == NULL){
		return;
    }

	for(int it=0; it < 3; it++)
	{
        if(high_sc[it]==0)break;
        fprintf(users_to_write, "   %lu  ",high[it]->sc);
        for (int jt =0;jt<10;jt++)
        {
            fprintf(users_to_write, "%c", (high[it]->date)[jt]);
        }
        fprintf(users_to_write, "\n");
	}
	fclose(users_to_write);
}
