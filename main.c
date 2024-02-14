//Basak Su Gedik 21118080072

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Separate numbers
void parseLine(char line[],int numbers[]){
    int count = 0;
    char *token = strtok(line, " ");
    while(token != NULL){
        int number = atoi(token);
        numbers[count] = number;
        token = strtok(NULL, " ");
        count++;

    }
}

//Reading the dimension from first line
int parseFirstLine(char line[]){
    int dimension = 0;
    char *token = strtok(line, " ");
    while (token != NULL){
        dimension = atoi(token);
        token = strtok(NULL, " ");
    }
    return dimension;
}

//Calculating the amount of numbers in an upper triangular matrix excluding zeros
int calculateRequiredAmountOfNumbers(int matrixDimension){
    return(matrixDimension * (matrixDimension + 1)) / 2;
}

int main()
{
    FILE*file;
    char line[1024];
    char firstLine[1024];
    char secondLine[1024];
    char thirdLine[1024];
    int lineCount= 0;
    int matrixDimension = 0;
    int requiredAmountOfNumbers = 0;

    //Reading numbers from input.txt
    file=fopen("input.txt", "r");
    if(file==NULL){
        printf("File can't be found.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL){
        if(lineCount == 0){
            strncpy(firstLine, line, 1024);
            //printf("First line is %s",firstLine);
        }
        if(lineCount == 1){
            strncpy(secondLine, line, 1024);
            //printf("Second line is %s",secondLine);
        }
        if(lineCount == 2){
            strncpy(thirdLine, line, 1024);
            //printf("Third line is %s",thirdLine);
        }
        lineCount++;
    }

    printf("\n");
    fclose(file);

    matrixDimension = parseFirstLine(firstLine);
    requiredAmountOfNumbers = calculateRequiredAmountOfNumbers(matrixDimension);
    int matrixANumbers[requiredAmountOfNumbers];
    int matrixBNumbers[requiredAmountOfNumbers];
    int matrixCNumbers[requiredAmountOfNumbers];
    parseLine(secondLine,matrixANumbers);
    parseLine(thirdLine,matrixBNumbers);

    //Filling arrays with the numbers that is given in the text
    printf("Matrix A Numbers : ");
    for(int i=0; i<requiredAmountOfNumbers;++i){
        printf("%d ",matrixANumbers[i]);
    }
    printf("\n");
    printf("Matrix B Numbers : ");
    for(int j=0; j<requiredAmountOfNumbers;++j){
        printf("%d ",matrixBNumbers[j]);
    }

    //Multiplying two matrices
    int resultIndex = 0;
    int matrixEqualityIndex = 0;
    int indexIncreaseAmount = matrixDimension;

    for(int i = 0; i < matrixDimension; i++){
        for(int j = 0; j < matrixDimension; j++){
            if(j >= i){
                if(j == i){
                    matrixEqualityIndex = resultIndex;
                }
                matrixCNumbers[resultIndex] = 0;
                if(resultIndex == matrixEqualityIndex){//Diagonal calculation (c4 = a4 * b4)
                    matrixCNumbers[resultIndex] = matrixANumbers[matrixEqualityIndex] * matrixBNumbers[matrixEqualityIndex];
                    indexIncreaseAmount --;
                } else {
                    int matrixBIndexValue = resultIndex;
                    for (int k = 0; k <= resultIndex - matrixEqualityIndex; k++){//Calculating how many summation will be needed
                        if(k == 0){//First calculation (c1 += a0*b1 or c2 += a0 * b2)
                            matrixCNumbers[resultIndex] += matrixANumbers[matrixEqualityIndex] * matrixBNumbers[matrixBIndexValue];
                        } else {// Other calculations (c1 += a1 * b4 or c2 += a1 * b5 + a2 * b7)
                            matrixBIndexValue += ((indexIncreaseAmount + 1) - k);
                            matrixCNumbers[resultIndex] += matrixANumbers[matrixEqualityIndex + k] * matrixBNumbers[matrixBIndexValue];
                        }
                    }
                }
                    resultIndex ++;
            }
        }
    }

    //Print Matrix C As a 1d Array
    printf("\n");
    printf("Matrix C Numbers : ");
    for(int a = 0; a < requiredAmountOfNumbers; ++a){
        printf("%d ",matrixCNumbers[a]);
    }
    printf("\n");

    //Print Matrix C as an an upper triangular matrix
    printf("Matrix C in an upper triangular matrix form : \n");
    int printIndex = 0;
    for(int b = 0;b < matrixDimension ; b++){
        for (int c = 0;c < matrixDimension; c++){
            if(c >= b){
                printf("%d\t", matrixCNumbers[printIndex]);
                printIndex ++;
            } else {
                printf("0\t");
            }
        }
        printf("\n");
    }

    return 0;
}

