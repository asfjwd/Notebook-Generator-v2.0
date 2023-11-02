#include <bits/stdtr1c++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type,
less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

// T.insert(x)
// *T.find_by_order(k) -> kth element
// T.order_of_key(x) -> position of 1st element >= x