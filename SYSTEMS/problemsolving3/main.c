#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void close_file(FILE * f) {
    fclose(f);
    f = NULL;
}

FILE * open_file(const char * name, const char * mode) {
    FILE * f;
    if ((f = fopen(name, mode)) == NULL) {
        printf("File open error\nName : %s , Mode : %s\n", name, mode);
        exit(1);
    }
    return f;
}

int comparator(const void * a, const void * b) {
    return *((int *)a) - *((int *)b);
}

void copy_file(char * filesource, char * filedest) {
    FILE * src = open_file(filesource, "r");
    FILE * dest = open_file(filedest, "w");
    int num;
    while((fscanf(src, "%d", &num)) != EOF) {
        fprintf(dest, "%d\n", num);
    }
    close_file(src);
    close_file(dest);
}

void writeToFile(int * arr, char * filename, int len) {
    FILE * f = open_file(filename, "w");
    int i;
    for (i = 0; i < len; i++) {
        fprintf(f, "%d\n", arr[i]);
    }
    close_file(f);
}

void mergeFiles(char * file1, char * file2, char * dest) {
    FILE * f1 = open_file(file1, "r");
    FILE * f2 = open_file(file2, "r");
    FILE * destFile = open_file(dest, "w");
    int eof1, eof2, n1 = -1, n2 = -1;
    while(1) {
        if (n1 == -1) {
            eof1 = fscanf(f1, "%d", &n1);
            if (eof1 == EOF) break;
        }
        if (n2 == -1) {
            eof2 = fscanf(f2, "%d", &n2);
            if (eof2 == EOF) break;
        }

        if (n1 > n2) {
            fprintf(destFile, "%d\n", n2);
            n2 = -1;
        } else {
            fprintf(destFile, "%d\n", n1);
            n1 = -1;
        }
    }

    FILE * restOver = eof1 == EOF ? f2 : f1;

    while(fscanf(restOver, "%d", &n1) != EOF) {
        fprintf(destFile, "%d\n", n1);
    }
    close_file(f1);
    close_file(f2);
    close_file(destFile);
}

void sort_file(char * filename) {
    FILE * f = fopen(filename, "r");
    int max_nums = 15900;
    int * arr = (int *)malloc(sizeof(int) * 15900);
    int i, rounds = 65, fileIndex = 1, eof = 0, merger = 0;
    char filesToWrite[3][9] = {"file1.txt", "file2.txt", "file3.txt"};
    while(1) {
        for (i = 0; i < max_nums && !eof; i++) {
            eof = fscanf(f, "%d", &arr[i]) == EOF ? 1 : 0;
            if (eof) break;
        }
        mergesort(arr, eof ? i : max_nums, sizeof(int), comparator);
        writeToFile(arr, filesToWrite[0], i);
        fileIndex *= -1;
        if (merger == 0) {
            if (eof) {
                copy_file(filesToWrite[0], filesToWrite[2]);
                close_file(f);
                return;
            }
            copy_file(filesToWrite[0], filesToWrite[1]);
            merger = 1;
        } else if (merger == 1){
            mergeFiles(filesToWrite[0], filesToWrite[1], filesToWrite[2]);
            copy_file(filesToWrite[2], filesToWrite[1]);
            merger = 2;
        } else {
            mergeFiles(filesToWrite[0], filesToWrite[1], filesToWrite[2]);
            copy_file(filesToWrite[2], filesToWrite[1]);
        }
        if (eof) {
            break;
        }
    }
    close_file(f);
}

typedef struct sample {
    int a;
    char b[46];
    long long c;
}sample;

void test_file_io() {
    FILE * f = open_file("testit.txt", "w");
    int trans[6] = { 1920409673, 543519849, 543449442, 1701080931, 1767990304, 3045740 };
    fwrite(trans, sizeof(trans), 1, f);
    close_file(f);
}

int main() {
//    sort_file("input.txt");
    test_file_io();
//    printf("%s\n", "I am harsha");
    return 0;
}