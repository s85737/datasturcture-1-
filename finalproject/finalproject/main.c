//
//  main.c
//  finalproject
//
//  Created by 최제현 on 2020/06/09.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int temp = 0;

int* singi_atol(char *s)
{
    int i;
    
    int *change = (unsigned int *)malloc(strlen(s)*2);
    
    for (i=0; i < (int)strlen(s) ; i++){
        change[i] = (unsigned char)s[i];
        temp += change[i];
    }
    return change;
    free(change);
}



/**
 *encoder 함수에서  *USER STATUS* 문자열을 인식하면 실행되는 함수입니다.
 *파일포인터는 USER STATUS 끝에서 시작한다고 가정하고, ID 등등을 인식하면
 *짧게 압축하여 인코딩 될 TXT 파일에 저장합니다.
 *라인마다 ID: value 라고 보고, 라인마다 탐색을 해서 저장합니다.
 
 @author 최제현
 @version 06/09 - *USER STATUS* 문자열 인식 구현은 하지 않았습니다. 추후 수정
 params 파일원본,인코딩될 파일
 */

FILE* encodeUserState(FILE* encodedFile, FILE* originalFile){
    char charValue[1024], id[1024];
    int intValue, *ASCIITemp, i;
    
    fgets(charValue, 255, originalFile);
    //USER STATUS 인식 추가
    if((strcmp(charValue, "*USER STATUS*\n") == 0)){
        fprintf(encodedFile,"d1\n");
    }
   
    
    
    fscanf(originalFile, "%s ",id);
    if((strcmp(id, "ID:") == 0)){
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue)-1;
        fprintf(encodedFile,"%d ",intValue);
        fprintf(encodedFile,"%s",charValue);
        ASCIITemp = singi_atol(charValue);
        for(i =0; i < intValue; i++ )
            fprintf(encodedFile,"%d ",ASCIITemp[i]);
    }
    
    fprintf(encodedFile,"\n");
    fprintf(encodedFile,"%d",temp-10);
    temp = 0;
    
    fscanf(originalFile, "%s ",id);
    if((strcmp(id, "NAME:") == 0)){
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue)-1;
        fprintf(encodedFile,"\n%d ",intValue);
        fprintf(encodedFile,"%s",charValue);
        ASCIITemp = singi_atol(charValue);
        for(i =0; i < intValue; i++ )
            fprintf(encodedFile,"%d ",ASCIITemp[i]);
    }
    fprintf(encodedFile,"\n");
    fprintf(encodedFile,"%d",temp-10);
    fscanf(originalFile, "%s ",id);
    
    if((strcmp(id, "GENDER:") == 0)){
        fgets(charValue, 255, originalFile);
        if((strcmp(charValue, "FEMALE")))
            fprintf(encodedFile,"\n1 F\n");
        else if(strcmp(charValue, "MALE"))
            fprintf(encodedFile,"\n0 M\n");
    }
    fscanf(originalFile, "%s ",id);
    if((strcmp(id, "AGE:") == 0)){
        fgets(charValue, 255, originalFile);
        intValue = atoi(charValue);
        fprintf(encodedFile,"%d\n",intValue);
    }
    fscanf(originalFile, "%s ",id);
    
    if((strcmp(id, "HP:") == 0)){
        fgets(charValue, 255, originalFile);
        intValue = atoi(charValue);
        fprintf(encodedFile,"%d\n",intValue);
    }
    fscanf(originalFile, "%s ",id);
    
    if((strcmp(id, "MP:") == 0)){
        fgets(charValue, 255, originalFile);
        intValue = atoi(charValue);
        fprintf(encodedFile,"%d\n",intValue);
    }
    fscanf(originalFile, "%s ",id);
    if((strcmp(id, "COIN:") == 0)){
        fgets(charValue, 255, originalFile);
        intValue = atoi(charValue);
        fprintf(encodedFile,"%d\n",intValue);
    }
    fclose(encodedFile);
    return encodedFile =  fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/encodedFile.txt", "rt+");
    
    // encodedFile 닫고 다시 리턴 임시조치임.
}



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
        fprintf(stderr, "라인 %d에서 변조가 일어났습니다. %d %d %s %s\n", line, intValue, ASCIISum, charResult, charValue);
        if(ASCIISum == intTemp){
            //case 2-1 : 아스키코드 합의 값이 일치할때, 나머지 2개 변조의심
            return 1;
        }else if(intValue == lenStr){
            // 합의 값이 둘다 일치하지 않을때는 나머지 2개를 신뢰, 문자열 길이가 일치하면 0출
            return 0;
        }else{
            //case 2-2 : 아스키 코드 합이 둘다 일치하지않고, 문자열 길이도 일치하지 않을때
            //감점 최대한 덜되게
        
            return 0;
            
        }
        
    }
    
    //default
    return 0;
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


