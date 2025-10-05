#include <stdio.h>
#include <sys/stat.h>
#include <ftw.h>

#define MAX_FTW_DEPTH 16

static int num_dirs, num_regular;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    switch(typeflag){
        case FTW_F: // file
            num_regular++;
            return 0;
        case FTW_D: // directory
            num_dirs++;
            return 0;
        default:
            return 0;
    }
    return 0;
}

int main(int argc, char** argv) {
    // Check arguments and set things up
    if (argc != 2) {
        printf ("Usage: %s <path>\n", argv[0]);
        printf ("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    ftw(argv[1], callback, MAX_FTW_DEPTH);

    // Print out the results
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}