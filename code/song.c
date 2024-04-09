#include <stdio.h>

#define STRING_SIZE 256

struct Song { //구조체
    char title[STRING_SIZE];
    char singer[STRING_SIZE];
    char composer[STRING_SIZE];
    char lyricist[STRING_SIZE];
    char genre[STRING_SIZE];
    char playtime[STRING_SIZE];
    char album[STRING_SIZE];
    char release[STRING_SIZE];

};

int main(){
    int mode;
    printf("menu\n");
    printf("1. 노래 리스트 관리\n");
    printf("2. 검색 기능\n");
    printf("3. 플레이리스트\n");
    printf("4. 종료\n");
    printf("메뉴 선택 : ");
    scanf("%d",&mode);

    switch (mode){
        case 1: //노래 리스트 관리
            
            break;
        
        case 2: //검색 기능

            break;

        case 3: //플레이리스트

            break;

        case 4: //종료

            break;

        default: //error
            break;
    }
    return 0;
}
