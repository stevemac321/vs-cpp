#pragma once

template <typename DataType>
concept Numeric = std::is_arithmetic_v<DataType>;

template <Numeric DataType>
void merge(DataType A[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    DataType* pL = new DataType[n1 + 1]; // Allocate n1+1 for sentinel
    DataType* pR = new DataType[n2 + 1]; // Allocate n2+1 for sentinel
    if (!pL || !pR) {
        std::perror("allocation failed");
        return;
    }

    // copy A into the new subarrays
    for (int i = 0; i < n1; i++) {
        pL[i] = A[p + i];
    }
    for (int j = 0; j < n2; j++) {
        pR[j] = A[q + 1 + j];
    }
    // set the 'sentinels'
    pL[n1] = '\0';
    pR[n2] = '\0';

    int i = 0;  // index for pL
    int j = 0;  // index for pR
    // copy allocated subarrays back into A
    for (int k = p; k <= r; k++) {
        if (pL[i] <= pR[j]) {
            A[k] = pL[i];
            i++;
            if (i == n1) { // pL is exhausted, copy remaining pR
                while (k + 1 <= r) {
                    k++;
                    A[k] = pR[j];
                    j++;
                }
                break;
            }
        }
        else {
            A[k] = pR[j];
            j++;
            if (j == n2) { // pR is exhausted, copy remaining pL
                while (k + 1 <= r) {
                    k++;
                    A[k] = pL[i];
                    i++;
                }
                break;
            }
        }
    }

    delete[] pL;
    delete[] pR;
}
template <Numeric DataType>
void merge_sort(DataType A[], int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}
////////////////////////////////////////////////////
void test_merge_sort()
{
    TEST_BEGIN("test_merge_sort 1")
   int a[] = {55,33,88,11,77,66,0,99};
   int b[] = {0,11,33,55,66,77,88,99};
    merge_sort(a, 0, __countof(a) -1);
    ASSERT_ITER_EQ(std::begin(a), std::end(a), std::begin(b), std::end(b)); 
    TEST_END("test_merge_sort 1")
}