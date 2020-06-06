#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE 100

// 회원정보 저장을 위한 구조체
typedef struct _person
{
    char name[255];
    int age;
    char email[255];
}PERSON;


// 회원 추가 함수
void addUser(PERSON person[], int* index);
// 회원 수정 함수
void updateUser(PERSON person[], int index);
// 회원 삭제 함수
void deleteUser(PERSON person[], int* index);
// 회원 정보 저장 함수
void saveFile(PERSON person[], int index);



int main(void)
{
    // 회원은 최대 100명으로 가정
    PERSON person[MAX_SIZE];
    int menu;
    FILE* fp = NULL;

    // 파일에서 읽어온 한줄 저장
    char buffer[255];
    int personCount = 0;
    int i;

    // 파일로부터 신규회원 정보를 읽어와야 한다.
    fp = fopen("DB.txt", "r");
    if (fp == NULL) // 파일 오픈 에러
    {
        printf("DB File Open Error\n");
        return 0;
    }

    // 파일의 끝까지
    while (!feof(fp))
    {
        // buffer를 0으로 초기화한다.
        memset (buffer, 0, 255);
        // 한줄씩 읽으면서 캐리지리턴 및 줄바꿈문자를 제거한다.
        // 이름
        fgets(buffer, 254, fp);
        // buffer에 읽어온 문자열의 길이가 0이라면 더이상 데이터가 없음을 나타내므로 반복을 종료한다.
        if(strlen(buffer) == 0)
            break;
        if(buffer[strlen(buffer) - 2] == '\r')
            buffer[strlen(buffer) - 2] = 0;
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = 0;
        strcpy(person[personCount].name, buffer);

        // 나이
        fgets(buffer, 254, fp);
        if (buffer[strlen(buffer) - 2] == '\r')
            buffer[strlen(buffer) - 2] = 0;
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = 0;
        person[personCount].age = atoi(buffer);

        // 이메일
        fgets(buffer, 254, fp);
        if (buffer[strlen(buffer) - 2] == '\r')
            buffer[strlen(buffer) - 2] = 0;
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = 0;
        strcpy(person[personCount].email, buffer);

        // 사람 명수 증가
        personCount++;
    }

    // 파일 닫기
    fclose(fp);


    // 종료할때까지 반복
    while (1)
    {
        // 메뉴 출력
        printf("1. 신규회원 저장\n");
        printf("2. 회원정보 수정\n");
        printf("3. 회원 삭제\n");
        printf("4. 모든 회원 리스트\n");
        printf("5. 종료\n");
        printf("입력하세요> ");
        scanf("%d", &menu);

        // 종료를 선택하면 파일에 저장하고 종료한다.
        if (menu == 5)
        {
            saveFile(person, personCount);
            printf("종료합니다.\n");
            break;
        }

        // 종료가 아니면
        switch (menu)
        {
            // 회원 추가
            case 1:
                addUser(person, &personCount);
                break;
            // 회원 수정
            case 2:
                updateUser(person, personCount);
                break;
            // 회원 삭제
            case 3:
                deleteUser(person, &personCount);
                break;
            // 회원리스트 출력
            case 4:
                for (i = 0; i < personCount; i++)
                {
                    printf("%s / %d / %s\n", person[i].name, person[i].age, person[i].email);
                }
                printf("\n");
                break;
            default:
                break;
        }

    }

    return 0;
}


// 회원정보 추가함수
void addUser(PERSON person[], int* index)
{
    char YN;
    char* result;
    int count;
    char tempEmail[255];

    while (1)
    {
        count = 0;
        // 버퍼제거
        while (getchar() != '\n');

        // 구조체 배열에 정보를 입력받는다.
        printf("\n이름: ");
        gets(person[*index].name);
        printf("나이: ");
        scanf("%d", &person[*index].age);
        printf("이메일: ");
        scanf("%s", tempEmail);


        // 이메일 적합 여부를 따진다.
        strcpy(person[*index].email, tempEmail);

        result = strtok(tempEmail, "@");
        result = strtok(NULL, "@");

        if (result == NULL)
        {
            printf("이메일 형식에 적합하지 않습니다.\n");
        }
        else
        {
            result = strtok(result, ".");
            result = strtok(NULL, ".");
            if (result == NULL)
            {
                printf("이메일 형식에 적합하지 않습니다.\n");
            }
            else
            {
                result = strtok(NULL, ".");
                if (result != NULL)
                {
                    printf("이메일 형식에 적합하지 않습니다.\n");
                }
                else // 이메일이 형식에 적합한 경우
                {
                    (*index)++;
                }
            }
        }

        // 계속 입력 여부
        printf("계속 입력 할까요? (Y/N) ");
        scanf(" %c", &YN);

        if (YN == 'N' || YN == 'n')
        {
            printf("입력이 완료되었습니다.\n\n");
            break;
        }
    }
}


