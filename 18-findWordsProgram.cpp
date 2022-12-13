//
// Created by Khaing Hsu Yee on 12/11/2022.
//
#include "stdio.h"
#include "stdlib.h"
int countW1();
int countW2();
char w1[7]={'w','i','n','h','t','u','t'};
char w2[17]={'N','a','t','i','o','n','a','l','C','y','b',
             'e','r','C','i','t','y'};
int main(){
    int count1=countW1();
    printf("\"winhtut\" is found %d times\n",count1);
    int count2=countW2();
    printf("\"NationalCyberCity\" is found %d times\n",count2);
    return 0;

}
int countW1(){
    FILE *fptr;
    fptr= fopen("words.txt","r");
    int count=0;

    if(fptr== NULL){
        printf("File does not exit!");

    }
    else{
        char c= fgetc(fptr);
        while(!feof(fptr)){
            int i=0;
            while (i<7){
                if(c==w1[i]){
                    c= fgetc(fptr);
                    i++;
                }
                else{

                    if(c!=w1[0]){
                        c= fgetc(fptr);
                    }
                    break;

                }
            }
            if(i==7){
                count++;
            }
        }
    }
    return count;
}
int countW2(){
    FILE *fptr;
    fptr= fopen("words.txt","r");
    int count=0;

    if(fptr== NULL){
        printf("File does not exit!");

    }
    else{
        char c= fgetc(fptr);
        while(!feof(fptr)){
            int i=0;
            while (i<17){
                if(c==w2[i]){
                    c= fgetc(fptr);
                    i++;
                }
                else{

                    if(c!=w2[0]){
                        c= fgetc(fptr);
                    }
                    break;

                }
            }
            if(i==17){
                count++;
            }
        }
    }
    return count;
}