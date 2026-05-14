#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 20

void do_more(FILE *fp)
{
    char buffer[1024];
    int line_count = 0;

    // Читаємо файл порядно
    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (line_count == PAGE_SIZE)
        {
            // Виводимо підказку та чекаємо на ввід
            printf("\033[7m -- More -- \033[m"); // Інвертований колір для тексту

            // Очікуємо натискання Enter
            // Ми використовуємо getchar() з stdin, оскільки файл читається окремо
            int c = getchar();
            if (c == 'q' || c == 'Q')
                exit(0); // Можливість виходу

            line_count = 0; // Скидаємо лічильник
            // Очищення рядка "-- More --" (опціонально для краси)
            printf("\r            \r");
        }

        if (fputs(buffer, stdout) == EOF)
            exit(1);
        line_count++;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Використання: %s <файл1> [файл2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Обробка кожного файлу, переданого в аргументах
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp != NULL)
        {
            do_more(fp);
            fclose(fp);
        }
        else
        {
            perror(argv[i]);
            exit(1);
        }
    }

    return EXIT_SUCCESS;
}