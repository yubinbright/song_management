#include "header.h"
#define MAX_SIZE 100000
#define STRING_SIZE 256

int IsSpace(char ch);
char* strrtrim(char* s);
char* strltrim(char* s);
char* trim(char* s);

int IsSpace(char ch)
{
	if (ch < 0)  // 음수인경우 한글로 간주
		return 0;
	else
		return isspace(ch);
}

char* strrtrim(char* s)	//뒷 공백 제거
{
	char* t;

	t = strchr(s, '\0');
	while (t > s && IsSpace(t[-1]))
		--t;
	*t = '\0';
	return s;
}

char* strltrim(char* s)	//앞 공백 제거
{
	char* t;
	char* e;

	t = s;
	e = strchr(s, '\0');
	while (IsSpace(*t))
		++t;

	memmove(s, t, e - t + 1);

	return s;
}

char* trim(char* s)	//앞뒤 공백 제거
{
	strltrim(s);
	strrtrim(s);

	return s;
}

void song_list_menu() //노래 리스트 주 메뉴
{
	char input_text[STRING_SIZE];	//삭제할 문자열(노래)이 들어갈 배열
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
			add_song();
			song_list_menu();
			break;

		case 3: //노래 삭제
			get_dlt_song(input_text); //삭제 문자열 입력 및 생성 후 삭제
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
	FILE* fp;
	fp = fopen("song_list.txt", "r");
	if (fp == NULL)
	{
		printf("오류");
	}
	char name[STRING_SIZE];
	char singer[STRING_SIZE];
	char song_writer[STRING_SIZE];
	char lylic_writer[STRING_SIZE];
	char genre[STRING_SIZE];
	char playtime[STRING_SIZE];
	char album_name[STRING_SIZE];
	char album_time[STRING_SIZE];
	char song[STRING_SIZE * 8];
	while (fgets(song, sizeof(song), fp) != NULL)
	{
		sscanf(song, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", name, singer, song_writer, lylic_writer, genre, playtime, album_name, album_time);
		printf("%s / ", name); //제목 출력
		int size = 0;

		//가수 출력
		while (1)
		{
			if (singer[size] == '|') //인물 구분자를 만났을 때
			{
				while (1) //띄어쓰기를 만날 때 또는 끝날 때 까지 건너뛰기
				{
					size++;
					if (singer[size] == NULL) //문자열이 끝났을 때
					{
						break;
					}
					else if (singer[size] == ' ') //띄어쓰기를 만났을 때
					{
						size = size + 1;
						break;
					}
				}
			}
			if (singer[size] == NULL) //문자열이 끝났을 때
			{
				printf(" / ");
				break;
			}
			printf("%c", singer[size]);
			size++;
		}
		size = 0;

		//작곡가 출력
		while (1)
		{
			if (song_writer[size] == '|') //인물 구분자를 만났을 때
			{
				while (1) //띄어쓰기를 만날 때 또는 끝날 때 까지 건너뛰기
				{
					size++;
					if (song_writer[size] == NULL) //문자열이 끝났을 때
					{
						break;
					}
					else if (song_writer[size] == ' ') //띄어쓰기를 만났을 때
					{
						size = size + 1;
						break;
					}
				}
			}
			if (song_writer[size] == NULL) //문자열이 끝났을 때
			{
				printf(" / ");
				break;
			}
			printf("%c", song_writer[size]);
			size++;
		}
		size = 0;

		//작사가 출력
		while (1)
		{
			if (lylic_writer[size] == '|') //인물 구분자를 만났을 때
			{
				while (1) //띄어쓰기를 만날 때 또는 끝날 때 까지 건너뛰기
				{
					size++;
					if (lylic_writer[size] == NULL) //문자열이 끝났을 때
					{
						break;
					}
					else if (lylic_writer[size] == ' ') //띄어쓰기를 만났을 때
					{
						size = size + 1;
						break;
					}
				}
			}
			if (lylic_writer[size] == NULL) //문자열이 끝났을 때
			{
				printf(" / ");
				break;
			}
			printf("%c", lylic_writer[size]);
			size++;
		}

		printf("%s / ", genre); //장르 출력
		printf("%s / ", playtime); //재생시간 출력
		printf("%s / ", album_name); //앨범명 출력
		printf("%s\n", album_time); //앨범 출시 날짜 출력
	}
	fclose(fp);
}
/*
void song_add()//노래 추가
{
	char name[MAX_SIZE]; //제목
	char singer[200]; //가수
	char song_writer[200]; //작곡가
	char lyric_writer[200]; //작사가
	char genre[20]; //장르
	int play_time_hour = 0, play_time_min = 0, play_time_sec = 0; //재생시간들
	char album_name[200]; //앨범명
	int album_year = 0, album_month = 0, album_day = 0;//앨범출시날짜

	FILE* fp;
	fp = fopen("song_list.txt", "a+");

	//제목 입력
	printf("\n제목을 입력하세요.\n\n");
	printf("제목 : ");
	int err=1;
	getchar();
	do
	{
		gets(name, MAX_SIZE);
		if (strlen(name) == 0) //입력하지 않았을 때
		{
			printf("\n제목 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:좋니)\n\n");
			printf("제목 : ");
		}
		else if (name[0] == ' ' || name[0] == '\t' || name[strlen(name) - 1] == ' ' || name[strlen(name) - 1] == '\t') //앞 뒤에 공백이 있을 때
		{
			printf("\n제목 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:좋니)\n\n");
			printf("제목 : ");
			name[0] = NULL;
		}
		else //맞는 입력일 때
		{
			err = 0;
		}
	} while (err == 1);
	//printf("\n%s", name);

	//가수 입력
	printf("\n가수를 입력하세요.\n\n");
	printf("가수 : ");
	err = 1;
	getchar();
	do
	{
		gets(singer, 200);
		if (strlen(singer) == 0) //입력하지 않았을 때
		{
			printf("\n가수 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("가수 : ");
		}
		else if (singer[0] == ' ' || singer[0] == '\t' || singer[strlen(singer) - 1] == ' ' || singer[strlen(singer) - 1] == '\t') //앞 뒤에 공백이 있을 때
		{
			printf("\n가수 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("가수 : ");
			singer[0] = NULL;
		}
		else //맞는 입력일 때
		{
			err = 0;
		}
	} while (err == 1);
	//printf("\n%s", singer);

	//작곡가 입력
	printf("\n작곡가를 입력하세요.\n\n");
	printf("작곡가 : ");
	err = 1;
	getchar();
	do
	{
		gets(song_writer, 200);
		if (strlen(song_writer) == 0) //입력하지 않았을 때
		{
			printf("\n작곡가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작곡가 : ");
		}
		else if (song_writer[0] == ' ' || song_writer[0] == '\t' || song_writer[strlen(song_writer) - 1] == ' ' || song_writer[strlen(song_writer) - 1] == '\t') //앞 뒤에 공백이 있을 때
		{
			printf("\n작곡가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작곡가 : ");
			song_writer[0] = NULL;
		}
		else //맞는 입력일 때
		{
			err = 0;
		}
	} while (err == 1);
	//printf("\n%s", song_writer);

	//작사가 입력
	printf("\n작사가를 입력하세요.\n\n");
	printf("작사가 : ");
	err = 1;
	getchar();
	do
	{
		gets(lyric_writer, 200);
		if (strlen(lyric_writer) == 0) //입력하지 않았을 때
		{
			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작사가 : ");
		}
		else if (lyric_writer[0] == ' ' || lyric_writer[0] == '\t' || lyric_writer[strlen(lyric_writer) - 1] == ' ' || lyric_writer[strlen(lyric_writer) - 1] == '\t') //앞 뒤에 공백이 있을 때
		{
			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작사가 : ");
			lyric_writer[0] = NULL;
		}
		else //맞는 입력일 때
		{
			err = 0;
		}
	} while (err == 1);
	//printf("\n%s", lyric_writer);

	//작사가 입력
	printf("\n작사가를 입력하세요.\n\n");
	printf("작사가 : ");
	err = 1;
	getchar();
	do
	{
		gets(lyric_writer, 200);
		if (strlen(lyric_writer) == 0) //입력하지 않았을 때
		{
			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작사가 : ");
		}
		else if (lyric_writer[0] == ' ' || lyric_writer[0] == '\t' || lyric_writer[strlen(lyric_writer) - 1] == ' ' || lyric_writer[strlen(lyric_writer) - 1] == '\t') //앞 뒤에 공백이 있을 때
		{
			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작사가 : ");
			lyric_writer[0] = NULL;
		}
		else //맞는 입력일 때
		{
			err = 0;
		}
	} while (err == 1);
	//printf("\n%s", lyric_writer);

	//장르 입력
	printf("\n장르를 입력하세요.\n\n");
	printf("장르 : ");
	err = 1;
	getchar();
	do
	{
		gets(genre, 20);
		if (strcmp(genre,"클래식")==0 || strcmp(genre, "재즈") == 0 || strcmp(genre, "팝") == 0 || strcmp(genre, "발라드") == 0 || strcmp(genre, "힙합") == 0 || strcmp(genre, "트로트") == 0 || strcmp(genre, "디스코") == 0 || strcmp(genre, "댄스") == 0) //맞는 입력일 때
		{
			err = 0;
		}
		else //규칙과 다를 때
		{
			printf("\n장르 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:재즈)\n\n");
			printf("장르 : ");
			genre[0] = NULL;
		}
	} while (err == 1);
	//printf("\n%s", genre);

	//재생시간 입력
	printf("\n재생시간을 입력하세요.\n\n");
	printf("재생시간 : ");
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 

	//앨범명 입력
	printf("\n앨범명을 입력하세요.\n\n");
	printf("앨범명 : ");
	err = 1;
	getchar();
	do
	{
		gets(album_name, 200);
		if (strlen(album_name) == 0) //입력하지 않았을 때
		{
			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작사가 : ");
		}
		else if (album_name[0] == ' ' || album_name[0] == '\t' || album_name[strlen(album_name) - 1] == ' ' || album_name[strlen(album_name) - 1] == '\t') //앞 뒤에 공백이 있을 때
		{
			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
			printf("작사가 : ");
			album_name[0] = NULL;
		}
		else //맞는 입력일 때
		{
			err = 0;
		}
	} while (err == 1);
	//printf("\n%s", album_name);

	//앨범 출시 날짜 입력
	printf("\n앨범 출시 날짜를 입력하세요.\n\n");
	printf("앨범 출시 날짜 : ");
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
}
*/

void add_song() {
	char title_buffer[STRING_SIZE] = "";	//제목
	char singers_buffer[STRING_SIZE] = "";	//가수
	char composers_buffer[STRING_SIZE] = "";	//작곡가
	char lyricists_buffer[STRING_SIZE] = "";	//작사가
	char genre_buffer[STRING_SIZE] = "";    //장르
	char playtime_buffer[STRING_SIZE]; //재생시간
	char album_buffer[STRING_SIZE];    //앨범명
	char release_buffer[STRING_SIZE];  //앨범출시날짜
	FILE* fp = fopen("song_list.txt", "a");	//추가모드로 파일 열기


	printf("\n제목을 입력하세요.\n");	//제목
	while (1) {
		printf("\n");
		printf("제목 :");
		gets(title_buffer, STRING_SIZE);	//제목 입력받기

		char* title = trim(title_buffer);	//앞뒤 공백 제거

		//printf("%s\n", title);			//제대로 입력되었는지 확인(검사)
		if (strlen(title) == 0) {	//틀린 입력일 경우
			printf("\n제목 입력이 잘못되었습니다.정확히 입력해주세요.(예시:좋니)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			fprintf(fp, "%s | ", title);
		}
		break;
	}	//제목 끝

	printf("\n가수를 입력하세요.\n");	//가수
	while (1) {
		printf("\n");
		printf("가수 :");
		gets(singers_buffer);	//가수 입력받기

		char* singers = trim(singers_buffer);	//앞뒤 공백 제거

		if (strlen(singers) == 0) {	//틀린 입력일 경우
			printf("\n가수 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			char* singer_buffer = strtok(singers, ",");	//","를 기준으로 자르기
			char* singer = trim(singer_buffer);	//앞뒤 공백 제거
			//중복 확인

			fprintf(fp, "%s ", singer);			//첫 가수 파일에 저장
			singer = strtok(NULL, ",");

			while (singer != NULL) {				//가수가 더 있을 경우 계속 추가 저장
				char* next_singer = trim(singer);	//앞뒤 공백 제거
				//중복 확인
				fprintf(fp, ", %s ", next_singer);
				singer = strtok(NULL, ",");
			}
			fputs("| ", fp);
		}
		break;
	}		//가수 끝


	printf("\n작곡가를 입력하세요.\n");	//작곡가
	while (1) {
		printf("\n");
		printf("작곡가 :");
		gets(composers_buffer);	//작곡가 입력받기

		char* composers = trim(composers_buffer);	//앞뒤 공백 제거

		if (strlen(composers) == 0) {	//틀린 입력일 경우
			printf("\n작곡가 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			char* composer_buffer = strtok(composers, ",");	//","를 기준으로 자르기
			char* composer = trim(composer_buffer);	//앞뒤 공백 제거
			//중복 확인

			fprintf(fp, "%s ", composer);			//첫 작곡가 파일에 저장
			composer = strtok(NULL, ",");

			while (composer != NULL) {				//작곡가가 더 있을 경우 계속 추가 저장
				char* next_composer = trim(composer);	//앞뒤 공백 제거
				//중복 확인
				fprintf(fp, ", %s ", next_composer);
				composer = strtok(NULL, ",");
			}
			fputs("| ", fp);
		}
		break;	//작곡가 끝
	}

	printf("\n작사가를 입력하세요.\n");	//작사가
	while (1) {
		printf("\n");
		printf("작사가 :");
		gets(lyricists_buffer);	//작사가 입력받기

		char* lyricists = trim(lyricists_buffer);	//앞뒤 공백 제거

		if (strlen(lyricists) == 0) {	//틀린 입력일 경우
			printf("\n작사가 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			char* lyricist_buffer = strtok(lyricists, ",");	//","를 기준으로 자르기
			char* lyricist = trim(lyricist_buffer);	//앞뒤 공백 제거
			//중복 확인

			fprintf(fp, "%s ", lyricist);			//첫 작사가 파일에 저장
			lyricist = strtok(NULL, ",");

			while (lyricist != NULL) {				//작사가가 더 있을 경우 계속 추가 저장
				char* next_lyricist = trim(lyricist);	//앞뒤 공백 제거
				//중복 확인
				fprintf(fp, ", %s ", next_lyricist);
				lyricist = strtok(NULL, ",");
			}
			fputs("| ", fp);
		}
		break;	//작사가 끝
	}

	printf("\n장르를 입력하세요.\n");	//장르
	while (1) {
		printf("\n");
		printf("장르 :");
		gets(genre_buffer);

		char* genre = trim(genre_buffer);	//앞뒤 공백 제거

		if (strcmp(genre, "클래식") * strcmp(genre, "재즈") * strcmp(genre, "팝") * strcmp(genre, "발라드") * strcmp(genre, "힙합") * strcmp(genre, "트로트") * strcmp(genre, "디스코") * strcmp(genre, "댄스") == 0 || strlen(genre) == 0) {	//맞는 입력일 경우
			fprintf(fp, "%s | ", genre);
		}
		else {		//틀린 입력일 경우
			printf("\n장르 입력이 잘못되었습니다.정확히 입력해주세요.(예시:재즈)\n");
			continue;
		}
		break;
	}		//장르 끝

	printf("\n시간을 입력하세요.\n");	//재생시간
	while (1) {
		char minute_str[STRING_SIZE] = "";
		char second_str[STRING_SIZE] = "";
		int count_m = 0;
		int count_s = 0;
		int error = 0;
		printf("\n");
		printf("시간 :");
		gets(playtime_buffer);

		char* playtime = trim(playtime_buffer);	//앞뒤 공백 제거

		//"분","초" 각각 개수 세기
		char* ptr_m = strstr(playtime, "분");
		while (ptr_m != NULL) // 더이상 "분"이 등장하지 않을 때까지 반복
		{
			ptr_m = strstr(ptr_m + 1, "분"); // 다음 등장 위치 탐색
			count_m++;
		}
		char* ptr_s = strstr(playtime, "초");
		while (ptr_s != NULL) // 더이상 "초"가 등장하지 않을 때까지 반복
		{
			ptr_s = strstr(ptr_s + 1, "초"); // 다음 등장 위치 탐색
			count_s++;
		}

		//재생시간 문법 형식 확인
		if (strlen(playtime) == 0) { error = 1; }	//틀린 입력일 경우	
		else if (count_m == 1 && count_s == 1) {	//모두 1개씩 있는 경우
			strcpy(minute_str, strtok(playtime, "분"));
			char* temp = strtok(NULL, "분");
			strcpy(second_str, strtok(temp, "초"));
			if (strtok(NULL, "초") != NULL) { error = 1; }
		}
		else if (count_m == 1 && count_s == 0) {	//입력에 "분"이 1개 있는 경우
			if (strcmp(playtime, "분") == 0) {
				error = 1;
			}
			else {
				strcpy(minute_str, strtok(playtime, "분"));
				if (strtok(NULL, "분") != NULL) { error = 1; }
			}
		}
		else if (count_m == 0 && count_s == 1) {	//입력에 "초"가 1개 있는 경우
			if (strcmp(playtime, "초") == 0) {
				error = 1;
			}
			else {
				strcpy(second_str, strtok(playtime, "초"));
				if (strtok(NULL, "초") != NULL) { error = 1; }
			}
		}
		else { error = 1; }		//나머지는 모두 틀린 경우

		if (error == 1) {		//오류 처리
			printf("\n시간 입력이 잘못되었습니다.정확히 입력해주세요.(예시:02분44초)\n");
			continue;
		}

		//재생시간 의미 규칙 확인
		if (strcmp(minute_str, "")) {	//"분"이 공백이 아니면
			for (int i = 0; i < strlen(minute_str); i++)	//문자열이 숫자인지 확인
			{
				if (!isdigit(minute_str[i])) { error = 1; }
			}
			if (error == 0) {
				int minute = atoi(minute_str);
				if (minute <= 0) {			//"분"은 0보다 크다
					error = 1;
				}
				else {
					fprintf(fp, "%02d분", minute);
				}
			}
		}
		if (strcmp(second_str, "")) {	//"초"가 공백이 아니면
			for (int i = 0; i < strlen(second_str); i++)	//문자열이 숫자인지 확인(분과 초 사이 공백 있을 시 error=1)
			{
				if (!isdigit(second_str[i])) { error = 1; }
			}
			if (error == 0) {
				int second = atoi(second_str);
				if (second <= 0 || second >= 60) {	//"초"는 1~59사이
					error = 1;
				}
				else {
					fprintf(fp, "%d초", second);
				}
			}
		}
		if (error == 1) {
			printf("\n시간 입력이 잘못되었습니다.정확히 입력해주세요.(예시:02분44초)\n");
			continue;
		}

		fputs(" | ", fp);
		break;
	}		//재생시간 끝

	printf("\n앨범명을 입력하세요.\n");	//앨범명
	while (1) {
		printf("\n");
		printf("앨범명 :");
		gets(album_buffer);	//앨범명 입력받기

		char* album = trim(album_buffer);	//앞뒤 공백 제거

		if (0) {	//틀린 입력일 경우
			printf("\n앨범명 입력이 잘못되었습니다.정확히 입력해주세요.(예시:밤양갱)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			fprintf(fp, "%s | ", album);
		}
		break;
	}	//앨범명 끝

	printf("\n앨범 출시 날짜를 입력하세요.\n");	//앨범 출시 날짜
	while (1) {
		char* year_str = "";
		char* month_str = "";
		char* day_str = "";
		int count_hyphen = 0;
		int count_slash = 0;
		int count_dot = 0;
		int error = 0;
		printf("\n");
		printf("앨범 출시 날짜 :");
		gets(release_buffer);

		char* release = trim(release_buffer);	//앞뒤 공백 제거

		//'-','/','.' 각각 개수 세기
		char* ptr_hyphen = strchr(release, '-');
		while (ptr_hyphen != NULL) // 더이상 '-'이 등장하지 않을 때까지 반복
		{
			ptr_hyphen = strchr(ptr_hyphen + 1, '-'); // 다음 등장 위치 탐색
			count_hyphen++;
		}
		char* ptr_slash = strchr(release, '/');
		while (ptr_slash != NULL) // 더이상 '/'가 등장하지 않을 때까지 반복
		{
			ptr_slash = strchr(ptr_slash + 1, '/'); // 다음 등장 위치 탐색
			count_slash++;
		}
		char* ptr_dot = strchr(release, '.');
		while (ptr_dot != NULL) // 더이상 '.'가 등장하지 않을 때까지 반복
		{
			ptr_dot = strchr(ptr_dot + 1, '.'); // 다음 등장 위치 탐색
			count_dot++;
		}

		//앨범 출시 날짜 문법 형식 확인
		if (count_hyphen == 2 && count_slash == 0 && count_dot == 0) {	//'-'이 2개인 경우
			year_str = strtok(release, "-");
			month_str = strtok(NULL, "-");
			day_str = strtok(NULL, "-");
		}
		else if (count_hyphen == 0 && count_slash == 2 && count_dot == 0) {	//'/'이 2개인 경우
			year_str = strtok(release, "/");
			month_str = strtok(NULL, "/");
			day_str = strtok(NULL, "/");
		}
		else if (count_hyphen == 0 && count_slash == 0 && count_dot == 2) {	//'.'이 2개인 경우
			year_str = strtok(release, ".");
			month_str = strtok(NULL, ".");
			day_str = strtok(NULL, ".");
		}
		else if (count_hyphen == 0 && count_slash == 0 && count_dot == 0) {	//모두 숫자인 경우
			if (strlen(release) == 8) {
				for (int i = 0; i < strlen(release); i++)	//문자열이 숫자인지 확인
				{
					if (!isdigit(release[i])) { error = 1; }
				}
				if (error == 0) {
					int temp = atoi(release);
					int year = temp / 10000;
					int month = (temp % 10000) / 100;
					int day = temp % 100;
					//check_date(year, month, day)	//날짜 확인 함수(true/false)
				}
			}
			else { error = 1; }
		}
		else { error = 1; }		//나머지는 모두 틀린 경우

		for (int i = 0; i < strlen(year_str); i++)	//문자열이 숫자인지 확인
		{
			if (!isdigit(year_str[i])) { error = 1; }
		}
		for (int i = 0; i < strlen(month_str); i++)	//문자열이 숫자인지 확인
		{
			if (!isdigit(month_str[i])) { error = 1; }
		}
		for (int i = 0; i < strlen(day_str); i++)	//문자열이 숫자인지 확인
		{
			if (!isdigit(day_str[i])) { error = 1; }
		}

		if (error == 1) {
			printf("\n앨범 출시 날짜 입력이 잘못되었습니다.정확히 입력해주세요.\n(예시:2024-04-01 또는 2024/04/01 또는 2024.04.01 또는 20240401)\n");
			continue;
		}

		//앨범 출시 날짜 의미 규칙 확인
		int year = atoi(year_str);
		int month = atoi(month_str);
		int day = atoi(day_str);
		//check_date(year, month, day)	//날짜 확인 함수(true/false)
		fprintf(fp, "%04d-%02d-%02d", year, month, day);

		fputs(" \n", fp);
		break;
	}		//앨범 출시 날짜 끝

	fclose(fp);
}

void get_dlt_song(char* dlt_song) { // 삭제 문자열 입력 및 생성 함수 -> 해당 문자열 삭제 함수로 넘어감
	char dlt_songname[STRING_SIZE];	// 삭제할 노래 제목
	char dlt_singer[STRING_SIZE];	// 삭제할 노래 가수
	int line_number_check[MAX_SIZE] = { 0 };	// 노래 중복시 삭제할 노래 선택 때 사용할 배열
	int line_num = 0;	// 중복 노래 개수 담을 변수

	printf("노래를 삭제합니다.\n");
	printf("삭제할 노래의 제목을 입력하세요: ");
	fgets(dlt_songname, STRING_SIZE, stdin);
	dlt_songname[strcspn(dlt_songname, "\n")] = '\0'; // 개행 문자 제거

	printf("삭제할 노래의 가수를 입력하세요: ");
	fgets(dlt_singer, STRING_SIZE, stdin);
	dlt_singer[strcspn(dlt_singer, "\n")] = '\0'; // 개행 문자 제거

	FILE* file = fopen("song_list.txt", "r");
	if (file == NULL) {
		printf("Error opening file for reading.\n");
		return;
	}

	char buffer[STRING_SIZE];	// txt파일에서 읽어올 문자열 원본
	char dlt_print[STRING_SIZE];	// 노래 정보의 구분자를 '\t' 에서 ' / ' 로 바꿔 출력할 배열
	int line_number = 1; // 중복 노래 각 줄 번호를 저장할 변수
	int selected_line = 0; // 노래가 중복되지 않으면 삭제할 특정 노래의 줄을 담고, 중복되면 사용자가 선택한 번호 저장할 변수
	while (fgets(buffer, STRING_SIZE, file) != NULL) {
		char* token = strtok(buffer, "\t"); // 탭을 구분자로 사용하여 문자열을 분할
		char* song = strtok(NULL, "\t");

		// 입력한 제목과 가수를 txt파일에서 비교하며, 중복 노래 개수 카운트
		if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
			line_number_check[line_num] = line_number;
			line_num++;
		}
		line_number++;
	}

	fclose(file);

	if (line_num > 1) { // 삭제 노래 제목과 가수가 중복인 경우
		line_number = 1; // 줄 번호 초기화
		file = fopen("song_list.txt", "r"); // 파일을 다시 열어서 출력
		while (fgets(buffer, STRING_SIZE, file) != NULL) {
			strcpy(dlt_print, buffer);
			char* token = strtok(buffer, "\t"); // 탭을 구분자로 사용하여 문자열을 분할
			char* song = strtok(NULL, "\t");

			// 제목과 가수 일치시 해당 노래 정보 출력
			if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
				printf("%d.  ", line_number);
				for (int k = 0; k < strlen(dlt_print); k++) {
					if (dlt_print[k] == '\t')
						printf(" / ");
					else
						printf("%c", dlt_print[k]);
				}
			}
			line_number++;
		}
		fclose(file);

		printf("삭제할 노래의 번호를 선택하세요: ");
		scanf("%d", &selected_line);
		getchar();

		// 선택한 번호가 잘못된 경우 오류 메시지 출력 후 종료
		int valid_selection = 0;	
		for (int i = 0; i < line_num; i++) {
			if (selected_line == line_number_check[i]) {
				valid_selection = 1;
				break;
			}
		}
		if (!valid_selection) {
			printf("잘못된 노래의 번호입니다.\n");
			return;
		}
	}
	else if (line_num == 1) { // 삭제 노래가 중복되지 않은 경우
		line_number = 1; // 줄 번호 초기화
		file = fopen("song_list.txt", "r"); // 파일을 다시 열어서 출력
		while (fgets(buffer, STRING_SIZE, file) != NULL) {
			strcpy(dlt_print, buffer);
			char* token = strtok(buffer, "\t"); // 탭을 구분자로 사용하여 문자열을 분할
			char* song = strtok(NULL, "\t");

			// 제목과 가수 일치시 해당 노래 정보 출력
			if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
				for (int k = 0; k < strlen(dlt_print); k++) {
					if (dlt_print[k] == '\t')
						printf(" / ");
					else
						printf("%c", dlt_print[k]);
				}
				selected_line = line_number;
			}
			line_number++;
		}
		fclose(file);
	}
	else {
		printf(".!! 삭제 대상이 존재하지 않습니다\n");
		return;
	}

	// 선택한 번호에 해당하는 줄을 다시 읽기 위해 fopen
	file = fopen("song_list.txt", "r");
	if (file == NULL) {
		printf("Error opening file for reading.\n");
		return;
	}

	// 선택한 번호에 해당하는 줄을 다시 읽어서 dlt_song에 저장
	line_number = 1;
	while (fgets(buffer, STRING_SIZE, file) != NULL) {
		if (line_number == selected_line) {
			strcpy(dlt_song, buffer);
			break;
		}
		line_number++;
	}

	fclose(file);

	// dlt_song 문자열을 song_list에서 삭제하는 함수
	song_dlt("song_list.txt", dlt_song);
}

void song_dlt(const char* filename, const char* dlt_song) {	// dlt_song 문자열을 song_list에서 삭제하는 함수
	FILE* input_file = fopen(filename, "r");    // 기존 txt 파일
	if (input_file == NULL) {
		printf("%s파일을 찾지 못했습니다.\n", filename);
		return;
	}

	FILE* output_file = fopen("temp.txt", "w"); // 새로 덮어씌울 txt 파일
	if (output_file == NULL) {
		printf("파일 생성 에러\n");
		fclose(input_file);
		return;
	}

	char line[STRING_SIZE];   // 기존 문자열을 담아둘 배열
	int found = 0;  // 문자열 발견 여부 확인 변수

	while (fgets(line, sizeof(line), input_file)) {
		// 찾으려는 문자열이 포함된 행이 아닌 경우 새 파일에 쓰기
		if (strstr(line, dlt_song) == NULL) {
			fputs(line, output_file);
		}
		else {
			found = 1; // 문자열 발견
		}
	}

	char dlt_ans[STRING_SIZE];	// 삭제 여부 답변 입력 배열
	if (found) {
		printf("정말 삭제하시겠습니까? (Delete/...)\n");
		scanf("%s", &dlt_ans);	// 삭제 여부
		if (strcmp(dlt_ans, "Delete") == 0)	// "Delete"와 일치시 삭제 진행
			printf("성공적으로 노래를 삭제했습니다.\n");
		else
			return;	// 일치하지 않으면 리턴
	}
	else {
		printf("..! 삭제 대상이 존재하지 않습니다\n");
	}

	fclose(input_file);
	fclose(output_file);

	remove(filename);   // 기존 파일 삭제
	rename("temp.txt", filename);   // 새로 쓴 파일의 이름 변경
}
