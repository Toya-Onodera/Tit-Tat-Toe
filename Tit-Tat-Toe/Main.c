#include <stdio.h>
#include <stdbool.h>

// �v���C���[�̊i�[����l���`
#define O 100
#define X -100

// �v���g�^�C�v�錾
void showBoard(int[]);
void inputPlayer(int*, int);
int judgmentGame(int[]);

int main (void)
{
	// �Ֆʗp�̕ϐ�
	int board[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// �^�[�����J�E���g����ϐ�
	int turn = 1;

	// �Q�[���̏I���Ɋւ���ϐ�
	int judgmentNum = 0;

	// �Q�[�����I���̔��肪�o��܂Ń��[�v
	while (judgmentNum == 0)
	{
		showBoard(board);

		inputPlayer(&board, turn);

		judgmentNum = judgmentGame(board);

		// �����I��
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

// �Ֆʂ�\������֐�
void showBoard(int borad[])
{
	// �z��̃C���f�b�N�X�p�̕ϐ�
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

// �v���C���[�̓��͕����̊֐�
void inputPlayer(int *board, int turn)
{
	// scanf ���ɕ\������e�L�X�g�p�̕ϐ�
	char questionText[] = "?> ";
	questionText[0] = (turn % 2 != 0) ? 'o' : 'x';

	// scanf ���Ɋi�[����ϐ�
	int selectIndex = 0;

	// �i�[�̊Ǘ��t���O
	bool saveFlg = false;

	while (!saveFlg)
	{
		printf("%s", questionText);
		scanf("%d", &selectIndex);


		// ���͂��ꂽ���l��1�`9�͈͓̔�����
		// ���ł� O(100) �� X(-100) ���i�[����Ă�����i�[���Ȃ�
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

// ����������s���֐�
// �c���΂߂��m�F���� o �� x ��3����ł��邩�m�F����
// 0 �p�� or ��������
// 1 o ����
// 2 x ����
int judgmentGame(int board[])
{
	int i, j;

	// �m�F�p (�v�Z���ʂ���) �̕ϐ�
	int lineSum;

	// ��
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

	// �c
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

	// 1�A5�A9 �̎΂�
	lineSum = board[0] + board[4] + board[8];
	
	switch (lineSum)
	{
		case 300:
			return 1;
		case -300:
			return 2;
	}

	// 3�A5�A7 �̎΂�
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