#include <assert.h>

int main(int argc, char **argv) {
    int is_debug = -1;
    assert(is_debug++);
    return is_debug;
}
