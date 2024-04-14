#include "header.h"


#define STRING_SIZE 256

struct Song { //구조체
    char title[STRING_SIZE];    //제목
    char singer[STRING_SIZE];   //가수
    char composer[STRING_SIZE]; //작곡가
    char lyricist[STRING_SIZE]; //작사가
    char genre[STRING_SIZE];    //장르
    char playtime[STRING_SIZE]; //재생시간
    char album[STRING_SIZE];    //앨범명
    char release[STRING_SIZE];  //앨범출시날짜

};

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int mode;
    int err = 0;
    while (1)
    {
        if (err == 0) {
            printf("\n노래 관리 프로그램입니다.\n");
            printf("원하는 메뉴를 선택하세요.\n\n");
        }
        else if (err == 1) {
            printf("\n해당 메뉴는 존재하지 않습니다.\n");
            printf("밑의 메뉴 중 선택하세요(예시:1)\n\n");
            err = 0;
        }
        printf("1. 노래 리스트 관리\n");
        printf("2. 검색 기능\n");
        printf("3. 플레이리스트\n");
        printf("4. 종료\n\n");
        printf("메뉴 선택 : ");
        scanf(" %d", &mode);

        switch (mode) {
        case 1: //노래 리스트 관리
            song_list_menu();
            break;

        case 2: //검색 기능

            break;

        case 3: //플레이리스트

            break;

        case 4: //종료

            break;

        default: //error
            err = 1;
            break;
        }
    }
    
    return 0;
}
