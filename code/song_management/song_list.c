#include "header.h"

void song_list_menu() //노래 리스트 주 메뉴
{
	int mode, err=0;
	while (1)
	{
		if (err == 0) //입력 조건에 맞았을 때
		{
			printf("\n원하는 메뉴를 선택하세요.\n\n");
		}
		else //입력 조건에 맞지 않았을 때
		{
			printf("\n해당 메뉴는 존재하지 않습니다.\n");
			printf("밑의 메뉴 중 선택하세요(예시:1)\n\n");
			err = 0;
		}
		printf("1. 노래 리스트 출력\n");
		printf("2. 노래 추가\n");
		printf("3. 노래 삭제\n");
		printf("0. 뒤로 가기\n");
		printf("\n메뉴 선택 : ");
		scanf(" %d", &mode);

		switch (mode) {
		case 1: //노래 리스트 출력
			song_list_print();
			break;

		case 2: //노래 추가
			song_add();
			break;

		case 3: //노래 삭제
			song_dlt();
			break;

		case 0: //뒤로 가기
			return 0;
			break;
		default: //error
			while (getchar() != '\n'); //입력 버터 비우기
			err = 1;
			break;
		}
	}
}

void song_list_print()//노래 리스트 출력
{
	printf("\n노래 리스트를 출력합니다.");
	printf("\n\n제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범 출시 날짜\n");

}

void song_add()//노래 추가
{
	char name[100000];
	char singer[200];
	char song_writer[200];
	char lyric_writer[200];
	char genre[20];
	int play_time_hour = 0, play_time_min = 0, play_time_sec = 0;
	char album_name[200];
	int album_year = 0, album_month = 0, album_day = 0;
	printf("?");


}

void song_dlt(char* filename, char* dlt_text)//노래 삭제
{
	FILE* input_file = fopen(filename, "r");    //기존 txt파일
	if (input_file == NULL) {
    		printf("Error opening input file.\n");
    		return;
	}

	FILE* output_file = fopen("temp.txt", "w"); //새로 덮어씌울 txt파일
	if (output_file == NULL) {
    		printf("Error opening temporary file.\n");
    		fclose(input_file);
    		return;
	}

	char line[MAX_STRING_LENGTH];   //기존 문자열을 담아둘 배열
	int found = 0;  // 문자열 발견 여부 확인 변수
	while (fgets(line, MAX_STRING_LENGTH, input_file)) {    // 찾으려는 문자열이 포함된 행이 아닌 경우 새 파일에 쓰기
    		if (!strstr(line, text)) {
        		fputs(line, output_file);   // 제거하고자 하는 문자열과 일치하지 않으면 새로운 txt파일에 쓰기, 일치할 경우 해당 문자열은 쓰지 않음
    		}
    		else {
        		found = 1; // 문자열 발견
    		}
	}

	fclose(input_file);
	fclose(output_file);

	remove(filename);   // 기존 파일 삭제
	rename("temp.txt", filename);   // 새로 쓴 파일의 이름 변경

	if (found) {
    		printf("성공적으로 노래를 삭제했습니다.\n");
	}
	else {
    		printf("삭제하고자 하는 문자열을 발견하지 못했습니다.\n");
	}
}
