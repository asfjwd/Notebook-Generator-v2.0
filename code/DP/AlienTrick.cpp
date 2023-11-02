/**
 * Author: anik sarker, sm junayer, hrd dhrubo
 * License: CC0
 * Source: Upside-Down library
 * Description: Divide $n$ elements into $k$ groups and minimize the sum of a cost function for each group. If $f_n(k)\geq f_n(k+1)$ (monotone) and $f_n(k-1)-f_n(k)\geq f_n(k)-f_n(k+1)$ (convex) we can apply alien trick. It means with the increase of $k$, answer becomes more optimal, but the rate of becoming optimal slows down. We define $g_n = f_n(k) + kC$. That means we need to add a penalty $C$ for each group we use. We can binary search on $C$ as $g$ is convex. Compute $g_n$ and the optimal $k$ on each iteration -- $k$ decreases when $C$ increases.
 * Time: $O(n \log \text{max})$
 */