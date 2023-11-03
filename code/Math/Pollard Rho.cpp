/**
 * Author: chilli, SJTU, pajenegod
 * Date: 2020-03-04
 * License: CC0
 * Source: own
 * Description: Pollard-rho randomized factorization algorithm. Returns prime
 * factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11\}).
 * Time: $O(n^{1/4})$, less for numbers with small factors.
 * Status: stress-tested
 *
 * Details: This implementation uses the improvement described here
 * (https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants), where
 * one can accumulate gcd calls by some factor (40 chosen here through
 * exhaustive testing). This improves performance by approximately 6-10x
 * depending on the inputs and speed of gcd. Benchmark found here:
 * (https://ideone.com/nGGD9T)
 *
 * GCD can be improved by a factor of 1.75x using Binary GCD
 * (https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/).
 * However, with the gcd accumulation the bottleneck moves from the gcd calls
 * to the modmul. As GCD only constitutes ~12% of runtime, speeding it up
 * doesn't matter so much.
 *
 * This code can probably be sped up by using a faster mod mul - potentially
 * montgomery reduction on 128 bit integers.
 * Alternatively, one can use a quadratic sieve for an asymptotic improvement,
 * which starts being faster in practice around 1e13.
 *
 * Brent's cycle finding algorithm was tested, but doesn't reduce modmul calls
 * significantly.
 *
 * Subtle implementation notes:
 * - we operate on residues in [1, n]; modmul can be proven to work for those
 * - prd starts off as 2 to handle the case n = 4; it's harmless for other n
 *   since we're guaranteed that n > 2. (Pollard rho has problems with prime
 *   powers in general, but all larger ones happen to work.)
 * - t starts off as 30 to make the first gcd check come earlier, as an
 *   optimization for small numbers.
 */

typedef long long ll;
typedef unsigned long long ull;

namespace Rho {
  ull mul (ull a, ull b, ull mod) {
    ll ret = a * b - mod * (ull) (1.L / mod * a * b);
    return ret + mod * (ret < 0) - mod * (ret >= (ll) mod);
  }

  ull bigMod (ull a, ull e, ull mod) {
    ull ret = 1;
    while (e) {
      if (e & 1) ret = mul(ret, a, mod);
      a = mul(a, a, mod), e >>= 1;
    }
    return ret;
  }
    
  bool isPrime (ull n) {
    if (n < 2 or n % 6 % 4 != 1) return (n | 1) == 3;
    ull a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    ull s = __builtin_ctzll(n - 1), d = n >> s;
    for (ull x : a) {
      ull p = bigMod(x % n, d, n), i = s;
      while (p != 1 and p != n - 1 and x % n and i--) p = mul(p, p, n);
      if (p != n - 1 and i != s) return 0;
    }
    return 1;
  }
    
  ull pollard (ull n) {
    auto f = [&] (ull x) {return mul(x, x, n) + 1;};
    ull x = 0, y = 0, t = 0, prod = 2, i = 1, q;
    while (t++ % 40 or __gcd(prod, n) == 1) {
      if (x == y) x = ++i, y = f(x);
      if ((q = mul(prod, max(x, y) - min(x, y), n))) prod = q;
      x = f(x), y = f(f(y));
    }
    return __gcd(prod, n);
  }

  vector <ull> factor (ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
  }
};
