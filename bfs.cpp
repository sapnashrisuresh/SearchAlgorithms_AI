/*
 * bfs.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: Sapna
 */

// traverses vertices reachable from s.
#include<iostream>
#include<fstream>
#include <queue>
#include <list>
#include <string>
#include <vector>
#include "main2.h"

 string names1[100];
 int n;

class Ranking1
{
private:
 int m_node;
 int m_weight;

public:
 std::priority_queue<Ranking1> open2;
 std::priority_queue<Ranking1> open;
 void priority(int s,int c);
 void replace(int s,int c);
 void addEdge(int v, int w);
 int bfs(int s,int d, string names1[100],int data[100][100]);
 list<int> *adj;

 explicit Ranking1()
 {}

 explicit Ranking1(int node,int weight) : m_node(node), m_weight(weight)
 {
 }


 void size(int n)
 {
	 adj = new list<int>[n];
 }

 //Compares two words. This overloaded operator prioritizes words according to their cost.
 const bool operator < (const Ranking1& pW) const
 {
	 if(m_weight!=pW.m_weight)
		 return (m_weight > pW.m_weight);
	 else
	 {
		 string str1=names1[m_node];
		 string str2=names1[pW.m_node];
		 	 if (str1.compare(str2)>0)
		 		return true;
		 	 else
		 		 return false;
	 }
 }

 //Overloaded "put to" operator for streaming output.
 friend std::ostream& operator <<(std::ostream& out, const Ranking1& pW)
 {
     out<<pW.m_node;
     //open2.push(Ranking1(pW.m_node,pW.m_weight));
     return out;
 }
};

void Ranking1::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

//std::priority_queue<Ranking1> Ranking1::priority(int s,int c)
void Ranking1::priority(int s,int c)
{

Ranking1 pW,element;
open.push(Ranking1(s,c));

while(!open.empty())
{
	element=open.top();
	open2.push(element);
	open.pop();
}

while(!open2.empty())
{
	element=open2.top();
	open.push(element);
	open2.pop();
}
return;
}

void Ranking1::replace(int s,int c)
{
Ranking1 pW,element;

while(!open.empty())
{
	element=open.top();
	if(element.m_node==s)
	{
		element.m_weight=c;
	}
	open2.push(element);
  open.pop();
}

while(!open2.empty())
{
	element=open2.top();
	open.push(element);
	open2.pop();
}

return;
}

int Ranking1::bfs(int s,int d, string names1[100],int data[100][100])
{
		Ranking1 pw;
		Ranking1 pw2;
		//string log[10];
		int source=s;
		int p=0,totalcost=0,cost[100],path[100];
		int parent[100];
		vector<int> closeq;
		vector<int>::iterator v;
		vector<int>::iterator u;
		std::ofstream out("output.txt");
		parent[source]=100;
		cost[source]=0;

	    // Mark all the vertices as not visited
	    bool *visited = new bool[100];
	    for(int i = 0; i < n; i++)
	        visited[i] = false;
	    visited[s] = true;
	    pw.priority(s,cost[s]);
	        // 'i' will be used to get all adjacent vertices of a vertex
	        list<int>::iterator i;
	        while(!pw.open.empty())
	            {
	                // Dequeue a vertex from queue and print it
	            	pw2=pw.open.top();
	                s = pw2.m_node;
	                closeq.push_back(s);

	                if(s==d)
	                        {

	                			out<<names1[closeq.front()];
	                			u=closeq.begin();
	                			u++;
	                			while(u!=closeq.end())
	                			{
	                				out<<"-"<<names1[*u];
	                				u++;
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
	                        	out<<names1[source];
	                        	for(int i=p-2;i>=0;i--)
	                        	{
	                        		out<<"-"<<names1[path[i]];
	                        	}
	                        	for(int i=p-1;i>0;i--)
	                        	{
	                        		totalcost=totalcost+data[path[i]][path[i-1]];

	                        	}
	                        	out<<"\n"<<totalcost;
	                        	//fclose (stdout);
	                        	out.close();
	                        	return 0;
	                        }


	                        pw.open.pop();


	                        // Get all adjacent vertices of the dequeued vertex s
	                        // If a adjacent has not been visited, then mark it visited
	                        // and enqueue it
	                        for(i = adj[s].begin(); i != adj[s].end(); i++)
	                        {
	                        	int newcost=cost[s]+1;

	                            if(!visited[*i])
	                            {
	                            	cost[*i]=newcost;
	                            	parent[*i]=s;
	                                visited[*i] = true;
	                                pw.priority(*i,cost[*i]);
	                            }
	                            if(visited[*i])
	                            {
	                            	//case 3: if a vertex has been explored and the current cost is lesser than
	                            	//node cost, then push it back to the queue
	                            	v=find(closeq.begin(), closeq.end(), *i);
	                            	if(v!=closeq.end() && cost[*i]>newcost)
	                            	{
	                            		cost[*i]=newcost;
	                            		parent[*i]=s;
	                            		pw.priority(*i,cost[*i]);
	                            	}
	                            	 //case 2: if a vertex has been visited and the current cost is lesser than
	                            	 //node cost, then delete it and push it back with updated values to the queue
	                            	if(cost[*i]>newcost)
	                            	{
	                            		parent[*i]=s;
	                            		cost[*i]=newcost;
	                            		pw.replace(*i,cost[*i]);
	                            	}
	                            }

	                        }
	                    }

	        		out<<names1[closeq.front()];
	        	    u=closeq.begin();
	        	    u++;
	        	    while(u!=closeq.end())
	        	    {
	        	          out<<"-"<<names1[*u];
	        	          u++;
	        	    }
	                out<<std::endl;
	                    out<<"NoPathAvailable";
	                    out.close();
	                    //fclose (stdout);
	                    return 0;
}

int main2()
{
	Ranking1 g;
	int data[100][100],a;
		int source, destination;
					  string src, dest;

					  ifstream in;
					  in.open("input.txt");
					  in>>a;
					  in >> src;
					  in >> dest;
					  in >> n;

					  for (int i=0;i<n;i++)
					  {
					  	  in>>names1[i];
					  	  if(names1[i]==src)
					  	     source=i;
					  	   if(names1[i]==dest)
					  	      destination=i;

					  }


					  for (int j=0; j<n; j++)
					  {
						  for (int k=0; k<n; k++)
					  		  {
					  			  in>>data[j][k];
					  		  }
					  }
					  g.size(n);
					      for(int i=0;i<n;i++)
					      {	for(int j=0;j<n;j++)
					      	{
					      		if(data[i][j]!=0)
					      		    			g.addEdge(i,j);
					      	}

					      }

					      int c=g.bfs(source,destination,names1,data);

					  return c;
}
