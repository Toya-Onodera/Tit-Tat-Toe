#include <stdio.h>
#include <stdbool.h>

// プレイヤーの格納する値を定義
#define O 100
#define X -100

// プロトタイプ宣言
void showBoard(int[]);
void inputPlayer(int*, int);
int judgmentGame(int[]);

int main (void)
{
	// 盤面用の変数
	int board[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// ターンをカウントする変数
	int turn = 1;

	// ゲームの終了に関する変数
	int judgmentNum = 0;

	// ゲームが終了の判定が出るまでループ
	while (judgmentNum == 0)
	{
		showBoard(board);

		inputPlayer(&board, turn);

		judgmentNum = judgmentGame(board);

		// 試合終了
		if (judgmentNum != 0 || turn == 9)
		{
			showBoard(board);

			switch (judgmentNum)
			{
				case 1:
					puts("o win!");
					break;
				case 2:
					puts("x win!");
					break;
				default:
					puts("even.");
					break;
			}

			break;
		}

		turn++;
	}
	
	return 0;
}

// 盤面を表示する関数
void showBoard(int borad[])
{
	// 配列のインデックス用の変数
	const index[9] = { 6, 7, 8, 3, 4, 5, 0, 1, 2 };

	for (int i = 0; i < 9; i++)
	{
		switch (borad[index[i]])
		{
			case O:
				printf("o");
				break;
			case X:
				printf("x");
				break;
			default:
				printf("%d", borad[ index[i] ]);
				break;
		}

		if ((i + 1) == 9)
		{
			printf("\n");
		}

		else if ((i + 1) % 3 == 0)
		{
			printf("\n-+-+-\n");
		}

		else
		{
			printf("|");
		}
	}
}

// プレイヤーの入力部分の関数
void inputPlayer(int *board, int turn)
{
	// scanf 時に表示するテキスト用の変数
	char questionText[] = "?> ";
	questionText[0] = (turn % 2 != 0) ? 'o' : 'x';

	// scanf 時に格納する変数
	int selectIndex = 0;

	// 格納の管理フラグ
	bool saveFlg = false;

	while (!saveFlg)
	{
		printf("%s", questionText);
		scanf("%d", &selectIndex);


		// 入力された数値が1～9の範囲内かつ
		// すでに O(100) か X(-100) が格納されていたら格納しない
		if (selectIndex >= 1
			&& selectIndex <= 9)
		{
			selectIndex--;
			
			if (board[selectIndex] != O
				&& board[selectIndex] != X)
			{
				board[selectIndex] = (turn % 2 != 0) ? O : X;
				saveFlg = true;

				printf("\n");

				return;
			}
		}

		puts("\nERROR");
	}
}

// 勝利判定を行う関数
// 縦横斜めを確認して o か x が3つ並んでいるか確認する
// 0 継続 or 引き分け
// 1 o 勝利
// 2 x 勝利
int judgmentGame(int board[])
{
	int i, j;

	// 確認用 (計算結果を代入) の変数
	int lineSum;

	// 横
	for (i = 0; i < 3; i++)
	{
		lineSum = 0;

		for (j = 0; j < 3; j++)
		{
			lineSum += board[(3 * i) + j];
		}

		switch (lineSum)
		{
			case 300:
				return 1;
			case -300:
				return 2;
		}
	}

	// 縦
	for (i = 0; i < 3; i++)
	{
		lineSum = 0;

		for (j = 0; j < 3; j++)
		{
			lineSum += board[i + (3 * j)];
		}

		switch (lineSum)
		{
			case 300:
				return 1;
			case -300:
				return 2;
		}
	}

	// 1、5、9 の斜め
	lineSum = board[0] + board[4] + board[8];
	
	switch (lineSum)
	{
		case 300:
			return 1;
		case -300:
			return 2;
	}

	// 3、5、7 の斜め
	lineSum = board[2] + board[4] + board[6];

	switch (lineSum)
	{
		case 300:
			return 1;
		case -300:
			return 2;
	}

	return 0;
}