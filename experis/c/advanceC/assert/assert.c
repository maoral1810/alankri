/* #define NDEBUG */
#include <assert.h> /* assert */

int main(void)
{
    int i = 10;
    int j = 20;

    assert(i == 20);
    assert(i == 20);
    assert(j == 20);

    return 0;
}