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
			song_list_menu();
			break;

		case 2: //노래 추가

			break;

		case 3: //노래 삭제

			break;

		case 0: //뒤로 가기

			break;
		default: //error
			while (getchar() != '\n'); //입력 버터 비우기
			err = 1;
			break;
		}
	}
	

}