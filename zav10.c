#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    double n;
    int count = 5; // Кількість чисел для генерації

    // 1. Встановлюємо початкове значення для унікальної послідовності
    srand((unsigned int)time(NULL));

    printf("Введіть максимальне значення n: ");
    if (scanf("%lf", &n) != 1)
    {
        fprintf(stderr, "Помилка вводу\n");
        return EXIT_FAILURE;
    }

    printf("\n(a) Випадкові числа від 0.0 до 1.0:\n");
    for (int i = 0; i < count; i++)
    {
        // Нормалізація до [0.0, 1.0]
        double r1 = (double)rand() / (double)RAND_MAX;
        printf("%f\n", r1);
    }

    printf("\n(b) Випадкові числа від 0.0 до %.2f:\n", n);
    for (int i = 0; i < count; i++)
    {
        // Масштабування до [0.0, n]
        double rn = ((double)rand() / (double)RAND_MAX) * n;
        printf("%f\n", rn);
    }

    return EXIT_SUCCESS;
}