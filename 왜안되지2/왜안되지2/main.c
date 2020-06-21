#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_BUF_SIZE 256
int line = 0;
void printError(int line);
void printDesError(int line);

char* ASCIICheck(char* input){
    
    char* token = (char*)malloc(sizeof(char)*256);
    int* change = (int*)malloc(sizeof(int)*512);
    int i=0;
    
    do{
        if(* input     == '\n' ||
           *(input-1) == '\n' ||
           *(input-2) == '\n' ||
           *(input+1) == '\n' ||
           *(input+2) == '\n') {
            sscanf(input, "%d ",&change[i]);
            token[i] = change[i];
            token[i+1] = '\0';
            break;
        }
        else if (*(input+3) == '\n'){
            input -= 1;
            sscanf(input, "%d ",&change[i]);
            token[i] = change[i];
            break;
        }else{
            sscanf(input, "%d ",&change[i]);
            
            token[i] = change[i];
            i++;
        }
    }while(input+=3);
    
    return token;
}

/**
 *문자열 라인의 변조 여부를 탐색합니다.
 
 
 
 @author 최제현
 @version 6/13
 @params line : 현재 줄, intValue : 원본파일의 문자열 길이, cTemp : ASCII문자열, charValue : 읽어온 문자열
 @return
 0 : charValue 문자열 출력
 1 : ASCII 문자열 출력
 */

int modifyCheck(int line ,int intValue ,int ASCIISum, char* charResult, char* charValue){
    
    size_t lenStr, ASCIILen;
    int intTemp=0;
    
    lenStr = strlen(charValue);
    ASCIILen = strlen(charResult);
    
    for(int i = 0; i< ASCIILen+1; i++){
        intTemp += charResult[i];
    }
    
    if(strcmp(charValue, charResult) == 0 &&
       intValue == lenStr &&
       ASCIISum == intTemp
       ){
        //case 1 : 원본 문자열과, ASCII 문자열이 둘다 변조되지 않았을 때
        return 0;
        
    }else{
        
        //case 2 : 원본 문자열이나, ASCII 문자열 둘 중 하나가 변조되었을 때
        fprintf(stderr, "라인 %d에서 변조가 일어났습니다. %d %d %s %s\n", line, intTemp, ASCIISum, charResult, charValue);
        if(strcmp(charValue, "d4")){
        }else if(strcmp(charResult, "d4")){
        }else{
        printError(line);
        }
            if(ASCIISum == intTemp){
            //case 2-1 : 아스키코드 합의 값이 일치할때, 나머지 2개 변조의심
            return 1;
        }else if(intValue == lenStr){
            // 합의 값이 둘다 일치하지 않을때는 나머지 2개를 신뢰, 문자열 길이가 일치하면 0출
            return 0;
        }else{
            //case 2-2 : 아스키 코드 합이 둘다 일치하지않고, 문자열 길이도 일치하지 않을때
            //감점 최대한 덜되게
            return 1;
            
        }
        
    }
    
    //default
    return 0;
}

int modifyDesCheck(int line ,int intValue ,int ASCIISum, char* charResult, char* charValue){
    
    size_t lenStr, ASCIILen;
    int intTemp=0;
    
    lenStr = strlen(charValue);
    ASCIILen = strlen(charResult);
    
    for(int i = 0; i< ASCIILen+1; i++){
        intTemp += charResult[i];
    }
    
    if(strcmp(charValue, charResult) == 0 &&
       intValue == lenStr &&
       ASCIISum == intTemp
       ){
        //case 1 : 원본 문자열과, ASCII 문자열이 둘다 변조되지 않았을 때
        return 0;
        
    }else{
        
        //case 2 : 원본 문자열이나, ASCII 문자열 둘 중 하나가 변조되었을 때
//        fprintf(stderr, "라인 %d에서 변조가 일어났습니다. %d %d %s %s\n", line, intTemp, ASCIISum, charResult, charValue);
        if(strcmp(charValue, "d4")){
        }else if(strcmp(charResult, "d4")){
        }else{
        printDesError(line);
        }
            if(ASCIISum == intTemp){
            //case 2-1 : 아스키코드 합의 값이 일치할때, 나머지 2개 변조의심
            return 1;
        }else if(intValue == lenStr){
            // 합의 값이 둘다 일치하지 않을때는 나머지 2개를 신뢰, 문자열 길이가 일치하면 0출
            return 0;
        }else{
            //case 2-2 : 아스키 코드 합이 둘다 일치하지않고, 문자열 길이도 일치하지 않을때
            //감점 최대한 덜되게
            return 1;
            
        }
        
    }
    
    //default
    return 0;
}

