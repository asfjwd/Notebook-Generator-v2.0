/**
 * Description: Build Euler order of $2N$ size - write node ID when entering AND exiting. Path ($u, v$) with in[$u$] < in[$v$] is now range. If u is LCA, then range is [in[$u$], in[$v$]]. If not, then range is [out[$u$], in[$v$]] $\cup$ [in[LCA], in[LCA]]. Nodes that appear exactly once (not 0 or 2 times) on these ranges are relevant, maintain them during Mo.
 * Time: O(N \sqrt Q)
 */
