/**
 * Barebones min heap sort implementation in C.
 * Author: Adam Hutchings
 * Do as you wish with this code.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

#define SWAP(a, b) do { \
    a ^= b; \
    b ^= a; \
    a ^= b; \
} while (0)

/**
 * Sift an element up in a heap.
 */
int heap_siftup(int * elements, int max, int idx) {
    if (idx >= max)
        return -1;
    int pidx;
    while (idx != 0) {
        pidx = (idx - 1) / 2;
        if (elements[idx] < elements[pidx]) {
            SWAP(elements[idx], elements[pidx]);
        } else {
            break;
        }
        idx = pidx;
    }
    return 0;
}

/**
 * Create a heap from an unstructured array.
 */
int heapify(int * elements, int ct) {
    for (int i = 0; i < ct; ++i) {
        heap_siftup(elements, ct, i);
    }
    return 0;
}

/**
 * Remove the largest element and re-heapify the array.
 */
int heap_pop(int * elements, int ct) {

    if (ct == 0)
        return -1;

    int ret = elements[0];
    int idx = 0;
    int cidx;

    while (1) {
        int lc = idx * 2 + 1;
        int rc = idx * 2 + 2;
        if (rc < ct) {
            if (elements[rc] < elements[lc]) {
                cidx = rc;
            } else {
                cidx = lc;
            }
        } else if (lc < ct) {
            cidx = lc;
        } else {
            break;
        }
        elements[idx] = elements[cidx];
        idx = cidx;
    }

    elements[idx] = elements[ct - 1];
    heap_siftup(elements, ct - 1, idx);

    return ret;

}

int main(int argc, char ** argv) {

    /* Sorts numbers smallest to largest. */

    int ELEMENT_CT;

    if ((argc < 2) || (sscanf(argv[1], "%d", &ELEMENT_CT) != 1)) {
        ELEMENT_CT = 1000000;
        printf("%s\n", "Heap sort: invalid size -- using 1 million elements.");
    } else {
        printf("Heap sort: benchmark with %d elements.\n", ELEMENT_CT);
    }

    printf("%s\n", "Heap sort: creating random data ...");
    char cmd[64];
    snprintf(cmd, 64, "python3 src/gen-randoms.py %d", ELEMENT_CT);
    /* Generate random data. */
    system(cmd);

    FILE * fp = fopen("data/random.txt", "r");
    int * ints = malloc(ELEMENT_CT * sizeof(int));
    int * sorted_ints = malloc(ELEMENT_CT * sizeof(int));
    for (int i = 0; i < ELEMENT_CT; ++i) {
        fscanf(fp, "%d\n", &ints[i]);
    }

    printf("Heap sort: created file with %d elements.\n", ELEMENT_CT);

    struct timeval stop, start;
    gettimeofday(&start, NULL);
    
    heapify(ints, ELEMENT_CT);

    for (int i = 0; i < ELEMENT_CT; ++i) {
        if (i % (ELEMENT_CT / 100) == 0) {
            printf("Heap sort: %d%% complete.\n", i / (ELEMENT_CT / 100));
        }
        sorted_ints[i] = heap_pop(ints, ELEMENT_CT - i);
    }

    gettimeofday(&stop, NULL);
    unsigned long time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    printf("Heap sort: took %.3f seconds to sort %d elements.\n", time / 1000000.0f, ELEMENT_CT);

    printf("%s\n", "Heap sort: verifying ...");

    /* Check the order. */
    for (int i = 0; i < ELEMENT_CT; ++i) {
        if (sorted_ints[i] != i) {
            printf("Heap sort: failed at index %d.\n", i);
            return -1;
        }
    }

    printf("%s\n", "Heap sort: verified data.");

    free(ints);
    free(sorted_ints);
    return 0;
    
}
