//
//  main.c
//  pointer-array
//
//  Created by 최제현 on 2020/03/30.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int score[3] = { 91, 86, 97};
    char grade[3] = { 'A', 'B', 'A' };
    
    printf("총점과 등급의 관계\n");
    for (int i= 0; i < 3; i++) {
        printf("총점 %d = > 등급 %c\n", score[i], grade[i]);
    }
    
    //배열의 주소로 확인해보기
    for(int j =0; j< 3; j++){
        printf("score[%d]의 주소 : 0x%p\n", j, &score[j]); //주소는 %p
        printf("score[%d]의 내용 : %d\n", j, score[j]);
    }
    //포인터로 주소 확인해보기
    
    for (int j = 0; j <3; j++){
        printf("\nscore[%d]의 주소 : 0x%p\n", j, score+j);// score는 ? score배열의 이름을 저장하는 포인터 변수ㄱ
        printf("score[%d]의 내용 : %d\n", j, *(score+j));
    }
    system("PAUSE");
    
    return 0;
}
