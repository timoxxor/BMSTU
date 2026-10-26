#define NOB_IMPLEMENTATION
#include "nob.h"
#include <unistd.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *path;
} LabTarget;

static const LabTarget known_labs[] = {
    {"lab1.1", "lab1/lab1.1"},
    {"lab1.2", "lab1/lab1.2"},
    {"lab3.1", "lab3/lab3.1"},
    {"lab3.2", "lab3/lab3.2"},
};

static void print_usage(const char *program) {
    nob_log(NOB_INFO, "Usage: %s <target> [run|clean]", program);
    nob_log(NOB_INFO, "       %s run <target>", program);
    nob_log(NOB_INFO, "       %s clean [target]", program);
    nob_log(NOB_INFO, "       %s all", program);
    nob_log(NOB_INFO, "Available targets:");
    for (size_t i = 0; i < NOB_ARRAY_LEN(known_labs); ++i) {
        nob_log(NOB_INFO, "  %-8s (%s)", known_labs[i].name, known_labs[i].path);
    }
}

static const char *resolve_lab_path(const char *name) {
    for (size_t i = 0; i < NOB_ARRAY_LEN(known_labs); ++i) {
        if (strcmp(name, known_labs[i].name) == 0 || strcmp(name, known_labs[i].path) == 0) {
            return known_labs[i].path;
        }
    }

    if (strncmp(name, "lab", 3) == 0) {
        const char *dot = strchr(name, '.');
        if (dot != NULL) {
            int major_len = dot - name;
            char major[64] = {0};
            if (major_len < (int)sizeof(major)) {
                strncpy(major, name, major_len);
                const char *candidate = nob_temp_sprintf("%s/%s", major, name);
                if (nob_get_file_type(candidate) == NOB_FILE_DIRECTORY) {
                    return candidate;
                }
            }
        }
    }

    if (nob_get_file_type(name) == NOB_FILE_DIRECTORY) {
        return name;
    }

    return NULL;
}

static bool build_lab(const char *lab_path) {
    const char *src_dir = nob_temp_sprintf("%s/src", lab_path);
    const char *inc_dir = nob_temp_sprintf("%s/include", lab_path);
    const char *build_dir = nob_temp_sprintf("%s/build", lab_path);
    const char *bin_dir = nob_temp_sprintf("%s/bin", lab_path);
    const char *bin_path = nob_temp_sprintf("%s/main", bin_dir);

    if (nob_get_file_type(src_dir) != NOB_FILE_DIRECTORY) {
        nob_log(NOB_ERROR, "directory '%s' has no src/ directory", lab_path);
        return false;
    }

    if (!nob_mkdir_if_not_exists(build_dir)) return false;
    if (!nob_mkdir_if_not_exists(bin_dir)) return false;

    Nob_File_Paths inc_files = {0};
    Nob_File_Paths all_headers = {0};
    if (nob_get_file_type(inc_dir) == NOB_FILE_DIRECTORY) {
        if (nob_read_entire_dir(inc_dir, &inc_files)) {
            for (size_t i = 0; i < inc_files.count; ++i) {
                const char *h_name = inc_files.items[i];
                if (strcmp(h_name, ".") == 0 || strcmp(h_name, "..") == 0) continue;
                nob_da_append(&all_headers, nob_temp_sprintf("%s/%s", inc_dir, h_name));
            }
        }
    }

    Nob_File_Paths src_files = {0};
    if (!nob_read_entire_dir(src_dir, &src_files)) return false;

    Nob_File_Paths obj_files = {0};
    bool any_rebuilt = false;

    for (size_t i = 0; i < src_files.count; ++i) {
        const char *src_name = src_files.items[i];
        if (!nob_sv_ends_with_cstr(nob_sv_from_cstr(src_name), ".cpp")) continue;

        const char *src_path = nob_temp_sprintf("%s/%s", src_dir, src_name);
        size_t name_len = strlen(src_name);
        const char *obj_path = nob_temp_sprintf("%s/%.*s.o", build_dir, (int)(name_len - 4), src_name);
        nob_da_append(&obj_files, obj_path);

        Nob_File_Paths deps = {0};
        nob_da_append(&deps, src_path);
        for (size_t j = 0; j < all_headers.count; ++j) {
            nob_da_append(&deps, all_headers.items[j]);
        }

        if (nob_needs_rebuild(obj_path, deps.items, deps.count)) {
            Nob_Cmd cmd = {0};
            nob_cmd_append(&cmd, "g++", "-std=c++17", "-Wall", "-Wextra", "-pedantic", "-g", "-O0");
            if (nob_get_file_type(inc_dir) == NOB_FILE_DIRECTORY) {
                nob_cmd_append(&cmd, nob_temp_sprintf("-I%s", inc_dir));
            }
            nob_cmd_append(&cmd, "-c", src_path, "-o", obj_path);
            if (!nob_cmd_run(&cmd)) return false;
            any_rebuilt = true;
        }
    }

    if (obj_files.count == 0) {
        nob_log(NOB_WARNING, "no .cpp files found in %s", src_dir);
        return false;
    }

    if (any_rebuilt || nob_needs_rebuild(bin_path, obj_files.items, obj_files.count)) {
        Nob_Cmd link_cmd = {0};
        nob_cmd_append(&link_cmd, "g++");
        for (size_t i = 0; i < obj_files.count; ++i) {
            nob_cmd_append(&link_cmd, obj_files.items[i]);
        }
        nob_cmd_append(&link_cmd, "-o", bin_path);
        if (!nob_cmd_run(&link_cmd)) return false;
    }

    return true;
}

