#include "header.h"

#define STRING_SIZE 256

struct Song {
    char title[STRING_SIZE];
    char singer[STRING_SIZE];
    char composer[STRING_SIZE];
    char lyricist[STRING_SIZE];
    char genre[STRING_SIZE];
    char playtime[STRING_SIZE];
    char album[STRING_SIZE];
    char release[STRING_SIZE];
};

//검색 함수 선언
void search();
// 노래 검색 함수 선언
void searchSong(char* filename, char* searchWord, int found);

void searchTag(); //태그 검색
void searchZero();//태그 검색에서 0 입력시
void searchWordOfTag(const char *filename, const char *tag, const char *word); //검색어 검색

void searchMenu(){
    int mode;
    int err = 0;
    while (1)
    {
        if (err == 0) {
            printf("\n노래 관리 프로그램입니다.\n");
            printf("원하는 메뉴를 선택하세요.\n\n");
        }
        else if (err == 1) {
            printf("\n해당 메뉴는 존재하지 않습니다.");
            printf("다시 선택하세요.\n\n");
            err = 0;
        }
        printf("1. 통합 검색\n");
        printf("2. 태그 검색\n");
        printf("0. 뒤로 가기\n\n");
        printf("메뉴 선택 : ");
        scanf(" %d", &mode);

        switch (mode) {
        case 1: //통합 검색
            system("cls");
            search();
            break;

        case 2: //태그 검색
            system("cls");
            searchTag();
            break;

        case 0: //뒤로 가기
            system("cls");
            main();
            break;

        default: //error
            err = 1;
            break;
        }
    }
}

// 검색 함수 정의
void search() {
    // 검색할 파일명 지정
    char filename[] = "song_list.txt";
    // 검색어 저장 변수 선언
    char searchWord[STRING_SIZE];
    // 검색 결과 여부를 나타내는 변수 초기화
    int found = 0;
    // 사용자에게 검색어 입력 요청
    printf("통합 검색을 선택하셨습니다.\n검색어를 입력하세요: ");
    // 사용자가 검색어를 입력할 때까지 반복
    do {
        // 사용자로부터 검색어 입력 받음
        fgets(searchWord, sizeof(searchWord), stdin);
        // 개행 문자 제거
        searchWord[strcspn(searchWord, "\n")] = '\0';
        // 검색 함수 호출
        searchSong(filename, searchWord, found);
        // 만약 검색 결과가 없다면 다시 검색어 입력 요청
        if (!found) {
            printf("해당 검색어는 존재하지 않습니다.\n검색어를 다시 입력하세요: ");
        }
    } while (!found);
    // return 0;
}

// 노래 검색 함수 정의
void searchSong(char* filename, char* searchWord, int found) {
    // 파일 포인터 선언 및 파일 열기 시도
    FILE* file = fopen("song_list.txt", "r");
    // 파일 열기 실패 시 메시지 출력 후 종료
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 노래 정보를 저장할 구조체 배열 선언
    struct Song song[STRING_SIZE];

    // 파일로부터 데이터 읽어와 구조체에 저장
    for (int i = 0; i < STRING_SIZE; i++)
        fscanf(file, "%s %s %s %s %s %s %s %s", &song[i].title, &song[i].singer, &song[i].composer, &song[i].lyricist, &song[i].genre, &song[i].playtime, &song[i].album, &song[i].release);

    // 검색어와 일치하는 노래 정보 출력
    for (int i = 0; i < STRING_SIZE; i++) {
        if (strstr(song[i].title, searchWord) != NULL ||
            strstr(song[i].singer, searchWord) != NULL ||
            strstr(song[i].composer, searchWord) != NULL ||
            strstr(song[i].lyricist, searchWord) != NULL ||
            strstr(song[i].genre, searchWord) != NULL ||
            strstr(song[i].playtime, searchWord) != NULL ||
            strstr(song[i].album, searchWord) != NULL ||
            strstr(song[i].release, searchWord) != NULL) {

            printf("제목: %s/", song[i].title);
            printf("가수: %s/", song[i].singer);
            printf("작곡가: %s/", song[i].composer);
            printf("작사가: %s/", song[i].lyricist);
            printf("장르: %s/", song[i].genre);
            printf("재생시간: %s/", song[i].playtime);
            printf("앨범명: %s/", song[i].album);
            printf("앨범출시날짜: %s/", song[i].release);
            printf("\n");
            // 검색 결과를 찾았으므로 found 변수를 1로 설정
            found = 1;
        }
    }

    fclose(file);
}

