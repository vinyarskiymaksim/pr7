#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Функція для перевірки, чи є файл вихідним кодом C
int is_c_file(const char *name)
{
    const char *ext = strrchr(name, '.');
    return (ext && strcmp(ext, ".c") == 0);
}

int main()
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char response;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("Не вдалося відкрити каталог");
        return EXIT_FAILURE;
    }

    printf("Аналіз вихідних кодів C у поточному каталозі...\n\n");

    while ((entry = readdir(dir)) != NULL)
    {
        if (is_c_file(entry->d_name))
        {
            printf("Файл: %s\n", entry->d_name);
            printf("Надати іншим користувачам дозвіл на читання? (y/n): ");

            scanf(" %c", &response); // Пробіл перед %c ігнорує символи переходу на новий рядок

            if (response == 'y' || response == 'Y')
            {
                // Отримуємо поточні права файлу
                if (stat(entry->d_name, &file_stat) == 0)
                {
                    // Додаємо біт S_IROTH (Read by Others) до існуючих прав
                    mode_t new_mode = file_stat.st_mode | S_IROTH;

                    if (chmod(entry->d_name, new_mode) == 0)
                    {
                        printf("Успішно: Права оновлено для %s\n", entry->d_name);
                    }
                    else
                    {
                        perror("Помилка при зміні прав");
                    }
                }
            }
            else
            {
                printf("Пропущено: %s залишився без змін.\n", entry->d_name);
            }
            printf("-----------------------------------\n");
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}