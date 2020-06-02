#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE 256
#define MAX_BUF 1024

void showMenu();
void memberDel();
void fileCopy();
void memberAdd();
void memberEdit();
void clear_stdin();

int count = 0;

void clear_stdin(){
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {};
    
}
void memberAdd(){
    
    FILE* fd = fopen("Student_List.txt", "a");
    
    //예외처리 : 파일 open 실패
    if (fd == NULL){
        fprintf(stderr ,"파일을 여는데 실패하였습니다.\n");
        exit(1);
    }
    
    
    char name[MAX_SIZE], email[MAX_SIZE], choice;
    int age,lenName,lenEmail, intResult;
    
    clear_stdin();
    fseek(fd, 0, SEEK_SET);
    
    fprintf(stdout, "이름 : ");
    if(fgets(name, 256, stdin) != NULL){ //최대 256-1개 입력
        lenName = strlen(name);
        if(lenName == 255) name[lenName] = '\n'; //오버플로우시 배열 마지막에 개행문자 삽입
        clear_stdin();
        if ((intResult = (fprintf(fd,"NAME %d %s",lenName-1, name))) == '\0'){ //size 에서 개행문자 갯수 제거
            fprintf(stderr, "\n writing error! \n\n"); // 예외처리 : 파일 입력 오류
            exit(-1);
        }
    }else{
        fprintf(stderr,"\n\n data reading error!\n"); // 예외처리 : 입력값을 읽지 못할 때
    }
    
    
    fprintf(stdout, "나이: ");
    fscanf(stdin, "%d", &age);
    if(age <= 200 && age >= 0){ // 예외처리 나잇값이 잘 못 입력되었을 때
        clear_stdin();
        if((intResult = (fprintf(fd,"AGE %d\n", age))) == '\0'){
            fprintf(stderr, "\n data reading error!\n");
            exit(-1);
        }
    }else{
        fprintf(stderr, "나이는 음수이거나, 200살을 넘을 수 없습니다. 임의값 200살로 저장됩니다.\n");
        age = 200;
        fprintf(fd,"AGE %d\n", age);
        
    }
    
    fprintf(stdout, "이메일 : ");
    fscanf(stdin, "%255s", email); //버퍼 오버플로우 방지, email 띄어쓰기 입력 방지로 scanf 사용
    lenEmail = strlen(email);
    if (lenEmail == 255) name[lenEmail] = '\n';
    clear_stdin();
    if ((intResult = fprintf(fd,"EMAIL %d %s\n",lenEmail, email)) == '\0'){
        fprintf(stderr, "\n writing error! \n\n");
        exit(-1);
    }
    
    
    clear_stdin();
    fclose(fd);
    count++; //fclose 오류 방지
    
    //fclose 메모리 에러 방지를 위해 3번이상 계속입력 방지
    if(count <= 3){
        fprintf(stdout, "계속 입력할까요? Y/N ");
        fscanf(stdin,"%s", &choice);
        clear_stdin();
        rewind(stdout);
        name[0] = '\0';
        email[0] = '\0';
        
        if(toupper(choice) == 'Y'){
            
            memberAdd();
            return;
        }
        else if(toupper(choice) == 'N'){
            fprintf(stdout, "\n입력이 완료되었습니다.\n\n");
            showMenu();
            return;
            
        }
        else{
            fprintf(stderr, "Y/N 둘중 하나만 입력해 주세요. 메뉴로 돌아갑니다.\n");
            showMenu();
            return;
        }
    }else{
        clear_stdin();
        count = 0;
        fprintf(stdout, "\n입력이 완료되었습니다.\n\n");
        showMenu();
        return;
    }
    
    
    return;
    
}


