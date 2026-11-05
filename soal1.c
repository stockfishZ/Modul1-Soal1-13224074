#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char id[30];
    float temp;
} Sensor;

void check(FILE *file){
    if (file == NULL){
        printf("failed");
        abort();
    }
}

int scan(FILE *file, char target[], Sensor **arr){
    int found = 0;
    int i = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
        char zonename[30];
        char zonecheck[30];
        int j = 0; int k = 0;

        while (line[j] != ',' && line[j] != '\0'){
            zonename[k] = line[j];
            j++; k++;
        }
        zonename[k] = '\0';
        if (line[j] == '\0') continue;

        j++; k = 0;
        while (line[j] != ',' && line[j] != '\0'){
            zonecheck[k] = line[j];
            j++; k++;
        }
        zonecheck[k] = '\0';
        if (line[j] == '\0') continue;

        if (strcmp(zonecheck, target) == 0){
            found = 1;
            *arr = realloc(*arr, (i + 1) * sizeof(Sensor));
            strcpy((*arr)[i].id, zonename);
            (*arr)[i].temp = atof(line + j + 1);
            i++;
        }
    }
    if (found == 0){
        printf("999");
        exit(0);
    }
    return i;
}

void swap(Sensor* xp, Sensor* yp){
    Sensor temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(Sensor arr[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].temp < arr[j + 1].temp ||
               (arr[j].temp == arr[j + 1].temp && strcmp(arr[j].id, arr[j + 1].id) > 0)) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}

void printarray(Sensor arr[], int n){
    float sum = 0;
    for (int i = 0; i < n; i++){
        printf("%s %.2f\n", arr[i].id, arr[i].temp);
        sum += arr[i].temp;
    }
    printf("AVERAGE %.2f\n", sum / n);
}

int main(){
    Sensor *data = NULL;
    char filename[30] = ""; char target[30];
    scanf("%s %s", filename, target);

    FILE *file = fopen(filename, "r");

    check(file);
    int n = scan(file, target, &data);
    fclose(file);
    bubbleSort(data, n);
    printarray(data, n);
    free(data);

    return 0;
}