void searchTag() {
    char tag[STRING_SIZE], word[STRING_SIZE];
    int err = 0;
    int goback;
    while (1) {
        system("cls");
        if (err == 0) {
            printf("태그 검색을 선택하셨습니다.\n");
        } else {
            printf("해당 검색어는 존재하지 않습니다.\n");
            err = 0;
        }
        printf("(태그 = 제목/가수/작곡가/작사가/장르/재생시간/앨범명/앨범출시날짜)\n");
        printf("검색할 태그를 입력하세요 (0 입력 시 뒤로가기) : ");
        scanf("%s", tag);

        if (strcmp(tag,"제목") == 0 || strcmp(&tag,"가수") == 0 || strcmp(&tag,"작곡가") == 0 || strcmp(&tag,"작사가") == 0 || strcmp(&tag,"장르") == 0 || strcmp(&tag,"재생시간") == 0 || strcmp(&tag,"앨범명") == 0 || strcmp(&tag,"앨범출시날짜") == 0) {
            printf("검색어를 입력하세요 (0 입력 시 뒤로가기) : ");
            scanf("%s", word);
            printf("\n");
            if (word[0] == '0') {
                searchZero("song_list.txt", tag, word);
                break;
            } else {
                // 검색 결과 출력
                searchWordOfTag("song_list.txt", tag, word);
            }
            break;
        }
        else if(strcmp(&tag,"0") == 0){ // 뒤로가기
            searchMenu();
            break;
        }
        else{ // 잘못입력
            err = 1;
        }
    }
}

void searchZero(const char *filename, const char *tag, const char *word) {
    int err = 0;
    int goback = 0;
    while (1) {
        if (err == 0) {
            printf("'0'을 입력 하셨습니다. 정말 뒤로 가시겠습니까?\n\n");
        } else {
            printf("잘못 입력 하셨습니다. 다시 선택해주세요.\n\n");
            err = 0;
        }
        printf("1. 뒤로가기\n");
        printf("2. '0' 검색하기\n\n");
        printf("메뉴선택 : ");
        scanf("%d", &goback);
        printf("\n");
        if (goback == 1) {
            searchTag();
            break;
        } else if (goback == 2) { // '0' 검색
            searchWordOfTag("song_list.txt", tag, word);
            break;
        } else {
            err = 1;
            break;
        }
    }
}

void searchWordOfTag(const char *filename, const char *tag, const char *word) {
    FILE *file = fopen(filename, "r");

    struct Song song;
    char line[STRING_SIZE * 8]; // 가장 긴 라인의 길이를 기준으로 버퍼를 할당
    printf("제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범출시날짜\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        
        if (strcmp(tag, "제목") == 0 && strstr(song.title, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
        else if (strcmp(tag, "가수") == 0 && strstr(song.singer, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
        else if (strcmp(tag, "작곡가") == 0 && strstr(song.composer, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
        else if (strcmp(tag, "작사가") == 0 && strstr(song.lyricist, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
        else if (strcmp(tag, "장르") == 0 && strstr(song.genre, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
        else if (strcmp(tag, "재생시간") == 0 && strstr(song.playtime, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
        else if (strcmp(tag, "앨범명") == 0 && strstr(song.album, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
        else if (strcmp(tag, "앨범출시날짜") == 0 && strstr(song.release, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
                   song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
    }

    fclose(file);

    printf("\n메인화면으로 돌아가려면 아무키나 누르세요.");
    _getwch(); // 한글은 엔터를 쳐야함.
    system("cls");
    main();
}