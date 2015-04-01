/*
 * dfs.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: Sapna
 */

// traverses vertices reachable from s.

#include<iostream>
#include<fstream>
#include <list>
#include <stack>
#include <vector>
#include "main3.h"

using namespace std;

class Graph2
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
public:
    Graph2(int V);  // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    void sort(int n,string names[100]);
    int DFS(int s,int d,string names[100], int data[100][100]);  // prints DFS traversal from a given source s
};

Graph2::Graph2(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph2::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}


int Graph2::DFS(int s,int d, string names[100],int data[100][100])
{
	int source,p=0,totalcost=0;
	source=s;
	int parent[100],path[100],cost[100];
	vector<int> closeq;
	vector<int>::iterator v;
	std::ofstream out("output.txt");
	parent[source]=100;
	cost[source]=0;
    // Mark all the vertices as not visited
    bool *visited = new bool[100];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Create a stack for DFS
    vector<int> stack;
    vector<int>::iterator u;
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    stack.push_back(s);
    //cout<<names[s]<<"\n";

    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;

    while(!stack.empty())
    {
        // pop a vertex from stack and print it
        s=stack.back();
        closeq.push_back(s);

        if(s==d)
        {
        	out<<names[closeq.front()];
        	v=closeq.begin();
        	v++;
        	while(v!=closeq.end())
        	{
        		out<<"-"<<names[*v];
        		v++;
        	}
        	out<<std::endl;
        	path[0]=s;
        	p++;
        	while(parent[s]!=100)
        	{
        		path[p]=parent[s];
        		s=path[p];
        		p++;

        	}
        	out<<names[source];
        	for(int i=p-2;i>=0;i--)
        	{
        		out<<"-"<<names[path[i]];
        	}
        	for(int i=p-1;i>0;i--)
        	{
        		totalcost=totalcost+data[path[i]][path[i-1]];

        	}
        	out<<"\n"<<totalcost;
        	out.close();
        	return 0;
        }
        stack.pop_back();
        // Get all adjacent vertices of the dequeued vertex s
        // case 1: If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = adj[s].begin(); i != adj[s].end(); i++)
        {
        	int newcost=cost[s]+1;
            if(!visited[*i])
            {
            	cost[*i]=newcost;
            	parent[*i]=s;
                visited[*i] = true;
                stack.push_back(*i);

            }
            //case 3: if a vertex has been explored and the current cost is lesser than
            //node cost, then push it back to the stack
            v=find(closeq.begin(), closeq.end(), *i);
            if(v!=closeq.end() && cost[*i]>newcost)
            {

                cost[*i]=newcost;
                parent[*i]=s;
                stack.push_back(*i);
            }
            //case 2: if a vertex has been visited and the current cost is lesser than
            //node cost, then delete it and push it back with updated values to the stack
            if(visited[*i] && cost[*i]>newcost)
            {
            	u=find(stack.begin(), stack.end(), *i);
            	if(u!=stack.end())
            	{//cout<<"here for "<<*i<<"\n";
            		int position=distance(closeq.begin(),v);
            		stack.erase(stack.begin()+position);
            		parent[*i]=s;
            		cost[*i]=newcost;
            		stack.push_back(*i);
            	}
            }

        }

    }
    out<<names[closeq.front()];
    v=closeq.begin();
    v++;
    while(v!=closeq.end())
    {
    	out<<"-"<<names[*v];
        v++;
    }
    out<<std::endl;
    out<<"NoPathAvailable";
    out.close();
    return 0;
}

int main3()
{
	int a,n,source,destination;
	string src,dest,names[100],names2[100],names3[100],target;
	int data[100][100],data2[100][100],sortarray[100];
	ifstream in;
				  in.open("input.txt");
				  in >> a;
				  in >> src;
				  in >> dest;
				  in >> n;

				  for (int i=0;i<n;i++)
				  {
					  in>>names2[i];
				  	  names3[i]=names2[i];

				  }
				  std::sort(names3,names3+n);
				  int j=n-1;
				  for (int i=0;i<n;i++)
				  {
					  names[i]=names3[j];
				  	  j--;
				  }
				  for(int i=0;i<n;i++)
				  {
					  target=names2[i];
				  	  for(int j=0;j<n;j++)
				  	  {
				  		  if(names[j]==target)
				  		  sortarray[i]=j;
				  	  }
				   }

				   for (int j=0; j<n; j++)
				   {
					   for (int k=0; k<n; k++)
				  	   {
						   in>>data2[j][k];
				  		   data[sortarray[j]][sortarray[k]]=data2[j][k];
				  	   }
				    }

				    for(int i=0;i<n;i++)
				    {
				    	if(names[i]==src)
				    		source=i;
				    	if(names[i]==dest)
				    		destination=i;
				    }

				    // Create a graph for the adjacency matrix
				    Graph2 g(n);
				    for(int i=0;i<n;i++)
				    {
				    	for(int j=0;j<n;j++)
				    	{
				    		if(data[i][j]!=0)
				    		{    g.addEdge(i,j); 	}
				    	}
				    }

				   int c=g.DFS(source,destination,names,data);
    return 0;
}