void printError(int line){
    int friendIndex = 1;
    
    switch (line) {
        case 1:
            fprintf(stderr, "*USER STATUS* ID 섹션에서 변조가 발생했습니다.\n");
            break;
        case 2:
            fprintf(stderr, "*USER STATUS* NAME 섹션에서 변조가 발생했습니다.\n");
            break;
        case 3:
            fprintf(stderr, "*USER STATUS* GENDER 섹션에서 변조가 발생했습니다.\n");
            break;
        case 4:
            fprintf(stderr, "*USER STATUS* AGE 섹션에서 변조가 발생했습니다.\n");
            break;
        case 5:
            fprintf(stderr, "*USER STATUS* HP 섹션에서 변조가 발생했습니다.\n");
            break;
        case 6:
            fprintf(stderr, "*USER STATUS* MP 섹션에서 변조가 발생했습니다.\n");
            break;
        case 7:
            fprintf(stderr, "*USER STATUS* COIN 섹션에서 변조가 발생했습니다.\n");
            break;
        case 8:
            fprintf(stderr, "*USER STATUS* ITEM 섹션에서 변조가 발생했습니다.\n");
            break;
        case 9:
            fprintf(stderr, "*USER STATUS* ITEM 섹션에서 변조가 발생했습니다.\n");
            break;
        case 10:
            fprintf(stderr, "*USER STATUS* ITEM  섹션에서 변조가 발생했습니다.\n");
            break;
        case 11:
            fprintf(stderr, "*USER STATUS* ITEM 섹션에서 변조가 발생했습니다.\n");
            break;
            
            
        default:
            break;
    }
    
    if(line>12 ){
        friendIndex = (line - 13) / 5 + 1 ;
        line - 13;
        switch ((line % 5)) {
            case 0:
                fprintf(stderr,"\nFRIEND%d ID에서 변조가 일어났습니다.%d\n",friendIndex, line);
                break;
                
            case 1:
                fprintf(stderr,"\nFRIEND%d NAME에서 변조가 일어났습니다.%d\n",friendIndex, line);
                break;
            case 2:
                fprintf(stderr,"\nFRIEND%d GENDER에서 변조가 일어났습니다.%d\n",friendIndex, line);
                break;
            case 3:
                fprintf(stderr,"\nFRIEND%d AGE에서 변조가 일어났습니다.%d\n",friendIndex, line);
                break;
            case 4:
                fprintf(stderr,"\nFRIEND%d 공백구간에서 변조가 일어났습니다.%d\n",friendIndex, line);
                break;
                
            default:
                break;
        }
    }
}


void printDesError(int line){
if(line == 0){
    return;
}else{
    fprintf(stderr,"*DESCRIPTILON* %d라인에서 변조가 일어났습니다.\n",line);
}
}
/**
 *decoder 함수에서  d1 문자열을 인식하면 실행되는 함수입니다.
 *파일포인터는 d1 끝에서 시작한다고 가정하고,
 * 첫번째로 저장된, 원본 문자열 길이, encodedFile에 저장된 문자열의 길이 등을 비교.
 *라인마다 정해진 규칙대로 탐색합니다.
 
 @author 최제현
 @version 06/09 - 유니코드 or 아스키코드 비교 추가필요.
 params 파일원본,인코딩될 파일
 */