// delete member function
void memberDel(){
    FILE *fd = fopen("Student_List.txt", "r+");
    FILE *fdc = fopen("copy.txt", "w+");
    char buffer[MAX_SIZE], *ptr, name[MAX_SIZE], email[MAX_SIZE], temp[MAX_SIZE], input[MAX_SIZE];
    char cpyBuf[MAX_BUF];
    int wordPo, age, wordSize, intResult, currPo, prevPo;
    long copySize;
    
    
    clear_stdin();
    rewind(fd);
    rewind(fdc);
    
    //예외처리 : 파일 open 실패
    if (fd == NULL){
        fprintf(stderr ,"파일을 여는데 실패하였습니다.\n");
        exit(1);
    }
    
    printf("삭제할 이름은 ? : ");
    fgets(name, 256,stdin);
    clear_stdin();
    name[strlen(name)-1] = '\0';
    
    // w+ 는 덮어쓰기는 가능하지만, 원본파일의 내용을 다 지워버리기 때문에 r+사용
    // name, age, email 모두 가변길이기 때문에, 뒤의 내용 훼손가능
    
    //해당 이름 탐색
    while(fgets(buffer, MAX_SIZE, fd) != NULL){
        ptr = strstr(buffer, name); //문자열 비교
        prevPo = ftell(fd);
        if (ptr != NULL){
            wordPo = -1*(strlen(buffer))+5;
            fseek(fd, wordPo, SEEK_CUR);
            fscanf(fd,"%d", &wordSize); // 글자수를 통한 정확한 검색
            if(wordSize == strlen(name)){
                copySize = prevPo - strlen(buffer) -1;// 현재 포인터 이전줄까지의 크기 계산, 포인터 이동했으므로 보정
                
                fseek(fd, 0 , SEEK_SET); // 수정할 사람 앞부분의 자료
                
                if(copySize >= 0){ // 예외처리 copySize 가 음수가 나올경우 복사하지 않음
                    intResult = fread(cpyBuf, 1, copySize, fd);
                    if (intResult != copySize){
                        fprintf(stderr,"Reading error");
                        exit(1);
                    }
                    intResult = fwrite(cpyBuf, 1, copySize, fdc); //수정할 사람 앞부분의 데이터 fdc로 이동
                    if (intResult != copySize){
                        fprintf(stderr,"writing error");
                        exit(1);
                    }
                }
                
                fseek(fdc, 0, SEEK_END); // 파일포인터 위치 조정
                
                fprintf(fdc,"\n");
                
                fseek(fd, prevPo, SEEK_SET); // 원본파일의 파일포인터 수정할 사람의 파일 포인터로 다시 이동
                
                fgets(temp, MAX_SIZE, fd);//NAME에서 2줄 이동을 위해 fgets 사용
                fgets(temp, MAX_SIZE, fd);
                
                
                while(!feof(fd)){              //수정할 사람 다음사람들의 정보 fdc로 이동
                    if(fgets(cpyBuf, 1024, fd) != NULL) // 예외처리 : 맨끝정보 변경시 : 더이상 문자열을 읽을 수 없>을경우 읽지않음
                        fputs(cpyBuf, fdc);
                    cpyBuf[0] = '\0'; // 버퍼 초기화
                }
                
                fclose(fdc);
                fclose(fd);
                fileCopy();
                fprintf(stdout, "\n삭제 완료되었습니다.\n\n");
                clear_stdin();
                showMenu();
                return;
            }else{
                wordPo = fseek(fd, 1, SEEK_CUR);
                wordPo = ftell(fd);
                continue;
            }
        }
        
    }
    fprintf(stderr,"\n사용자 %s 은 없습니다.\n\n", name);
    fclose(fdc);
    fclose(fd);
    clear_stdin();
    showMenu();
    return;
}

