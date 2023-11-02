/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Suppose you have left and right parts in bipartite graph and you found the maximum matching $M$. Let's define orientation of edges. Those edges that belong to $M$ will go from right to left, all other edges will go from left to right. Now run DFS starting at all left vertices that are not incident to edges in $M$. Some vertices of the graph will become visited during this DFS and some not-visited. To get minimum vertex cover you take all visited right vertices of $M$, and all not-visited left vertices of $M$.
 * Status: stress-tested
 */
