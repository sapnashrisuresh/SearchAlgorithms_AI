### CSCI561 - Fall 2014 - Sample Makefile - Assignment 1 - Sapnashri Suresh

### Example for a C++ agent:
agent: main_call.cpp bfs.cpp dfs.cpp ucs.cpp
	g++ main_call.cpp bfs.cpp dfs.cpp ucs.cpp -o agent

run: agent
	./agent