int decoderUserStatus(char* encoded, char* decoded){
    
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/encoded.txt", "rt");
    FILE* decodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/decoded.txt", "at+");
    
    char charValue[MAX_BUF_SIZE], asciiTemp[MAX_BUF_SIZE];
    char* charResult = malloc(sizeof(char)*256);
    char numValue[MAX_BUF_SIZE], asciiValue[MAX_BUF_SIZE];
    int intValue, temp, ASCIISum;
    char getSpace[512];
    int getPoint;
    

    fgets(charValue, 256, encodedFile);
    //USER STATUS 인식 추가
    if((strcmp(charValue, "d1\n") == 0)){
        fprintf(decodedFile,"*USER STATUS*\n");
    }else{
        printError(line);
        fprintf(stderr,"\n*USER STATUS* 섹션 구분에서 변조가 발생했습니다.\n");
    }
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        fprintf(stderr,"\n*USER STATUS* 섹션 구분에서 변조가 발생했습니다.\n");
    }
    
    line++;
    
    getPoint = ftell(encodedFile);
    
    fscanf(encodedFile, "%s ",numValue);
    intValue = atoi(numValue);
    fscanf(encodedFile, "%s ",charValue);
    //길이에서 개행문자 제거
    
    //ASCII코드 문자열로 변환
    fgets(asciiTemp, 256, encodedFile);
    fgets(asciiValue, 256, encodedFile);
    ASCIISum = atoi(asciiValue);
    strcpy(charResult, ASCIICheck(asciiTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"ID: %s\n", charValue);
    }else{
        fprintf(decodedFile,"ID: %s\n", charResult);
    }
    
    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        printError(line);
    }
    getPoint = ftell(encodedFile);
    line++;
    fscanf(encodedFile, "%s ",numValue);
    intValue = atoi(numValue);
    fgets(charValue, 255, encodedFile);
    charValue[strlen(charValue)-1] = '\0';
    //길이에서 개행문자 제거
    //ASCII코드 문자열로 변환
    fgets(asciiTemp, 256, encodedFile);
    fgets(asciiValue, 256, encodedFile);
    ASCIISum = atoi(asciiValue);
    strcpy(charResult, ASCIICheck(asciiTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"NAME: %s\n", charValue);
    }else{
        fprintf(decodedFile,"NAME: %s\n", charResult);
    }
    
    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        printError(line);
    }
    getPoint = ftell(encodedFile);
    line++;
    fscanf(encodedFile, "%s ",numValue);
    intValue = atoi(numValue);
    fscanf(encodedFile, "%s ",charValue);
    //길이에서 개행문자 제거
    
    //ASCII코드 문자열로 변환
    fgets(asciiTemp, 256, encodedFile);
    fgets(asciiValue, 256, encodedFile);
    ASCIISum = atoi(asciiValue);
    strcpy(charResult, ASCIICheck(asciiTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){//변경필요
        if((strcmp(charResult, "M"))==0){
            fprintf(decodedFile,"GENDER: MALE\n");
        }else if((strcmp(charResult, "F"))==0){
            fprintf(decodedFile,"GENDER: FEMALE\n");
        }else{
            printError(line);
        }
    }else{
        if((strcmp(charResult, "M"))==0){
            fprintf(decodedFile,"GENDER: MALE\n");
        }else if((strcmp(charResult, "F"))==0){
            fprintf(decodedFile,"GENDER: FEMALE\n");
        }else{
            printError(line);
        }
        
    }
    
    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        printError(line);
    }
    getPoint = ftell(encodedFile);
    
    line++;
    fscanf(encodedFile, "%s ",numValue);
    intValue = atoi(numValue);
    fscanf(encodedFile, "%s ",charValue);
    //길이에서 개행문자 제거
    
    //ASCII코드 문자열로 변환
    fgets(asciiTemp, 256, encodedFile);
    fgets(asciiValue, 256, encodedFile);
    ASCIISum = atoi(asciiValue);
    strcpy(charResult, ASCIICheck(asciiTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"AGE: %s\n", charValue);
    }else{
        fprintf(decodedFile,"AGE: %s\n", charResult);
    }
    
    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        printError(line);
    }
    getPoint = ftell(encodedFile);
    
    line++;
    fscanf(encodedFile, "%s ",numValue);
    intValue = atoi(numValue);
    fscanf(encodedFile, "%s ",charValue);
    //길이에서 개행문자 제거
    
    //ASCII코드 문자열로 변환
    fgets(asciiTemp, 256, encodedFile);
    fgets(asciiValue, 256, encodedFile);
    ASCIISum = atoi(asciiValue);
    strcpy(charResult, ASCIICheck(asciiTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"HP: %s\n", charValue);
    }else{
        fprintf(decodedFile,"HP: %s\n", charResult);
    }
    
    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        printError(line);
    }
    getPoint = ftell(encodedFile);
    
    line++;
    fscanf(encodedFile, "%s ",numValue);
    intValue = atoi(numValue);
    fscanf(encodedFile, "%s ",charValue);
    //길이에서 개행문자 제거
    
    //ASCII코드 문자열로 변환
    fgets(asciiTemp, 256, encodedFile);
    fgets(asciiValue, 256, encodedFile);
    ASCIISum = atoi(asciiValue);
    strcpy(charResult, ASCIICheck(asciiTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"MP: %s\n", charValue);
    }else{
        fprintf(decodedFile,"MP: %s\n", charResult);
    }
    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        printError(line);
    }
    getPoint = ftell(encodedFile);
    
    line++;
    fscanf(encodedFile, "%s ",numValue);
    intValue = atoi(numValue);
    fscanf(encodedFile, "%s ",charValue);
    //길이에서 개행문자 제거
    
    //ASCII코드 문자열로 변환
    fgets(asciiTemp, 256, encodedFile);
    fgets(asciiValue, 256, encodedFile);
    ASCIISum = atoi(asciiValue);
    strcpy(charResult, ASCIICheck(asciiTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"COIN: %s\n", charValue);
    }else{
        fprintf(decodedFile,"COIN: %s\n", charResult);
    }
    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        printError(line);
    }
    line++;
    temp = ftell(encodedFile);
    fclose(decodedFile);
    fclose(encodedFile);
    
    return temp;
}

