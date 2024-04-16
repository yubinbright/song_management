#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    // 검색 함수 호출
    search();
    return 0;
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
    return 0;
}

// 노래 검색 함수 정의
void searchSong(char* filename, char* searchWord, int found) {
    // 파일 포인터 선언 및 파일 열기 시도
    FILE* file = fopen(filename, "r");
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

