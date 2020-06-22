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
    
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/copy.txt","w+");
    FILE* originalFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/UserInfo.txt","r+");
    
    fgets(charValue, 255, originalFile);
    //USER STATUS 인식 추가
    if ((strcmp(charValue, "*USER STATUS*\n") == 0)) {
        fprintf(encodedFile, "d1\n\n");
    }
    
    addAscii = 0;
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "ID:") == 0)) {
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue) - 1;
        fprintf(encodedFile, "%d ", intValue);
        fprintf(encodedFile, "%s\n", charValue);
        ASCIITemp = atoAscii(charValue);
        for (int i = 0; i < intValue; i++)
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
    }
    
    fprintf(encodedFile, "\n%d\n", addAscii-10);
    addAscii = 0;
    
    
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "NAME:") == 0)) {
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue) - 1;
        fprintf(encodedFile, "\n%d ", intValue);
        fprintf(encodedFile, "%s\n", charValue);
        ASCIITemp = atoAscii(charValue);
        for (int i = 0; i < intValue; i++)
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
        
    }
    fprintf(encodedFile, "\n%d\n", addAscii-10);
    addAscii = 0;
    fscanf(originalFile, "%s ", id);
    
    if ((strcmp(id, "GENDER:") == 0)) {
        fgets(charValue, 255, originalFile);
        if ((strcmp(charValue, "FEMALE"))){
            fprintf(encodedFile, "\n1 F\n\n");
            fprintf(encodedFile, "%d\n", 'F');
            fprintf(encodedFile, "%d\n\n", 'F');
        }
        else if (strcmp(charValue, "MALE")){
            fprintf(encodedFile, "\n0 M\n\n");
            fprintf(encodedFile, "%d\n", 'M');
            fprintf(encodedFile, "%d\n\n", 'M');
        }
    }
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "AGE:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n\n", intValue, charValue);
        ASCIITemp = atoAscii(charValue);
        for(i=0; i < intValue; i++){
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
            
        }
    }
    fprintf(encodedFile, "\n%d\n\n", addAscii);
    addAscii = 0;
    
    fscanf(originalFile, "%s ", id);
    
    if ((strcmp(id, "HP:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n\n", intValue, charValue);
        ASCIITemp = atoAscii(charValue);
        for(i=0; i < intValue; i++){
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
            
        }
    }
    fprintf(encodedFile, "\n%d\n\n", addAscii);
    addAscii = 0;
    fscanf(originalFile, "%s ", id);
    
    if ((strcmp(id, "MP:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n\n", intValue, charValue);
        ASCIITemp = atoAscii(charValue);
        for(i=0; i < intValue; i++){
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
            
        }
    }
    fprintf(encodedFile, "\n%d\n\n", addAscii);
    addAscii = 0;
    
    
    
    fscanf(originalFile, "%s ", id);
    if ((strcmp(id, "COIN:") == 0)) {
        fscanf(originalFile, "%[^ \n]s", charValue);
        
        intValue = strlen(charValue);
        fprintf(encodedFile, "%d %s\n\n", intValue, charValue);
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
      fprintf(encodedFile, "\nd2\n\n");
      break;
    }
  }
}

void itemASCII(FILE* encodedFile, char item[], char* amount){
  char temp[100];
  int num, totalASCII = 0;

  for(int i = 0; item[i] != '\0'; i++){
    temp[i] = item[i];
    num = i;
  }
  temp[++num] = ' ';

  for(int i = 0; amount[i] != '\0'; i++){
    temp[i + num] = amount[i];
  }
  for(int i = 0; temp[i] != '\n'; i++){
    fprintf(encodedFile,"%d ", temp[i]);
    totalASCII += (int)temp[i];
  }
  fprintf(encodedFile,"\n");
  fprintf(encodedFile,"%d\n\n",totalASCII);

  return;
}

