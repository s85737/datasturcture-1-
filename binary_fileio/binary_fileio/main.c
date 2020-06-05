#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void showMenu();
void memberAdd();
void memberRead();

int main(int argc, const char * argv[]) {
    showMenu();
    return 0;
}


// 플레이어 입력 함수
void memberAdd(){
    
    FILE * fp = fopen("database.bin", "ab");
    if(fp == NULL){ //예외처리 : 파일 열기 오류
        fprintf(stderr, "Error to open!!\n");
        exit(1);
    }
    
    char name[255], choice;
    unsigned int age, hp, num=0;
    double x, y;
    size_t lenWord, i;
    
    printf("ID 를 입력하세요: ");
    fscanf(stdin, "%255s", name);// 문자열 입력 255자 제한
    fwrite(name, sizeof(char), sizeof(name), fp); // 문자크기 char인 문자열 fp에 name의 바이트 수 만큼 입력.
    
    printf("나이 를 입력하세요: ");
    fscanf(stdin, "%d", &age);
    if(age <= 127){
        fwrite(&age, sizeof(int), 1, fp);
    }else{ //예외처리 : 나이가 127살을 넘었을 때
        fprintf(stderr, "나이는 127살을 넘을 수 없습니다. 임의값 127살로 변경됩니다. \n");
        age = 127;
        fwrite(&age, sizeof(int), 1, fp);
    }
    
    printf("HP 를 입력하세요: ");
    fscanf(stdin, "%d", &hp);
    if(hp <= 65535){// 예외처리 : HP가 65535를 넘겼을 때
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
        
        num++; //동행의 수 count
        
        if(choice == 'N') {
            printf("완료되었습니다.\n");
            fwrite(&num, sizeof(int), 1, fp); //입력이 완료되었을 때 동행의 수 파일 맨 마지막에 저장
            fclose(fp);
            showMenu();
            return;
        }
        else if (choice == 'Y') continue;
        else{
            printf("Y/N 둘중 하나만 입력해주세요. 메뉴로 돌아갑니다.\n");
            fclose(fp);
            showMenu();
            return;
        }
        
        
    }while(choice == 'Y' || num <= 255); //동맹의 수가 255가 넘으면 작동중지.
    
    
    fclose(fp);
    
    showMenu();
    
}

//플레이어 리스트 출력 함수
void memberRead(){
    
    
    FILE * fp = fopen("database.bin", "rb");
    char wordBuffer[512];
    int lenName = sizeof(char)*255; // 플레이어 이름 최대 255자까지 저장.
    int intBuffer;
    double doBuffer, position;
    
    
    if(fp == NULL){
        fprintf(stderr, "Error to open!!\n");
        exit(1);
    }
    // 파일에 ID, 나이, HP, 좌표, 동맹 ID, 동맹의 수 순으로 저장되어 있는것을 고려
    
    fread(wordBuffer, 1, lenName, fp); // fp파일에서 플레이어 이름 읽어와서 Buffer에 저장. 1바이트씩 255자 모두 읽어옴.
    
    fprintf(stdout, "ID: %s /", wordBuffer); // word Buffer에 저장된 문자열 화면에 출력.
    
    fread(&intBuffer, 1, sizeof(int), fp); //버퍼에 나이 저장
    
    fprintf(stdout, "나이: %d /", intBuffer);
    
    fread(&intBuffer, 1, sizeof(int), fp); //버퍼에 HP 저장
    
    fprintf(stdout, "HP: %d /", intBuffer);
    
    fread(&doBuffer, 1, sizeof(double), fp); //버퍼에 x좌표 저장
    
    fprintf(stdout, "좌표: %0.3lf,", doBuffer); //좌표는 소수점 3째 자리까지 출력
    
    fread(&doBuffer, 1, sizeof(double), fp); //버퍼에 y좌표 저장
    
    fprintf(stdout, "%0.3lf \n", doBuffer);
    
    position = ftell(fp); // 현재 파일 포인터 저장
    fseek(fp, -sizeof(int), SEEK_END); // 맨 마지막 위치에서 동맹의 수를 읽어와야 하므로 int만큼 뒤로 이동
    
    fread(&intBuffer, 1, sizeof(int), fp); //버퍼에 동맹의 수 저장
    
    fprintf(stdout, "등록된 동맹 수: %d \n", intBuffer);
    
    fseek(fp, position, SEEK_SET); // 동맹의 ID를 받아오기 위해 파일포인터 이전위치로 다시 이동
    
    for (int i=0; i < (intBuffer-1) ; i++ ){ // 출력 시 포맷을 맞추어 주기 위해 마지막 동맹 전까지. 출력
        fread(wordBuffer, 1, lenName, fp);
        fprintf(stdout, "%s /", wordBuffer);
    }
    
    fread(wordBuffer, 1, lenName, fp); //마지막 동맹 출력
    fprintf(stdout, "%s\n", wordBuffer);
    
    fprintf(stdout, "완료되었습니다.");
    
    fclose(fp);
    
    showMenu();
    return;
    
    
}

//메뉴 출력함수
void showMenu(){
    
    
    char choice;
    
    fprintf(stdout, "1. 플레이어 정보 기록\n");
    fprintf(stdout, "2. 플레이어 정보 확인\n");
    fprintf(stdout, "3. 종료\n");
    fprintf(stdout, "입력하세요> ");
    fscanf(stdin, " %c", &choice);
    
    
    switch(choice){
            
        case '1' : memberAdd(); break;
        case '2' : memberRead(); break;
        case '3' : fprintf(stdout, "\n 종료합니다. \n\n"); return;
        default :  fprintf(stderr, "\n\n메뉴 번호를 확인해 주세요\n\n"); break;//예외처리: 잘못된 번호가 입력 되었을 시
    }
    
    
}


