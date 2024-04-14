
#include "header.h"

const int MAX = 100000;

void playlistMenu()
{
	char getMenu;

	printf("원하는 메뉴에 해당하는 숫자를 입력해주세요.\n\n");
	printf("0. 뒤로가기\n");
	printf("1. 플레이리스트 출력\n");
	printf("2. 플레이리스트 추가\n");
	printf("3. 플레이리스트 삭제\n\n");
	printf("메뉴 선택: ");
	scanf("%c", &getMenu);

	if (getMenu == '0')
	{
		//이전메뉴로 돌아갑니다.
	}
	else if (getMenu == '1')
	{
		//플리 목록 출력
		printPlaylist();
	}
	else if (getMenu == '2')
	{
		//플리 추가
		addPlaylist();
	}
	else if (getMenu == '3')
	{
		//플리 삭제
		deletePlaylist();
	}
	else
	{
		//다시 플리메뉴 선택 페이지로 이동
		playlistMenu();
	}

	return;
}

//플레이리스트 목록을 출력
void printPlaylist()
{
	char getMenu0 = NULL;
	printf("\n");

	FILE* fp = fopen("Playlist_list.txt", "r");

	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fp);
	printf("%s", buffer);

	fclose(fp);

	buffer[0] = '\n';

	printf("원하는 플레이리스트에 해당하는 번호를 입력하세요. (숫자 \"0\"입력시 이전 페이지로 이동) : ");

	//버퍼비우기용
	while (getchar() != '\n');


	scanf("%c", &getMenu0);//원하는 플리에 해당하는 번호 입력받기

	while (getchar() != '\n');

	if (getMenu0 == '0')
	{
		//이전 페이지 출력
		playlistMenu();
	}
	else
	{
		FILE* fp = fopen("Playlist_list.txt", "r");
		char playlistName[MAX] = { 0, };
		while (feof(fp) == 0) //원하는 플리에 해당하는 번호를 발견할 때까지 루프
		{
			fgets(playlistName, MAX, fp);
			char c = playlistName[0]; //원하는 플리에 매칭된 번호인가 체크
			if (c == getMenu0)
			{
				openPlaylist(playlistName);
				break;
			}
		}

		if (feof(fp) == 0)
		{
			fclose(fp);
			printPlaylist();
		}
	}
}

void openPlaylist(char* playlistName)
{
	//받은 플레이리스트 이름에서 공백과 숫자를 지워줌
	//ex) <1. 퇴근길 플레이리스트 -> 퇴근길 플레이리스트>로 받아 변경해줌
	char* pliName = playlistName + 3;

	int len = strlen(pliName);
	if (len > 0 && pliName[len - 1] == '\n') {
		pliName[len - 1] = '\0'; // 개행 문자를 제거
	}

	strcat(pliName, ".txt");

	FILE* fs1 = fopen(pliName, "r");

	//파일을 못찾았을 경우
	if (fs1 == NULL)
	{
		//프로그램 강제종료
	}

	//플레이리스트 속 노래들을 출력
	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fs1);
	printf("%c", pliName);
	printf("\n%s\n", buffer);

	fclose(fs1);

	printf("\n아래의 메뉴 중 원하는 번호를 선택해주세요. \n\n");
	printf("0. 뒤로가기\n");
	printf("1. 현재 플레이리스트에 노래 추가\n");
	printf("2. 현재 플레이리스트에 노래 삭제\n");
	printf("\n메뉴선택 : ");

	char getMenu;
	scanf("%c", &getMenu);
	if (getMenu == '0')
	{
		//이전 페이지로 이동
		printPlaylist();
	}
	if (getMenu == '1')
	{
		addSong();
	}
	if (getMenu == '2')
	{
		deleteSong();
	}
	return;
}


//플레이리스트 추가
void addPlaylist()
{

}

//플레이리스트 삭제
void deletePlaylist()
{

}

void addSong()
{

}

void deleteSong()
{

}