#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 256
int addAscii = 0;

int* atoAscii(char* s)
{
    int i;
    int* change = (int*)malloc(strlen(s) * 2);
    for (i = 0; i < (int)strlen(s); i++) {
        change[i] = (unsigned char)s[i];
        addAscii += change[i];
    }
    return change;
    
}

void encoderUserStatus(char* encoded, char* original) {
    char charValue[512], id[512];
    int intValue, temp, *ASCIITemp, i = 0;
    
    FILE* encodedFile = fopen(encoded,"w+");
    FILE* originalFile = fopen(original,"r+");
    
    fgets(charValue, 255, originalFile);
    //USER STATUS 인식 추가
    if ((strcmp(charValue, "*USER STATUS*\n") == 0)) {
        fprintf(encodedFile, "d1\n");
    }
    
    addAscii = 0;
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "ID:") == 0)) {
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue) - 1;
        fprintf(encodedFile, "%d ", intValue);
        fprintf(encodedFile, "%s", charValue);
        ASCIITemp = atoAscii(charValue);
        for (int i = 0; i < intValue; i++)
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
    }
    
    fprintf(encodedFile, "\n%d", addAscii);
    addAscii = 0;
    
    
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "NAME:") == 0)) {
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue) - 1;
        fprintf(encodedFile, "\n%d ", intValue);
        fprintf(encodedFile, "%s", charValue);
        ASCIITemp = atoAscii(charValue);
        for (int i = 0; i < intValue; i++)
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
        
    }
    fprintf(encodedFile, "\n%d", addAscii);
    addAscii = 0;
    fscanf(originalFile, "%s ", id);
    
    if ((strcmp(id, "GENDER:") == 0)) {
        fgets(charValue, 255, originalFile);
        if ((strcmp(charValue, "FEMALE"))){
            fprintf(encodedFile, "\n1 F\n");
            fprintf(encodedFile, "%d\n", 'F');
        }
        else if (strcmp(charValue, "MALE")){
            fprintf(encodedFile, "\n0 M\n");
            fprintf(encodedFile, "%d\n", 'M');
        }
    }
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "AGE:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n", intValue, charValue);
        ASCIITemp = atoAscii(charValue);
        for(i=0; i < intValue; i++){
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
            
        }
    }
    fprintf(encodedFile, "\n%d\n", addAscii);
    addAscii = 0;
    
    fscanf(originalFile, "%s ", id);
    
    if ((strcmp(id, "HP:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n", intValue, charValue);
        ASCIITemp = atoAscii(charValue);
        for(i=0; i < intValue; i++){
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
            
        }
    }
    fprintf(encodedFile, "\n%d\n", addAscii);
    addAscii = 0;
    fscanf(originalFile, "%s ", id);
    
    if ((strcmp(id, "MP:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n", intValue, charValue);
        ASCIITemp = atoAscii(charValue);
        for(i=0; i < intValue; i++){
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
            
        }
    }
    fprintf(encodedFile, "\n%d\n", addAscii);
    addAscii = 0;
    
    
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "COIN:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n", intValue, charValue);
        ASCIITemp = atoAscii(charValue);
        for(i=0; i < intValue; i++){
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
            
        }
    }
    fprintf(encodedFile, "\n%d\n", addAscii);
    addAscii = 0;
    
    fclose(originalFile);
    fclose(encodedFile);
    return;
}
//------------------------------------------------------------------------//
void item_d2(FILE* originalFile, FILE* encodedFile)
{
    char buffer[255]; // ITEMS 확인하는 버퍼
    
    while (!feof(originalFile)) {
        fgets(buffer, 255, originalFile);
        if ((strcmp("*ITEMS*\n", buffer) == 0))
        {
            fseek(originalFile, -10, SEEK_CUR);//파일포인터 옮기기
            fprintf(encodedFile, "\nd2\n");
            break;
        }
    }
}
/*encode items*/
void encodedItems(char* original, char* encoded)
{
    char compareWord[255];
    char originalWord[255];
    char amountValue[255]; /*아이템 갯수*/
    int item_Maxcount = 0; /*아이템 최대 갯수*/
    int c;
    
    FILE* originalFile = fopen(original, "r");
    FILE* encodedFile = fopen(encoded,"a+");
    
    item_d2(originalFile, encodedFile);
    
    while (!feof(originalFile))
    {
        
        fscanf(originalFile, " %s", originalWord);
        
        if ((strcmp(originalWord, "BOMB:")) == 0)
        {
            fgets(amountValue, 255, originalFile);
            fprintf(encodedFile, "%s %d\n", "i1", atoi(amountValue));
            item_Maxcount += atoi(amountValue);
        }
        if ((strcmp(originalWord, "POTION:")) == 0)
        {
            fgets(amountValue, 255, originalFile);
            fprintf(encodedFile, "%s %d\n", "i2", atoi(amountValue));
            item_Maxcount += atoi(amountValue);
        }
        if ((strcmp(originalWord, "CURE:")) == 0)
        {
            fgets(amountValue, 255, originalFile);
            fprintf(encodedFile, "%s %d\n", "i3", atoi(amountValue));
            item_Maxcount += atoi(amountValue);
        }
        if ((strcmp(originalWord, "BOOK:")) == 0)
        {
            fgets(amountValue, 255, originalFile);
            fprintf(encodedFile, "%s %d\n", "i4", atoi(amountValue));
            item_Maxcount += atoi(amountValue);
        }
        if ((strcmp(originalWord, "SHIELD:")) == 0)
        {
            fgets(amountValue, 255, originalFile);
            fprintf(encodedFile, "%s %d\n", "i5", atoi(amountValue));
            item_Maxcount += atoi(amountValue);
        }
        if ((strcmp(originalWord, "CANNON:")) == 0)
        {
            fgets(amountValue, 255, originalFile);
            fprintf(encodedFile, "%s %d\n", "i6", atoi(amountValue));
            item_Maxcount += atoi(amountValue);
        }
        // 아무것도 없을경우 오류 출력
    }
    
    if (item_Maxcount == 0)
    {
        fprintf(stderr, "No Item Error occured.");
        
    }
    // 여기까지 인코드 작업
    
    if (item_Maxcount >= 256)
    {
        fprintf(stderr, "item amount error occured");
        exit(1);
    }
    // 아이템 최대갯수가 255를 넘었을 경우 오류출력 (이거를 굳이 해야하나 모르>겠네요)
    fclose(originalFile);
    fclose(encodedFile);
    return;
}