void encodedItems(char* original, char* encoded)
{
  char compareWord[255];
  char originalWord[255];
  char amountValue[255]; /*아이템 갯수*/
  int item_Maxcount = 0; /*아이템 최대 갯수*/
  int c;

  FILE* originalFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/UserInfo.txt", "r");
     FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/copy.txt","a+");
     
  item_d2(originalFile, encodedFile);

  while (!feof(originalFile))
  {

    fscanf(originalFile, " %s", originalWord);

    if ((strcmp(originalWord, "BOMB:")) == 0)
    {
      fgets(amountValue, 255, originalFile);
      fprintf(encodedFile, "%d %s %d\n\n",(int)strlen(amountValue)+1, "i1", atoi(amountValue));
      itemASCII(encodedFile,"i1",amountValue);
      item_Maxcount += atoi(amountValue);
    }
    if ((strcmp(originalWord, "POTION:")) == 0)
    {
      fgets(amountValue, 255, originalFile);
      fprintf(encodedFile, "%d %s %d\n\n",(int)strlen(amountValue)+1, "i2", atoi(amountValue));
      itemASCII(encodedFile,"i2",amountValue);
      item_Maxcount += atoi(amountValue);
    }
    if ((strcmp(originalWord, "CURE:")) == 0)
    {
      fgets(amountValue, 255, originalFile);
      fprintf(encodedFile, "%d %s %d\n\n",(int)strlen(amountValue)+1, "i3", atoi(amountValue));
      itemASCII(encodedFile,"i3",amountValue);
      item_Maxcount += atoi(amountValue);
    }
    if ((strcmp(originalWord, "BOOK:")) == 0)
    {
      fgets(amountValue, 255, originalFile);
      fprintf(encodedFile, "%d %s %d\n\n",(int)strlen(amountValue)+1, "i4", atoi(amountValue));
      itemASCII(encodedFile,"i4",amountValue);
      item_Maxcount += atoi(amountValue);
    }
    if ((strcmp(originalWord, "SHIELD:")) == 0)
    {
      fgets(amountValue, 255, originalFile);
      fprintf(encodedFile, "%d %s %d\n\n",(int)strlen(amountValue)+1, "i5", atoi(amountValue));
      itemASCII(encodedFile,"i5",amountValue);
      item_Maxcount += atoi(amountValue);
    }
    if ((strcmp(originalWord, "CANNON:")) == 0)
    {
      fgets(amountValue, 255, originalFile);
      fprintf(encodedFile, "%d %s %d\n\n",(int)strlen(amountValue)+1, "i6", atoi(amountValue));
      itemASCII(encodedFile,"i6",amountValue);
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



int friendList(char* original, char* encoded) {
    //originalFile = 원본파일, encodedFile =인코딩 된 파일
    char temp[MAX_STRING_SIZE];
    int *asciiResult;
    int lenStr,i=0;
    char charValue[512], desline[512];
    int intValue, * ASCIITemp;
    FILE* originalFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/UserInfo.txt", "r");
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/copy.txt","a+");
    addAscii = 0;
    while (1) {//파일포인터 FRIENDLIST까지 이동시키기 위한 조치
      fgets(temp, 256, originalFile);
      if((strcmp(temp, "*FRIENDS LIST*\n")) == 0){
        strcpy(charValue, "d3\n");
        intValue = strlen(charValue)-1;
        charValue[intValue] = '\0';
        fprintf(encodedFile, "%d %s\n\n", intValue,charValue);
        ASCIITemp = atoAscii(charValue);
        for (int i = 0; i < intValue; i++)
          fprintf(encodedFile, "%d ", ASCIITemp[i]);
        fprintf(encodedFile, "\n%d\n\n", addAscii);
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
                fprintf(encodedFile, "0 M\n\n");
                fprintf(encodedFile, "%d\n", 'M');
                fprintf(encodedFile, "%d\n\n", 'M');
            }//MALE인 경우
            else if (strcmp(temp, "FEMALE") == 0) {
                fprintf(encodedFile, "1 F\n\n");
                fprintf(encodedFile, "%d\n", 'F');
                fprintf(encodedFile, "%d\n\n", 'F');
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
                fprintf(encodedFile, "%d %s\n\n", lenStr, temp);
                asciiResult = atoAscii(temp);
                for(i=0; i < lenStr; i++){
                    fprintf(encodedFile, "%d ", asciiResult[i]);
                    
                }
                fprintf(encodedFile, "\n%d\n", addAscii);
                
                fprintf(encodedFile, "\n");
            }
        }
    }
    i = ftell(originalFile);
    fclose(originalFile);
    fclose(encodedFile);
    return i;
}

void encodeDescription(char* original, char* encoded, int point)
{
    char charValue[512], desline[512];
    int intValue, temp, * ASCIITemp, i = 0;
    
    FILE* originalFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/UserInfo.txt", "r");
    FILE* encodedFile = fopen("/Users/s85737/Documents/2020:1/assignment/datastructure/datastucture1/왜안되지/왜안되지/copy.txt","a+");
    
    fseek(originalFile, point-30, SEEK_SET);
    addAscii =0;
    
    while (1) {//파일포인터 FRIENDLIST까지 이동시키기 위한 조치
        fgets(charValue, 255, originalFile);
        //USER STATUS 인식 추가
        if ((strcmp(charValue, "*DESCRIPTION*\n") == 0)) {
            strcpy(charValue, "d4\n");
            intValue = strlen(charValue)-1;
            charValue[intValue] = '\0';
            fprintf(encodedFile, "%d %s\n", intValue,charValue);
            ASCIITemp = atoAscii(charValue);
            for (int i = 0; i < intValue; i++)
                fprintf(encodedFile, "%d ", ASCIITemp[i]);
            fprintf(encodedFile, "\n%d\n\n", addAscii);
            break;
        }
        }
    

    addAscii = 0;

    while (!feof(originalFile))
    {
        fgets(charValue, 255, originalFile);
        intValue = strlen(charValue)-1;
        charValue[intValue] = '\0';
        fprintf(encodedFile, "%d %s\n", intValue,charValue);
        ASCIITemp = atoAscii(charValue);
        for (int i = 0; i < intValue; i++)
            fprintf(encodedFile, "%d ", ASCIITemp[i]);
        fprintf(encodedFile, "\n%d\n", addAscii);
    }
}

//--------------------------------------------------------------------------------------//

void functionEncoder(char* originalFile, char* encodedFile){
    int i=0;
    encoderUserStatus(encodedFile,originalFile);
    encodedItems(originalFile,encodedFile);
    i = friendList(originalFile,encodedFile);
    encodeDescription(originalFile, encodedFile, i);
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






