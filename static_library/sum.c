#include "sum.h"
#include "mul.h"

int sum_and_mul(int first, int second) {
    return first + mul(first, second);
}
