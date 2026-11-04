#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//cek apakah file empty
void check(FILE *file){
    if (file == NULL){
        printf("failed");
        abort();
    }
}

void scan(FILE *file, char target[], char zonearr[][10], float zonetemp[]){
    int found = 0;
    int i = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
        if (strstr(line, target)){
            found = 1;
            char zonename[30];
            int j = 0; int k = 0;

            while (true){
                if (line[j] != ','){
                    zonename[k] = line[j];
                    j++; k++;
                }else{
                    break;
                }
            }

            strcpy(zonearr[i], zonename);
            //printf("ok: %s\n", zonearr[i]);
            
            char zonetemptemp[30];
            float zonetempget;
            int commacounter = 0;
            
            j = 0; k = 0;
            while (true){
                if (line[j] == ','){
                    commacounter++;
                }
                if (commacounter == 2){
                    zonetemptemp[k] = line[j+1];
                    k++;
                }
                if (line[j] == '\0'){
                    break;
                }
                j++;
            }
            
            zonetempget = atof(zonetemptemp);
            //printf("yooi: %.2f\n", zonetempget);
            zonetemp[i] = zonetempget;
        }
    }
    if (found == 0){
        printf("999");
        abort();
    }
}

void swap(float* xp, float* yp){
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(float arr[], int n, char zonearr[][10]){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                char stemp[30];
                strcpy(stemp, zonearr[j]);
                strcpy(zonearr[j], zonearr[j+1]);
                strcpy(zonearr[j+1], stemp);
                swapped = true;
            }else if (arr[j] == arr[j+1]){
                if (strcmp(zonearr[j], zonearr[j+1]) > 0){
                    char stemptemp[30];
                    strcpy(zonearr[j], zonearr[j+1]);
                    strcpy(zonearr[j+1], stemptemp);
                    //printf("%s - ", zonearr[0]);
                }
            }
        }

        if (swapped == false)
            break;
    }
}

void printarray(char zonearr[][10], float zonetemp[]){
    //printf("%s - ", zonearr[0]);
    for (int i = 0;  i < 10/*sizeof(zonearr)/sizeof(zonearr[0])*/; i++){
        //printf("%s - ", zonearr[i]);
        //printf("%.2f\n", zonetemp[i]);
    }
}

int main(){
    char zonearr[10][10];
    float zonetemp[10];
    char filename[30] = ""; char target[30];
    scanf("%s %s", &filename, &target);
    
    FILE *file = fopen(filename, "r");
    
    check(file);
    scan(file, target, zonearr, zonetemp);
    bubbleSort(zonetemp, sizeof(zonetemp)/sizeof(zonetemp[0]), zonearr);
    printarray(zonearr, zonetemp);

    return 0;
}
