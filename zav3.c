#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[])
{
    // 1. Перевірка аргументів: програма, слово, файл
    if (argc < 3)
    {
        fprintf(stderr, "Використання: %s <слово> <файл>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *search_word = argv[1];
    char *filename = argv[2];
    char line[MAX_LINE_LENGTH];

    // 2. Відкриття файлу для читання
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Помилка відкриття файлу");
        return EXIT_FAILURE;
    }

    // 3. Порядкове зчитування та пошук
    int line_number = 0;
    while (fgets(line, sizeof(line), file))
    {
        line_number++;
        // Перевіряємо, чи є шукане слово у зчитаному рядку
        if (strstr(line, search_word) != NULL)
        {
            printf("%d: %s", line_number, line);
        }
    }

    // 4. Очищення ресурсів
    fclose(file);
    return EXIT_SUCCESS;
}