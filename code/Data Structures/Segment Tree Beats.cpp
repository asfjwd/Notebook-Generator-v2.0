/**
 * Description: For update $A_i\rightarrow A_i\bmod x$ and similar, keep range min, max in node and lazily update whenever $\text{min} = \text{max}$. For update $A_i \rightarrow \min(A_i,x)$ and similar, keep range max, second max in node and lazily update whenever $x > \text{second max}$.
 * Time: O(\log^2 N), O(\log N)
 */
