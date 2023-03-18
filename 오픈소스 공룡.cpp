#include<stdio.h>
#include<windows.h> //콘솔창을 이용하여 무엇인가를 하고 싶을 때 사용하는 함수이다.
#include<conio.h> //콘솔 입출력 함수를 제공하는 헤더 파일
#include<time.h>
//(v2.0) 큰 나무와 새 장애물 추가로 콘솔창 y좌표 확장
#define DINO_BOTTOM_Y 17 //공룡 발과 땅이 닿는 y좌표 정의
#define TREE_BOTTOM_Y 20 //나무의  y좌표 기준점
#define TREE_BOTTOM_X 40 //나무의 처음 거리 x좌표
#define BIGTREE_BOTTOM_Y  10 //(v2.0) 큰 나무의 y좌표 기준점
#define BIGTREE_BOTTOM_X 80 //(v2.0) 큰 나무의 처음 거리 x좌표
#define BIRD_BOTTOM_X 60 //(v2.0) 새의 처음거리 x좌표
#define BIRD_BOTTOM_Y 5 //(v2.0) 새의 y좌표 기준점

//콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView()  //System()함수는 운영체제(도스창) 명령어를 실행시키는 함수.
{
	system("mode con:cols=100 lines=30");  //콘솔창 크기 지정 함수
	system("오픈소스 기초 프로젝트 프로젝트1 구글 공룡 게임. 2019036043 남용진"); //콘솔창 이름표현
}

//커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//공룡을 그리는 함수
//콘솔창 왼쪽위가 (x,y)=(0,0) 오른쪽으로 갈수록 x증가, 아래쪽으로 갈수록 y증가
void DrawDino(int dinoY)
{
    GotoXY(0, dinoY);
    static bool legFlag = true;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");
    if (legFlag)  //움직이는 공룡의 다리표현
    {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag = false;
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = true;
    }
}

//나무를 그리는 함수
void DrawTree(int treeX)
{
    GotoXY(treeX, TREE_BOTTOM_Y + 5);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 6);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 7);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 8);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 9);
    printf(" $$ ");
}
//(v2.0) 큰 나무 장애물 추가
void DrawbigTree(int bigtreeX)
{
    GotoXY(bigtreeX, BIGTREE_BOTTOM_Y + 13);
    printf("$$$$$$");
    GotoXY(bigtreeX, BIGTREE_BOTTOM_Y + 14);
    printf(" $$$$ ");
    GotoXY(bigtreeX, BIGTREE_BOTTOM_Y + 15);
    printf(" $$$$ ");
    GotoXY(bigtreeX, BIGTREE_BOTTOM_Y + 16);
    printf(" $$$$ ");
    GotoXY(bigtreeX, BIGTREE_BOTTOM_Y + 17);
    printf(" $$$$ ");
    GotoXY(bigtreeX, BIGTREE_BOTTOM_Y + 18);
    printf(" $$$$ ");
    GotoXY(bigtreeX, BIGTREE_BOTTOM_Y + 19);
    printf(" $$$$ ");
}
//(v2.0) 새 모양 장애물 추가
void Drawbird(int birdX)
{
    GotoXY(birdX, BIRD_BOTTOM_Y);
    printf("$$   ");
    GotoXY(birdX, BIRD_BOTTOM_Y + 1);
    printf("  $$$$$");
    GotoXY(birdX, BIRD_BOTTOM_Y + 2);
    printf("    ||  ");
}

//충돌 했을때 게임종료 글씨 표현
void DrawGameOver(const int score)
{
    system("cls");
    int x = 18;
    int y = 11;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);

    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

