#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main()
{
    FILE *in_pipe, *out_pipe;
    char buffer[BUFFER_SIZE];

    // 1. Відкриваємо rwho для читання виводу
    in_pipe = popen("rwho", "r");
    if (!in_pipe)
    {
        perror("Помилка при відкритті rwho");
        return EXIT_FAILURE;
    }

    // 2. Відкриваємо more для запису даних у його stdin
    out_pipe = popen("more", "w");
    if (!out_pipe)
    {
        perror("Помилка при відкритті more");
        pclose(in_pipe);
        return EXIT_FAILURE;
    }

    // 3. Читаємо дані з rwho і перенаправляємо їх у more
    while (fgets(buffer, BUFFER_SIZE, in_pipe) != NULL)
    {
        fputs(buffer, out_pipe);
    }

    // 4. Закриваємо потоки
    pclose(in_pipe);
    pclose(out_pipe);

    return EXIT_SUCCESS;
}