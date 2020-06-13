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


/**
 *encoder 함수에서  *USER STATUS* 문자열을 인식하면 실행되는 함수입니다.
 *파일포인터는 USER STATUS 끝에서 시작한다고 가정하고, ID 등등을 인식하면
 *짧게 압축하여 인코딩 될 TXT 파일에 저장합니다.
 *라인마다 ID: value 라고 보고, 라인마다 탐색을 해서 저장합니다.
 
 @author 최제현
 @version 06/09 - *USER STATUS* 문자열 인식 구현은 하지 않았습니다. 추후 수정
 params 파일원본,인코딩될 파일
 */
int* singi_atol(char *s, FILE* encodedFIle)
{
    int i;
    
    int *change = (unsigned int *)malloc(strlen(s)*2);
    for (i=0; i < (int)strlen(s) ; i++){
        change[i] =(unsigned char)s[i];
    }
    return change;
    
}

FILE* encodeUserState(FILE* encodedFile, FILE* originalFile){
    char charValue[1024], id[1024];
    int intValue, temp, *ASCIITemp;
    
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
        ASCIITemp = singi_atol(charValue, encodedFile);
        for(int i =0; i < intValue; i++ )
            fprintf(encodedFile,"%d ",ASCIITemp[i]);
        
    }
    fscanf(originalFile, "%s ",id);
    if((strcmp(id, "NAME:") == 0)){
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue)-1;
        fprintf(encodedFile,"\n%d ",intValue);
        fprintf(encodedFile,"%s",charValue);
        ASCIITemp = singi_atol(charValue, encodedFile);
        for(int i =0; i < intValue; i++ )
            fprintf(encodedFile,"%d ",ASCIITemp[i]);
        
    }
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
           *(input+2) == '\n') break;
        else if(*(input+3) == '\n') *(input+2);
        sscanf(input, "%d ",&change[i]);
        
        token[i] = change[i];
        i++;
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

int modifyCheck(int line ,int intValue ,char* cTemp, char* charValue){
    
    size_t strLen, ASCIILen;
    int temp;
    
    strLen = strlen(charValue);
    ASCIILen = strlen(cTemp);
    
    if(intValue == strLen &&
       strLen == ASCIILen &&
       strcmp(charValue, cTemp) == 0){
        //case 1 : 아스키 길이, 원본길이, 문자열길이가 모두 일치하고 아스키와 문자열이 일치할 때
        
    }else if(intValue != strLen &&
             strLen == ASCIILen &&
             strcmp(charValue, cTemp) == 0){
        //case 2 : 원본길이가 변조된것이 의심될 때
        //문자열 길이와, ASCII길이가 같고, 문자열이 같을 때
        fprintf(stderr, "라인 %d에서 변조가 일어났습니다.\n", line);
    }else if(intValue != strLen &&
             intValue == ASCIILen){
        fprintf(stderr, "라인 %d에서 변조가 일어났습니다.\n", line);
    }
    
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


void decodeUserState(FILE* encodedFile){
    FILE* decodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/decodedFile.txt", "wt");
    char charValue[1024], id[1024], cTemp[1024];
    int intValue, strLen, temp, ASCIILen, line = 0;
    
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
    strcpy(cTemp, ASCIICheck(cTemp));
    ASCIILen = strlen(cTemp);
    if(intValue == strLen && strLen == ASCIILen){
        
                fprintf(decodedFile,"ID: %s",charValue);
    } // 다를경우 mark
    line++;
    fscanf(encodedFile, "%d ",&intValue);
    fgets(charValue, 255, encodedFile);
    charValue[strlen(charValue)-1] = '\0';
    
    //유니코드 비교 추가
    fgets(cTemp, 256, encodedFile);
    strcpy(cTemp, ASCIICheck(cTemp));
    
    
    temp = modifyCheck(line, intValue, cTemp, charValue);
    fprintf(decodedFile,"\nNAME: %s", charValue);
    
    line++;
    fscanf(encodedFile, "%d ",&intValue);
    fgets(charValue, 2, encodedFile);
    if((strcmp(charValue, "F")) == 0) temp = 1;
    else if((strcmp(charValue, "M")) == 0) temp = 0;
    else fprintf(stderr,"예외처리 필요!");
    
    //유니코드 비교 추가
    if(intValue == temp & temp == 0){ //charValue 자체 문자열을 바꿔도 되지만, 귀찮아서 이래함
        fprintf(decodedFile,"\nGENDER: MALE");
    }else if (intValue == temp & temp == 1){
        fprintf(decodedFile,"\nGENDER: FEMALE");
    }
    
    fclose(decodedFile);
    
}

int main(int argc, char* argv[]){
    
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/encodedFile.txt", "wt+");
    FILE* originalFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/finalproject/finalproject/test1_sample.txt", "rt");
    // 일반버퍼, 항목, 저장된 값 버퍼
    
    encodedFile = encodeUserState(encodedFile, originalFile);
    
    decodeUserState(encodedFile);
    
    fclose(originalFile);
    fclose(encodedFile);
    
    
    return 0;
}