void friendList(char* original, char* encoded) {
    //originalFile = 원본파일, encodedFile =인코딩 된 파일
    char temp[MAX_STRING_SIZE];
    int *asciiResult;
    int lenStr,i=0;
    FILE* originalFile = fopen(original, "r");
    FILE* encodedFile = fopen(encoded,"a+");
    while (1) {//파일포인터 FRIENDLIST까지 이동시키기 위한 조치
        fgets(temp, 256, originalFile);
        if((strcmp(temp, "*FRIENDS LIST*\n")) == 0){
            fprintf(encodedFile, "\nd3\n");
            break;
        }
    }
    while (1) {
        fscanf(originalFile, "%s", temp);//한단어 읽기
        if (strcmp(temp, "*DESCRIPTION*") == 0) break;//friendlist끝난시점이면 종료
        else {//이외의 경우(FRIEND2)이 나왔을 경우
            fscanf(originalFile, "%s %[^\n]s", temp, temp);
            //값의 index와 value를 두번받음
            if (strcmp(temp, "MALE") == 0) {
                fprintf(encodedFile, "0 M\n");
                fprintf(encodedFile, "%d\n", 'M');
                fprintf(encodedFile, "%d\n", 'M');
            }//MALE인 경우
            else if (strcmp(temp, "FEMALE") == 0) {
                fprintf(encodedFile, "1 F\n");
                fprintf(encodedFile, "%d\n", 'F');
                fprintf(encodedFile, "%d\n", 'F');
            }
            //FEMALE인 경우
            else { //GENDER가 아닌경우(ID,NAME,AGE 인 경우)
                //fprintf(encodedFile, "%d ", (int)strlen(temp));//문자열 길이 기록(정>상x)
                //fprintf(encodedFile, "%s\n", temp);//value값을 파일에 적음
                //for (int i = 0; temp[i] != '\0'; i++)//요거 자주쓸거같은데 함수로 빼>도 되지 않나요
                //{//문자열 아스키코드 출력
                //  fprintf(encodedFile, "%d ", temp[i]);//문자를 아스키코드로 출력
                //}
                addAscii = 0;
                lenStr = strlen(temp);
                fprintf(encodedFile, "%d %s\n", lenStr, temp);
                asciiResult = atoAscii(temp);
                for(i=0; i < lenStr; i++){
                    fprintf(encodedFile, "%d ", asciiResult[i]);
                    
                }
                fprintf(encodedFile, "\n%d", addAscii);
                
                
                
                fprintf(encodedFile, "\n");
            }
        }
    }
    fclose(originalFile);
    fclose(encodedFile);
    return;
}

//--------------------------------------------------------------------------------------//

void functionEncoder(char* originalFile, char* encodedFile){
    encoderUserStatus(encodedFile,originalFile);
    encodedItems(originalFile,encodedFile);
    friendList(originalFile,encodedFile);
    
    return;
}

int main(int argc, char* argv[])
{
    
    //FILE* originalFile = fopen(argv[1]/*originalFile*/, "rt");
    //FILE* encodedFile = fopen(argv[2]/*encodedFile*/, "wt+");
    
    functionEncoder(argv[1],argv[2]);
    
    //fclose(originalFile);
    //fclose(encodedFile);
    
    return 0;
}






