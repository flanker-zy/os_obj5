#pragma once
#include<iostream>
#include<fstream>

using namespace std;

#define MAXSIZE 100
typedef struct Lnode{
	int num;
	Lnode* next;
	int step = 0;
}work,*worklist;

typedef struct List {
	work* front;
	work* rear;
}LinkQueue;