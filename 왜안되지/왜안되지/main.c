#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[100];
    char age[100];
    char mail[100];
};

//cnt변수를 포인터로 한 것은 읽은 개수가 얼마인지 되돌려 줘야하므로
void loadData(struct Person* data, int* cnt) {
    FILE* fp = fopen("UserInfo.txt", "r");
    if (fp == NULL) return; //파일 없으면
    while (1)
    {
        if (fscanf(fp, "%s", data[*cnt].name) == EOF) break; //데이터를 못읽으면 루프탈출
        fscanf(fp, "%s", data[*cnt].age);
        fscanf(fp, "%s", data[*cnt].mail);
        (*cnt)++; //입력회원 카운트
    }
    fclose(fp);
}
void saveData(struct Person* data, int cnt)
{
    FILE* fp = fopen("UserInfo", "w+");
    int i;
    for (i = 0; i < cnt; i++) { //파일에 출력
        printf("%s %s %s", data[i].name, data[i].age, data[i].mail);
        fprintf(fp, "%s %s %s \n", data[i].name, data[i].age, data[i].mail);
    }
    fclose(fp);
}
int main()
{
    struct Person data[100];
    int cnt = 0; //저장된 회원
    int menu; //메뉴 선택지
    int i, j; //j = 회원 삭제시 다음 데이터로 덮어쓸 변수
    char n[20], a[20], m[20]; //n,a,m = 회원수정후 새로 다시 저장하는 곳
    char ch; //추가 계속
    char find[20];
    //struct Person tmp;
    loadData(data, &cnt);

    FILE* fp = fopen("UserInfo.txt", "w");

    while (1)
    {
        printf("1. 신규회원 저장 \n");
        printf("2. 회원정보 수정 \n"); // 추가해야 할 항목
        printf("3. 회원 삭제 \n");
        printf("4. 모든 회원 리스트 \n");
        printf("5. 종료 \n");

        printf("입력하세요>  ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            do {
                printf("이름: ");
                scanf(" %[^\n]s", data[cnt].name);

                printf("나이: ");
                scanf("%s", data[cnt].age);

                printf("이메일: ");
                scanf("%s", data[cnt].mail);

                fprintf(fp, "%s %s %s", data[cnt].name, data[cnt].age, data[cnt].mail);
                printf("%s %s %s", data[cnt].name, data[cnt].age, data[cnt].mail);

                cnt++;

                //데이터 추가계속
                printf("데이터 추가를 계속?(Y/N): ");
                scanf(" %[^\n]s", &ch);
                getchar();
                printf("\n");
            } while (ch != 'N');
            printf("입력이 완료되었습니다. \n\n");
            break;

        case 2: //회원 수정
            printf("수정할 회원 이름: ");
            scanf(" %[^\n]s", find);
            for (i = 0; i < cnt; i++) {
                if (strcmp(data[i].name, find) == 0)
                {
                    printf("%s %s %s \n", data[i].name, data[i].age, data[i].mail);
                    strcpy(data[i].name, find);

                    printf("이름: ");
                    scanf(" %[^\n]s", n);
                    strcpy(data[i].name, n);

                    printf("나이: ");
                    scanf("%s", a);
                    strcpy(data[i].age, a);

                    printf("이메일: ");
                    scanf("%s", m);
                    strcpy(data[i].mail, m);
                }

            }
            break;

        case 3: //회원 삭제
            printf("삭제할 회원: ");
            scanf(" %[^\n]s", find);

            for (i = 0; i < cnt; i++) //입력한 인원수 만큼 검색
            {
                if (strcmp(data[i].name, find) == 0) //같은 이름 찾으면 삭제-> 다음 데이터로 덮음
                    for (j = i; j < cnt - 1; j++)
                        data[j] = data[j + 1]; //다음 데이터로 덮어쓰기
                cnt--; //전체 개수 하나 줄임
            }

            break;

        case 4:
            printf("모든 회원 리스트 출력: \n");

            //원래 출력되어야 하는 함수
            printf("HONG GIL DONG / 20 / hong@gmail.com \n");
            printf("PARK GIL DONG / 20 / parkpark@hotmail.com \n");

            for (i = 0; i < cnt; i++) { //입력한 회원수 만큼 검색
                
                 printf("%s %s %s\n", data[i].name, data[i].age, data[i].mail);
                
            }
            printf("\n");

            break;

        case 5:
            saveData(data, cnt);
            printf("종료합니다");


            return(0);

        }
    }
    return 0;
}
