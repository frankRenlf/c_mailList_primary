#define _CRT_SECURE_NO_WARNINGS 
#include"head.h"

void menu()
{
	printf("**********\n1.add\n2.del\n3.search\n4.modify\n5.sort\n6.show\n0.exit\n**********\n");
}

void InitContact(Contact* pc)
{
	assert(pc);
	pc->sz = 0;
	//memset(pc->data, 0, sizeof(pc->data));
	PeoInfo* tmp = (PeoInfo*)malloc(DEFAULT_SZ * sizeof(PeoInfo));
	if (tmp != NULL)
	{
		pc->data = tmp;
	}
	else
	{
		printf("InitContact()::%s\n", strerror(errno));
		return;
	}
	pc->capacity = DEFAULT_SZ;

	//load file
	LoadContact(pc);	
}



void check_capacity(Contact* pc)
{
	assert(pc);
	if (pc->sz == pc->capacity)
	{
		PeoInfo* tmp = (PeoInfo*)realloc(pc->data, (pc->capacity + DEFAULT_SZ) * sizeof(PeoInfo));
		if (tmp != NULL)
		{
			pc->data = tmp;
			pc->capacity += DEFAULT_SZ;
			printf("Successful capacity increase\n");
		}
		else
		{
			printf("%s\n", strerror(errno));
		}
	}
}

void AddContact(Contact* pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	check_capacity(pc);
	printf("Enter name: ");
	scanf("%s", name);
	if (FindByName(pc, name) == -1)
	{
		strcpy(pc->data[pc->sz].name, name);
		printf("Enter age: ");
		scanf("%d", &(pc->data[pc->sz].age));
		printf("Enter sex: ");
		scanf("%s", pc->data[pc->sz].sex);
		printf("Enter tele: ");
		scanf("%s", pc->data[pc->sz].tele);
		printf("Enter address: ");
		scanf("%s", pc->data[pc->sz].addr);

		pc->sz++;
		printf("Operation success!\n");
	}
	else
	{
		printf("The name is exit\nOperation failed!\n");
	}
}

void DelContact(Contact* pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	if (pc->sz == 0)
	{
		printf("Mail list is empty\n");
		return;
	}
	printf("name: ");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("Name is not exit\n");
	}
	else
	{
		int j = 0;
		for (j = pos; j < pc->sz - 1; j++)
		{
			pc->data[j] = pc->data[j + 1];
		}
		memset(&(pc->data[pc->sz - 1]), 0, sizeof(pc->data[0]));
		pc->sz--;
		printf("Operation success!\n");
	}
}

int SearchContact(Contact* pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	if (pc->sz == 0)
	{
		printf("Mail list is empty\n");
		return;
	}
	printf("name: ");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("Name is not exit\n");
	}
	else
	{
		printf("%-10s\t%-5s\t%-5s\t%-13s\t%-20s\n", "name", "age", "sex", "telephone", "address");
		printf("%-10s\t%-5d\t%-5s\t%-13s\t%-20s\n", pc->data[pos].name, pc->data[pos].age, pc->data[pos].sex, pc->data[pos].tele, pc->data[pos].addr);
	}
	return pos;
}

void ModifyContact(Contact* pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	int pos = SearchContact(pc);
	printf("Enter name: ");
	scanf("%s", name);
	if (FindByName(pc, name) == -1)
	{
		strcpy(pc->data[pos].name, name);
		printf("Enter age: ");
		scanf("%d", &(pc->data[pos].age));//(pc->data+pos)->age
		printf("Enter sex: ");
		scanf("%s", pc->data[pos].sex);
		printf("Enter tele: ");
		scanf("%s", pc->data[pos].tele);
		printf("Enter address: ");
		scanf("%s", pc->data[pos].addr);
		printf("Operation success!\n");
	}
	else
	{
		printf("The name is exit\nOperation failed!\n");
	}
	printf("Operation success!\n");
}

void SortContact(Contact* pc)
{
	assert(pc);
	if (pc->sz == 0)
	{
		printf("Mail list is empty\n");
		return;
	}
	int (*pl[])(int, int) = { 0,CompareByName,CompareByAge,CompareByTele,CompareByAddress };
	printf("1.name\n2.age\n3.telephone\n4.address\n");
	printf("Sort by what: ");
	int input = 0;
	scanf("%d", &input);
	//qsort(void* base, size_t num, size_t size,int (*compar)(const void*, const void*));
	qsort(pc->data, pc->sz, sizeof(pc->data[0]), pl[input]);
	printf("Operation success!\n");
}


void ShowContact(const Contact* pc)
{
	assert(pc);
	printf("%-10s\t%-5s\t%-5s\t%-13s\t%-20s\n", "name", "age", "sex", "telephone", "address");
	for (int i = 0; i < pc->sz; i++)
	{
		printf("%-10s\t%-5d\t%-5s\t%-13s\t%-20s\n", pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
}

void DestroyContact(Contact* pc)
{
	assert(pc);
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
	printf("Destroy data\n");
}

int FindByName(const Contact* pc, char name[])
{
	int i = 0;
	for (int i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int CompareByName(const void* e1, const void* e2)
{
	return strcmp(((PeoInfo*)e1)->name, ((PeoInfo*)e2)->name);
}

int CompareByAge(const void* e1, const void* e2)
{
	return ((PeoInfo*)e1)->age - ((PeoInfo*)e2)->age;

}
int CompareByAddress(const void* e1, const void* e2)
{
	return strcmp(((PeoInfo*)e1)->addr, ((PeoInfo*)e2)->addr);

}
int CompareByTele(const void* e1, const void* e2)
{
	return strcmp(((PeoInfo*)e1)->tele, ((PeoInfo*)e2)->tele);
}

void LoadContact(Contact* pc)
{
	FILE* pf = fopen("contact.txt", "rb");
	if (pf == NULL)
	{
		printf("InitContact:: open for reading: %s\n", strerror(errno));
		return;
	}
	//read data
	PeoInfo buf = { 0 };
	while (fread(&buf, sizeof(PeoInfo), 1, pf))
	{
		check_capacity(pc);
		pc->data[pc->sz] = buf;
		pc->sz++;
	}
	//close file
	fclose(pf);
	pf = NULL;
}

void SaveContact(Contact* pc)
{
	FILE* pf = fopen("contact.txt", "wb");
	if (pf == NULL)
	{
		printf("SaveContact: %s\n", strerror(errno));
		return ;
	}
	//write
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
	}
	printf("Save file\n");
	//close
	fclose(pf);
	pf = NULL;
}
