#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<errno.h>

//#define MAX 1000
#define NAME_MAX 20
#define SEX_MAX 5
#define ADDR_MAX 30
#define TELE_MAX 12
#define DEFAULT_SZ 3

typedef struct PeoInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char addr[ADDR_MAX];
	char tele[TELE_MAX];
}PeoInfo;

typedef struct Contact
{
	//PeoInfo data[MAX];
	PeoInfo* data;
	int sz;
	int capacity;
}Contact;

void menu();
void InitContact(Contact* pc);
void check_capacity(Contact* pc);

void AddContact(Contact* pc);
void DelContact(Contact* pc);
int SearchContact(Contact* pc);
void ModifyContact(Contact* pc);
void SortContact(Contact* pc);
void ShowContact(const Contact* pc);
void DestroyContact(Contact* pc);


int FindByName(Contact* pc, char name[]);
int CompareByName(const void* e1, const void* e2);
int CompareByAge(const void* e1, const void* e2);
int CompareByAddress(const void* e1, const void* e2);
int CompareByTele(const void* e1, const void* e2);
