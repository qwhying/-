#include<cstdio>
#include<stdlib.h>
#include <Windows.h>
typedef struct GOAL
{
	char name[20];
	int score;
}goal;
void Cursor(int x, int y)
{
	COORD  pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//返回标准的输入、输出或错误的设备的句柄，也就是获得输入、输出/错误的屏幕缓冲区的句柄
	SetConsoleCursorPosition(hOutput, pos);
}

//对于风云榜进行控制台输出
int rank()
{
	goal tmp[10];
	FILE* fp;
	int i = 0, n = 0;
	int j = 0;
	errno_t err;
	err = fopen_s(&fp,"高分榜.txt", "r");
	if (fp == NULL)
	{
		printf("cannot open the files\n");
		system("pause");
		return -2;//如果文件出现错误返回-1  

	}
	/*else {
		printf("T");
		Sleep(1000);
	}*/
	char c = fgetc(fp);
	while (i < 10 && (!feof(fp)))
	{
		fscanf_s(fp, "%s%d", tmp[i].name, 20, &tmp[i].score);
		printf("T");
		i++;
		j++;
	}
	printf("%d", j);
	fclose(fp);
	if (j != 0)
	{
		for (i = 1; i < j + 1; i++)
		{
			printf("\n");
			printf("%5d", i);
			printf("%10s %10d", tmp[i - 1].name, tmp[i - 1].score);

		}
	}
	else
	{
		printf("还没有来挑战，快点来挑战吧");
	}

	return 0;
}

//对风云榜进行信息添加
int rankchange()
{
	int score = 0;

	goal tmp[10];
	FILE* fp = NULL;
	int i = 0, n = 0;
	int j = 0;
	errno_t err;
	err = fopen_s(&fp, "高分榜.txt", "r");
	if (fp == NULL)
	{
		printf("cannot open the file\n");
		system("pause");
		return -1;//如果文件出现错误返回-1  
	}
	char c = fgetc(fp);
	
		//rewind(fp);
	while ((i < 10) && (!feof(fp))&&c!=-1)
	{
		fseek(fp, -1L, 1);
		fscanf_s(fp, "%s", &tmp[i].name, 20);
		fscanf_s(fp, "%d", &tmp[i].score);
		printf("NUll");
		i = i + 1;
		j++;
		c = fgetc(fp);
		c = fgetc(fp);
	}
	

	if (i == 9)
	{
		if (score > tmp[i].score)
		{
			Cursor(35, 15);
			printf("大侠请输入您的大名：");
			scanf_s("%s", &tmp[i].name);
			tmp[i].score = score;
		}
		else if (score < tmp[i].score)
		{
			printf("没有达到前十名，未能进入英雄榜");
		}
		else
		{
			printf("有点遗憾，虽然你已经和第十名分数相同，但是根据先来后到的原则，不能录入");
		}
	}
	else {
		Cursor(35, 15);;
		printf("大侠请输入您的大名：");
		scanf_s("%s", tmp[i].name,20);
		printf("%s ", tmp[i].name);
		tmp[i].score = score;
		printf("%d ", tmp[i].score);
		printf("^%d\n", i);
	}

	fclose(fp);
	err= fopen_s(&fp,"高分榜.txt", "w");
	if (fp == NULL)
	{
		printf("cannot open the file\n");
		system("pause");
		return -1;//如果文件出现错误返回-1  
	}


	for (int j = 0; j <= i; j++)

	{
		fprintf(fp, "%s ", tmp[j].name);
		fprintf(fp, "%d ", tmp[j].score);
		//fprintf(fp, "\n");
	}


	fclose(fp);
	return 0;

}

//对文件当中的信息进行重新排序修改
int readrank()
{
	goal tmp[10];
	goal temp;
	int j = 0, i = 0, k = 0;
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp,"rank.txt", "rb");
	if (fp == NULL)
	{
		printf("cannot open the files\n");
		system("pause");
		return -1;
	}
	while (i < 10 && fscanf_s(fp, "%s %d", tmp[i].name, &tmp[i].score) != EOF)
	{
		i++;
	}
	for (j = 0; j < i; j++)
		for (k = 0; k <= i; k++)
		{
			if (tmp[k].score > tmp[j].score)
			{
				temp = tmp[k];
				tmp[k] = tmp[j];
				tmp[j] = temp;
			}
		}
	for (i = 0; i <= 10; i++)
		fprintf(fp, "%s %d", tmp[i].name, tmp[i].score);
	fclose(fp);
	return 0;
}


int main()
{

	/*	file* fstream = null;
		int	ireturn = 1;
		char ch;
		errno_t err;
		err = fopen_s(&fstream,"高分榜.txt", "r+");
		if (fstream != null)
		{
			fseek(fstream, 0, seek_set);

			ch = fgetc(fstream);

			if (feof(fstream))
			{
				printf("it reaches the end\n");
			}
			else
			{
				printf("it doesn't reach the end\n");
			}
		}*/
	//rank();
	rankchange();
	rankchange();
	readrank();
	return 0;
}