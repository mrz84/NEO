#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <time.h>
#include <stddef.h>
#include <ctype.h>



#define  MAX_SIZE_ADDRESS  1000
#define  BEING_STAGED 1

char all_orders_name[50][100] = {
        "<init>",
        "<add -d>",
        "<reset>",
        "<reset -d>",
        "<reset -undo>",
        "<status>"

};
int order_number = 20;

struct br {
    int id;
    int num_commit;
    char name[MAX_SIZE_ADDRESS];
    int last;
};
typedef struct br br;

// main functions

char *find_dir (char *name, char *path);
int add_to_stage (char* filepath, char* dir_address);

int file_exists (char *dir, char *file);
void wildcard_fun (char *wildcard, char *directory, int (doing)(char*, char*));

void do_directory_files (char *directory, int (*doing)(char *f, char *d));
void delete_name_from_file (char *name, char *filename);

int remove_from_stage (char* filepath, char* dir_address);
int creat_configuration (char* email, char* username, char* bench, char* now);//this function need a chang

int add_file_to_stage_area (char* dir_address_area, char* file_name, char * address_dir);
void delete_file_from_directory (char *directory, char* name);

int for_status_is_not_negative (char* f1, char* f2);
int comparing_tow_files_with_address (char* ad1, char* ad2);

int add_alias_in_file (int code, char* name_of_alias);

void str_num (char* str, int num);

void copy_and_rename_dir_for_commit (char *name, char *path);
int counting_number_files_commit ();
void make_file_and_edit_for_commit (char* address, char* massage);
void write_in_id (int id);
int chang_config (int branch, int new_num_of_commit, char* name_of_branch);
int chang_num_of_commits (int new_num_of_commit, int branch_num);

int make_new_branch (int zero, char* name, int last_com);

int log_print (int id);
br branch_name_to_data (char* name, int id);
int compare_first_line_wild(char *file_name, char *word);

int write_in_date (int id);
int compare_first_line(char *file_name, char *word);

bool checking_stage ();
int checkout_recursive (int id);

//int move_files(char *src_dir, char *dest_dir);

int checkout_recursive_for_revert (int id, int id_of_ignore, char* address1);
void copy_and_rename_dir_for_revert (char *name, char *path);

int diff(char *file11, char *file22, int start1, int end1, int start2, int end2, char* name1, char* name2);
char** list_files(char* dir);
int contains(char* str, char** arr);
void print_files(char* dir1, char* dir2);

int checkout_recursive_for_merge (int id, int num);
void add_files_for_merge(char* dir1, char* dir2, char* address);

void print_file_content(const char *directory_path, const char *file_name);

// orders

int config_name_ord (int argc, char* argv[]);
int config_email_ord (int argc, char* argv[]);
char* global_config_email (int argc, char* argv[]);
char* global_config_name (int argc, char* argv[]);


int init_ord (int argc, char * const  argv[]);

int add_ord (int argc, char* argv[]);

int reset_ord (int argc, char* argv[]);

int status_ord (int argc);

int alias_order (int argc, char** argv);

int commit_ord (int argc, char* argv[]);
int set_ord (int argc, char* argv[]);
int replace_ord (int argc, char* argv[]);
int remove_ord (int argc, char* argv[]);

int branch_ord(int argc, char* argv[]);
int branch_print_ord (int argc, char* argv[]);

int log_main_ord (int argc, char* argv[]);
int log_branch (int argc, char* argv[]);
int log_name (int argc, char* argv[]);
int log_date (int argc, char* argv[]);
int log_search (int argc, char* argv[]);
int log_search_wild (int argc, char* argv[]);

int checkout_ord (int argc, char* argv[]);

int revert_ord (int argc, char* argv[]);
int revert_n_ord (int argc, char* argv[]);
int revert_H_ord (int argc, char* argv[]);

int diff_ord (int argc, char* argv[]);
int diff_c_ord (int argc, char* argv[]);

int merge_ord (int argc, char* argv[]);

int tag_ord (int argc, char* argv[]);

int pre (int argc, char* argv[]);

int stash (int argc, char* argv[]);
// ######################################  MAIN  ###################################

int main(int argc, char* argv[]) {
    printf("!!!!\n");
    if (argc < 2) {
        perror ("invalid inputs, please write arguments\n");
        return 1;
    }

    if (!strcmp(argv[1], "config") && argc == 4 && !strcmp(argv[2], "user.name"))
        config_name_ord (argc, argv);

    if (!strcmp(argv[1], "config") && argc == 4 && !strcmp(argv[2], "user.email"))
        config_email_ord (argc, argv);

    if (!strcmp(argv[1], "config") && argc == 5 && !strcmp(argv[3], "user.name"))
        global_config_name (argc, argv);

    if (!strcmp(argv[1], "config") && argc == 5 && !strcmp(argv[3], "user.email"))
        global_config_email (argc, argv);




    if (!strcmp(argv[1], "init"))
        init_ord (argc, argv);

    else if (!strcmp(argv[1], "add")) {
        add_ord (argc, argv);
        char stage_path[MAX_SIZE_ADDRESS];
        if (find_dir("NEO", "/Users") == NULL) {
            perror("error in finding NEO\n");
            return 1;
        }

        strcpy(stage_path, find_dir("NEO", "/Users"));
        strcat(stage_path, "/lastadd.txt");
        FILE* file_stage_last = fopen(stage_path, "w");
        if (file_stage_last == NULL) {
            perror("error in opening stage file.\n");
            return 1;
        }

        fprintf(file_stage_last, "%d ", argc);
        for (int i = 0; i < argc; i++) {
            fprintf(file_stage_last,"%s ", argv[i]);
        }
        fclose(file_stage_last);
    }

    else if (!strcmp(argv[1], "reset") && strcmp(argv[2], "-undo")){
        reset_ord(argc, argv);
    }
    else if (!strcmp(argv[1], "reset") && !strcmp(argv[2], "-undo")){
        char stage_path[MAX_SIZE_ADDRESS];
        if (find_dir("NEO", "/Users") == NULL) {
            perror("error in finding NEO\n");
            return 1;
        }
        strcpy(stage_path, find_dir("NEO", "/Users"));
        strcat(stage_path, "/lastadd.txt");
        FILE* file_stage_last = fopen(stage_path, "r");
        if (file_stage_last == NULL) {
            perror("error in opening stage file.\n");
            return 1;
        }

        char** last_argv = (char**) malloc(20 * sizeof (char*));
        for (int i = 0; i < 20; i++) {
            last_argv[i] = (char*) calloc(50, 1);
        }

        int last_argc;
        fscanf(file_stage_last, "%d ", &last_argc);

        for (int i = 0; i < last_argc; i++) {
            if (1 != i) {
                fscanf(file_stage_last,"%s", last_argv[i]);

            } else {
                fscanf(file_stage_last,"%s", last_argv[i]);
                strcpy(last_argv[1],"reset");
            }
        }

        fclose(file_stage_last);
        main(last_argc, (char **) last_argv);
        for (int i = 0; i < 20; i++) {
            free(last_argv[i]);
        }
        free(last_argv);
    }

    else if (!strcmp(argv[1], "status"))
        status_ord(argc);

    else if (!strcmp(argv[1], "config") && !strcmp(argv[2], "alias"))
        alias_order(argc, argv);

    else if (!strcmp(argv[1], "commit") )
        commit_ord( argc, argv);

    else if (!strcmp(argv[1], "set") && !strcmp(argv[1], "set"))
        set_ord(argc, argv);

    else if (!strcmp(argv[1], "replace"))
        replace_ord(argc, argv);

    else if (!strcmp(argv[1], "remove"))
        remove_ord(argc, argv);

    else if (!strcmp(argv[1], "branch") && argc == 3)
        branch_ord(argc, argv);

    else if (!strcmp(argv[1], "branch") && argc == 2)
        branch_print_ord(argc, argv);
    // ***************************************** log ************************************
    else if (!strcmp(argv[1], "log") && argc == 2)
        log_main_ord (argc, argv);

    else if (!strcmp(argv[1], "log") && !strcmp(argv[2], "-n"))
        log_main_ord (argc, argv);

    else if (!strcmp(argv[1], "log") && !strcmp(argv[2], "-branch"))
        log_branch (argc, argv);

    else if (!strcmp(argv[1], "log") && !strcmp(argv[2], "author"))
        log_name (argc, argv);

    else if (!strcmp(argv[1], "log") && (!strcmp(argv[2], "-since") || !strcmp(argv[2], "-before")))
        log_date (argc, argv);

    else if (!strcmp(argv[1], "log") && !strcmp(argv[2], "-search"))
        log_search (argc, argv);

    else if (!strcmp(argv[1], "log") && !strcmp(argv[2], "-searchw"))
        log_search_wild (argc, argv);
    // **********************************************************************************
    else if (!strcmp(argv[1], "checkout"))
        checkout_ord (argc, argv);

    else if (!strcmp(argv[1], "revert") && argc == 6)
        revert_H_ord (argc, argv);

    else if (!strcmp(argv[1], "revert") && argc == 5)
        revert_ord ( argc, argv);

    else if (!strcmp(argv[1], "revert") && argc == 4)
        revert_n_ord (argc, argv);

    else if (!strcmp(argv[1], "diff") && !strcmp(argv[2], "-f"))
        diff_ord (argc, argv);

    else if (!strcmp(argv[1], "diff") && !strcmp(argv[1], "-c"))
        diff_c_ord (argc, argv);

    else if (!strcmp(argv[1], "tag"))
        tag_ord (argc, argv);

    else if (!strcmp(argv[1], "stash"))
        tag_ord (argc, argv);

    else if (!strcmp(argv[1], "pre-commit"))
        tag_ord (argc, argv);

    else {
        char order[MAX_SIZE_ADDRESS];
        sprintf(order, "%s", argv[1]);
        system(order);
    }

    system("set -f");
    return 0;
}


// ######################################  orders  ###################################

//////

