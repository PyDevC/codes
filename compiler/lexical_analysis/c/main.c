#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FILE_BUFFER_SIZE 1024
#define u32 uint32_t

typedef struct {
    FILE *f;
    u32 line_no;
    u32 col_no;
} FileReader;

static const FileReader nil_reader = {0, 0, 0};

static FILE *OpenIfReadable(const char *filename) {
    return fopen(filename, "r");
}

static u32 ReaderLine(const FileReader *r) {
    return (r ? r : &nil_reader)->line_no;
}

static const char *ReadNextLine(FileReader *r, char *buf, u32 bufsize) {
    FileReader *active = r ? r : (FileReader *)&nil_reader;
    if (!active->f) {
        return NULL;
    }
    return fgets(buf, (int)bufsize, active->f);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    FILE *fp = OpenIfReadable(argv[1]);
    if (!fp) {
        perror("File does not exist or cannot be opened");
        return EXIT_FAILURE;
    }

    FileReader *mainfile = malloc(sizeof(FileReader));
    char *reader = malloc(FILE_BUFFER_SIZE * sizeof(char));

    if (!mainfile || !reader) {
        free(reader);
        free(mainfile);
        fclose(fp);
        return EXIT_FAILURE;
    }

    mainfile->f = fp;
    mainfile->line_no = 0;
    mainfile->col_no = 0;

    while (ReadNextLine(mainfile, reader, FILE_BUFFER_SIZE) != NULL) {
        printf("%s", reader);
        mainfile->line_no++;
    }

    (void)ReaderLine(mainfile);

    fclose(mainfile->f);
    free(reader);
    free(mainfile);
    return EXIT_SUCCESS;
}
