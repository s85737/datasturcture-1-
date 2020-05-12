//
//  main.c
//  star
//
//  Created by 최제현 on 2020/05/12.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){ // main함수에 argument 입력받을 수 있게 설정


  if(argc == 2){ // argument의 갯수가 2이면 프로그램 시작

    int count = atoi(argv[1]); //argv에 저장된 문자열을 정수로 변환

if(count == 0){ //예외처리 argument 가 0또는 문자열로 입력되었을떄
                printf("1 이상 또는 숫자를 입력해주세요.\n");
                return 0;
    }

    for(int i = 0 ; i< count ; i++) { //별 삼각형 생성
      for(int j = 0 ; j<=i ; j++) {
        printf("*");
      }
      printf("\n");
    }
     return 0;
  }
  else{ //예외처리 argument가 입력되지 않거나 갯수를 초과입력하면 출력
  printf("usage) ./a.out number\n");
  }
  return 0;

}