int config_name_ord (int argc, char* argv[]) {

    char address_of_main[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/name.txt");
    FILE* file = fopen(address_of_main, "w");
    fprintf(file, "%s\n", argv[4]);

    return 0;
}
int config_email_ord (int argc, char* argv[]) {

    char address_of_main[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/email.txt");
    FILE* file = fopen(address_of_main, "w");
    fprintf(file, "%s\n", argv[4]);

    return 0;
}

char* global_config_email (int argc, char* argv[]) {
    DIR *dir;
    struct dirent *entry;
    char *result = NULL;
    char new_path[256];

    dir = opendir("/Users/");
    if (dir == NULL) {
        perror("opendir() error");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (strcmp(entry->d_name, "NEO") == 0) {

            result = (char *)calloc(MAX_SIZE_ADDRESS, 1);
            if (result == NULL)
            {
                perror("calloc() error\n");
                closedir(dir);
                return NULL;
            }
            getcwd(result, 1000);
            strcat(result, "/");
            strcat(result, "NEO");
            closedir(dir);
            strcat(result, "/email.txt");
            FILE* file = fopen(result, "w");
            fprintf(file, "%s\n", argv[4]);

            fclose(file);
        }

        if (entry->d_type == DT_DIR) {
            getcwd(new_path, 1000);
            strcat(new_path, "/");
            strcat(new_path, entry->d_name);
            result = find_dir("NEO", new_path);
            if (result != NULL)
            {
                closedir(dir);
                return result;
            }
        }
    }

    closedir(dir);
    return NULL;
}

char* global_config_name (int argc, char* argv[]) {
    DIR *dir;
    struct dirent *entry;
    char *result = NULL;
    char new_path[256];

    dir = opendir("/Users/");
    if (dir == NULL) {
        perror("opendir() error");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (strcmp(entry->d_name, "NEO") == 0) {

            result = (char *)calloc(MAX_SIZE_ADDRESS, 1);
            if (result == NULL)
            {
                perror("calloc() error\n");
                closedir(dir);
                return NULL;
            }
            getcwd(result, 1000);
            strcat(result, "/");
            strcat(result, "NEO");
            closedir(dir);
            strcat(result, "/name.txt");
            FILE* file = fopen(result, "w");
            fprintf(file, "%s\n", argv[4]);

            fclose(file);
        }

        if (entry->d_type == DT_DIR) {
            getcwd(new_path, 1000);
            strcat(new_path, "/");
            strcat(new_path, entry->d_name);
            result = find_dir("NEO", new_path);
            if (result != NULL)
            {
                closedir(dir);
                return result;
            }
        }
    }

    closedir(dir);
    return NULL;
}


int init_ord (int argc, char * const  argv[]) {
    char cwd [MAX_SIZE_ADDRESS] = {0};
    char tmp_dir[MAX_SIZE_ADDRESS] = {0};
    char now_address[MAX_SIZE_ADDRESS];
    getcwd(now_address, 1000);

    if (getcwd(cwd, sizeof(cwd)) == NULL){
        perror("error in getcwd()\n");
        return 1;
    }
    bool exist = false;
    struct dirent * ent;
    if (strcmp(tmp_dir, "/"))
        if (chdir("..") != 0) {
            perror("error in changing directory\n");
            return 1;
        }

    do {
        DIR* dir = opendir(".");
        if (dir == NULL) {
            perror("error in opening dir\n");
            return 1;
        }
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && !strcmp(ent->d_name, "NEO")) {
                exist = true;
            }
        }

        if (getcwd(tmp_dir, sizeof (tmp_dir)) == NULL){
            perror("error in getcwd.()\n");
            return 1;
        }

        if (strcmp(tmp_dir, "/"))
            if (chdir("..") != 0){
                perror("error in changing directory\n");
                return 1;
            }

    } while (strcmp(tmp_dir, "/") && exist == false);

    if (exist){
        printf("the repository is already existed\n");
    } else {
        chdir(now_address);

        if (mkdir("../NEO", 0700) != 0 ) {

            perror("error in making repository\n");
            printf("error is: %d\n", errno);
            return 1;
        } else {
            creat_configuration("U", "E", "master", now_address);
        }
    }
    return 0;
}

//////

int add_ord (int argc, char* argv[]) {
    if (argc < 3) {
        printf ("invalid argument\n");
        return 1;
    }
    char now_address[MAX_SIZE_ADDRESS];
    getcwd(now_address, MAX_SIZE_ADDRESS);

    if (strcmp(argv[2], "-d") != 0) {
        if (strchr(argv[2], '*') == NULL) {
            if (add_to_stage(argv[2], now_address)) return 1;
        }
        else {
            wildcard_fun(argv[2], now_address, add_to_stage);
        }
        return 0;

    } else {
        for (int i = 3; i < argc; i++) {
            if (strchr(argv[i], '.') == NULL) {
                char now_address1[MAX_SIZE_ADDRESS];
                strcpy(now_address1, now_address);
                strcat(now_address1, "/");
                strcat(now_address1, argv[i]);
                do_directory_files(now_address1, add_to_stage);


            } else {
                add_to_stage(argv[i], now_address);
            }
        }
        return 0;
    }
}

//////

int reset_ord (int argc, char* argv[]) {
    if (argc < 3) {
        printf ("invalid argument\n");
        return 1;
    }
    char now_address[MAX_SIZE_ADDRESS];
    getcwd(now_address, MAX_SIZE_ADDRESS);

    if (strcmp(argv[2], "-d") != 0) {

        if (strchr(argv[2], '*') == NULL) {
            if (remove_from_stage(argv[2], now_address)) return 1;
        }
        else{
            wildcard_fun(argv[2], now_address, remove_from_stage);
        }

        return 0;

    } else {
        for (int i = 3; i < argc; i++) { ;
            if (strchr(argv[i], '.') == NULL) {
                char now_address_1[MAX_SIZE_ADDRESS];
                strcpy(now_address_1, now_address);
                strcat(now_address_1, "/");
                strcat(now_address_1, argv[i]);

                do_directory_files(now_address_1, remove_from_stage);

            } else {
                remove_from_stage(argv[i], now_address);
            }
        }
        return 0;
    }
}

//////

int status_ord (int argc) {

    if (argc > 2) {
        printf("invalid command\n");
    }

    char now_address [MAX_SIZE_ADDRESS];
    getcwd(now_address, MAX_SIZE_ADDRESS);

    DIR *dir;
    struct dirent *entry;

    dir = opendir(now_address);
    if (dir == NULL) {
        perror("Unable to open directory\n");
        exit(1);
    }

    bool exist = false;
    while ((entry = readdir(dir)) != NULL) {

        if (strstr(entry->d_name, ".txt") != NULL) {


            if (find_dir("NEO", "/Users") == NULL) {
                perror("error in finding NEO\n");
                return 1;
            }
            char stage_path[MAX_SIZE_ADDRESS] = {0};
            strcpy(stage_path, find_dir("NEO", "/Users"));
            strcat(stage_path, "/stage.txt");

            FILE* file_stage = fopen(stage_path, "r");
            if (file_stage == NULL) {
                perror("error in opening stage file.\n");
                return 1;
            }

            int positive_or_not = 0;
            bool being_in_stage = false;
            char file_s_path[MAX_SIZE_ADDRESS] = {0};
            while (fgets(file_s_path, MAX_SIZE_ADDRESS, file_stage) != NULL) {
                file_s_path[strlen(file_s_path) - 1] = '\0';

                if (!strcmp(file_s_path, entry->d_name)) {
                    being_in_stage = true;
                    positive_or_not = for_status_is_not_negative (entry->d_name, now_address);
                    break;
                }
            }

            if (being_in_stage == false) {
                printf("%s -?\n", entry->d_name);
            } else if (being_in_stage == true && positive_or_not == 1) {
                printf("%s +?\n", entry->d_name);
            }
        }
    }

    closedir(dir);

    return 0;
}

//////

int alias_order (int argc, char* argv[]) {
    char order[MAX_SIZE_ADDRESS];
    sprintf(order, "alias %s='%s'", argv[3], argv[4]);
    system(order);
    return 0;
}

//////

