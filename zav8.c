#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char response;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("Не вдалося відкрити каталог");
        return EXIT_FAILURE;
    }

    printf("УВАГА: Режим інтерактивного видалення файлів!\n");
    printf("-------------------------------------------\n");

    while ((entry = readdir(dir)) != NULL)
    {
        // Пропускаємо спеціальні посилання . та ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Отримуємо інформацію про файл, щоб переконатися, що це не каталог
        if (lstat(entry->d_name, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                // Пропускаємо директорії для безпеки
                continue;
            }

            printf("Видалити файл '%s'? (y/n): ", entry->d_name);

            // Отримуємо відповідь користувача
            if (scanf(" %c", &response) == 1)
            {
                if (response == 'y' || response == 'Y')
                {
                    if (unlink(entry->d_name) == 0)
                    {
                        printf("Файл '%s' видалено успішно.\n", entry->d_name);
                    }
                    else
                    {
                        perror("Помилка при видаленні");
                    }
                }
                else
                {
                    printf("Файл '%s' збережено.\n", entry->d_name);
                }
            }
        }
        printf("-------------------------------------------\n");
    }

    closedir(dir);
    printf("Обробку завершено.\n");
    return EXIT_SUCCESS;
}