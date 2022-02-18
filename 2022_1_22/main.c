#define _CRT_SECURE_NO_WARNINGS 
#include"head.h"

int main()
{
	int input = 0;
	Contact con;
	InitContact(&con);
	do {
		menu();
		printf("Enter> ");  
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			AddContact(&con);
			break;
		case 2:
			DelContact(&con);
			break;
		case 3: 
			SearchContact(&con);
			break;
		case 4:
			ModifyContact(&con);
			break;
		case 5:
			SortContact(&con);
			break;
		case 6:
			ShowContact(&con);
			break;
		case 0:
			SaveContact(&con);
			DestroyContact(&con);
			printf("exit\n");
			break;
		default:
			printf("select error\n");
			break;
		}
	} while (input);
	return 0;
}