int commit_ord (int argc, char* argv[]) {
    if (argc > 4) {
        perror("invalid command\n");
        return 0;
    }
    if (strlen(argv[3]) > 72) {
        perror("please write a massage with at last 72 character\n");
        return 0;
    }
    if (argc < 4) {
        perror("please write a massage\n");
        return 0;
    }

    char address_of_main[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/config.txt");
    FILE* file = fopen(address_of_main, "r");
    char data[MAX_SIZE_ADDRESS];
    fgets(data, MAX_SIZE_ADDRESS, file);
    fclose(file);

    int branch_id;
    int num_of_commits;
    char a[1000];
    sscanf(data, "%d %d %s", &branch_id, &num_of_commits,a);

    char* address_copy = (char*) calloc(MAX_SIZE_ADDRESS, 1);
    strcpy(address_copy, find_dir("NEO", "/Users"));
    strcat(address_copy, "/all/");

    str_num(address_copy, branch_id);

    strcat(address_copy, "/");
    char name[MAX_SIZE_ADDRESS];
    str_num(name, num_of_commits+1);
    copy_and_rename_dir_for_commit (name, address_copy);

    str_num(address_copy, num_of_commits+1);
    strcat(address_copy, ".txt");

    if (!strcmp(argv[2], "-s")) {

        char stage_path[MAX_SIZE_ADDRESS];
        char p1[MAX_SIZE_ADDRESS];
        char p2[MAX_SIZE_ADDRESS];
        strcpy(stage_path, find_dir("NEO", "/Users"));
        strcat(stage_path, "/shortcom.txt");
        FILE* files = fopen (stage_path, "r");

        bool exist = false;
        while (fscanf(files, "%s", p1) != 0) {
            fgets(p2, MAX_SIZE_ADDRESS, files);
            if (!strcmp(p1, argv[3])) {
                exist = true;
                break;
            }
        }
        p2[strlen(p2) - 1] = 0;

        if (exist == false) {
            printf("there is no any shortcut whit this name\n");
            return 0;
        }

        fclose(files);
        make_file_and_edit_for_commit(address_copy, p2);
    }
    else
        make_file_and_edit_for_commit(address_copy, argv[3]);

    int id = (num_of_commits+1) + (branch_id*100);
    write_in_id(id);
    write_in_date(id);
    
    chang_num_of_commits (num_of_commits+1, branch_id);
    chang_config (-1, num_of_commits+1, NULL);

    char arr[MAX_SIZE_ADDRESS];
    char arr2[MAX_SIZE_ADDRESS];
    char arr3[MAX_SIZE_ADDRESS];
    sprintf(arr, "rm -r %s/stageArea/*", find_dir("NEO", "/Users"));
    system(arr);
    sprintf(arr2, "rm %s/stage.txt", find_dir("NEO", "/Users"));
    system(arr2);
    sprintf(arr3, "touch %s/stage.txt", find_dir("NEO", "/Users"));
    system(arr3);
    return 0;
}

int set_ord (int argc, char* argv[]) {
    if (argc < 6) {
        perror("invalid input\n");
        return 1;
    }

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/shortcom.txt");
    FILE* file = fopen (stage_path, "a");

    fprintf(file, "%s %s\n", argv[5], argv[3]);

    fclose(file);
    return 0;
}

int remove_ord (int argc, char* argv[]) {
    if (argc < 4) {
        perror("invalid input\n");
        return 1;
    }
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    char stage_path[MAX_SIZE_ADDRESS];

    char data[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/shortcom.txt");

    FILE* file = fopen (stage_path, "r");
    char input[MAX_SIZE_ADDRESS] = {0};

    bool exist = false;
    while (fgets(data, MAX_SIZE_ADDRESS, file) != NULL) {
        char p1[MAX_SIZE_ADDRESS] = {0};
        sscanf(data, "%s", p1);
        if (!strcmp(p1, argv[3])) {
            exist = true;
        }
        else
            strcat(input, data);
    }

    fclose(file);
    FILE* file1 = fopen (stage_path, "w");
    fwrite(input, 1, MAX_SIZE_ADDRESS, file1);

    if (exist == false) {
        printf("there is no any shortcut whit this name\n");
        return 0;
    }

    fclose(file);
    fclose(file1);
    return 0;
}

int replace_ord (int argc, char* argv[]) {
    if (argc < 6) {
        perror("invalid input\n");
        return 1;
    }
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    char stage_path[MAX_SIZE_ADDRESS];
    char p1[MAX_SIZE_ADDRESS];
    char data[MAX_SIZE_ADDRESS] = {0};
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/shortcom.txt");

    FILE* file = fopen (stage_path, "r");

    char input[MAX_SIZE_ADDRESS] = {0};

    bool exist = false;
    while (fgets(data, MAX_SIZE_ADDRESS, file) != NULL) {
        sscanf(data, "%s", p1);

        if (!strcmp(p1, argv[5])) {
            strcat(input, p1);
            strcat(input, " ");
            strcat(input, argv[3]);
            strcat(input, "\n");
            exist = true;
        }
        else {
            strcat(input, data);
        }
    }
    printf(",,%s..", input);

    fclose(file);
    FILE* file1 = fopen (stage_path, "w");
    fwrite(input, 1, MAX_SIZE_ADDRESS, file1);

    if (exist == false) {
        printf("there is no any shortcut whit this name\n");
        return 0;
    }

    fclose(file1);
    return 0;
}

//////

int branch_ord(int argc, char* argv[]) {

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    printf("m;m");
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/all/branches.txt");

    FILE* file3 = fopen (stage_path, "r");

    char null[MAX_SIZE_ADDRESS];
    int num1, num2;
    char br_name [MAX_SIZE_ADDRESS];
    bool exist = false;
    while (fgets(null, MAX_SIZE_ADDRESS, file3) != NULL) {
        sscanf(null, "%d%d%s", &num1, &num2, br_name);
        if (!strcmp(br_name, argv[2]))
            exist = true;
    }
    if (exist == true) {
        printf("this branch is existed you can make it\n");
        return 0;
    }
    fclose(file3);

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path1[MAX_SIZE_ADDRESS];
    strcpy(stage_path1, find_dir("NEO", "/Users"));
    strcat(stage_path1, "/config.txt");

    FILE* file = fopen (stage_path1, "r");
    int num11, num22;
    fgets(null, MAX_SIZE_ADDRESS, file);
    sscanf(null, "%d%d", &num11, &num22);

    fclose(file3);
    make_new_branch (0, argv[2], num11*100+num22);
    fclose(file);
    return 0;
}

int branch_print_ord (int argc, char* argv[]) {

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/all/branches.txt");

    FILE* file3 = fopen (stage_path, "r");
    int i = 0;
    char null[MAX_SIZE_ADDRESS];
    while (fgets(null, MAX_SIZE_ADDRESS, file3) != NULL) {
        printf("%s", null);
    }

    return 0;
}

/////

int log_main_ord (int argc, char* argv[]) {
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/id.txt");

    FILE* file = fopen (stage_path, "r");
    int i = 0;
    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

    int num = 0;
    if (argc > 2) {
        num = i - atoi(argv[3]);
    }
    for (int j = i-1; j >= num; j--) {
        char name[MAX_SIZE_ADDRESS];
        int id;
        sscanf(data[j], "%d%s", &id, name);
        log_print(id);
    }
    return 0;
}

int log_branch (int argc, char* argv[]) {

    br data;
    data = branch_name_to_data (argv[3], -1);
    if (data.id == -1) {
        printf("there is no any branch with this name\n");
        return 1;
    }

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    for (int i = 1; i <= data.num_commit; i++) {
        char stage_path[MAX_SIZE_ADDRESS];
        strcpy(stage_path, find_dir("NEO", "/Users"));
        strcat(stage_path, "/all/");
        str_num(stage_path, data.id);
        strcat(stage_path, "/");
        str_num(stage_path, i);
        strcat(stage_path, ".txt");
        FILE* file = fopen (stage_path, "r");

        char null[MAX_SIZE_ADDRESS];
        char date[MAX_SIZE_ADDRESS];
        fgets(null, MAX_SIZE_ADDRESS, file);
        fgets(date, MAX_SIZE_ADDRESS, file);

        printf("\033[96m%d: \033[0m\033[33m %d \033[0m\033[95m %s\033[0m\n", i, data.id*100 + i, date);
        fclose(file);

    }
    return 0;
}

int log_name (int argc, char* argv[]) {

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/id.txt");

    FILE* file = fopen (stage_path, "r");
    int i = 0;
    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

    for (int j = i-1; j >= 0; j--) {
        int num;
        sscanf(data[j], "%d", &num);

        int commit = num % 100;
        int branch = num / 100;

        char stage_path1[MAX_SIZE_ADDRESS];
        strcpy(stage_path1, find_dir("NEO", "/Users"));
        strcat(stage_path1, "/all/");
        str_num(stage_path1, branch);
        strcat(stage_path1, "/");
        str_num(stage_path1, commit);
        strcat(stage_path1, ".txt");

        FILE* file1 = fopen (stage_path1, "r");
        int ii = 0, jj = 0;
        char data1[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
        for(; jj < 5; jj++)
            fgets(data1[jj], 1000, file1);
        if (!strcmp(data1[jj], argv[3])) {
            printf("%s\t%s", argv[3], data1[1]);
        }
    }
    return 0;
}

int log_date (int argc, char* argv[]) {
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/date.txt");

    FILE* file = fopen (stage_path, "r");
    int i = 0;
    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

    for (int j = i-1; j >= 0; j--) {
        int num;
        char date1[MAX_SIZE_ADDRESS];
        sscanf(data[j], "%d%s", &num, date1);
        printf("%d %s\n", num, date1);
        if (strcmp(data[j], argv[3]) < 0 && !strcmp(argv[2], "-since")) {
            printf("%d %s\n", num, date1);
        }
        if (strcmp(data[j], argv[3]) > 0 && !strcmp(argv[2], "-before")) {
            printf("%d %s\n", num, date1);
        }
    }
    return 0;
}

int log_search (int argc, char* argv[]) {
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/date.txt");

    FILE* file = fopen (stage_path, "r");
    int i = 0;
    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

    for (int j = i-1; j >= 0; j--) {
        int num;
        char date1[MAX_SIZE_ADDRESS];
        sscanf(data[j], "%d%s", &num, date1);

        int commit = num % 100;
        int branch = num / 100;

        char stage_path1[MAX_SIZE_ADDRESS];
        strcpy(stage_path1, find_dir("NEO", "/Users"));
        strcat(stage_path1, "/all/");
        str_num(stage_path1, branch);
        strcat(stage_path1, "/");
        str_num(stage_path1, commit);
        strcat(stage_path1, ".txt");

        for (int k = 3; k < argc; k++) {
            if (compare_first_line(stage_path1, argv[k])) {
                printf("\"%s\" is in %d - %s\n", argv[k], num, date1); // ????????
            }
        }
    }
    return 0;
}

int log_search_wild (int argc, char* argv[]) {
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/date.txt");

    FILE* file = fopen (stage_path, "r");
    int i = 0;
    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

    for (int j = i-1; j >= 0; j--) {
        int num;
        char date1[MAX_SIZE_ADDRESS];
        sscanf(data[j], "%d%s", &num, date1);

        int commit = num % 100;
        int branch = num / 100;

        char stage_path1[MAX_SIZE_ADDRESS];
        strcpy(stage_path1, find_dir("NEO", "/Users"));
        strcat(stage_path1, "/all/");
        str_num(stage_path1, branch);
        strcat(stage_path1, "/");
        str_num(stage_path1, commit);
        strcat(stage_path1, ".txt");

        if (compare_first_line_wild(stage_path1, argv[3]))
            printf("the wildcard \"%s\" is in %d - %s\n", argv[3], num, date1); // ????????

    }
    return 0;
}

//////

int checkout_ord (int argc, char* argv[]) {
    if (checking_stage() == false) {
        printf("stage is not empty\n");
        return 1;
    }

    if (argc == 4) {
        if (find_dir("NEO", "/Users") == NULL) {
            perror("error in finding NEO\n");
            return 1;
        }
        char stage_path[MAX_SIZE_ADDRESS];
        strcpy(stage_path, find_dir("NEO", "/Users"));
        strcat(stage_path, "/id.txt");

        FILE* file = fopen (stage_path, "r");
        int i = 0;
        char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
        for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

        int j = i-1;
        char name[MAX_SIZE_ADDRESS];
        int id;
        sscanf(data[j - atoi(argv[3])], "%d%s", &id, name);
        checkout_recursive(id);

    } else if (!strcmp(argv[2], "HEAD")) {
        if (find_dir("NEO", "/Users") == NULL) {
            perror("error in finding NEO\n");
            return 1;
        }
        char stage_path[MAX_SIZE_ADDRESS];
        strcpy(stage_path, find_dir("NEO", "/Users"));
        strcat(stage_path, "/id.txt");

        FILE* file = fopen (stage_path, "r");
        int i = 0;
        char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
        for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

        int j = i-1;
        char name[MAX_SIZE_ADDRESS];
        int id;
        sscanf(data[j], "%d%s", &id, name);
        checkout_recursive(id);

    } else if (argv[2][0] <= '9' && argv[2][0] >= '0') {
        checkout_recursive(atoi(argv[2]));

    } else {
        br data = branch_name_to_data(argv[2], -1);
        checkout_recursive(data.id*100 + data.num_commit);
    }

    char arr[MAX_SIZE_ADDRESS];
    char arr1[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    char stage_path1[MAX_SIZE_ADDRESS];
    strcpy(stage_path1, find_dir("NEO", "/Users"));
    strcat(stage_path1, "/faze2");
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/where.txt");
    FILE* file = fopen(stage_path, "r");
    fgets(arr1, 1000, file);
    arr1[strlen(arr1) - 1] = 0;
    printf("%s....%d", arr1, errno);
    fclose(file);

    //move_files(stage_path1, arr1);
    //char arr3[MAX_SIZE_ADDRESS];
    //sprintf(arr3, "rm -r %s/faze2/*", find_dir("NEO", "/Users"));
    //system(arr3);

    return 0;
}

//////

int revert_ord (int argc, char* argv[]) {

    if (strlen(argv[3]) > 72) {
        perror("please write a massage with at last 72 character\n");
        return 0;
    }

    char address_of_main[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/config.txt");
    FILE* file = fopen(address_of_main, "r");
    char data[MAX_SIZE_ADDRESS];
    fgets(data, MAX_SIZE_ADDRESS, file);
    fclose(file);

    int branch_id;
    int num_of_commits;
    char a[1000];
    sscanf(data, "%d %d %s", &branch_id, &num_of_commits,a);

    checkout_recursive_for_revert (branch_id*100 + num_of_commits, atoi(argv[4]), NULL);

    char* address_copy = (char*) calloc(MAX_SIZE_ADDRESS, 1);
    strcpy(address_copy, find_dir("NEO", "/Users"));
    strcat(address_copy, "/all/");

    str_num(address_copy, branch_id);

    strcat(address_copy, "/");
    char name[MAX_SIZE_ADDRESS];
    str_num(name, num_of_commits+1);

    copy_and_rename_dir_for_revert (name, address_copy);

    str_num(address_copy, num_of_commits+1);
    strcat(address_copy, ".txt");

    make_file_and_edit_for_commit(address_copy, argv[3]);

    int id = (num_of_commits+1) + (branch_id*100);
    write_in_id(id);
    write_in_date(id);

    chang_num_of_commits (num_of_commits+1, branch_id);
    chang_config (-1, num_of_commits+1, NULL);

    char arr[MAX_SIZE_ADDRESS];
    sprintf(arr, "rm -r %s/collect-for-revert/*", find_dir("NEO", "/Users"));
    system(arr);

    return 0;
}

int revert_n_ord (int argc, char* argv[]) {
    int branch ;
    int commit ;

    if (argc == 3) {
        if (find_dir("NEO", "/Users") == NULL) {
            perror("error in finding NEO\n");
        }
        char stage_path[MAX_SIZE_ADDRESS];
        strcpy(stage_path, find_dir("NEO", "/Users"));
        strcat(stage_path, "/config.txt");
        FILE* file = fopen(stage_path, "r");

        char arr[MAX_SIZE_ADDRESS];
        fgets(arr, MAX_SIZE_ADDRESS, file);
        sscanf(arr, "%d %d", &branch, &commit);

    } else {
        branch = atoi(argv[3]) / 100;
        commit = atoi(argv[3]) % 100;
    }

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/all/");
    str_num(stage_path, branch);
    strcat(stage_path, "/");
    str_num(stage_path, commit);

    char remove[MAX_SIZE_ADDRESS];
    sprintf(remove, "rm -r %s/*", stage_path);
    system(remove);

    return 0 ;
}

int revert_H_ord (int argc, char* argv[]) {

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/id.txt");

    FILE* file = fopen (stage_path, "r");
    int i = 0;
    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++);

    int j = i-1- atoi(argv[5]);
    char id[MAX_SIZE_ADDRESS] = {0};
    sscanf(data[j], "%s", id);

    char* new_argv[40] = {
            "./neogit",
            "revert",
            "-m",
            argv[3],
            id
    };
    int new_argc = 5;
    main(new_argc, new_argv);

    return 0 ;
}

//////

int diff_ord (int argc, char* argv[]) {

    char address1[MAX_SIZE_ADDRESS];
    getcwd(address1, 1000);
    strcat(address1, argv[3]);

    char address2[MAX_SIZE_ADDRESS];
    getcwd(address2, 1000);
    strcat(address2, argv[4]);

    bool line1 = false, line2 = false;
    for (int i = 0; i < argc; i++) {
        if(!strcmp("-line1", argv[i]))
            line1 = true;
        if (!strcmp("-line2", argv[i]))
            line2 = true;
    }

    if (line1 == false && line2 == false) {
        diff(address1, address2, 1, 1000000, 1, 1000000, argv[3], argv[4]);

    } else if (line1 == true && line2 == false) {
        diff(address1, address2, atoi(argv[6]), atoi(argv[7]), 1, 1000000, argv[3], argv[4]);

    } else if (line1 == false && line2 == true) {
        diff(address1, address2, 1, 1000000, atoi(argv[9]), atoi(argv[10]), argv[3], argv[4]);

    } else if (line1 == true && line2 == true) {
        diff(address1, address2, atoi(argv[6]), atoi(argv[7]), atoi(argv[9]), atoi(argv[10]), argv[3], argv[4]);

    }

    return 0;
}
int diff_c_ord (int argc, char* argv[]) {

    int branch ;
    int commit ;
    branch = atoi(argv[3]) / 100;
    commit = atoi(argv[3]) % 100;

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/all/");
    str_num(stage_path, branch);
    strcat(stage_path, "/");
    str_num(stage_path, commit);

    int branch2 ;
    int commit2 ;
    branch2 = atoi(argv[4]) / 100;
    commit2 = atoi(argv[4]) % 100;

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char stage_path1[MAX_SIZE_ADDRESS];
    strcpy(stage_path1, find_dir("NEO", "/Users"));
    strcat(stage_path1, "/all/");
    str_num(stage_path1, branch2);
    strcat(stage_path1, "/");
    str_num(stage_path1, commit2);

    print_files(stage_path, stage_path1);

    return 0;
}

//////

int merge_ord (int argc, char* argv[]) {
    br dataB = branch_name_to_data(argv[2], -1);
    checkout_recursive_for_merge(dataB.id*100 + dataB.num_commit, 1);

    br dataB1 = branch_name_to_data(argv[3], -1);
    checkout_recursive_for_merge(dataB1.id*100 + dataB1.num_commit, 2);

    char address_of_main[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/all/branches.txt");
    FILE* file = fopen(address_of_main, "r");
    char data[MAX_SIZE_ADDRESS];
    fgets(data, MAX_SIZE_ADDRESS, file);
    fclose(file);

    int branch_id;
    int num_of_commits;
    char a[1000];
    sscanf(data, "%d %d %s", &branch_id, &num_of_commits,a);

    char* address_copy = (char*) calloc(MAX_SIZE_ADDRESS, 1);
    strcpy(address_copy, find_dir("NEO", "/Users"));
    strcat(address_copy, "/all/");

    str_num(address_copy, branch_id);

    strcat(address_copy, "/");
    char name[MAX_SIZE_ADDRESS];
    str_num(name, num_of_commits+1);
    copy_and_rename_dir_for_commit (name, address_copy);

    char address1[MAX_SIZE_ADDRESS];
    strcpy(address1, find_dir("NEO", "/Users"));
    strcat(address1, "/merge/");
    str_num(address1, 1);

    char address2[MAX_SIZE_ADDRESS];
    strcpy(address2, find_dir("NEO", "/Users"));
    strcat(address2, "/merge/");
    str_num(address2, 2);

    str_num(address_copy, num_of_commits+1);

    add_files_for_merge(address1, address2, address_copy);

    strcat(address_copy, ".txt");
    make_file_and_edit_for_commit(address_copy, "merge two branches");

    int id = (num_of_commits+1) + (branch_id*100);
    write_in_id(id);
    write_in_date(id);

    chang_num_of_commits (num_of_commits+1, branch_id);
    chang_config (-1, num_of_commits+1, NULL);

    char arr[MAX_SIZE_ADDRESS];
    char arr2[MAX_SIZE_ADDRESS];
    sprintf(arr, "rm -r %s/merge/1/*", find_dir("NEO", "/Users"));
    system(arr);
    sprintf(arr, "rm -r %s/merge/2/*", find_dir("NEO", "/Users"));
    system(arr2);

    return 0;
}

//////

int tag_ord (int argc, char* argv[]) {

    int f = -1;
    int m = -1;
    int c = -1;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-f"))
            f = i;
        if (!strcmp(argv[i], "-c"))
            c = i;
        if (!strcmp(argv[i], "-m"))
            m = i;
    }
    int id;
    if (m == -1) {
        char address_of_main[MAX_SIZE_ADDRESS];
        if (find_dir("NEO", "/Users") == NULL) {
            perror("error in finding NEO\n");
            return 1;
        }

        strcpy(address_of_main, find_dir("NEO", "/Users"));
        strcat(address_of_main, "/config.txt");
        FILE* file = fopen(address_of_main, "r");
        char data[MAX_SIZE_ADDRESS];
        fgets(data, MAX_SIZE_ADDRESS, file);
        fclose(file);

        int commit, branch;
        sscanf(data, "%d%d", &branch, &commit);
        id = branch*100 + commit;
    }
    else {
        id = atoi(argv[m+1]);
    }

    char address_of_main[MAX_SIZE_ADDRESS];
    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/tags");

    char name[MAX_SIZE_ADDRESS];
    strcpy(name, argv[3]);
    strcat(name, ".txt");

    if (file_exists(address_of_main, name)) {
        printf("you can choose this name\n");
        return 0;
    }

    strcat(address_of_main, "/");
    strcat(address_of_main, argv[3]);
    strcat(address_of_main, ".txt");

    FILE* file = fopen(address_of_main, "w");

    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    int i = 0;
    sprintf(data[i], "neogit tag show %s\n", argv[3]);
    i++;
    sprintf(data[i], "tag %s\n", argv[3]);
    i++;
    sprintf(data[i], "commit: %d\n", id);
    i++;
    sprintf(data[i], "author: %s\n", "????");
    i++;

    time_t current_time;
    struct tm *time_info;
    char timeString[30];

    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%a %b %d %H:%M:%S %Y", time_info);

    sprintf(data[i], "Date: %s\n", timeString);
    i++;

    if (m > 0) {
        sprintf(data[i], "Message: %s\n", argv[m+1]);
        i++;
    }

    fclose(file);

    return 0;
}

int compare(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int tag__ord (int argc, char* argv[]) {

    DIR *directory;
    struct dirent *file;
    char *files[100], *temp;
    int count = 0;

    char address_of_main[MAX_SIZE_ADDRESS];
    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/tags");

    directory = opendir(address_of_main);
    if (directory) {
        while ((file = readdir(directory)) != NULL) {
            if (file->d_type == DT_REG) {
                files[count] = strdup(file->d_name);
                count++;
            }
        }
        closedir(directory);

        qsort(files, count, sizeof(char*), compare);

        for (int i = 0; i < count; i++) {
            printf("%s\n", files[i]);
            free(files[i]);
        }
    }
    return 0;
}

int tag_show_ord (int argc, char* argv[]) {

    char address_of_main[MAX_SIZE_ADDRESS];
    strcpy(address_of_main, find_dir("NEO", "/Users"));
    strcat(address_of_main, "/tags");

    char name[MAX_SIZE_ADDRESS];
    strcpy(address_of_main, argv[3]);
    strcat(address_of_main, ".txt");

    print_file_content(address_of_main, name);

    return 0;
}

int hook_show_all_ord (int argc, char* argv[]) {
    for (int i = 1; i <= 5; i++) {
        printf("\"hook-id%d\"\n", i);
    }
    return 0;
}
int hook_add_ord (int argc, char* argv[]) {
    char address[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/hooklist.txt");
    FILE *fptr;
    fptr = fopen (address, "a");
    if (fptr == NULL) {
        printf ("Error in opening file.\n");
        exit (1);
    }

    fprintf(fptr, "%d\n", atoi(argv[4]));
    fclose(fptr);
    return 0;
}
int hook_remove_ord (int argc, char* argv[]) {
    char address[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/hooklist.txt");
    delete_name_from_file (argv[4], address);
    return 0;
}
int hook_show_list_ord (int argc, char* argv[]) {
    char address[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/hooklist.txt");
    FILE *fptr;
    fptr = fopen (address, "r");
    if (fptr == NULL) {
        printf ("Error in opening file.\n");
        exit (1);
    }

    char output[MAX_SIZE_ADDRESS];
    for (; fgets(output, 1000, fptr) != NULL;)
        printf("hook-id%s", output);

    fclose(fptr);
    return 0;
}

int pre (int argc, char* argv[]) {


    do_directory_files()
}

int hook1(char* filePath, char* name) {
    FILE *file = fopen(filePath, "r");
    if (file) {
        char ext[5];
        int len = strlen(filePath);
        strcpy(ext, &filePath[len - 4]);

        if (strcmp(ext, ".txt") == 0) {

            char buffer[100];
            int found = 0;
            while (fscanf(file, "%s", buffer) == 1) {
                if (strcmp(buffer, "TODO") == 0) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                printf("EXIST\n");
            } else {
                printf("NO\n");
            }
        } else if (strcmp(ext, ".cpp") == 0 || strcmp(ext, ".c") == 0) {

            char line[200];
            int found = 0;
            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, "// TODO") != NULL) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                printf("EXIST\n");
            } else {
                printf("NO\n");
            }
        } else {
            printf("VVV\n");
        }

        fclose(file);
    } else {
        printf("Error opening the file.\n");
    }
}

int hook2(char* filePath, char* name) {
    FILE *file = fopen(filePath, "r");
    if (file) {
        char ext[5];
        int len = strlen(filePath);
        strcpy(ext, &filePath[len - 4]);

        if (strcmp(ext, ".txt") == 0 || strcmp(ext, ".c") == 0 || strcmp(ext, ".cpp") == 0) {
            fseek(file, -1, SEEK_END);
            char lastChar;
            do {
                fseek(file, -1, SEEK_CUR);
                lastChar = fgetc(file);
            } while (isspace(lastChar));

            if (lastChar == EOF) {
                printf("FAILED\n");
            } else {
                printf("PASSED\n");
            }
        } else {
            printf("SKIPPED\n");
        }

        fclose(file);
    } else {
        printf("Error opening the file.\n");
    }
    return 0;
}

int hook3(char* filePath) {
    char validFormats[7][5] = {".txt", ".c", ".cpp", ".pdf", ".doc", ".jpg", ".png"};

    char ext[5];
    int len = strlen(filePath);
    strcpy(ext, &filePath[len - 4]);

    for (int i = 0; i < 7; i++) {
        if (strcmp(ext, validFormats[i]) == 0) {
            return 1; // Valid format found
        }
    }
    return 0; // Not a valid format
}

void hook3_1(char* filePath) {
    if (hook3(filePath)) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}

int hook4(char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }

    int curlyCount = 0, roundCount = 0, squareCount = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '(') {
            roundCount++;
        } else if (c == ')') {
            roundCount--;
        } else if (c == '{') {
            curlyCount++;
        } else if (c == '}') {
            curlyCount--;
        } else if (c == '[') {
            squareCount++;
        } else if (c == ']') {
            squareCount--;
        }
    }

    fclose(file);

    if (curlyCount == 0 && roundCount == 0 && squareCount == 0) {
        return 1;
    } else {
        return 0;
    }
}

void hook5(char* filePath) {
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);

    if (fileSize > 5 * 1024 * 1024) { // 5 MB in bytes
        printf("FAILED\n");
    } else {
        printf("PASSED\n");
    }
}

int isValidFormat(const char *filePath) {

    const char *fileExtension = strrchr(filePath, '.');
    if (fileExtension != NULL) {
        if (strcmp(fileExtension, ".c") == 0 || strcmp(fileExtension, ".cpp") == 0 || strcmp(fileExtension, ".txt") == 0) {
            return 1;
        }
    }
    return 0;
}

int hook6(char *filePath, char* name) {
    if (!isValidFormat(filePath)) {
        printf("SKIPPED\n");
        return 0;
    }

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize > 20000) {
        printf("FAILED\n");
    } else {
        printf("PASSED\n");
    }
    fclose(file);
    return 0;
}