int decoderItems(int filePointer, char* encoded, char* decoded){
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/encoded.txt", "rt");
    FILE* decodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/decoded.txt", "at+");
    fseek(encodedFile, filePointer, SEEK_SET);
    char buffer[MAX_BUF_SIZE];
    char getSpace[512];
    int getPoint;
    
    line++;
    
    fgets(buffer, 256, encodedFile);
    if((strcmp(buffer, "d2\n") == 0)){
        fprintf(decodedFile,"\n*ITEMS*\n");
    }else{
        fprintf(stderr,"\n*ITEMS 섹션 구분에서 변조가 발생했습니다.\n");
        fprintf(decodedFile,"*ITEMS*\n\n");
    }
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        fprintf(stderr,"\n*ITEMS 섹션 구분에서 변조가 발생했습니다.\n");
    }
    
    while (1) {//파일포인터 FRIENDLIST까지 이동시키기 위한 조치
        getPoint = ftell(encodedFile);
        fgets(buffer, 256, encodedFile);
        if((strcmp(buffer, "d3\n")) == 0){
            fseek(encodedFile, getPoint, SEEK_SET);
            break;
        }
    }
    
    
    filePointer = ftell(encodedFile);
    fclose(encodedFile);
    fclose(decodedFile);
    return filePointer;
    
}

//-----------------------------------------------------

