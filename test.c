#include <openssl/sha.h>
#include <stdio.h>

void test_help()
{
    printf("Available tests:\n"

           "    test config                         show configuration\n"
           "    test hash <s1> <s2> ...             compute hash of strings s1, s2, ...\n"
           "    test c2i <c1> <c2> ...              compute c2i(c1), c2i(c2), ...\n"
           "    test i2c <i1> <i2> ...              compute i2c(i1), i2c(i2), ...\n"
           "    test h2i <s> <t> [n]                compute h2i(H(s), t, n)\n"
           "    test i2i <i1> <t1> ...              compute i2i(i1, t1), i2i(i2, t2), ...\n"
           "    test time_i2i [N]                   compute average time of single i2i call over N calls\n"
           "    test full_chain <width> <i1> ...    compute (full) chains starting at i1, i2, ...\n"
           "    test FULL_chain <width> <i1> ...    compute (full, with details) chains starting at i1, i2, ...\n"
           "    test chain <w1> <i1> <w2> <i2> ...  compute chains starting at i1, i2, ..., of length w1, w2, ...\n"
           "    test search <FILENAME> <i>          search the first and last occurences of i in table\n"
           "    test list                           this list\n");
}