// edit member function
void memberEdit(){
    
    FILE *fd = fopen("Student_List.txt", "r+");
    FILE *fdc = fopen("copy.txt", "w+");
    char buffer[MAX_SIZE], *ptr, name[MAX_SIZE], email[MAX_SIZE], temp[MAX_SIZE], input[MAX_SIZE];
    char cpyBuf[MAX_BUF];
    int wordPo, age, wordSize, intResult, currPo, prevPo;
    long copySize;
    
    
    clear_stdin();
    rewind(fd);
    rewind(fdc);
    
    if (fd == NULL){
        fprintf(stderr ,"\n파일을 여는데 실패하였습니다.\n\n");
        exit(1);
    }
    
    printf("수정할 이름은 ? : ");
    fgets(name, 256,stdin);
    clear_stdin();
    name[strlen(name)-1] = '\0'; //정확한 검색을 위해 배열값 조정
    
    // w+ 는 덮어쓰기는 가능하지만, 원본파일의 내용을 다 지워버리기 때문에 r+사용
    // name, age, email 모두 가변길이기 때문에, 뒤의 내용 훼손가능
    
    //해당 이름 탐색
    while(fgets(buffer, MAX_SIZE, fd) != NULL){
        ptr = strstr(buffer, name); //문자열 비교
        prevPo = ftell(fd);
        if (ptr != NULL){
            wordPo = -1*(strlen(buffer))+5;
            fseek(fd, wordPo, SEEK_CUR);
            fscanf(fd,"%d", &wordSize); // 글자수를 통한 정확한 검색
            if(wordSize == strlen(name)){
                copySize = prevPo - strlen(buffer) -1;// 현재 포인터 이전줄까지의 크기 계산, 포인터 이동했으므로 보정
                
                fseek(fd, 0 , SEEK_SET); // 수정할 사람 앞부분의 자료
                if(copySize >= 0){ // 예외처리 copySize 가 음수가 나올경우 복사하지 않음
                    intResult = fread(cpyBuf, 1, copySize, fd);
                    if (intResult != copySize){ // 예외처리 : 파일 복사 오류 감지
                        fprintf(stderr,"Reading error");
                        exit(1);
                    }
                    intResult = fwrite(cpyBuf, 1, copySize, fdc); //수정할 사람 앞부분의 데이터 fdc로 이동
                    if (intResult != copySize){ // 예외처리 : 파일 이동 오류 감지
                        fprintf(stderr,"writing error");
                        exit(1);
                    }
                }
                
                fseek(fdc, 0, SEEK_END);
                
                //수정할 사람의 데이터 다시입력
                fprintf(stdout,"사용자 %s 을 수정합니다.\n", name);
                name[0] = '\0'; //검색에 사용된 이름버퍼 초기화
                
                rewind(stdin);
                fprintf(stdout, "이름 : ");
                if(fgets(name, 256, stdin) != NULL){
                    clear_stdin();
                    wordSize = strlen(name);
                    if(wordSize == 255) name[wordSize] = '\n';
                    // 이름 항목 오버플로우 방지코드
                    if ((intResult = (fprintf(fdc,"\nNAME %d %s", wordSize-1, name)))>265 || intResult == '\0'){
                        fprintf(stderr, "\n writing error! \n\n");
                        exit(-1);
                    }
                }else{
                    fprintf(stderr,"\n\n data reading error!\n");
                }
                
                
                fprintf(stdout, "나이: ");
                fscanf(stdin, "%d", &age);
                if(age <= 200 && age >= 0){
                    clear_stdin();
                    if((intResult = (fprintf(fdc,"AGE %d\n", age))) == '\0'){
                        fprintf(stderr, "\n data reading error!\n");
                        exit(-1);
                    }
                }else{
                    fprintf(stderr, "나이는 음수이거나, 200살을 넘을 수 없습니다.2 임의값 200살로 저장됩니다.\n");
                    age = 200;
                    fprintf(fdc,"AGE %d\n", age);
                    
                }
                
                fprintf(stdout, "이메일 : ");
                fscanf(stdin, "%255s", email); //버퍼 오버플로우 방지
                wordSize = strlen(email);
                if (wordSize == 255) name[wordSize] = '\n';
                clear_stdin();
                if ((intResult = fprintf(fdc,"EMAIL %d %s\n",wordSize, email))>265 || intResult == '\0'){
                    fprintf(stderr, "\n writing error! \n\n");
                    exit(-1);
                }
                
                
                fseek(fd, prevPo, SEEK_SET); // 원본파일의 파일포인터 수정할 사람의 파일 포인터로 다시 이동
                
                fgets(temp, MAX_SIZE, fd);//NAME에서 2줄 이동을 위해 fgets 사용
                fgets(temp, MAX_SIZE, fd);
                
                
                while(!feof(fd)){              //수정할 사람 다음사람들의 정보 fdc로 이동
                    if(fgets(cpyBuf, 1024, fd) != NULL) // 예외처리 : 맨끝정보 변경시 : 더이상 문자열을 읽을 수 없>을경우 읽지않음
                        fputs(cpyBuf, fdc);
                    cpyBuf[0] = '\0'; // 버퍼 초기화
                }
                
                fclose(fdc);
                fclose(fd);
                fileCopy();
                fprintf(stdout, "\n수정이 완료되었습니다.\n\n");
                clear_stdin();
                showMenu();
                return;
            }else{
                wordPo = fseek(fd, 1, SEEK_CUR);
                wordPo = ftell(fd); //debug : filepointer 위치
                continue;
            }
        }
        
    }
    fprintf(stderr,"\n사용자 %s 은 없습니다.\n\n", name);
    fclose(fdc);
    fclose(fd);
    clear_stdin();
    showMenu();
    return;
}

