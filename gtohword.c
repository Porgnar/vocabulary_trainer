#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//terminálba text színező függvények
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
    char cond[]="quit\n"; //ezzel hasonlítju össze a quit szót, ha beírják, akkor kilép a program biztonságosan.
    int quit;

    for(int i=0;i<10;i++){
        history[i]=-1;
    };


    FILE *ft;
    FILE *fp;

    fp=fopen("vocabulary.txt","r");
    while((fgets(buffer,255,fp))!=NULL){                    //megszámoljuk hány soros a file
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
        int r1=rand()%wordcount;                //random szám ami kiválasztja hanyadik sorban levő szót kérdezi meg a program
        int r2=rand()%101;                              //random szám ami megcsinálja a tudás biast, a fileban a szám reprezentálja 0-100 közt mennyire tudjuk a szót
        int know=-5;                                        //ha a szavakat szám nélkül csak  egyik nyelv másik nyelv adjuk meg a tudás biast nem tesszük bele a programba, akkor magától 0-ról elkezdi a biast
        //printf("%d\n",r1);
        int counter=0;
        int oops=0;


        for(int i=0;i<10;i++){
            if(history[i]==r1){oops++;} ;       //megnézzük, hogy az előző 10 kiválasztott szó közt ne legyen az újonnan kiválasztott szavunk
        };


        while((fgets(buffer,255,fp))!=NULL){                //soronként beolvassuk a filet egy bufferbe


            if((counter==r1)&&(oops==0)){               //ha nincs az előző 10 szó közt, akkor a kiválasztott szavunk kiadja

            //    printf("%d\n",know);

                sscanf(buffer,"%s %s %d",gword,hword,&know);     //a beolvasott bufferelt sort tördeljük önálló szavakra és tudás biasra

                if(know<0){know=0;};
         //       printf("%s %s %d\n",gword,hword,know);

                if(know<=r2){                //ha a tudásunk kisebb vagy egyenlő egy 0-100 generált random számnál, akkor megkérdezi a szót, egyébként nem (minnél jobban ismerünk egy szót, annál ritkábban kerül elő

                    printf("A(z) %s szó magyar megfelelője: ",gword);

                    fgets(buffer, sizeof buffer,stdin);                 //beolvassuk a user inputot terminálból bufferbe

                    sscanf(buffer,"%s",input);          //kiolvassuk a bufferből, így szebben konvertálódnak a szavak, rögtöni összehasonlításra

                    quit=strcmp(buffer,cond);           //kilépési kondíció, ha quitet gépelünk és entert ütünk, akkor kilép a program, biztonságosan leállva

                    //printf("nemet%snemet     %s\n",buffer);
                    int eh=strcmp(input,hword);         //megnézi hogy helyes e az általunk beírt fordítás, a fileban megadotthoz nézve

                    //printf("eh:%d\n",eh);

                    if((eh==0)&&(quit!=0)){green();printf("Helyes!\n");if(know<100){know++;};}          //ha nem léptünk ki akkor helyes válasz esetén a tudás biast növeljük egyel, zöld szövegű visszajelzést kapunk a helyes válaszról
                    else if((eh!=0)&&(quit!=0)){red(); printf("Helytelen!\n");if(know>0){know--;};};    //ha nem léptünk ki akkor a hleytelen válasz esetén a tudás biast csökkentjük egyel, vörös szövegű visszajelzést kapunk helytelen válaszról

                    //printf("%s %s %d\n",gword,hword,know);

                    for(int i=0;i<10;i++){
                        history[i]=history[i+1];        //toljuk a már megkérdezett szavak listáját egyel, a 10. megkérdezett kiesik, az új bekerül.
                    };
                    history[9]=r1;
            };

            fprintf(ft,"%s %s %d\n",gword,hword,know);      //kiírjuk egy temporary fileba annak a szónak a sorát amit megkérdeztünk, az updatelt tudás bias számmal

            reset();                //manuálisan visszaállítjuk a terminál alapszínére a szövegünk színét, hogy ne permanensen fessük a terminált zöldre
        }
        else{fprintf(ft,"%s",buffer);};                 //ha nem kérdezett sort buffereltünk, akkor egyenesen átírjuk a temporary fileba

        counter++;
    };//inner while

    fclose(fp);
    fclose(ft);

    remove("vocabulary.txt");    //kitörli az erdeti szószedetünk

    rename("replace.tmp","vocabulary.txt");         //átnevezi az átmeneti fileunk ami a frissített tudás biasu számokat tartalmazza, az eredeti szószedetet gyakorlatilag felülírva ezzel, hogy bármikor onnan folytathassuk a szókártyázást tudásilag, ahol abbahagytuk

    if(quit==0){break;};   //biztonságos kilépés, mert az utolsó tudás biast is kimenti, nem tűnnek el szavaink, tudás bias, ha mégis erőltetve zárnánk be akkor a legutolsó még helyesen legutó ciklus tudás biassal használhatjuk a programunk

    };//outer while

};//main
