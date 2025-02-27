#include "common.h"
#include <time.h>

void Spin(int sleep) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < sleep) {
    }
}
