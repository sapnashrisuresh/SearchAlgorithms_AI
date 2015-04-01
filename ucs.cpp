/*
 * dfs.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: Sapna
 */

// traverses vertices reachable from s.
#include<iostream>
#include<fstream>
#include <queue>
#include <list>
#include <string>
#include <vector>
#include "main4.h"

 string names2[100];
 int n2;

class Ranking2
{
private:
 int m_node;
 int m_weight;

public:
 std::priority_queue<Ranking2> open2;
 std::priority_queue<Ranking2> open;
 void priority(int s,int c);
 void replace(int s,int c);
 void addEdge(int v, int w);
 int ucs(int s,int d, string names2[100],int data[100][100]);
 list<int> *adj;

 explicit Ranking2()
 {}

 explicit Ranking2(int node,int weight) : m_node(node), m_weight(weight)
 {
 }


 void size(int n2)
 {
	 adj = new list<int>[n2];
 }

 //Compares two words. This overloaded operator prioritizes words according to their weight.
 const bool operator < (const Ranking2& pW) const
 {
	 if(m_weight!=pW.m_weight)
		 return (m_weight > pW.m_weight);
	 else
	 {
		 string str1=names2[m_node];
		 string str2=names2[pW.m_node];
		 	 if (str1.compare(str2)>0)
		 		return true;
		 	 else
		 		 return false;
	 }
 }

 //Overloaded "put to" operator for streaming output.
 friend std::ostream& operator <<(std::ostream& out, const Ranking2& pW)
 {
     out<<pW.m_node;
     return out;
 }
};

void Ranking2::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Ranking2::priority(int s,int c)
{

Ranking2 pW,element;
open.push(Ranking2(s,c));

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

void Ranking2::replace(int s,int c)
{
Ranking2 pW,element;

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


int Ranking2::ucs(int s,int d, string names2[100],int data[100][100])
{
		Ranking2 pw;
		Ranking2 pw2;
		int source=s,newcost;
		vector<int> closeq;
		vector<int>::iterator v;
		int p=0,totalcost=0,cost[100];
		int parent[100],path[100];
		std::ofstream out("output.txt");
		parent[source]=100;
		cost[source]=0;

	    // Mark all the vertices as not visited
	    bool *visited = new bool[100];
	    for(int i = 0; i < n2; i++)
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

	                			out<<names2[closeq.front()];
	                		    v=closeq.begin();
	                		    v++;
	                		    while(v!=closeq.end())
	                		    {
	                		        out<<"-"<<names2[*v];
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
	                        	out<<names2[source];
	                        	for(int i=p-2;i>=0;i--)
	                        	{
	                        		out<<"-"<<names2[path[i]];
	                        	}
	                        	for(int i=p-1;i>0;i--)
	                        	{
	                        		totalcost=totalcost+data[path[i]][path[i-1]];

	                        	}
	                        	out<<"\n"<<totalcost;
	                        	out.close();
	                        	return 0;
	                        }


	                        pw.open.pop();

	                        // Get all adjacent vertices of the dequeued vertex s
	                        // case 1: If a adjacent has not been visited, then mark it visited
	                        // and enqueue it
	                        for(i = adj[s].begin(); i != adj[s].end(); i++)
	                        {
	                        	//cout<<"parent is "<<s<<"\n";
	                        	//cout<<"here "<<*i;
	                        	newcost=cost[s]+data[*i][s];
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

	        out<<names2[closeq.front()];
	        v=closeq.begin();
	        v++;
	        while(v!=closeq.end())
	        {
	        	  out<<"-"<<names2[*v];
	        	  v++;
	        }
	                out<<std::endl;
	                    out<<"NoPathAvailable";
	                    out.close();
	                    return 0;
}

int main4()
{
	Ranking2 g;
	int data[100][100],a,n2;
		int source, destination;
					  string src, dest;

					  ifstream in;
					  in.open("input.txt");
					  in>>a;
					  in >> src;
					  in >> dest;
					  in >> n2;
					  for (int i=0;i<n2;i++)
					  {
					  	  in>>names2[i];
					  	  if(names2[i]==src)
					  	     source=i;
					  	   if(names2[i]==dest)
					  	      destination=i;
					  }


					  for (int j=0; j<n2; j++)
					  {
						  for (int k=0; k<n2; k++)
					  		  {
					  			  in>>data[j][k];
					  		  }
					  }
					  g.size(n2);
					      for(int i=0;i<n2;i++)
					      {	for(int j=0;j<n2;j++)
					      	{
					      		if(data[i][j]!=0)
					      		    			g.addEdge(i,j);
					      	}

					      }

					      int c=g.ucs(source,destination,names2,data);


					  return c;
}
