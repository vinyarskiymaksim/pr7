#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// Функція-фільтр: вибирає лише каталоги, ігноруючи "." та ".."
int directory_filter(const struct dirent *entry)
{
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
    {
        return 0;
    }
    // DT_DIR означає Directory. Працює на більшості сучасних ФС Linux.
    return (entry->d_type == DT_DIR);
}

int main()
{
    struct dirent **namelist;
    int n;

    // scandir(шлях, масив_результатів, фільтр, компаратор)
    n = scandir(".", &namelist, directory_filter, alphasort);

    if (n < 0)
    {
        perror("Помилка scandir");
        return EXIT_FAILURE;
    }
    else
    {
        printf("Знайдено підкаталогів: %d\n", n);
        printf("---------------------------\n");
        for (int i = 0; i < n; i++)
        {
            printf("[DIR] %s\n", namelist[i]->d_name);
            free(namelist[i]); // Звільняємо кожен елемент
        }
        free(namelist); // Звільняємо сам масив
    }

    return EXIT_SUCCESS;
}