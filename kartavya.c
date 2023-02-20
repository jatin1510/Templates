#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size[3] = {3, 2, 5};
    int *arr[3];
    for (int i = 0; i < 3; i++)
    {
        int sz = size[i];
        arr[i] = (int *)calloc(sz, sz * sizeof(int));
        for (int j = 0; j < sz; j++)
            scanf("%d", &arr[i][j]);
    }

    int search;
    scanf("%d", &search);

    for (int i = 0; i < 3; i++)
    {
        int sz = size[i];
        for (int j = 0; j < sz; j++)
        {
            if (arr[i][j] == search)
            {
                printf("yes\n");
                return 0;
            }
        }
    }
    printf("no\n");

    return 0;
}