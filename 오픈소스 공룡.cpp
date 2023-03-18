#include<stdio.h>
#include<windows.h> //�ܼ�â�� �̿��Ͽ� �����ΰ��� �ϰ� ���� �� ����ϴ� �Լ��̴�.
#include<conio.h> //�ܼ� ����� �Լ��� �����ϴ� ��� ����
#include<time.h>
//(v2.0) ū ������ �� ��ֹ� �߰��� �ܼ�â y��ǥ Ȯ��
#define DINO_BOTTOM_Y 17 //���� �߰� ���� ��� y��ǥ ����
#define TREE_BOTTOM_Y 20 //������  y��ǥ ������
#define TREE_BOTTOM_X 40 //������ ó�� �Ÿ� x��ǥ
#define BIGTREE_BOTTOM_Y  10 //(v2.0) ū ������ y��ǥ ������
#define BIGTREE_BOTTOM_X 80 //(v2.0) ū ������ ó�� �Ÿ� x��ǥ
#define BIRD_BOTTOM_X 60 //(v2.0) ���� ó���Ÿ� x��ǥ
#define BIRD_BOTTOM_Y 5 //(v2.0) ���� y��ǥ ������

//�ܼ� â�� ũ��� ������ �����ϴ� �Լ�
void SetConsoleView()  //System()�Լ��� �ü��(����â) ��ɾ �����Ű�� �Լ�.
{
	system("mode con:cols=100 lines=30");  //�ܼ�â ũ�� ���� �Լ�
	system("���¼ҽ� ���� ������Ʈ ������Ʈ1 ���� ���� ����. 2019036043 ������"); //�ܼ�â �̸�ǥ��
}

//Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//������ �׸��� �Լ�
//�ܼ�â �������� (x,y)=(0,0) ���������� ������ x����, �Ʒ������� ������ y����
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
    if (legFlag)  //�����̴� ������ �ٸ�ǥ��
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

//������ �׸��� �Լ�
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
//(v2.0) ū ���� ��ֹ� �߰�
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
//(v2.0) �� ��� ��ֹ� �߰�
void Drawbird(int birdX)
{
    GotoXY(birdX, BIRD_BOTTOM_Y);
    printf("$$   ");
    GotoXY(birdX, BIRD_BOTTOM_Y + 1);
    printf("  $$$$$");
    GotoXY(birdX, BIRD_BOTTOM_Y + 2);
    printf("    ||  ");
}

//�浹 ������ �������� �۾� ǥ��
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

//�浹������ true, �ƴϸ� false
bool isCollision(const int treeX, const int bigtreeX, const int birdX, const int dinoY)
{
    //Ʈ���� X�� ������ ��ü�ʿ� ���� ��, ������ ���̰� ������� �ʴٸ� �浹�� ó��
    GotoXY(0, 0);
    printf("treeX : %d, bigtreeX : %d, birdX : %d, dinoY : %d", treeX, bigtreeX, birdX, dinoY); // ������ X, Y�� ã���ϴ�.
//���࿡ X(����)�� ��ġ�� 2~4 �����̰� ���� �Ӹ��� Y�� 13���� ������(�ٴڿ� ����ﶧ) �浹
    if (treeX <= 4 && treeX >= 2 &&
        dinoY > 13)
    {
        return true;
    }

    //(v2.0) �߰��� ��ֹ��� �浹ó�� ��ǥ
    //X(ū ����)�� ��ġ�� 3~6 �����̰� ���� �Ӹ��� Y�� 10���� ������(�ٴڿ� ����ﶧ) �浹
    else if (bigtreeX <= 6 && bigtreeX >= 3 &&
        dinoY > 10)
    {
        return true;
    }
    //X(��)�� ��ġ�� 2~4 �����̰� ���� �Ӹ��� Y�� 9���� ������(õ�忡 ����ﶧ) �浹
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

    while (true)        //���� ����
    {
        //���� ���۽� �ʱ�ȭ
        bool isJumping = false;
        bool isBottom = true;
        const int zgravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;
        int bigtreeX = BIGTREE_BOTTOM_X;
        int birdX = BIRD_BOTTOM_X;

        int score = 0;   //���� 0�� ����
        clock_t start, curr;    //���� ���� �ʱ�ȭ
        start = clock();        //���۽ð� �ʱ�ȭ

        while (true)    //�� �ǿ� ���� ����
        {
            //(v2.0) �浹üũ ��ֹ����� x���� ������ y������ �Ǵ�
            if (isCollision(treeX, bigtreeX, birdX, dinoY))
                break;

            //(v2.0) ���� �ƴҽ� ������ �� ������ ���� ����
            if (GetKeyDown() == 'z')
            {
                isJumping = true;
                isBottom = false;
            }

            //�������̶�� Y�� ����, ������ �������� Y�� ����.
            if (isJumping)
            {
                dinoY -= zgravity;
            }
            else
            {
                dinoY += zgravity;
            }

            //Y�� ����ؼ� �����ϴ°� �������� �ٴ��� ����.
            if (dinoY >= DINO_BOTTOM_Y)
            {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            //(v2.0) ��ֹ��� �������� (x����) �������ϰ�
            //(v2.0) ��ֹ��� ��ġ�� ���� �����ΰ��� �ٽ� ������ ������ ��ȯ.
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
            //(v2.0) ���� �������� 2���� �ӵ��� ���ư�
            birdX -= 4;
            if (birdX <= 0)
            {
                birdX = BIRD_BOTTOM_X;
            }

            //(v2.0) ���� ������ ���� ����
            if (dinoY <= 7)
            {
                isJumping = false;
            }

            DrawDino(dinoY);        //���� �׸� �Լ�
            DrawTree(treeX);        //���� �׸� �Լ�
            DrawbigTree(bigtreeX);  // (v2.0) ū ���� �׸� �Լ�
            Drawbird(birdX);        // (v2.0) �� �׸� �Լ�

            curr = clock();            //����ð� �޾ƿ���
            if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1�ʰ� �Ѿ�����
            {
                score++;    //���ھ� UP
                start = clock();    //���۽ð� �ʱ�ȭ
            }
            Sleep(60);
            system("cls");    //clear

            //��������� 1�ʸ��� ���ִ°��� �ƴ϶� �׻� ������ָ鼭, 1�ʰ� �������� ++ ���ݴϴ�.
            GotoXY(27, 0);    //Ŀ���� ��� �������� �ű��. �ܼ�â�� cols=100�̴ϱ� 2*x�̹Ƿ� 22���� �־���
            printf("Score : %d ", score);    //���� �������.
        }

        //���� ���� �޴�
        DrawGameOver(score);
    }
    return 0;
}