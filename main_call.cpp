// Program to print BFS traversal from a given source vertex. BFS(int s)
// traverses vertices reachable from s.
#include<iostream>
#include <fstream>
#include <string>
#include "main2.h"
#include "main3.h"
#include "main4.h"

using namespace std;


int main()
{
	int a;
	ifstream in;
	in.open("input.txt");
	in >> a;
		  if(a==1)
		  { int b=main2();}
		  if(a==2)
		  { int c=main3(); }
		  if(a==3)
		  { int d=main4(); }

	  return 0;
}