void decodeUserState(){
    
    FILE* decodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/decodedFile.txt", "wt");
    
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/encodedFile2.txt", "rt+");
    
    char charValue[1024], cTemp[1024];
    char *charResult = malloc(sizeof(char)*256);
    int intValue, temp, ASCIISum, line = 0;
    
    fseek(encodedFile, 0, SEEK_SET);
    
    line++;
    fgets(charValue, 255, encodedFile);
    //USER STATUS 인식 추가
    if((strcmp(charValue, "d1\n") == 0)){
        fprintf(decodedFile,"*USER STATUS*\n");
    }
    line++;
    fscanf(encodedFile, "%d ",&intValue);
    fgets(charValue, 255, encodedFile);
    charValue[strlen(charValue)-1] = '\0';
    //길이에서 개행문자 제거
    
    //ASCII코드 문자열로 변환
    fgets(cTemp, 256, encodedFile);
    fscanf(encodedFile,"%d", &ASCIISum);
    strcpy(charResult, ASCIICheck(cTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"ID: %s", charValue);
    }else{
        fprintf(decodedFile,"ID: %s", charResult);
    }
    
    line++;
    fscanf(encodedFile, "%d ",&intValue);
    fgets(charValue, 255, encodedFile);
    charValue[strlen(charValue)-1] = '\0';
    
    //유니코드 비교 추가
    fgets(cTemp, 256, encodedFile);
    fscanf(encodedFile,"%d", &ASCIISum);
    strcpy(charResult, ASCIICheck(cTemp));
    
    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);
    
    if(temp == 0){
        fprintf(decodedFile,"\nNAME: %s", charValue);
    }else{
        fprintf(decodedFile,"\nNAME: %s", charResult);
    }
    
    
    line++;
    fscanf(encodedFile, "%d ",&intValue);
    fgets(charValue, 2, encodedFile);
    if((strcmp(charValue, "F")) == 0) temp = 1;
    else if((strcmp(charValue, "M")) == 0) temp = 0;
    else fprintf(stderr,"예외처리 필요!");
    
    //유니코드 비교 추가
    if(intValue == temp & temp == 0){ //charValue 자체 문자열을 바꿔도 되지만,
        fprintf(decodedFile,"\nGENDER: MALE");
    }else if (intValue == temp & temp == 1){
        fprintf(decodedFile,"\nGENDER: FEMALE");
    }
    
    fclose(decodedFile);
    
    line++;
    fscanf(encodedFile, "%d ",&intValue);
    fgets(charValue, 255, encodedFile);
    charValue[strlen(charValue)-1] = '\0';
    //길이에서 개행문자 제거

    //ASCII코드 문자열로 변환
    fgets(cTemp, 256, encodedFile);
    fscanf(encodedFile,"%d", &ASCIISum);
    strcpy(charResult, ASCIICheck(cTemp));

    temp = modifyCheck(line, intValue, ASCIISum, charResult, charValue);

    if(temp == 0){
      fprintf(decodedFile,"AGE: %s\n", charValue);
    }else{
      fprintf(decodedFile,"AGE: %s\n", charResult);
    }
    
}

int main(int argc, char* argv[]){
    
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/encodedFile.txt", "wt+");
    FILE* originalFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/test1_sample.txt", "rt");
    // 일반버퍼, 항목, 저장된 값 버퍼
    
    encodedFile = encodeUserState(encodedFile, originalFile);
    
    decodeUserState();
    
    fclose(originalFile);
    fclose(encodedFile);
    
    
    return 0;
}
