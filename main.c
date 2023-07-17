#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int number1 = m - l + 1;
    int number2 = r - m;
    int left[number1], right[number2];
    for (i = 0; i < number1; i++)
        left[i] = arr[l + i];
    for (j = 0; j < number2; j++)
        right[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < number1 && j < number2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }else {
            arr[k] = right[j];
            j++;
        }k++;
    }while (i < number1) {
        arr[k] = left[i];
        i++;
        k++;
    }while (j < number2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}



void mergeSort(int pData[], int l, int r)
{if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
        merge(pData, l, m, r);
    }
}


int parseData(char* inputFileName, int** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n, *data;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (int*)malloc(sizeof(int) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }for (i = 0; i < dataSz; ++i) {
            fscanf(inFile, "%d ", &n);
            data = *ppData + i;
            *data = n;
        }fclose(inFile);
    }return dataSz;
}


void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");

    for (i = 0; i < 100 && i < dataSz; ++i) {
        printf("%d ", pData[i]);
    }

    printf("\n\t");

    if (dataSz > 100) {
        for (i = sz; i < dataSz; ++i) {
            printf("%d ", pData[i]);
        }
    }

    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = { "C:\\Users\\blueg\\CLionProjects\\lab8\\input1.txt", "C:\\Users\\blueg\\CLionProjects\\lab8\\input2.txt", "C:\\Users\\blueg\\CLionProjects\\lab8\\input3.txt", "C:\\Users\\blueg\\CLionProjects\\lab8\\input4.txt" };

    for (i=0;i<4;++i)
    {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0)
            continue;

        pDataCopy = (int *)malloc(sizeof(int)*dataSz);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n",dataSz);
        printf("---------------------------\n");

        printf("Heap Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        heapSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }
    return 0;
}