//
// Created by Khaing Hsu Yee on 3/31/2023.
//

#ifndef DIP_BANK_PROJECT_1_ZOOM_ONLINE_BANK_H
#define DIP_BANK_PROJECT_1_ZOOM_ONLINE_BANK_H

#endif //DIP_BANK_PROJECT_1_ZOOM_ONLINE_BANK_H


#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define SIZE 1000
struct trans{
    char note[200];
};
struct data{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20];
    char loan_s[2];
    unsigned int monthly_income;
    unsigned int loan_amount;
    float loan_rate;
    char acc_s[10];
    int acc_level;
    unsigned int phNumber;
    unsigned int cur_amount;
    char address[100];
    int transAmoLimitPerDay;
    struct trans trc[100];

};

struct data db[SIZE];
int users=0;
int gValid=-1;
int emailExist=-1;
int two_charArray=-1;
int nrc_valid=-1;
int strongPass=-1;
int phValid=-1;
int phone_found=-1;
int space_array[30];
char int_to_char_array_data[10];

char current_time[30];


void welcome();
void userSector();
void login();
void registration();
void recording_alldata_toFile();
int charCounting(char toCount[50]);
void myGmailValidation(char toValidate[50]);
void emailExistChecking(char toCheck[50]);
void nrc_validation(char nrc_toCheck[50]);
void compare_two_charArray(char first[50],char second[50]);
void myStrongPassword(char pass[50]);
void phone_validation(unsigned int phNo);
void copy_two_char_array(char receiver[50],char transmiter[50]);
void finding_phone_number(unsigned int toFind);
void printingAllData();
void loadingAllDataFromFile();
void recording_alldata_toFile();
void transfer_money(int transfer,int receive,unsigned int amount);
void space_counter();
void transaction_record(int transfer,int receiver,char who,unsigned int amount);
void integer_to_char(unsigned int value);
void getTime();
void welcome(){
    int option=0;
    printf("Welcome to our Bank\n");
    printf("Press 1 to login!\nPress 2 to Register!\nPress 3 to exit!");
    scanf("%d",&option);
    if(option==1){
        login();
    }
    else if(option==2){
        registration();
    }
    else if(option==3){
        recording_alldata_toFile();
        exit(1);
    }
    else{
        welcome();
    }

}
void userSector(){
    int user_option=0;
    unsigned int phone=0;
    unsigned  int amount_to_transfer=0;
    printf("This is user sector\n");
    printf("Press 1 to Transfer Money:\nPress 2 to Withdraw:"
           "\nPress 3 to update your information\nPress 4 Cash in :\nPress 5 to Loan:"
           "\nPress 6 to view your history:\nPress 7 Exit");
    scanf("%d",&user_option);
    if(user_option == 1){
        printf("This is for Transfer Option:\n");

        phone_found=-1;
        while(phone_found == -1){
            printf("Enter receiver 's phone number:");
            scanf("%u",&phone);
            finding_phone_number(phone);
            if(phone_found == -1){
                printf("Your receiver phone number does not belong to any user!\n");
            }
        }
        printf("Are you sure to transfer to %s with email : %s\n",db[phone_found].name,
               db[phone_found].email);
        while(amount_to_transfer<db[emailExist].cur_amount){
            printf("Enter the amount to transfer:");
            scanf("%u",&amount_to_transfer);
            if(amount_to_transfer<db[emailExist].cur_amount-1000){
                break;

            }else{
                printf("Your balance is not enough to transfer!\n");
                amount_to_transfer=0;
            }
        }
        two_charArray = -1;
        char trans_pass[50];
        int wrong_count=0;
        while (two_charArray == -1){
            printf("Enter your password to proceed transaction:");
            scanf(" %[^\n]",&trans_pass[0]);
            compare_two_charArray(db[emailExist].password,trans_pass);
            if(two_charArray == -1){
                printf("Wrong Password!\n");
                wrong_count++;
            }
            if(wrong_count == 3){
                printf("Wrong Password for three times.\nSo you need to wait for some time!\n");
                userSector();
            }
        }

        transfer_money(emailExist,phone_found,amount_to_transfer);

        printingAllData();
        userSector();

    }else if(user_option==7){

        welcome();

    }



}
void transfer_money(int transfer,int receiver,unsigned int amount){
    printf("loading to transfer.....\n");
    db[transfer].cur_amount=db[transfer].cur_amount-amount;
    db[receiver].cur_amount=db[receiver].cur_amount+amount;
    printf("Transaction succeed!");
    transaction_record(transfer,receiver,'t',amount);
    transaction_record(transfer,receiver,'r',amount);

}
void transaction_record(int transfer,int receiver,char who,unsigned int amount){

    int trans_name_counter= charCounting(db[transfer].name);
    int receiver_name_counter = charCounting(db[receiver].name);
    integer_to_char(amount);
   int amount_count = charCounting(int_to_char_array_data);
    getTime();
    int current_count= charCounting(current_time);


    char from[5]={'f','r','o','m','-'};
    char to[4]={'-','t','o','-'};
    char at[4]={'-','a','t','-'};

    if(who == 't'){
        int index_point=0;
        for(int i=0;i<5;i++){
            db[transfer].trc[space_array[transfer]-15].note[i]=from[i];
            index_point++;
        }
        for(int i=0;i<trans_name_counter;i++){
            db[transfer].trc[space_array[transfer]-15].note[index_point]=db[transfer].name[i];
            index_point++;
        }
        for(int i=0;i<4;i++){
            db[transfer].trc[space_array[transfer]-15].note[index_point]=to[i];
            index_point++;
        }
        for(int i=0;i<receiver_name_counter;i++){
            db[transfer].trc[space_array[transfer]-15].note[index_point]=db[receiver].name[i];
            index_point++;
        }

        db[transfer].trc[space_array[transfer]-15].note[index_point]='$';
        index_point++;

        for(int i=0;i<amount_count;i++){
            db[transfer].trc[space_array[transfer]-15].note[index_point]=int_to_char_array_data[i];
            index_point++;
        }
        for(int i=0;i<4;i++){
            db[transfer].trc[space_array[transfer]-15].note[index_point]=at[i];
            index_point++;
        }


        for(int i=0;i<current_count;i++){



            if(current_time[i] == ' '){
                db[transfer].trc[space_array[transfer]-15].note[index_point]='-';
                index_point++;
            }else{
                db[transfer].trc[space_array[transfer]-15].note[index_point]=current_time[i];
                index_point++;
            }


        }

        space_array[transfer]++;
    }else{
        char rec[14]={'-','R','e','c','e','i','v','e','-','F',
                      'r','o','m','-'};



        int index_point=0;
        for(int i=0;i<receiver_name_counter;i++){
            db[receiver].trc[space_array[receiver]-15].note[i]=db[receiver].name[i];
            index_point++;
        }
        for(int i=0;i<14;i++){
            db[receiver].trc[space_array[receiver]-15].note[index_point]=rec[i];
            index_point++;
        }
        for(int i=0;i<trans_name_counter;i++){
            db[receiver].trc[space_array[receiver]-15].note[index_point]=db[transfer].name[i];
            index_point++;
        }
        db[receiver].trc[space_array[receiver]-15].note[index_point]='$';
        index_point++;
        for(int i=0;i<amount_count;i++){
            db[receiver].trc[space_array[receiver]-15].note[index_point]=int_to_char_array_data[i];
            index_point++;
        }
        for(int i=0;i<4;i++){
            db[receiver].trc[space_array[receiver]-15].note[index_point]=at[i];
            index_point++;
        }


        for(int i=0;i<current_count;i++){

            if(current_time[i] == ' '){
                db[receiver].trc[space_array[receiver]-15].note[index_point]='-';
                index_point++;
            }else{
                db[receiver].trc[space_array[receiver]-15].note[index_point]=current_time[i];
                index_point++;
            }


        }
        space_array[receiver]++;
    }

}
void getTime(){
    FILE *fptr= fopen("23.txt","w");

    if(fptr == NULL){
        printf("Error");
    }else{

        time_t t;   // not a primitive datatype
        time(&t);
        fprintf(fptr,"%s", ctime(&t));
    }
    fclose(fptr);
    FILE *fptr2= fopen("23.txt","r");
    int i=0;

    while(!feof(fptr2)){
        char c= fgetc(fptr2);
        if(c == '\n'){
            break;
        }
        current_time[i]=c;
        i++;
    }
    fclose(fptr2);



}
void loadingAllDataFromFile(){
    FILE *fptr= fopen("ncc_db1.txt","r");
    if(fptr==NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    }
    else{
        for(int ncc=0;ncc<SIZE;ncc++){
            fscanf(fptr,"%u%s%s%s%s%s%s%u%u%f%s%d%u%u%s%d",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,
                   &db[ncc].email,&db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,
                   &db[ncc].loan_amount,&db[ncc].loan_rate,&db[ncc].acc_s,&db[ncc].acc_level,&db[ncc].phNumber,
                   &db[ncc].cur_amount,&db[ncc].address,&db[ncc].transAmoLimitPerDay);

            for(int gcc=0;gcc<space_array[ncc]-15;gcc++){
                fscanf(fptr," %s",&db[ncc].trc[gcc].note[0]);
            }
            if(db[ncc].email[0]=='\0')
                break;
            users++;

        }

    }
    fclose(fptr);
}
void printingAllData(){
    for(int ncc=0;ncc<users;ncc++){
        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%u-%u-%s-%d",db[ncc].id,db[ncc].name,db[ncc].nrc,
               db[ncc].email,db[ncc].password,db[ncc].pOrb,db[ncc].loan_s,db[ncc].monthly_income,
               db[ncc].loan_amount,db[ncc].loan_rate,db[ncc].acc_s,db[ncc].acc_level,db[ncc].phNumber,
               db[ncc].cur_amount,db[ncc].address,db[ncc].transAmoLimitPerDay);
        for(int gcc=0;gcc<space_array[ncc]-15;gcc++){
            printf("-%s",&db[ncc].trc[gcc].note[0]);
        }
        printf("\n");

    }
}
void recording_alldata_toFile(){

    FILE *fptr=fopen("ncc_db1.txt","w");
    if(fptr == NULL){
        printf("cannot open file to record:\n");
    }
    else{
        for(int ncc=0;ncc<users;ncc++){
            fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%u%c%f%c%s%c%d%c%u%c%u%c%s%c%d",
                    db[ncc].id,' ',db[ncc].name,' ',db[ncc].nrc,' ',
                   db[ncc].email,' ',db[ncc].password,' ',db[ncc].pOrb,' ',db[ncc].loan_s,' ',
                   db[ncc].monthly_income,' ',
                   db[ncc].loan_amount,' ',db[ncc].loan_rate,' ',db[ncc].acc_s,' ',
                   db[ncc].acc_level,' ',db[ncc].phNumber,' ',
                   db[ncc].cur_amount,' ',db[ncc].address,' ',db[ncc].transAmoLimitPerDay);
            for(int gcc=0;gcc<space_array[ncc]-15;gcc++){
                fprintf(fptr," %s",db[ncc].trc[gcc].note);
            }
            fprintf(fptr,"%c",'\n');

        }
    }

}
void login(){

    char L_email[50];
    char L_pass[50];
    emailExist=-1;
    two_charArray=-1;
    while(emailExist == -1 || two_charArray == -1){
        printf("This is Login!\n");
        printf("Enter your email:");
        scanf(" %[^\n]",&L_email[0]);
        printf("Enter your password:");
        scanf(" %[^\n]",&L_pass[0]);
        emailExistChecking(L_email);
        compare_two_charArray(L_pass,db[emailExist].password);
        if(emailExist == -1 || two_charArray == -1){
            emailExist = -1;
            two_charArray = -1;
            printf("Your login credential was wrong:\n");
        }

    }
    printf("Welcome Mr/Mrs %s",db[emailExist].name);
    printf("\nYour current amount is %u\n",db[emailExist].cur_amount);
    userSector();

}
void registration(){

    char reEmail[50];
    char reName[50];
    char reNrc[50];
    char repassword[50];
    unsigned int rephNo=0;
    printf("This is NCC Bank User Registration!\n");
    printf("Enter your email:");
    scanf(" %[^\n]",&reEmail[0]);
    gValid=-1;
    myGmailValidation(reEmail);
    if(gValid !=-1){
        emailExist=-1;
        emailExistChecking(reEmail);
        if(emailExist == -1){
            printf("Enter your name:");
            scanf(" %[^\n]",&reName[0]);
            nrc_valid=-1;
            while(nrc_valid==-1){
                printf("Enter your NRC:");
                scanf(" %[^\n]",&reNrc[0]);
                nrc_validation(reNrc);
                if(nrc_valid == -1){
                    printf("Your NRC Format was Not Valid!\n");
                }
            }
            printf("Your NRC has been accepted\n");
            strongPass=-1;
            while (strongPass==-1){
                printf("Enter your password:");
                scanf(" %[^\n]",&repassword[0]);
                myStrongPassword(repassword);
                if(strongPass==-1){
                    printf("Your password is weak and easy to guess!\n");
                }
            }
            printf("Your password is valid and saved!\n");
            phValid=-1;
            while (phValid==-1){
                printf("Enter your phone number:");
                scanf("%u",&rephNo);
                phone_validation(rephNo);
                if(phValid==-1){
                    printf("Your phone number is already taken!\n");
                }

            }
            printf("Your phone number is valid and saved!\n");
            printf("Enter your monthly income:");
            scanf("%u",&db[users].monthly_income);
            printf("Enter your current amount:");
            scanf("%u",&db[users].cur_amount);
            printf("Enter your address:");
            scanf(" %[^\n]",&db[users].address[0]);

            db[users].loan_amount=db[2].loan_amount;
            db[users].loan_rate=db[2].loan_rate;
            copy_two_char_array(db[users].name,reName);
            copy_two_char_array(db[users].nrc,reNrc);
            copy_two_char_array(db[users].email,reEmail);
            copy_two_char_array(db[users].password,repassword);
            db[users].phNumber=rephNo;
            copy_two_char_array(db[users].pOrb,db[2].pOrb);
            copy_two_char_array(db[users].loan_s,db[2].loan_s);
            copy_two_char_array(db[users].acc_s,db[2].loan_s);
            db[users].acc_level=db[2].acc_level;
            db[users].transAmoLimitPerDay=db[2].transAmoLimitPerDay;
            copy_two_char_array(db[users].trc[0].note,db[2].trc[0].note);
            db[users].id=users+1;
            users++;
            printingAllData();
            welcome();


        }else{
            printf("Your gmail already exists!\n");
            registration();
        }

    }else{
        printf("Your gmail format is invalid!\n");
        registration();
    }


}
void space_counter(){
    FILE *fptr= fopen("ncc_db1.txt","r");
    if(fptr == NULL){
        printf("File opening error at space_counter fun:\n");
    }else{
        char c= fgetc(fptr);
        int index=0;
        while(!feof(fptr)){
            if(c != '\n'){
                if(c == ' '){
                    space_array[index]+=1;

                }
                c= fgetc(fptr);
            }else{
                index++;
                c= fgetc(fptr);
            }
        }
        for (int aaa = 0; aaa < 30; ++aaa) {
            printf("%d ",space_array[aaa]);
        }
        printf("\n");
    }
}
void integer_to_char(unsigned int value){
    FILE *fptr= fopen("100.txt","w");
    if(fptr == NULL){
        printf("file opening error at integer_to_char:\n");
    }else{
        fprintf(fptr,"%u",value);
    }
    fclose(fptr);
    FILE *fptr2= fopen("100.txt","r");
    fscanf(fptr2,"%s",&int_to_char_array_data[0]);

}
void myGmailValidation(char toValidate[50]){
    int endPoint= charCounting(toValidate);
    char form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int count=0;
    for(int i=0;i<endPoint;i++){
        if(toValidate[i] == '@' || toValidate[i]== ' '){
            break;
        } else{
            count++;
        }
    }
    int toCheck=0;
    for(int i=0;i<endPoint;i++){
        if(toValidate[count] != form[i])
            break;
        else{
            count++;
            toCheck++;
        }
    }
    if(toCheck == 10){
        gValid=1;
    }
}
void emailExistChecking(char toCheck[50]){
    int toCheckCount= charCounting(toCheck);
    int sameCount = 0;
    for(int ncc=0;ncc<users;ncc++){
        int dbEmailCount= charCounting(db[ncc].email);
        sameCount=0;
        if(toCheckCount==dbEmailCount){
            for(int i=0;i<toCheckCount;i++){
                if(toCheck[i] != db[ncc].email[i])
                    break;
                else
                    sameCount++;
            }
        }
        if(sameCount==toCheckCount)
            emailExist=ncc;

    }
}
int charCounting(char toCount[50]){
    int count=0;
    for(int gcc=0;gcc<50;gcc++){
        if(toCount[gcc] == '\0'){
            break;
        }
        else
            count++;
    }
    return count;
}
void nrc_validation(char nrc_toCheck[50]){

    int nrc_counter =charCounting(nrc_toCheck);
    int nrc_char=0;

    for(register int i=0; i< nrc_counter ; i++){

        if( nrc_toCheck[i] == ')'){
            break;
        }
        nrc_char++;
    }

    for(int i=0; i<3; i++){

        two_charArray=-1;
        compare_two_charArray(nrc_toCheck,db[i].nrc);
        if(two_charArray == 1){
            nrc_valid=1;
            break;
        }

    }


}
void compare_two_charArray(char first[50],char second[50]){
    int firstCount= charCounting(first);
    int secondCount= charCounting(second);
    int sameCount=0;
    if(firstCount==secondCount){
        for(register int i=0;i<firstCount;i++){
            if(first[i] != second[i]){
                break;
            }
            else{
                sameCount++;
            }
        }
        if(firstCount==sameCount){
            two_charArray=1;
        }
    }
}
void myStrongPassword(char pass[50]){
    int pass_counter= charCounting(pass);
    int i=0;
    int special=0;
    int numchar=0;
    int capChar=0;
    int smallChar=0;
    while(strongPass==-1){
        if(i==pass_counter){
            strongPass=-1;
            break;
        }
        if(pass[i] >= 33 && pass[i] <= 42){
            special++;
        }
        else if(pass[i] >= 48 && pass[i] <= 57){
            numchar++;
        }
        else if(pass[i] >= 65 && pass[i] <= 90){
            capChar++;
        }
        else if(pass[i] >= 97 && pass[i] <= 122){
            smallChar++;
        }
        i++;
        if(special > 0 && numchar >0 && capChar >0 && smallChar >0){
            strongPass=1;
        }

    }

}
void phone_validation(unsigned int phNo){
    phValid=1;
    for(int i=0;i<users;i++){
        if(phNo == db[i].phNumber){
            phValid=-1;
            break;
        }
    }
}
void copy_two_char_array(char receiver[50],char transmiter[50]){
    int transmitter_count= charCounting(transmiter);
    for(int i=0;i<transmitter_count;i++){
        receiver[i]=transmiter[i];
    }
}
void finding_phone_number(unsigned int toFind){

    for(int i=0;i< users;i++){
        if(db[i].phNumber==toFind){
            phone_found=i;
            break;
        }
    }
}
