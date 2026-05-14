#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_permissions(mode_t mode)
{
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main()
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    struct passwd *pw;
    struct group *gr;
    char date[20];

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("Не вдалося відкрити каталог");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // Пропускаємо приховані файли для чистоти виводу (опціонально)
        if (entry->d_name[0] == '.')
            continue;

        if (stat(entry->d_name, &file_stat) == 0)
        {
            // 1. Права доступу
            print_permissions(file_stat.st_mode);

            // 2. Кількість посилань
            printf(" %2ld", (long)file_stat.st_nlink);

            // 3. Власник та група
            pw = getpwuid(file_stat.st_uid);
            gr = getgrgid(file_stat.st_gid);
            printf(" %-8s %-8s", pw->pw_name, gr->gr_name);

            // 4. Розмір файлу
            printf(" %8lld", (long long)file_stat.st_size);

            // 5. Час останньої модифікації
            strftime(date, 20, "%b %d %H:%M", localtime(&file_stat.st_mtime));
            printf(" %s", date);

            // 6. Ім'я файлу
            printf(" %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}