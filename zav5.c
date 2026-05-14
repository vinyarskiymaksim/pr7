#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void list_dir_recursive(const char *base_path)
{
    char path[1024];
    struct dirent *entry;
    struct stat statbuf;
    DIR *dir = opendir(base_path);

    // Перевірка, чи вдалося відкрити каталог
    if (!dir)
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        // Ігноруємо посилання на поточний та батьківський каталоги
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Створюємо повний шлях до об'єкта
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

        // Отримуємо інформацію про об'єкт
        if (stat(path, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                // Якщо це каталог — виводимо назву та йдемо глибше
                printf("[DIR]  %s\n", path);
                list_dir_recursive(path);
            }
            else
            {
                // Якщо це файл — просто виводимо шлях
                printf("[FILE] %s\n", path);
            }
        }
    }

    closedir(dir);
}

int main()
{
    printf("Початок рекурсивного обходу поточного каталогу:\n");
    printf("----------------------------------------------\n");
    list_dir_recursive(".");
    return 0;
}