#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char* argv[])
{
FILE *fp;

fp = fopen("player.bin","ab");

if ( fp==NULL)

{
fprintf(stderr,"ERROR ocuured");
return 1;

}

char buffer[254];
int stack;


for (;;)
{
printf("1. 플레이어 정보 기록\n2. 플레이어 정보 확인\n3. 종료\n입력하세요>");

scanf("%d",&stack);

switch(stack)
{

case 1:
{
char ID[254];
int age;
int HP;
double x;
double y;
int i;
char fr[254][254];
int temp;
int count;
char yn;


printf("ID를 입력하세요:");
scanf("%s",ID);
fwrite(ID,sizeof(ID),1,fp);

for (;;){

  printf("나이를 입력하세요:");
  scanf("%d",&age);


if ( 128 <= age || age < 0)
{
  printf("0~ 127 사이로 다시 입력해주세요.");
  scanf("%d",&age);

}

else
{
  fwrite(&age,sizeof(age),1,fp);
  break;

}

  }



printf("HP를 입력하세요:");
scanf("%d",&HP);
fwrite(&HP,sizeof(HP),1,fp);



printf("X좌표를 입력하세요:");
scanf(" %lf",&x);
fwrite(&x,sizeof(x),1,fp);

printf("Y좌표를 입력하세요:");
scanf(" %lf",&y);
fwrite(&y,sizeof(y),1,fp);


for ( ;; )
{
printf("동맹 ID를 입력하세요:");



for (i =0 ;temp != 1 ; i++)
{
scanf("%s",fr[i]);



printf("동맹을 계속 추가할까요? (y/n) : ");
scanf(" %c",&yn);

if(yn == 'n' || 'N')
{
printf("완료되었습니다.");
fwrite(&i,sizeof(i),1,fp);
temp = 1;
}

}

for (int k = 0 ; k <=i ; k++)
{
fwrite(&fr[k][254],sizeof(fr),1,fp);
}

break;
}


}
break;

case 2:

{

fseek(fp,0,SEEK_SET);

char output[254];
char fr2[254][254];
int age2;
int HP2;
double x2;
double y2;
int frnum2;
int d;
int c;

fread(output, sizeof(output) , 1, fp);
fread(&age2, sizeof(age2),1,fp);
fread(&HP2, sizeof(HP2),1,fp);
fread(&x2, sizeof(x2),1,fp);
fread(&y2, sizeof(y2),1,fp);


printf("ID: %s / 나이: %d / HP:  %d /좌표: %.3lf , %.3lf \n", output,age2,HP2,x2,y2 );


fread(&frnum2,sizeof(frnum2),1,fp);
printf("등록된 동맹 수 : %d", frnum2+1);

for(c = 0 ; c <= frnum2 ;c++)
{
fread(fr2[c], sizeof(fr2),1,fp);
}




for(d = 0; d <= frnum2 ; d++)
{

printf("%s",fr2[d]);

if (d == frnum2 )
{
printf("\n완료되었습니다.");
break;
}
else
{
printf(" / ");
}



}

}
break;
 // case 닫기
case 3:
{
  printf("종료되었습니다.");
  exit(1);

}

} //while 문 닫기

break;
} // for문 닫기


fclose(fp);
return 0;
}
