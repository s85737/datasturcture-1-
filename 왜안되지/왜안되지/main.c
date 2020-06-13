#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char *mes="efg_@#$%^&*";
    int *change;
    int i;
    char* itoa;
    change = (unsigned int *)calloc(strlen(mes),sizeof(char));
    itoa = (unsigned char *)calloc(strlen(mes),sizeof(char));
    
    for (i=0; i < (int)strlen(mes) ; i++) change[i] = mes[i] ;
    for (i=0; i < (int)strlen(mes) ; i++) itoa[i] = change[i] ;
    
    for(i=0; i< (int)strlen(mes);i++) printf("%d/",change[i]);
    printf("\n%s", itoa);
    
    return 0;
    
}