// 회원 정보 수정함수
void updateUser(PERSON person[], int index)
{
    int i;
    char tempName[255];
    char tempEmail[255];
    char updateName[255];
    char updateEmail[255];
    int updateAge;
    char* result;

    // 수정 이름 입력
    printf("수정할 사람 이름을 입력해주세요 : ");
    while (getchar() != '\n'); // 버퍼 제거
    gets(tempName);

    // 입력한 이름의 회원을 찾는다.
    for (i = 0; i < index; i++)
    {
        // 회원정보를 찾으면
        if (strcmp(tempName, person[i].name) == 0)
        {
            printf("사용자 %s 수정합니다.\n", tempName);

            // 수정할 회원정보를 입력 받는다.
            printf("이름: ");
            gets(updateName);
            printf("나이: ");
            scanf("%d", &updateAge);
            printf("이메일: ");
            scanf("%s", updateEmail);



            // 이메일이 부적합한지를 조사한다.
            strcpy(tempEmail, updateEmail);

            result = strtok(tempEmail, "@");
            result = strtok(NULL, "@");

            if (result == NULL)
            {
                printf("이메일 형식에 적합하지 않습니다.\n\n");
            }
            else
            {
                result = strtok(result, ".");
                result = strtok(NULL, ".");
                if (result == NULL)
                {
                    printf("이메일 형식에 적합하지 않습니다.\n\n");
                }
                else
                {
                    result = strtok(NULL, ".");
                    if (result != NULL)
                    {
                        printf("이메일 형식에 적합하지 않습니다.\n\n");
                    }
                    else // 적합한 경우
                    {
                        strcpy(person[i].name, updateName);
                        person[i].age = updateAge;
                        strcpy(person[i].email, updateEmail);
                                                
                        printf("수정 완료 되었습니다.\n\n");
                    }
                }
            }

            break;
        }
    }

    if (i == index)
    {
        printf("사용자 %s 은 없습니다.\n\n", tempName);
    }
}


// 회원 삭제 함수
void deleteUser(PERSON person[], int* index)
{
    int i;
    int k;
    char tempName[255];

    // 삭제할 이름을 입력받는다.
    printf("삭제할 사람 이름을 입력해주세요 : ");
    while(getchar() != '\n');
    gets(tempName);


    // 삭제할 회원을 찾는다.
    for (i = 0; i < *index; i++)
    {
        // 삭제할 회원을 발견하면
        if (strcmp(tempName, person[i].name) == 0)
        {
            printf("사용자 %s 를 삭제합니다.\n\n", tempName);

            // 현재 찾은 배열의 index 에 뒤의 배열값을 넣는다. (이걸 끝까지 반복하여, 한칸씩 앞당긴다)
            for (k = i; k < *index - 1; k++)
            {
                person[k] = person[k + 1];
            }
            // 한명이 삭제되었으므로 1명을 줄인다.
            (*index)--;

            break;
        }
    }

    if (i == *index)
    {
        printf("사용자 %s 은 없습니다.\n\n", tempName);
    }
}


// 파일에 저장
void saveFile(PERSON person[], int index)
{
    FILE* fp;
    int i;

    // DB 파일을 오픈한다. (쓰기모드)
    fp = fopen("DB.txt", "w");
    if (fp == NULL)
    {
        printf("File Save Error!!\n\n");
    }
    else
    {
        // 모든 회원정보를 다시 저장한다.
        for (i = 0; i < index; i++)
        {
            fprintf(fp, "%s\n", person[i].name);
            fprintf(fp, "%d\n", person[i].age);
            if(i == index - 1)
                fprintf(fp, "%s", person[i].email);
            else
                fprintf(fp, "%s\n", person[i].email);
        }
        fclose(fp);
    }
}