void fileCopy(){
    FILE *fd = fopen("Student_List.txt", "w");
    FILE *fdc = fopen("copy.txt", "r");
    char cpyBuf[MAX_BUF];
    
    while(!feof(fdc)){              //수정된 데이터 fd로 이동
        fgets(cpyBuf, 1024, fdc);
        fputs(cpyBuf, fd);
        cpyBuf[0] = '\0'; // 버퍼 초기화
    }
    
    fclose(fd);
    fclose(fdc);
    
    return;
    
}

// show memeber list fucntion
void showList(){
    FILE *fd = fopen("Student_List.txt", "r");
    char cpyBuf[MAX_SIZE], property[MAX_SIZE], resultBuf[MAX_BUF];
    int wordsize;
    
    rewind(fd);
    while(!feof(fd)){              //수정된 데이터 fd로 이동
        fscanf(fd, "%s %d", property, &wordsize);
        if(strcmp(property, "NAME") == 0){ // 데이터가 NAME 항목일 때 출력
            fgets(cpyBuf, MAX_SIZE, fd);
            cpyBuf[strlen(cpyBuf)-1] = '\0';
            if((strlen(cpyBuf)-1) == wordsize){
                fprintf(stdout, "%s /",cpyBuf);
                cpyBuf[0] = '\0'; //내용을 복사할 버퍼 초기화
            }else{
                fprintf(stderr,"\n\ndata error! \n\n");
                exit(-1);
            }
        }else if(strcmp(property, "AGE") == 0){ // 데이터가 AGE 항목일 때 출력
            fprintf(stdout, " %d /",wordsize);
            fseek(fd, 1, SEEK_CUR);
            cpyBuf[0] = '\0';
        }else if(strcmp(property, "EMAIL") == 0){ // 데이터가 EMAIL 항목일 때 출력
            fgets(cpyBuf, MAX_SIZE, fd);
            if((strlen(cpyBuf)-2) == wordsize){
                cpyBuf[strlen(cpyBuf)-1] = '\0';
                fprintf(stdout, "%s\n",cpyBuf);
                cpyBuf[0] = '\0';
            }else if(feof(fd)){
                fprintf(stdout, "\n 모든 회원 리스트 출력 완료 \n\n");
                fclose(fd);
                clear_stdin();
                showMenu();
                return;
            }else{ // 예외처리 : 데이터의 글자수가 맞지 않거나, 변조가 의심될때 오류출력
                fprintf(stderr,"\n\ndata error! \n\n");
                exit(-1);
            }
        }else{ // 예외처리 : 데이터 입력 형식이 맞지 않을 때 오류출력
            fprintf(stderr, "\n\ndatabase error!!\n");
            exit(-1);
        }
    }
    fprintf(stdout,"\n모든 회원 리스트 출력 완료 \n\n");
    fclose(fd);
    clear_stdin();
    showMenu();
    return;
}

//show main menu function
void showMenu(){
    
    
    char choice;
    
    clear_stdin();
    
    fprintf(stdout, "1. 신규회원 저장\n");
    fprintf(stdout, "2. 회원정보 수정\n");
    fprintf(stdout, "3. 회원 삭제\n");
    fprintf(stdout, "4. 모든 회원 리스트\n");
    fprintf(stdout, "5. 종료\n");
    fprintf(stdout, "입력하세요> ");
    fscanf(stdin, " %c", &choice);
    
    clear_stdin();
    
    switch(choice){
            
        case '1' : memberAdd(); break;
        case '2' : memberEdit(); break;
        case '3' : memberDel(); break;
        case '4' : showList(); break;
        case '5' : fprintf(stdout, "\n 종료합니다. \n\n"); return;
        default :  fprintf(stderr, "\n\n메뉴 번호를 확인해 주세요\n\n"); break;//예외처리: 잘못된 번호가 입력
            되었을 시
    }
    
    
}


int main(int argc, char* argv[]){
    showMenu();
}
