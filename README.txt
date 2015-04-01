

1. For DFS/BFS/UCS, as per clean and robust algorithm condition 3 :
	if there exists node in closed that has child’s state
		if PathCost(child) < PathCost(node)
			closed <- Delete-Node(closed,node)
			open <- Queuing-Fn(open,child)

   Hence, log(expansion) may have “multiple entries” of the same node as they are revisited.
