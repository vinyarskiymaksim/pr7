#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    struct timespec start, end;

    // 1. Фіксуємо час початку
    clock_gettime(CLOCK_MONOTONIC, &start);

    // --- Фрагмент коду для вимірювання (приклад: імітація роботи) ---
    printf("Виконання фрагмента коду...\n");
    for (long i = 0; i < 100000000; i++)
    {
        // Просто імітуємо навантаження на процесор
    }
    usleep(500000); // Додаткова затримка на 500 мс
    // --------------------------------------------------------------

    // 2. Фіксуємо час завершення
    clock_gettime(CLOCK_MONOTONIC, &end);

    // 3. Обчислення різниці в мілісекундах
    // Формула: (sec * 1000) + (nsec / 1,000,000)
    double elapsed_ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                        (end.tv_nsec - start.tv_nsec) / 1000000.0;

    printf("Час виконання: %.3f мс\n", elapsed_ms);

    return 0;
}