int decoderFriendsList(int filePointer, char* encoded, char* decoded){
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/encoded.txt", "rt");
    FILE* decodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/decoded.txt", "at+");
    
    char charValue[MAX_BUF_SIZE], asciiTemp[MAX_BUF_SIZE];
    char numValue[MAX_BUF_SIZE], asciiValue[MAX_BUF_SIZE];
    char* charResult = malloc(sizeof(char)*256);
    int intValue, temp, ASCIISum;
    int index = 0;
    char getSpace[512];
    int getPoint;
    
    
    fseek(encodedFile, filePointer, SEEK_SET);
     fgets(charValue, 256, encodedFile);
    //USER STATUS 인식 추가
    line++;
    if((strcmp(charValue, "d3\n") == 0)){
        fprintf(decodedFile,"*FRIEND LIST*\n");
    }else{
        printError(line);
        fprintf(decodedFile,"*FRIEND LIST*\n");
    }
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        fprintf(stderr,"\n*FRIEND LIST 섹션 구분에서 변조가 발생했습니다.\n");
    }
    
    while(!feof(encodedFile)){
        index++;
        line++;
        
        getPoint = ftell(encodedFile);
        fscanf(encodedFile, "%s ",numValue);
        intValue = atoi(numValue);
        fscanf(encodedFile, "%s ",charValue);
        //길이에서 개행문자 제거
        
        
        //ASCII코드 문자열로 변환
        fgets(asciiTemp, 256, encodedFile);
        fgets(asciiValue, 256, encodedFile);
        ASCIISum = atoi(asciiValue);
        strcpy(charResult, ASCIICheck(asciiTemp));
        if((strcmp(charValue, "d4"))==0){
            fseek(encodedFile, getPoint, SEEK_SET);
            break;
        }else if((strcmp(charResult, "d4"))==0){
            fseek(encodedFile, getPoint, SEEK_SET);
            break;
        }
        temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);

        if(temp == 0){
            fprintf(decodedFile,"FRIEND%d ID: %s\n",index ,charValue);
        }else{
            fprintf(decodedFile,"FRIEND%d ID: %s\n",index, charResult);
        }
        fseek(encodedFile, getPoint, SEEK_SET);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        getPoint = ftell(encodedFile);
        fgets(getSpace, 512, encodedFile);
        if((strcmp(getSpace, "\n"))!=0){
            fseek(encodedFile, getPoint, SEEK_SET);
            printError(line);
        }
        getPoint = ftell(encodedFile);
        
        line++;
        fscanf(encodedFile, "%s ",numValue);
        intValue = atoi(numValue);
        fgets(charValue, 255, encodedFile);
        charValue[strlen(charValue)-1] = '\0';
        //길이에서 개행문자 제거
        
        //ASCII코드 문자열로 변환
        fgets(asciiTemp, 256, encodedFile);
        fgets(asciiValue, 256, encodedFile);
        ASCIISum = atoi(asciiValue);
        strcpy(charResult, ASCIICheck(asciiTemp));
        
        temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
        
        if(temp == 0){
            fprintf(decodedFile,"FRIEND%d NAME: %s\n",index ,charValue);
        }else{
            fprintf(decodedFile,"FRIEND%d NAME: %s\n",index, charResult);
        }
        
        fseek(encodedFile, getPoint, SEEK_SET);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        getPoint = ftell(encodedFile);
        fgets(getSpace, 512, encodedFile);
        if((strcmp(getSpace, "\n"))!=0){
            fseek(encodedFile, getPoint, SEEK_SET);
            printError(line);
        }
        getPoint = ftell(encodedFile);
        
        line++;
        fscanf(encodedFile, "%s ",numValue);
        intValue = atoi(numValue);
        fscanf(encodedFile, "%s ",charValue);
        //길이에서 개행문자 제거
        
        if(intValue == 0 || intValue == 1){
            intValue = 1;
        }else{
            printError(line);
            intValue = 2;
        }
        
        //ASCII코드 문자열로 변환
        fgets(asciiTemp, 256, encodedFile);
        fgets(asciiValue, 256, encodedFile);
        ASCIISum = atoi(asciiValue);
        strcpy(charResult, ASCIICheck(asciiTemp));
        
        temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
        
        if(temp == 0){//변경필요
            if((strcmp(charResult, "M"))==0){
                fprintf(decodedFile,"FRIEND%d GENDER: MALE\n",index);
            }else if((strcmp(charResult, "F"))==0){
                fprintf(decodedFile,"FRIEND%d GENDER: FEMALE\n",index);
            }else{
                printError(line);
            }
        }else{
            if((strcmp(charResult, "M"))==0){
                fprintf(decodedFile,"FRIEND%d GENDER: MALE\n",index);
            }else if((strcmp(charResult, "F"))==0){
                fprintf(decodedFile,"FRIEND%d GENDER: FEMALE\n",index);
            }else{
                printError(line);
            }
            
        }
        fseek(encodedFile, getPoint, SEEK_SET);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        getPoint = ftell(encodedFile);
        fgets(getSpace, 512, encodedFile);
        if((strcmp(getSpace, "\n"))!=0){
            fseek(encodedFile, getPoint, SEEK_SET);
            printError(line);
        }
        getPoint = ftell(encodedFile);
        
        line++;
        fscanf(encodedFile, "%s ",numValue);
        intValue = atoi(numValue);
        fscanf(encodedFile, "%s ",charValue);
        //길이에서 개행문자 제거
        
        //ASCII코드 문자열로 변환
        fgets(asciiTemp, 256, encodedFile);
        fgets(asciiValue, 256, encodedFile);
        ASCIISum = atoi(asciiValue);
        strcpy(charResult, ASCIICheck(asciiTemp));
        
        temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
        
        if(temp == 0){
            fprintf(decodedFile,"FRIEND%d AGE: %s\n\n",index ,charValue);
        }else{
            fprintf(decodedFile,"FRIEND%d AGE: %s\n\n",index, charResult);
        }
        line++;
        fseek(encodedFile, getPoint, SEEK_SET);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        getPoint = ftell(encodedFile);
        if((fgets(getSpace, 512, encodedFile)==NULL)) break;
        if((strcmp(getSpace, "\n"))!=0){
            fseek(encodedFile, getPoint, SEEK_SET);
            printError(line);
        }
        getPoint = ftell(encodedFile);
    
        if((strcmp(getSpace, "d4"))==0){
            fseek(encodedFile, getPoint, SEEK_SET);
            break;
        }else if((strcmp(charValue, "d4"))==0){
        fseek(encodedFile, getPoint, SEEK_SET);
            break;
        }else if((strcmp(charValue, "/"))==0){
        fseek(encodedFile, getPoint, SEEK_SET);
        break;
        }
        
    }
    getPoint = ftell(encodedFile);
    fclose(encodedFile);
    fclose(decodedFile);
    return getPoint;
}

