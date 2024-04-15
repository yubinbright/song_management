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

void searchSong(char* filename, char* searchWord);

int main() {
    char filename[] = "song_list.txt"; 
    char searchWord[STRING_SIZE];
    int found = 0;

    printf("통합 검색을 선택하셨습니다.\n검색어를 입력하세요: ");
    fgets(searchWord, sizeof(searchWord), stdin);
    searchWord[strcspn(searchWord, "\n")] = '\0';
    do {
        searchSong(filename, searchWord);
        if (!found) {
            printf("해당 검색어는 존재하지 않습니다.\n검색어를 다시 입력하세요: ");
            fgets(searchWord, sizeof(searchWord), stdin);
            searchWord[strcspn(searchWord, "\n")] = '\0';
        }
    } while (!found);
    return 0;
}

void searchSong(char* filename, char* searchWord) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    struct Song song;

    while (fgets(song.title, sizeof(song.title), file)) {
        song.title[strcspn(song.title, "\n")] = '\0';

        if (strstr(song.title, searchWord) != NULL ||
            strstr(song.singer, searchWord) != NULL ||
            strstr(song.composer, searchWord) != NULL ||
            strstr(song.lyricist, searchWord) != NULL ||
            strstr(song.genre, searchWord) != NULL ||
            strstr(song.playtime, searchWord) != NULL ||
            strstr(song.album, searchWord) != NULL ||
            strstr(song.release, searchWord) != NULL) {

            printf("제목: %s/", song.title);
            printf("가수: %s/", song.singer);
            printf("작곡가: %s/", song.composer);
            printf("작사가: %s/", song.lyricist);
            printf("장르: %s/", song.genre);
            printf("재생시간: %s/", song.playtime);
            printf("앨범명: %s/", song.album);
            printf("앨범출시날짜: %s/", song.release);
            printf("\n");
        }
    }

    fclose(file);
}
