/**
 * Description: Sort queries by tuple $\left(\lfloor l/B\rfloor, \lfloor r/B\rfloor, t\right)$ where $t$ is the time of query. If DS has answer for $[L,R]$ at time $T$ now, then we have to adjust range (add/remove like usual Mo). For time, we need to make some updates if $t<T$ and rollback some updates if $t>T$.
 * Time: O(Q N^{2/3})
 */