static bool run_lab(const char *lab_path) {
    if (!build_lab(lab_path)) return false;

    char orig_cwd[1024];
    if (getcwd(orig_cwd, sizeof(orig_cwd)) == NULL) {
        nob_log(NOB_ERROR, "failed to get current working directory");
        return false;
    }

    if (chdir(lab_path) != 0) {
        nob_log(NOB_ERROR, "failed to chdir into '%s'", lab_path);
        return false;
    }

    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, "./bin/main");
    bool result = nob_cmd_run(&cmd);

    if (chdir(orig_cwd) != 0) {
        nob_log(NOB_WARNING, "failed to restore working directory to '%s'", orig_cwd);
    }
    return result;
}

static bool clean_lab(const char *lab_path) {
    nob_log(NOB_INFO, "cleaning %s", lab_path);
    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, "rm", "-rf", nob_temp_sprintf("%s/build", lab_path), nob_temp_sprintf("%s/bin", lab_path));
    return nob_cmd_run(&cmd);
}

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "nob.h");

    const char *program = nob_shift_args(&argc, &argv);

    if (argc <= 0) {
        print_usage(program);
        return 0;
    }

    bool should_run = false;
    bool should_clean = false;
    const char *target = NULL;

    while (argc > 0) {
        const char *arg = nob_shift_args(&argc, &argv);
        if (strcmp(arg, "run") == 0 || strcmp(arg, "-r") == 0 || strcmp(arg, "--run") == 0) {
            should_run = true;
        } else if (strcmp(arg, "clean") == 0) {
            should_clean = true;
        } else if (strcmp(arg, "help") == 0 || strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
            print_usage(program);
            return 0;
        } else {
            if (target == NULL) {
                target = arg;
            } else {
                nob_log(NOB_ERROR, "unexpected argument: %s", arg);
                print_usage(program);
                return 1;
            }
        }
    }

    if (should_clean) {
        if (target == NULL || strcmp(target, "all") == 0) {
            for (size_t i = 0; i < NOB_ARRAY_LEN(known_labs); ++i) {
                if (!clean_lab(known_labs[i].path)) return 1;
            }
            return 0;
        } else {
            const char *path = resolve_lab_path(target);
            if (path == NULL) {
                nob_log(NOB_ERROR, "unknown target '%s'", target);
                return 1;
            }
            return clean_lab(path) ? 0 : 1;
        }
    }

    if (target == NULL) {
        nob_log(NOB_ERROR, "no target specified");
        print_usage(program);
        return 1;
    }

    if (strcmp(target, "all") == 0) {
        for (size_t i = 0; i < NOB_ARRAY_LEN(known_labs); ++i) {
            if (should_run) {
                if (!run_lab(known_labs[i].path)) return 1;
            } else {
                if (!build_lab(known_labs[i].path)) return 1;
            }
        }
        return 0;
    }

    const char *path = resolve_lab_path(target);
    if (path == NULL) {
        nob_log(NOB_ERROR, "unknown target '%s'", target);
        print_usage(program);
        return 1;
    }

    if (should_run) {
        return run_lab(path) ? 0 : 1;
    } else {
        return build_lab(path) ? 0 : 1;
    }
}
