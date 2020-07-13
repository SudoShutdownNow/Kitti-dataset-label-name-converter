#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <string>
#pragma warning (disable :4996)
using namespace std;
//int numbercount(int n); //此函数已被淘汰
void rightmove(char* p,int length);
struct element
{
	char nlabel[15];//new label
	float data[15];
}element[50];

int main()
{
	char label1[15];
	char label2[15];
	char olabel1[15];
	char olabel2[15];
	cout << "请输入第一种原标签：";
	cin >> olabel1;
	cout << "请输入第一种新标签：";
	cin >> label1;
	cout << "请输入第二种原标签：";
	cin >> olabel2;
	cout << "请输入第二种新标签：";
	cin >> label2;

	FILE* fp;
	char filename[14];
	int i;
	int failure = 0;
	for (i = 1; ; i++)
	{
		start:
		sprintf(filename, "%d", i);
		int numbercount = strlen(filename);
		rightmove(filename, numbercount);
		filename[0] = 'b';//在这里定义文件打头的字母
		for (int j = 1; j <= 8-numbercount; j++)
		{
			filename[j] = '0';
		}
		filename[9] = '.';
		filename[10] = 't';
		filename[11] = 'x';
		filename[12] = 't';
		filename[13] = 0;
		//cout << filename << endl;


		if ((fp = fopen(filename , "r")) == NULL)
		{
			failure++;
			if (failure >= 100)//文件名断档大于100个时判断程序结束
			{
				cout << "文件名中断超过100个，已完成" << endl;
				break;
			}
			else
			{
				i++;
				goto start;
			}
			
		}
		char olabel[15];//old label from file
		int tiaoexist = 0;//已存在的条目数
		failure = 0;

		while (1)//读取部分
		{
			readbegin:
			if (fscanf(fp, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f", olabel,&element[tiaoexist].data[0], &element[tiaoexist].data[1], &element[tiaoexist].data[2], &element[tiaoexist].data[3], &element[tiaoexist].data[4], &element[tiaoexist].data[5], &element[tiaoexist].data[6], &element[tiaoexist].data[7], &element[tiaoexist].data[8], &element[tiaoexist].data[9], &element[tiaoexist].data[10], &element[tiaoexist].data[11], &element[tiaoexist].data[12], &element[tiaoexist].data[13] ) == EOF)
			{
				
				fclose(fp);
				break;
				
			}
			else
			{
				if (strcmp(olabel, olabel1) == 0)
				{
					strcpy(element[tiaoexist].nlabel, label1);
				}
				else if (strcmp(olabel, olabel2) == 0)
				{
					strcpy(element[tiaoexist].nlabel, label2);
				}
				else if (strcmp(olabel, label1) == 0)
				{
					strcpy(element[tiaoexist].nlabel, label1);
				}
				else if (strcmp(olabel, label2) == 0)
				{
					strcpy(element[tiaoexist].nlabel, label2);
				}

				else
				{
					cout << "文件 " << filename << "的第" << tiaoexist << "条数据标签是 " << olabel << "，无法被识别" << endl;
					strcpy(element[tiaoexist].nlabel, olabel);
					system("pause");
					tiaoexist++;
					goto readbegin;
					
				}
			}
			tiaoexist++;
		}

		fp = fopen(filename, "w");
		for (int w = 0; w <= tiaoexist - 1; w++)
		{
			fprintf(fp, "%s %.2f %d %.1f %.2f %.2f %.2f %.2f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\n", element[w].nlabel, element[w].data[0], int(element[w].data[1]), element[w].data[2], element[w].data[3], element[w].data[4], element[w].data[5], element[w].data[6], element[w].data[7], element[w].data[8], element[w].data[9], element[w].data[10], element[w].data[11], element[w].data[12], element[w].data[13], element[w].data[14]);
		}
		fclose(fp);
		cout << filename << "转换完成！" << endl;

	}
	cout << "全部完成！";
	system("pause");
}

/*int numbercount(int n)//count numbers 此函数已被淘汰
{
	int i;
	for (i = 1; n / 10 != 0; i++)
	{
		n /= 10;
	}
	return i;
}*/

void rightmove(char* p, int length)
{
	for (int i = 0; i <= length - 1; i++)
	{
		*(p + 8 - i) = *(p + length-1-i);
		*(p + length - 1) = '0';
	}
}

