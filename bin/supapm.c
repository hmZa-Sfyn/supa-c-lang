#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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

void create_project(const char *name) {
    char path[512];
    snprintf(path, sizeof(path), "%s/%s", getenv("PWD"), name);
    mkdir(path, 0755);
    
    char config_path[512];
    snprintf(config_path, sizeof(config_path), "%s/config.txt", path);
    FILE *config = fopen(config_path, "w");
    if (config) {
        fprintf(config, "Project: %s\n", name);
        fclose(config);
    }
    
    char lock_path[512];
    snprintf(lock_path, sizeof(lock_path), "%s/lock.txt", path);
    FILE *lock = fopen(lock_path, "w");
    if (lock) {
        fprintf(lock, "Locked\n");
        fclose(lock);
    }
    
    printf("Project '%s' created successfully.\n", name);
}

void remove_project(const char *name) {
    char path[512];
    snprintf(path, sizeof(path), "%s/%s", getenv("PWD"), name);
    char command[512];
    snprintf(command, sizeof(command), "rm -rf %s", path);
    system(command);
    printf("Project '%s' removed successfully.\n", name);
}

void upload_local(const char *name) {
    char path[512];
    snprintf(path, sizeof(path), "%s/%s", getenv("PWD"), name);
    char dest[512];
    snprintf(dest, sizeof(dest), "%s/%s", LIBS_DIR, name);
    char command[512];
    snprintf(command, sizeof(command), "mv %s %s", path, dest);
    system(command);
    printf("Project '%s' uploaded locally.\n", name);
}

void unupload_local(const char *name) {
    char path[512];
    snprintf(path, sizeof(path), "%s/%s", LIBS_DIR, name);
    char dest[512];
    snprintf(dest, sizeof(dest), "%s/%s", getenv("PWD"), name);
    char command[512];
    snprintf(command, sizeof(command), "mv %s %s", path, dest);
    system(command);
    printf("Project '%s' unuploaded locally.\n", name);
}

void print_help() {
    printf("Usage: supac <command> [arguments]\n");
    printf("Available commands:\n");
    printf("  --version        Show language version\n");
    printf("  --is_beta        Show if language is in beta\n");
    printf("  --llibs          List libraries\n");
    printf("  env              Show environment variables\n");
    printf("  env set <key> <value>  Set an environment variable\n");
    printf("  --plibs          Print path of libraries\n");
    printf("  --plang          Print path of language bin\n");
    printf("  --ppm            Print path of package manager\n");
    printf("  create <name>    Create a new project\n");
    printf("  remove <name>    Remove a project\n");
    printf("  upload_local <name> Move project to local libs\n");
    printf("  unupload_local <name> Remove project from local libs\n");
    printf("  --help           Show this help message\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "create") == 0 && argc == 3) {
        create_project(argv[2]);
    } else if (strcmp(argv[1], "remove") == 0 && argc == 3) {
        remove_project(argv[2]);
    } else if (strcmp(argv[1], "upload_local") == 0 && argc == 3) {
        upload_local(argv[2]);
    } else if (strcmp(argv[1], "unupload_local") == 0 && argc == 3) {
        unupload_local(argv[2]);
    } else {
        printf("Unknown command: %s\n", argv[1]);
        print_help();
    }

    return 0;
}