//충돌했으면 true, 아니면 false
bool isCollision(const int treeX, const int bigtreeX, const int birdX, const int dinoY)
{
    //트리의 X가 공룡의 몸체쪽에 있을 때, 공룡의 높이가 충분하지 않다면 충돌로 처리
    GotoXY(0, 0);
    printf("treeX : %d, bigtreeX : %d, birdX : %d, dinoY : %d", treeX, bigtreeX, birdX, dinoY); // 적절한 X, Y를 찾습니다.
//만약에 X(나무)의 위치가 2~4 사이이고 공룡 머리의 Y가 13보다 높을때(바닥에 가까울때) 충돌
    if (treeX <= 4 && treeX >= 2 &&
        dinoY > 13)
    {
        return true;
    }

    //(v2.0) 추가된 장애물들 충돌처리 좌표
    //X(큰 나무)의 위치가 3~6 사이이고 공룡 머리의 Y가 10보다 높을때(바닥에 가까울때) 충돌
    else if (bigtreeX <= 6 && bigtreeX >= 3 &&
        dinoY > 10)
    {
        return true;
    }
    //X(새)의 위치가 2~4 사이이고 공룡 머리의 Y가 9보다 낮을때(천장에 가까울때) 충돌
    else if (birdX <= 4 && birdX >= 2 &&
        dinoY < 9)
    {
        return true;
    }
    return false;
}

int main()
{
    SetConsoleView();

    while (true)        //게임 루프
    {
        //게임 시작시 초기화
        bool isJumping = false;
        bool isBottom = true;
        const int zgravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;
        int bigtreeX = BIGTREE_BOTTOM_X;
        int birdX = BIRD_BOTTOM_X;

        int score = 0;   //점수 0점 시작
        clock_t start, curr;    //점수 변수 초기화
        start = clock();        //시작시간 초기화

        while (true)    //한 판에 대한 루프
        {
            //(v2.0) 충돌체크 장애물들의 x값과 공룡의 y값으로 판단
            if (isCollision(treeX, bigtreeX, birdX, dinoY))
                break;

            //(v2.0) 땅이 아닐시 점프할 수 없었던 조건 삭제
            if (GetKeyDown() == 'z')
            {
                isJumping = true;
                isBottom = false;
            }

            //점프중이라면 Y를 감소, 점프가 끝났으면 Y를 증가.
            if (isJumping)
            {
                dinoY -= zgravity;
            }
            else
            {
                dinoY += zgravity;
            }

            //Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
            if (dinoY >= DINO_BOTTOM_Y)
            {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            //(v2.0) 장애물이 왼쪽으로 (x음수) 가도록하고
            //(v2.0) 장애물의 위치가 왼쪽 끝으로가면 다시 오른쪽 끝으로 소환.
            treeX -= 2;
            if (treeX <= 0)
            {
                treeX = TREE_BOTTOM_X;
            }
            bigtreeX -= 2;
            if (bigtreeX <= 0)
            {
                bigtreeX = BIGTREE_BOTTOM_X;
            }
            //(v2.0) 새는 나무보다 2배의 속도로 날아감
            birdX -= 4;
            if (birdX <= 0)
            {
                birdX = BIRD_BOTTOM_X;
            }

            //(v2.0) 낮은 점프의 점프 높이
            if (dinoY <= 7)
            {
                isJumping = false;
            }

            DrawDino(dinoY);        //공룡 그림 함수
            DrawTree(treeX);        //나무 그림 함수
            DrawbigTree(bigtreeX);  // (v2.0) 큰 나무 그림 함수
            Drawbird(birdX);        // (v2.0) 새 그림 함수

            curr = clock();            //현재시간 받아오기
            if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1초가 넘었을떄
            {
                score++;    //스코어 UP
                start = clock();    //시작시간 초기화
            }
            Sleep(60);
            system("cls");    //clear

            //점수출력을 1초마다 해주는것이 아니라 항상 출력해주면서, 1초가 지났을때 ++ 해줍니다.
            GotoXY(27, 0);    //커서를 가운데 위쪽으로 옮긴다. 콘솔창이 cols=100이니까 2*x이므로 22정도 넣어줌
            printf("Score : %d ", score);    //점수 출력해줌.
        }

        //게임 오버 메뉴
        DrawGameOver(score);
    }
    return 0;
}