int stash (int argc, char* argv[]) {


}
// ###################################  main functions  ###################################

//////

int creat_configuration (char* email, char* username, char* bench, char* now) {
    FILE* file = fopen ("NEO/config.txt", "w");
    FILE* file1 = fopen ("NEO/stage.txt", "w");
    FILE* file4 = fopen ("NEO/id.txt", "w");
    FILE* file5 = fopen ("NEO/shortcom.txt", "w");
    FILE* file6 = fopen ("NEO/name.txt", "w");
    FILE* file7 = fopen ("NEO/date.txt", "w");
    FILE* file8 = fopen ("NEO/where.txt", "w");
    FILE* file10 = fopen ("NEO/hooklist.txt", "w");

    if (file == NULL) {
        perror("error in opening file\n");
        return 1;
    }
    if (file1 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }

    if (file4 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (file5 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (file6 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (file7 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (mkdir("./NEO/stageArea", 0755) != 0) {
        perror("error in making stageArea\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/faze2", 0755) != 0) {
        perror("error in making stageArea\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (file8 == NULL) {
        perror("error in opening file\n");
        return 1;
    }

    fprintf (file, "1 0 master\n");
    fprintf (file6, "mrz\n");
    fprintf (file8, "%s\n", now);

    fclose(file);
    fclose(file1);
    fclose(file4);
    fclose(file5);
    fclose(file6);
    fclose(file7);
    fclose(file8);
    // ***************************** all *****************************

    if (mkdir("./NEO/all", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/merge", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/merge/1", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/merge/2", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/collect-for-revert", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/tags", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }

    FILE* file3 = fopen ("NEO/all/branches.txt", "w");
    fprintf (file3, "1 0 master\n");
    fclose(file3);

    if (mkdir("./NEO/all/1", 0755) != 0) {
        perror("error in making branch.txt\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    return 0;
}

//////

int add_to_stage (char* filepath, char* dir_address) {

    if (file_exists(dir_address, filepath) == 0) {
        printf ("there is no any file with this name\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS] = {0};
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }

    strcpy(stage_path, find_dir("NEO", "/Users"));
    char stage_area_path[MAX_SIZE_ADDRESS] = {0};
    strcpy(stage_area_path, find_dir("NEO", "/Users"));
    strcat(stage_area_path, "/stageArea");

    //printf("%s\n", stage_path);
    strcat(stage_path, "/stage.txt");
    FILE* file_stage = fopen(stage_path, "r");
    if (file_stage == NULL) {
        perror("error in opening stage file.\n");
        return 1;
    }

    char file_s_path[MAX_SIZE_ADDRESS];
    while (fgets(file_s_path, MAX_SIZE_ADDRESS, file_stage) != NULL) {
        file_s_path[strlen(file_s_path) - 1] = '\0';
        if (!strcmp(file_s_path, filepath)) {
            fclose(file_stage);
            return BEING_STAGED;
        }
    }

    fclose(file_stage);
    printf("^\n");
    FILE* file_stage1 = fopen(stage_path, "a");
    fprintf(file_stage1,"%s\n", filepath);
    add_file_to_stage_area (stage_area_path, filepath, dir_address);
    fclose(file_stage1);

    return 0;
}

//////

/*char* global_config_email (char *name, char *path) {
    DIR *dir;
    struct dirent *entry;
    char *result = NULL;
    char new_path[256];

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir() error");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (strcmp(entry->d_name, name) == 0) {

            result = (char *)calloc(MAX_SIZE_ADDRESS, 1);
            if (result == NULL)
            {
                perror("calloc() error\n");
                closedir(dir);
                return NULL;
            }
            strcpy(result, path);
            strcat(result, "/");
            strcat(result, name);
            closedir(dir);
            strcat(result, "/email.txt");
            FILE* file = fopen(result, "w");
            fprintf(file, "%s\n", argv[4]);

            fclose(file);
        }

        if (entry->d_type == DT_DIR) {
            strcpy(new_path, path);
            strcat(new_path, "/");
            strcat(new_path, entry->d_name);
            result = find_dir(name, new_path);
            if (result != NULL)
            {
                closedir(dir);
                return result;
            }
        }
    }

    closedir(dir);
    return NULL;
}
*/

char* find_dir(char *name, char *path) {

    char cwd [MAX_SIZE_ADDRESS] = {0};
    char tmp_dir[MAX_SIZE_ADDRESS] = {0};
    char now_address[MAX_SIZE_ADDRESS];
    getcwd(now_address, 1000);

    getcwd(cwd, sizeof(cwd));
    bool exist = false;
    struct dirent * ent;

    do {
        DIR* dir = opendir(".");
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && !strcmp(ent->d_name, "NEO")) {
                char* now_address1 = (char*) malloc(1000);
                getcwd(now_address1, 1000);
                strcat(now_address1, "/");
                strcat(now_address1, ent->d_name);
                chdir(now_address);
                return now_address1;
            }
        }
        getcwd(tmp_dir, sizeof (tmp_dir));
        if (strcmp(tmp_dir, "/"))
            chdir("..");

    } while (strcmp(tmp_dir, "/") && exist == false);
    chdir(now_address);
    return NULL;

}

//////

int file_exists (char *dir, char *file) {

    DIR *dp = opendir(dir);
    if (dp == NULL) {
        perror("error in opendir\n");
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, file) == 0) {
            closedir(dp);
            return 1;
        }
    }

    closedir(dp);
    return 0;
}

//////

void wildcard_fun (char *wildcard, char *directory, int (*doing) (char* ,char*)) {

    DIR *dir;
    struct dirent *entry;
    dir = opendir(directory);
    if (dir == NULL) {
        perror("Unable to open directory\n");
        exit(1);
    }

    bool exist = false;
    while ((entry = readdir(dir)) != NULL) {
        if (fnmatch(wildcard, entry->d_name, 0) == 0) {
            exist = true;
            doing(entry->d_name, directory);

        }
    }

    closedir(dir);
    if (exist == false) {
        printf("there is no any file with this wildcard\n");
    }
}

//////

void do_directory_files (char *directory, int (*doing)(char *f, char *d)) {

    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);
    if (dir == NULL) {
        perror("Unable to open directory\n");
        exit(1);
    }

    bool exist = false;
    while ((entry = readdir(dir)) != NULL) {

        if (strstr(entry->d_name, ".txt") != NULL) {
            doing(entry->d_name, directory);
            exist = true;
        }
    }

    closedir(dir);
    if (exist == false) {
        printf("there is no any file in directory\n");
    }

}

//////

int remove_from_stage (char* filepath, char* dir_address) {

    if (file_exists(dir_address, filepath) == 0) {
        printf ("there is no any file with this name\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/stage.txt");

    delete_name_from_file(filepath, stage_path);

    char stage_area_path[MAX_SIZE_ADDRESS];
    strcpy(stage_area_path, find_dir("NEO", "/Users"));
    strcat(stage_area_path, "/stageArea");
    delete_file_from_directory (stage_area_path, filepath);

    return 0;
}

/////

void delete_name_from_file (char *name, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("error in opening file\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    //printf("%lx", size);
    fseek(fp, 0, SEEK_SET);

    char *content = malloc(size + 1);

    if (fread(content, 1, size, fp) == 0){
        printf("error in reading file\n");
        return;
    }
    content[size] = '\0';
    char *new_content = calloc(size + 1, 1);

    fclose(fp);
    int index = 0;
    char *line = strtok(content, "\n");
    while (line != NULL) {

        if (strcmp(line, name) != 0) {
            strcpy(new_content + index, line);
            index += strlen(line);
            new_content[index++] = '\n';
        }

        line = strtok(NULL, "\n");
    }
    new_content[index++] = '\0';

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("error in opening file\n");
        free(new_content);
        free(content);
        return;
    }

    fwrite(new_content, 1, index, fp);

    fclose(fp);
    free(new_content);
    free(content);

}

//////

int add_file_to_stage_area (char* dir_address_area, char* file_name, char * address_dir) { // stag area address and file name

    char* file_address = (char*) malloc(MAX_SIZE_ADDRESS);

    strcat(file_address, "cp ");

    strcat(file_address, address_dir);
    strcat(file_address, "/");
    strcat(file_address, file_name);

    strcat(file_address, " ");
    strcat(file_address, dir_address_area);
    strcat(file_address, "/");
    printf("\n'%s'\n", file_address);
    system(file_address);
    free(file_address);

    return 0;
}

//////

void delete_file_from_directory (char *directory, char* name) {

    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);
    if (dir == NULL) {
        perror("Unable to open directory\n");
        exit(1);
    }
    char delete[MAX_SIZE_ADDRESS] = {0};
    while ((entry = readdir(dir)) != NULL) {
        if ( strcmp(entry->d_name, name) == 0) {
            strcpy(delete, directory);
            strcat(delete, "/");
            strcat(delete, name);
            unlink(delete);
            break;
        }
    }

    closedir(dir);

}

//////

int for_status_is_not_negative (char* f1, char* f2) { // address and ---> f2         // the name of the file  ---> f1

    DIR *dir;
    struct dirent *entry;
    char stage_path[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/stageArea");

    char target_address[MAX_SIZE_ADDRESS];
    strcpy(target_address, f2);
    strcat(target_address, "/");
    strcpy(target_address, f1);

    dir = opendir(stage_path);
    if (dir == NULL) {
        perror("Unable to open directory\n");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        if ( strcmp(entry->d_name, f1) == 0) {
            strcat(stage_path, "/");
            strcat(stage_path, entry->d_name);
            return comparing_tow_files_with_address(stage_path, target_address);
        }
    }
    return 1; // 1 means that there is no any similar file in stage area
}

//////

int comparing_tow_files_with_address (char* ad1, char* ad2) {
    FILE *file1 = fopen(ad1, "r");
    FILE *file2 = fopen(ad2, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        return 1;
    }

    fseek(file1, 0, SEEK_END);
    long file1_size = ftell(file1);
    fseek(file1, 0, SEEK_SET);

    fseek(file2, 0, SEEK_END);
    long file2_size = ftell(file2);
    fseek(file2, 0, SEEK_SET);

    if (file1_size != file2_size) {

        fclose(file1);
        fclose(file2);
        return 1;
    } else {
        int the_value_for_return = 0;
        char *buffer1 = (char *)malloc(file1_size);
        char *buffer2 = (char *)malloc(file2_size);

        fread(buffer1, 1, file1_size, file1);
        fread(buffer2, 1, file2_size, file2);

        if (memcmp(buffer1, buffer2, file1_size) == 0) {

        } else {
            the_value_for_return = 1;
        }

        free(buffer1);
        free(buffer2);
        fclose(file1);
        fclose(file2);
        return the_value_for_return;
    }
}

//////

int add_alias_in_file (int code, char* name_of_alias) {

    char alias_path[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(alias_path, find_dir("NEO", "/Users"));
    strcat(alias_path, "/alias.txt");

    FILE* file = fopen(alias_path, "a");
    char target_alias[MAX_SIZE_ADDRESS];
    fprintf(file, "%d %s\n", code, name_of_alias);

    fclose(file);
    return 0;
}

//////

int make_new_branch (int zero, char* name, int last_com) {
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/all/branches.txt");

    FILE* file3 = fopen (stage_path, "r");
    int i = 0;
    char null[MAX_SIZE_ADDRESS];
    for (;fgets(null, MAX_SIZE_ADDRESS, file3) != NULL; i++);
    fclose(file3);

    FILE* file4 = fopen (stage_path, "a");
    fprintf (file4, "%d %d %s %d\n", i+1, zero, name, last_com); // %d
    fclose(file3);

    chang_config(i+1, 0, name);
    char address_dir[MAX_SIZE_ADDRESS];
    strcpy(address_dir, find_dir("all", "/Users"));
    strcat(address_dir, "/");
    str_num(address_dir, i+1);

    if (mkdir( address_dir, 0755) != 0) {
        perror("error in making stageArea(b)\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    return 0;
}

//////

 void str_num (char* str, int num) {
     char arr[20] = {0};
     sprintf(arr, "%d", num);
     // printf("<%s>\n", arr);

     strcat(str, arr);
}

//////

void copy_and_rename_dir_for_commit (char *name, char *path) {
    char command[500];
    char address[500];
    strcpy(address, find_dir("NEO", "/Users"));
    sprintf(command, "cp -r %s/stageArea %s && mv %s/stageArea %s/%s", address, path, path, path, name);
    system(command);
}

void copy_and_rename_dir_for_revert (char *name, char *path) {
    char command[500];
    char address[500];
    strcpy(address, find_dir("NEO", "/Users"));
    sprintf(command, "cp -r %s/collect-for-revert %s && mv %s/collect-for-revert %s/%s", address, path, path, path, name);
    system(command);
}

//////

void make_file_and_edit_for_commit (char* address, char* massage) {
    FILE *fptr;
    fptr = fopen (address, "w");
    if (fptr == NULL)
    {
        printf ("Error in opening file.\n");
        exit (1);
    }

    time_t t = time (NULL);
    struct tm *tm = localtime (&t);
    char s [64];

    size_t ret = strftime (s, sizeof (s), "%d-%m-%Y %H:%M:%S", tm);
    if (ret == 0) {
        printf ("Error in formatting string.\n");
        return;
    }

    int num_of_files_for_commit;
    num_of_files_for_commit = counting_number_files_commit();

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char address1[MAX_SIZE_ADDRESS];
    strcpy(address1, find_dir("NEO", "/Users"));
    strcat(address1, "/name.txt");
    FILE* file1 = fopen (address, "r");

    char name[MAX_SIZE_ADDRESS];
    fgets(name, 100, file1);

    fprintf (fptr, "%s\n%s\n%d\n%s\n", massage, s, num_of_files_for_commit, name); // s --> time
    fclose (fptr);
}

//////

int counting_number_files_commit () {

    char address[MAX_SIZE_ADDRESS];
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/stage.txt");
    FILE* file = fopen(address, "r");

    char null[MAX_SIZE_ADDRESS];
    int i = 0;
    for (; fgets(null, MAX_SIZE_ADDRESS, file); i++);
    return i;
}

//////

void write_in_id (int id) {
    char address[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return;
    }
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/id.txt");

    FILE *fptr;
    fptr = fopen (address, "a");
    if (fptr == NULL) {
        printf ("Error in opening file.\n");
        exit (1);
    }
    fprintf(fptr, "%d\n", id);
    fclose(fptr);
}

//////

int chang_config (int branch, int new_num_of_commit, char* name_of_branch) {
    char address[MAX_SIZE_ADDRESS];
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/config.txt");
    FILE *fptr;
    fptr = fopen (address, "r");
    if (fptr == NULL) {
        printf ("Error in opening file.\n");
        exit (1);
    }

    int v1, v2;
    char name_branch[MAX_SIZE_ADDRESS];
    fscanf(fptr, "%d %d %s", &v1, &v2, name_branch);
    fclose(fptr);

    FILE *fptr1;
    fptr1 = fopen (address, "w");
    if (fptr1 == NULL) {
        printf ("Error in opening file.\n");
        exit (1);
    }
    if (name_of_branch != NULL) {
        strcpy(name_branch, name_of_branch);
    }
    if (branch != -1) {
        v1 = branch;
    }
    fprintf(fptr, "%d %d %s", v1, new_num_of_commit, name_branch);
    fclose(fptr1);

    return 0;
} // -1 n NULL <<<<<<<<<<<<
/*int creat_configuration (char* email, char* username, char* bench, char* now) {
    FILE* file = fopen ("NEO/config.txt", "w");
    FILE* file1 = fopen ("NEO/stage.txt", "w");
    FILE* file4 = fopen ("NEO/id.txt", "w");
    FILE* file5 = fopen ("NEO/shortcom.txt", "w");
    FILE* file6 = fopen ("NEO/name.txt", "w");
    FILE* file7 = fopen ("NEO/date.txt", "w");
    FILE* file8 = fopen ("NEO/where.txt", "w");
    FILE* file10 = fopen ("NEO/hooklist.txt", "w");

    if (file == NULL) {
        perror("error in opening file\n");
        return 1;
    }
    if (file1 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }

    if (file4 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (file5 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (file6 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (file7 == NULL) {
        perror("error in opening file.\n");
        return 1;
    }
    if (mkdir("./NEO/stageArea", 0755) != 0) {
        perror("error in making stageArea\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/faze2", 0755) != 0) {
        perror("error in making stageArea\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (file8 == NULL) {
        perror("error in opening file\n");
        return 1;
    }

    fprintf (file, "1 0 master\n");
    fprintf (file6, "mrz\n");
    fprintf (file8, "%s\n", now);

    fclose(file);
    fclose(file1);
    fclose(file4);
    fclose(file5);
    fclose(file6);
    fclose(file7);
    fclose(file8);
    // ***************************** all *****************************

    if (mkdir("./NEO/all", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/merge", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/merge/1", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/merge/2", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/collect-for-revert", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    if (mkdir("./NEO/tags", 0755) != 0) {
        perror("error in making all\n");
        printf("error is: %d\n", errno);
        return 1;
    }

    FILE* file3 = fopen ("NEO/all/branches.txt", "w");
    fprintf (file3, "1 0 master\n");
    fclose(file3);

    if (mkdir("./NEO/all/1", 0755) != 0) {
        perror("error in making branch.txt\n");
        printf("error is: %d\n", errno);
        return 1;
    }
    return 0;
}
*/
//////

int chang_num_of_commits (int new_num_of_commit, int branch) {
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/all/branches.txt");

    FILE *fptr;
    fptr = fopen (stage_path, "r");
    if (fptr == NULL) {
        printf ("Error in opening file.\n");
        exit (1);
    }

    char lines [100][100];
    int count = 0;
    while (fgets (lines[count], 100, fptr) != NULL) {
        count++;
    }
    fclose (fptr);

    int num1, num2, num3;
    char null[MAX_SIZE_ADDRESS];


    sscanf (lines [branch - 1], "%d %d %s %d", &num1, &num2, null, &num3);

    sprintf (lines [branch - 1], "%d %d %s %d\n", num1, new_num_of_commit, null, num3);

    fptr = fopen (stage_path, "w");
    if (fptr == NULL) {
        printf ("Error in opening file.\n");
        exit (1);
    }
    for (int i = 0; i < count; i++) {
        fputs (lines [i], fptr);
    }
    fclose (fptr);
    return 0;
}

//////

int log_print (int id) {
    printf("\033[93mid:\t%d\033[0m\n", id);

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    int commit_id = id % 100;
    int branch_id = id / 100;
    char address[MAX_SIZE_ADDRESS];
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/all/");
    str_num(address, branch_id);
    strcat(address, "/");
    str_num(address, commit_id);
    strcat(address, ".txt");

    FILE* file = fopen (address, "r");

    for (int i = 0; i < 4; i++) {
        char output[100] = {0};
        fgets(output, 100, file);
        printf("\033[96m%d:\033[0m\t\033[95m%s\033[0m", i+1, output);
    }
    fclose(file);

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char address1[MAX_SIZE_ADDRESS];
    strcpy(address, find_dir("NEO", "/Users"));
    strcat(address, "/all/branches.txt");
    FILE* file1 = fopen (address, "r");

    for (int i = 1; i <= branch_id; i++) {
        char data[MAX_SIZE_ADDRESS] = {0};
        fgets(data, 100, file1);
        if (i == branch_id) {
            printf("\033[34mbranch data:\t%s\033[0m\n", data);
        }
    }

    return 0;
}

br branch_name_to_data (char* name, int id) {

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/all/branches.txt");

    FILE* file = fopen (stage_path, "r");
    int i = 0;
    char data[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS];
    for (;fgets(data[i], MAX_SIZE_ADDRESS, file) != NULL; i++) {
        br out;
        sscanf(data[i], "%d%d%s%d", &out.id, &out.num_commit, out.name, &out.last);
        printf("**%s**\n", out.name);
        if (!strcmp(name, out.name)) {
            return out;
        }
        if (id == out.id) {
            return out;
        }
    }
    br null;
    null.id = -1;
    return null;
}

//////


int write_in_date (int id) {

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/date.txt");

    FILE* file = fopen (stage_path, "a");

    char date[11];
    time_t now_1;
    struct tm *local_time;

    time(&now_1);
    local_time = localtime(&now_1);

    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    snprintf(date, sizeof(date), "%04d/%02d/%02d", year, month, day);

    fprintf(file, "%d %s\n", id, date);
    return 0;
}

int compare_first_line(char *file_name, char *word) {
    char line[256];
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("error in opening file\n");
        return 0;
    }
    fgets(line, 1000, fp);
    fclose(fp);
    char *token;
    token = strtok(line, " \t\n");

    while (token != NULL) {

        if (strcmp(token, word) == 0) {
            return 1;
        }
        token = strtok(NULL, " \t\n");
    }
    return 0;
}

int compare_first_line_wild(char *file_name, char *word) {
    char line[256];
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("error in opening file\n");
        return -1;
    }
    fgets(line, sizeof(line), fp);
    fclose(fp);
    char *token;
    token = strtok(line, " \n");
    while (token != NULL) {
        if (fnmatch(word, token, 0) == 0) {
            return 1;
        }
        token = strtok(NULL, " \n");
    }
    return 0;
} // ?????????????????????

//////

int checkout_recursive (int id) {
    int branch = id / 100;;
    int commit = id % 100;
    for (; branch > 0;) {

        for (; commit > 0; commit--) {
            if (find_dir("NEO", "/Users") == NULL) {
                perror("error in finding NEO\n");
            }
            char stage_path[MAX_SIZE_ADDRESS];
            strcpy(stage_path, find_dir("NEO", "/Users"));
            strcat(stage_path, "/all/");
            str_num(stage_path, branch);
            strcat(stage_path, "/");
            str_num(stage_path, commit);
            char arr[MAX_SIZE_ADDRESS];

            char address1[MAX_SIZE_ADDRESS];

            strcpy(address1, find_dir("NEO", "/Users"));
            strcat(address1, "/faze2");
            sprintf(arr, "cp -n %s/* %s", stage_path, address1);

            system(arr);

        }
        if (branch == 1) {
            break;
        }
        br branch_data;
        branch_data = branch_name_to_data("erngnerygneyr7gyr goyersg9gnegn", branch);
        id = branch_data.last;
        branch = id / 100;
        commit = id % 100;
    }
    return 0;
}

//////

bool checking_stage () {
    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
        return 1;
    }
    char stage_path[MAX_SIZE_ADDRESS];
    strcpy(stage_path, find_dir("NEO", "/Users"));
    strcat(stage_path, "/stage.txt");

    FILE* file3 = fopen (stage_path, "r");
    int i = 0;
    char null[MAX_SIZE_ADDRESS];
    for (;fgets(null, MAX_SIZE_ADDRESS, file3) != NULL; i++);
    fclose(file3);
    if (i == 0) {
        return true;
    } else {
        return false;
    }
}

/*int move_files(char *src_dir, char *dest_dir)
{
    // Open the source directory
    DIR *src = opendir(src_dir);
    if (src == NULL)
    {
        perror("opendir");
        return 1;
    }

    // Read the source directory entries
    struct dirent *entry;
    while ((entry = readdir(src)) != NULL)
    {
        // Skip the . and .. entries
        if (entry->d_name[0] == '.')
            continue;

        // Construct the source file path
        char src_path[256];
        snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, entry->d_name);

        // Construct the destination file path
        char dest_path[256];
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, entry->d_name);

        // Check if the destination file exists
        if (access(dest_path, F_OK) == 0)
        {
            // Rename the source file to overwrite the destination file
            if (rename(src_path, dest_path) == -1)
            {
                perror("rename");
                return 2;
            }
        }
        else
        {
            // Construct the destination subdirectory path
            char sub_path[256];
            snprintf(sub_path, sizeof(sub_path), "%s/sub", dest_dir);

            // Check if the destination subdirectory exists
            if (access(sub_path, F_OK) == 0)
            {
                // Append the file name to the subdirectory path
                snprintf(dest_path, sizeof(dest_path), "%s/%s", sub_path, entry->d_name);
            }
            else
            {
                // Use the destination directory path as default
            }

            // Rename the source file to move it to the destination path
            if (rename(src_path, dest_path) == -1)
            {
                perror("rename");
                return 3;
            }
        }
    }


    if (closedir(src) == -1)
    {
        perror("closedir");
        return 4;
    }

    return 0;
}*/
//////

int checkout_recursive_for_revert (int id, int id_of_ignore, char* address1) {

    if (find_dir("NEO", "/Users") == NULL) {
        perror("error in finding NEO\n");
    }
    char stage_path2[MAX_SIZE_ADDRESS];
    strcpy(stage_path2, find_dir("NEO", "/Users"));
    strcat(stage_path2, "/collect-for-revert");

    int branch = id / 100;
    int commit = id % 100;

    for (; branch > 0;) {
        for (; commit > 0; commit--) {
            if (find_dir("NEO", "/Users") == NULL) {
                perror("error in finding NEO\n");
            }
            char stage_path[MAX_SIZE_ADDRESS];
            strcpy(stage_path, find_dir("NEO", "/Users"));
            strcat(stage_path, "/all/");
            str_num(stage_path, branch);
            strcat(stage_path, "/");
            str_num(stage_path, commit);

            char arr[MAX_SIZE_ADDRESS];
            sprintf(arr, "cp -n %s/* %s", stage_path, stage_path2);
            if (commit + 100*branch != id_of_ignore)
                system(arr);
            else {
                char remove[MAX_SIZE_ADDRESS];
                sprintf(remove, "rm -r %s/*", stage_path);
                system(remove);
            }

        }
        if (branch == 1) {
            break;
        }
        br branch_data;
        branch_data = branch_name_to_data("u68dvvd6u c 5es4693a4_ uy", branch);
        id = branch_data.last;
        branch = id / 100;
        commit = id % 100;
    }
    return 0;
}

//////

int diff(char *file11, char *file22, int start1, int end1, int start2, int end2, char* name1, char* name2) {

    FILE* f1 = fopen(file11, "r");
    FILE* f2 = fopen(file22, "r");
    if (f1 == NULL || f2 == NULL) {
        printf("error in opening file\n");
        return -1;
    }
    char line1[1000], line2[1000];
    int line_num1 = 1, line_num2 = 1;

    char file1[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS] = {0};
    char file2[MAX_SIZE_ADDRESS][MAX_SIZE_ADDRESS] = {0};

    int i1 = 1;
    for (; fgets(file1[i1], 1000, f1); i1++);
    int i2 = 1;
    for (; fgets(file1[i2], 1000, f2); i2++);

    int p1 = start1;
    int p2 = start2;

    for (; p1 <= i1 && p2 <= i2 && p1 <= end1 && p2 <= end2; p1++, p2++) {

        while (strlen(file1[p1]) == 1)  p1++;
        while (strlen(file1[p2]) == 1)  p2++;

        char out1[MAX_SIZE_ADDRESS];
        char out2[MAX_SIZE_ADDRESS];
        strcpy(out1, file1[p1]);
        strcpy(out2, file1[p2]);

        bool same = true;
        char *token1 = strtok(file1[p1], " \t\n");
        char *token2 = strtok(file1[p1], " \t\n");
        while (token1 != NULL && token2 != NULL) {

            if (strcmp(token1, token2))
                same &= false;

            token1 = strtok(NULL, " \t\n");
            token2 = strtok(NULL, " \t\n");
        }
        if (token1 != NULL || token2 != NULL) {
            same = false;
        }

        if (same == false) {
            printf("\033[34m%s\033[0m-%d\n", name1, p1);
            printf("\033[34m%s\033[0m", out1);

            printf("%s-%d\n", name2, p2);
            printf("\033[34m%s\033[0m>> >> >> >> >>\n", out2);
            return 1;
        }
    }

    return 0;
}

//////

char** list_files(char* dir) {

    char** files = malloc(100 * sizeof(char*));
    int index = 0;
    DIR* d = opendir(dir);
    if (d) {
        struct dirent* entry;
        while ((entry = readdir(d)) != NULL) {
            if (entry->d_type == DT_REG) {
                files[index] = malloc(256 * sizeof(char));
                strcpy(files[index], entry->d_name);
                index++;
            }
        }
        closedir(d);
    }
    files[index] = NULL;
    return files;
}

int contains(char* str, char** arr) {
    int i = 0;
    while (arr[i] != NULL) {
        if (strcmp(str, arr[i]) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

void print_files(char* dir1, char* dir2) {
    char** files1 = list_files(dir1);
    char** files2 = list_files(dir2);
    int i = 0;
    while (files1[i] != NULL) {
        if (!contains(files1[i], files2)) {
            printf("%s\n", files1[i]);
        }
        else {
            char address1[MAX_SIZE_ADDRESS];
            char address2[MAX_SIZE_ADDRESS];
            strcpy(address1, dir1);
            strcpy(address2, dir2);
            strcat(address1, "/");
            strcat(address1, files1[i]);
            strcat(address2, "/");
            strcat(address1, files1[i]);
            diff(address1, address2, 1, 1000000, 1, 1000000, files1[i], files2[i]);
        }
        i++;
    }
    i = 0;
    while (files2[i] != NULL) {
        printf("%s\n", files2[i]);
        i++;
    }
}

//////

int checkout_recursive_for_merge (int id, int num) {
    int branch = id / 100;
    int commit = id % 100;
    for (; branch > 0;) {

        for (; commit > 0; commit--) {
            if (find_dir("NEO", "/Users") == NULL) {
                perror("error in finding NEO\n");
            }
            char stage_path[MAX_SIZE_ADDRESS];
            strcpy(stage_path, find_dir("NEO", "/Users"));
            strcat(stage_path, "/all/");
            str_num(stage_path, branch);
            strcat(stage_path, "/");
            str_num(stage_path, commit);
            char arr[MAX_SIZE_ADDRESS];

            char address1[MAX_SIZE_ADDRESS];
            strcpy(address1, find_dir("NEO", "/Users"));
            strcat(address1, "/merge/");
            str_num(address1, num);

            sprintf(arr, "cp -n %s/* %s", stage_path, address1);
            system(arr);

        }
        if (branch == 1) {
            break;
        }
        br branch_data;
        branch_data = branch_name_to_data("ng7f trve75x v_+oj7", branch);
        id = branch_data.last;
        branch = id / 100;
        commit = id % 100;
    }
    return 0;
}

void add_files_for_merge(char* dir1, char* dir2, char* address) {
    char** files1 = list_files(dir1);
    char** files2 = list_files(dir2);
    int i = 0;
    while (files1[i] != NULL) {
        if (!contains(files1[i], files2)) {
            char arr[MAX_SIZE_ADDRESS];
            sprintf(arr, "cp %s/%s %s", dir1, files1[i], address);
            system(arr);
        }
        else {
            char address1[MAX_SIZE_ADDRESS];
            char address2[MAX_SIZE_ADDRESS];
            strcpy(address1, dir1);
            strcpy(address2, dir2);
            strcat(address1, "/");
            strcat(address1, files1[i]);
            strcat(address2, "/");
            strcat(address2, files2[i]);
            diff(address1, address2, 1, 1000000, 1, 1000000, files1[i], files2[i]);
        }
        i++;
    }
    i = 0;
    while (files2[i] != NULL) {
        char arr[MAX_SIZE_ADDRESS];
        sprintf(arr, "cp %s/%s %s", dir2, files2[i], address);
        system(arr);
        i++;
    }
}

//////

void print_file_content(const char *directory_path, const char *file_name) {
    char file_path[100];
    FILE *file_ptr;
    char ch;

    sprintf(file_path, "%s/%s", directory_path, file_name);

    file_ptr = fopen(file_path, "r");
    if (file_ptr == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    printf("Content of file '%s':\n", file_name);

    while ((ch = fgetc(file_ptr)) != EOF) {
        printf("%c", ch);
    }

    fclose(file_ptr);
}

//////

void searchWordInFile(const char *filePath, const char *searchWord) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return;
    }

    char line[256];
    int lineNumber = 1;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, searchWord) != NULL) {
            char *highlightedLine = malloc(strlen(line) + strlen("\x1b[31m\e[0m") + 1);
            sprintf(highlightedLine, "\x1b[31m%s\e[0m", line); // Adding red color escape codes

            printf("Line Number: %d\n", lineNumber);
            printf("%s", highlightedLine);

            free(highlightedLine);
        }
        lineNumber++;
    }

    fclose(file);
}

