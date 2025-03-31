#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define ENV_FILE "/usr/local/bin/supac/supac.env"
#define LIBS_DIR "/usr/local/bin/supac/libs"
#define BIN_DIR "/usr/local/bin/supac/bin"
#define PKG_MANAGER "bin/supac_pm"
#define LANG_MANAGER "bin/supac_langmang"

void print_version() {
    FILE *file = fopen(ENV_FILE, "r");
    if (!file) {
        perror("Error opening env file");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "LANGUAGE::VERSION=", 18) == 0) {
            printf("Version: %s", line + 18);
            break;
        }
    }
    fclose(file);
}

void print_is_beta() {
    FILE *file = fopen(ENV_FILE, "r");
    if (!file) {
        perror("Error opening env file");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "LANGUAGE::IS_BETA=", 19) == 0) {
            printf("Beta Status: %s", line + 19);
            break;
        }
    }
    fclose(file);
}

void list_libs() {
    DIR *dir = opendir(LIBS_DIR);
    if (!dir) {
        perror("Error opening libs directory");
        return;
    }
    struct dirent *entry;
    printf("Libraries in %s:\n", LIBS_DIR);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.')
            printf("  %s\n", entry->d_name);
    }
    closedir(dir);
}

void print_env() {
    FILE *file = fopen(ENV_FILE, "r");
    if (!file) {
        perror("Error opening env file");
        return;
    }
    char line[256];
    printf("Environment Variables:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("  %s", line);
    }
    fclose(file);
}

void set_env_var(const char *key, const char *value) {
    FILE *file = fopen(ENV_FILE, "a");
    if (!file) {
        perror("Error opening env file");
        return;
    }
    fprintf(file, "%s=%s\n", key, value);
    fclose(file);
    printf("Set %s to %s\n", key, value);
}

void print_path(const char *path) {
    printf("%s\n", path);
}

void print_help() {
    printf("Usage: supac <command>\n");
    printf("Available commands:\n");
    printf("  --version     Show language version\n");
    printf("  --is_beta     Show if language is in beta\n");
    printf("  --llibs       List libraries\n");
    printf("  env           Show environment variables\n");
    printf("  env set <key> <value>  Set an environment variable\n");
    printf("  --plibs       Print path of libraries\n");
    printf("  --plang       Print path of language bin\n");
    printf("  --ppm         Print path of package manager\n");
    printf("  --help        Show this help message\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        print_version();
    } else if (strcmp(argv[1], "--is_beta") == 0) {
        print_is_beta();
    } else if (strcmp(argv[1], "--llibs") == 0) {
        list_libs();
    } else if (strcmp(argv[1], "env") == 0) {
        if (argc == 2) {
            print_env();
        } else if (argc == 4 && strcmp(argv[2], "set") == 0) {
            set_env_var(argv[3], argv[4]);
        } else {
            printf("Invalid env command\n");
        }
    } else if (strcmp(argv[1], "--plibs") == 0) {
        print_path(LIBS_DIR);
    } else if (strcmp(argv[1], "--plang") == 0) {
        print_path(BIN_DIR);
    } else if (strcmp(argv[1], "--ppm") == 0) {
        print_path(PKG_MANAGER);
    } else if (strcmp(argv[1], "--help") == 0) {
        print_help();
    } else {
        printf("Unknown command: %s\n", argv[1]);
        print_help();
    }

    return 0;
}
