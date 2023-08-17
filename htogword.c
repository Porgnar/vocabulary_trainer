#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void reset () {
  printf("\033[0m");
};

void red() {
  printf("\033[0;31m");
};

void green() {
  printf("\033[0;32m");
};



int main(){

    printf("Type the word 'quit' to close the program.\n");

    srand(time(NULL));

    char buffer[255];
    int history[10];
    int wordcount=0;
    char cond[]="quit\n";
    int quit;

    for(int i=0;i<10;i++){
        history[i]=-1;
    };


    FILE *ft;
    FILE *fp;

    fp=fopen("vocabulary.txt","r");
    while((fgets(buffer,255,fp))!=NULL){
        wordcount++;
        };
    fclose(fp);

    //printf("%d\n",wordcount);

    while(1){

        fp=fopen("vocabulary.txt","r");
        ft=fopen("replace.tmp","w");


        char hword[50];
        char gword[50];
        char input[50];
        int r1=rand()%wordcount;
        int r2=rand()%101;
        int know=-5;
        //printf("%d\n",r1);
        int counter=0;
        int oops=0;


        for(int i=0;i<10;i++){
            if(history[i]==r1){oops++;} ;
        };


        while((fgets(buffer,255,fp))!=NULL){


            if((counter==r1)&&(oops==0)){

              // printf("%d\n",know);

                sscanf(buffer,"%s %s %d",gword,hword,&know);

                if(know<0){know=0;};
               // printf("%s %s %d\n",gword,hword,know);

                if(know<=r2){
                    printf("Das deutsche äquivalent für %s:  ",hword);

                    fgets(buffer, sizeof buffer,stdin);

                    sscanf(buffer,"%s",input);

                    quit=strcmp(buffer,cond);

                    //printf("nemet%snemet     %s\n",buffer);
                    int eh=strcmp(input,gword);

                    //printf("eh:%d\n",eh);

                    if((eh==0)&&(quit!=0)){green();printf("Korrekt!\n");if(know<100){know++;};}
                    else if((eh!=0)&&(quit!=0)){red(); printf("Falsch!\n");if(know>0){know--;};};

                    //printf("%s %s %d\n",gword,hword,know);

                    for(int i=0;i<10;i++){
                        history[i]=history[i+1];
                    };
                    history[9]=r1;
            };

            fprintf(ft,"%s %s %d\n",gword,hword,know);

            reset();
        }
        else{fprintf(ft,"%s",buffer);};

        counter++;
    };//inner while

    fclose(fp);
    fclose(ft);

    remove("vocabulary.txt");

    rename("replace.tmp","vocabulary.txt");

    if(quit==0){break;};

    };//outer while

};
