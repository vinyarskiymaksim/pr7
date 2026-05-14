#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define SECONDS_IN_7_DAYS (7 * 24 * 3600)
#define MAX_FILES 1000

typedef struct
{
    char path[1024];
    time_t mtime;
} FileInfo;

FileInfo changed_files[MAX_FILES];
int file_count = 0;

void analyze_directory(const char *base_path, time_t threshold)
{
    DIR *dir = opendir(base_path);
    if (!dir)
        return;

    struct dirent *entry;
    struct stat statbuf;
    char full_path[1024];

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);

        if (lstat(full_path, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                analyze_directory(full_path, threshold);
            }
            else if (S_ISREG(statbuf.st_mode))
            {
                // Перевіряємо, чи змінювався файл за останні 7 днів
                if (statbuf.st_mtime >= threshold)
                {
                    if (file_count < MAX_FILES)
                    {
                        strncpy(changed_files[file_count].path, full_path, 1024);
                        changed_files[file_count].mtime = statbuf.st_mtime;
                        file_count++;
                    }
                }
            }
        }
    }
    closedir(dir);
}

// Компаратор для сортування за часом (від новіших до старіших)
int compare_files(const void *a, const void *b)
{
    return ((FileInfo *)b)->mtime - ((FileInfo *)a)->mtime;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Використання: %s <директорія>\n", argv[0]);
        return 1;
    }

    time_t now = time(NULL);
    time_t threshold = now - SECONDS_IN_7_DAYS;

    printf("Аналіз файлів у '%s' за останні 7 днів...\n", argv[1]);

    analyze_directory(argv[1], threshold);

    // Сортуємо результати
    qsort(changed_files, file_count, sizeof(FileInfo), compare_files);

    printf("\nЗнайдено активних файлів: %d\n", file_count);
    printf("%-50s | %s", "Шлях до файлу", "Дата останньої зміни\n");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < file_count; i++)
    {
        char date[20];
        strftime(date, 20, "%Y-%m-%d %H:%M", localtime(&changed_files[i].mtime));
        printf("%-50s | %s\n", changed_files[i].path, date);
    }

    return 0;
}