void DecodeDescription(int filePointer, char* encoded, char* decoded)
{
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/encoded.txt", "rt");
    FILE* decodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지2/왜안되지2/decoded.txt", "at+");

    char numValue[256], asciiTemp[256];
    char charValue[256], asciiValue[256];
    char* charResult = malloc(sizeof(char) * 256);
    int intValue, temp, ASCIISum;
    int deline=0;


    char getSpace[512];
    int getPoint;

    fseek(encodedFile, filePointer, SEEK_SET);
    getPoint = ftell(encodedFile);

    fscanf(encodedFile, "%s ",numValue);
     intValue = atoi(numValue);
     fscanf(encodedFile, "%s ",charValue);
     //길이에서 개행문자 제거
     
     //ASCII코드 문자열로 변환
     fgets(asciiTemp, 256, encodedFile);
     fgets(asciiValue, 256, encodedFile);
     ASCIISum = atoi(asciiValue);
     strcpy(charResult, ASCIICheck(asciiTemp));
     
     temp = modifyDesCheck(deline, intValue, ASCIISum, charResult, charValue);
     
     if(temp == 0){
         fprintf(decodedFile, "*DESCRIPTION*\n");
     }else{
           fprintf(stderr, "*DESCRIPTION* 섹션 구분에서 변조가 발생했습니다.\n");
          fprintf(decodedFile, "*DESCRIPTION*\n");
     }


    fseek(encodedFile, getPoint, SEEK_SET);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    fgets(getSpace, 512, encodedFile);
    getPoint = ftell(encodedFile);
    fgets(getSpace, 512, encodedFile);
    if((strcmp(getSpace, "\n"))!=0){
        fseek(encodedFile, getPoint, SEEK_SET);
        fprintf(stderr, "*DESCRIPTION* 섹션 구분에서 변조가 발생했습니다.\n");
    }
    getPoint = ftell(encodedFile);



        line++;
        
        while(!feof(encodedFile)){
            deline++;
        getPoint = ftell(encodedFile);
        fscanf(encodedFile, "%s ", numValue);
        intValue = atoi(numValue);
        fscanf(encodedFile, "%s ", charValue);

        // 글자길이랑 , 원본 받기

        fgets(asciiTemp, 256, encodedFile); // 각 글자들에 대응하는 아스키코드 값 받기
        fgets(asciiValue, 256, encodedFile); // 아스키코드 값들의 합을 받기
        ASCIISum = atoi(asciiValue); //ASCIISum에 값의 합 정수형으로 저장하기
        strcpy(charResult, ASCIICheck(asciiTemp));
        // charResult에 ASCIICheck(asciiTemp)의 값을 복사하여 붙여넣음

        temp = modifyDesCheck(line, intValue, ASCIISum, charResult, charValue);

        if (temp == 0) {
            fprintf(decodedFile, "%s\n", charValue);
        }
        else {
            fprintf(decodedFile, "%s\n", charResult);
        }
        fseek(encodedFile, getPoint, SEEK_SET);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        fgets(getSpace, 512, encodedFile);
        getPoint = ftell(encodedFile);
        fgets(getSpace, 512, encodedFile);
             if(feof(encodedFile)) break;
        if ((strcmp(getSpace, "\n")) != 0) {
            fseek(encodedFile, getPoint, SEEK_SET);
            printDesError(deline);
        }
            getPoint = ftell(encodedFile);
            fgets(getSpace, 256, encodedFile);
            fgets(getSpace, 256, encodedFile);

            if(feof(encodedFile)) break;
            else fseek(encodedFile, getPoint, SEEK_SET);

        
}

        fclose(encodedFile);
        fclose(decodedFile);

    
}


void functionDecoder(char* encodedFile, char* decodedFile){
    int filePointer = 0;
    filePointer = decoderUserStatus(encodedFile, decodedFile);
    filePointer = decoderItems(filePointer, encodedFile, decodedFile);
    filePointer = decoderFriendsList(filePointer,encodedFile, decodedFile);
    DecodeDescription(filePointer, encodedFile, decodedFile);
}

int main(int argc, char* argv[])
{
    
    
    functionDecoder(argv[1],argv[2]);
    
    
    return 0;
}
