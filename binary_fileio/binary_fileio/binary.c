//
//  main.c
//  binary_fileio
//
//  Created by 최제현 on 2020/06/02.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void showMenu();
void clear_stdin();
void memberAdd();
void memberRead();

int main(int argc, const char * argv[]) {
    showMenu();
    return 0;
}

void memberAdd(){
  FILE* fp = fopen("/Users/s85737/Documents/2020 1학기/과제/자료구조/자료구조(1)/binary_fileio/binary_fileio/database.bin", "ab");  
//    FILE* fp = fopen("database.bin", "ab");
    if(fp == NULL){
        fprintf(stderr, "Error to open!!\n");
        exit(1);
    }
    
    char name[256], choice;
    unsigned int age, hp, num=1;
    double x, y;
    size_t lenWord, i;
    
    clear_stdin();
    
    printf("ID 를 입력하세요: ");
    fscanf(stdin, "%255s", name);
    i = fwrite(name, sizeof(char), sizeof(name), fp);
    if(i != sizeof(name)){
        fprintf(stderr, "writing error !! \n");
        exit(-1);
    }
    
    printf("나이 를 입력하세요: ");
    fscanf(stdin, "%d", &age);
    if(age <= 127){
        fwrite(&age, sizeof(int), 1, fp);
    }else{
        fprintf(stderr, "나이는 127살을 넘을 수 없습니다. 임의값 127살로 변경됩니다. \n");
        age = 127;
        fwrite(&age, sizeof(int), 1, fp);
    }
 
    printf("HP 를 입력하세요: ");
    fscanf(stdin, "%d", &hp);
    if(hp <= 65535){
        fwrite(&hp, sizeof(int), 1, fp);
    }else{
        fprintf(stderr, "HP는 65535를 넘을 수 없습니다. 임의값 65535로 변경됩니다. \n");
        hp = 65535;
        
        fwrite(&hp, sizeof(int), 1, fp);
    }
    
    printf("X 좌표 를 입력하세요: ");
    fscanf(stdin, "%lf", &x);
    fwrite(&x, sizeof(double), 1,fp);
    
    printf("Y 좌표 를 입력하세요: ");
    fscanf(stdin, "%lf", &y);
    fwrite(&y, sizeof(double), 1,fp);
    
    
    do{
    printf("동맹 ID 를 입력하세요: ");
        fscanf(stdin, "%255s", name);
        i = fwrite(name, sizeof(char), sizeof(name), fp);
        
    if(i != sizeof(name)){
        fprintf(stderr, "writing error !! \n");
    }
        
        printf("동맹을 계속 추가할까요?: ");
        fscanf(stdin,"%s", &choice);
        
        num++;
        
   }while(choice != 'N' || num > 255);
    
        fseek(fp, -(num)*(sizeof(name)), SEEK_CUR);
        fwrite(&num, sizeof(int), 1, fp);
  
    fclose(fp);
    
    showMenu();
    
}

void memberRead(){
    
  FILE* fp = fopen("/Users/s85737/Documents/2020 1학기/과제/자료구조/자료구조(1)/binary_fileio/binary_fileio/databin", "rb");
    //FILE* fp = fopen("database.bin", "rb");
    if(fp == NULL){
        fprintf(stderr, "Error to open!!\n");
        exit(1);
    }
    
    char wordBuffer[512];
    int lenName = sizeof(char)*256;
    int num, intBuffer;
    double doBuffer;
    
    fread(wordBuffer, 1, lenName, fp);
    
    fprintf(stdout, "ID: %s /", wordBuffer);
    
    fread(&intBuffer, 1, sizeof(int), fp);
    
    fprintf(stdout, "나이: %d /", intBuffer);
    
    fread(&intBuffer, 1, sizeof(int), fp);
    
    fprintf(stdout, "HP: %d /", intBuffer);
    
    fread(&doBuffer, 1, sizeof(double), fp);
    
    fprintf(stdout, "좌표: %0.3lf, \n", doBuffer);
    
    fread(&doBuffer, 1, sizeof(double), fp);
    
    fprintf(stdout, ",%0.3lf, \n", doBuffer);
    
    fread(&intBuffer, 1, sizeof(int), fp);
    
    fprintf(stdout, "등록된 동맹 수: %d \n", intBuffer);
    
    
    for (int i=0; i < (intBuffer-1) ; i++ ){
        fread(wordBuffer, 1, lenName, fp);
        fprintf(stdout, "%s /", wordBuffer);
    }
    
    fread(wordBuffer, 1, lenName, fp);
    fprintf(stdout, "%s\n", wordBuffer);
    
    fprintf(stdout, "완료되었습니다.");
    
    fclose(fp);
    
    showMenu();
    return;
    
        
 
}

void showMenu(){
    
    
    char choice;
    
    clear_stdin();
    
    fprintf(stdout, "1. 플레이어 정보 기록\n");
    fprintf(stdout, "2. 플레이어 정보 확인\n");
    fprintf(stdout, "3. 종료\n");
    fprintf(stdout, "입력하세요> ");
    fscanf(stdin, " %c", &choice);
    
    clear_stdin();
    
    switch(choice){
            
        case '1' : memberAdd(); break;
        case '2' : memberRead(); break;
        case '3' : fprintf(stdout, "\n 종료합니다. \n\n"); return;
        default :  fprintf(stderr, "\n\n메뉴 번호를 확인해 주세요\n\n"); break;//예외처리: 잘못된 번호가 입력 되었을 시
    }
    
    
}

void clear_stdin(){
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {};
}

