#include <stdio.h>
#include <stdbool.h>

//check if the index is within valid range for array
bool isValid(const int arr[],  int length,  int pos) {
    return pos >= 0 && pos < length;
}

//remove element at specified index, shifting remaining elements
void remove_element(int arr[],  int length,  int pos) {
    if (!isValid(arr,  length,  pos)) {
        printf("Error: Invalid index %d\n", pos); //exits if index is invalid
        return;
    }

    for (int i = pos; i < length - 1; i++) { //loops through array
        arr[i] = arr[i + 1]; //shifts each element one position left
    }

    arr[length - 1] = 0; // Set the last element to 0 after shifting
}

//insert an element at the specified index, shifting subsequent elements
void insert_element(int arr[],  int length,  int pos,  int value) {
    if (!isValid(arr,  length,  pos)) {
        printf("Error: Invalid index %d\n", pos); //prints error
        return; //exits if index is invalid
    }

    if (length >= 6) { //ensures there is space in the array
        printf("Error: Array is full.\n");
        return;
    }

    for (int i = length; i > pos; i--) { //shifts elements from the end
        arr[i] = arr[i - 1]; //shifts each element one position
    }

    arr[pos] = value; //inserts new value at the specified index
}

//reshape a 1D array into a 2D array in column-major order
void reshape(const int arr[],  int length,  int nRows,  int nCols,  int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: Array size does not match target dimensions.\n"); //prints error if not
        return; //exits if dimensions are incorrect
    }

    int index = 0; //index for traversing 1D array
    for (int col = 0; col < nCols; col++) { //iterates columns
        for (int row = 0; row < nRows; row++) { //iterates rows
            arr2d[row][col] = arr[index++]; //assigns values from 1D array to 2D
        }
    }
}

// transpose a matrix
void trans_matrix(int nRows,  int nCols,  const int mat[nRows][nCols],  int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

//check if the array contains any duplicate elements
bool found_duplicate(const int arr[], int length) {
    for (int i = 0; i < length - 1; i++) { //iterates each element except last
        for (int j = i + 1; j < length; j++) { //compares last element
            if (arr[i] == arr[j]) { //checks for duplicate
                return true; //returns true if duplicate found
            }
        }
    }
    return false; //returns false if no duplicate found
}

int main() {
    int myArray[6] = {10, 20, 30, 40, 50, 60}; //initializes test array
    int length = 6; //sets size

    //print original array
    printf("Original Array: ");
    for (int i = 0; i < length; i++) printf("%d ", myArray[i]);
    printf("\n"); //prints each element in array

    //test remove_element
    remove_element(myArray, length, 2);
    printf("After removal at index 2: ");
    for (int i = 0; i < length; i++) printf("%d ", myArray[i]);
    printf("\n"); //prints array after removal

    //test insert_element
    insert_element(myArray, length, 2, 25); //inserts 25 at index 2
    printf("After insertion of 25 at index 2: ");
    for (int i = 0; i < length; i++) printf("%d ", myArray[i]);
    printf("\n"); //prints array after insertion

    //test reshape
    int arr1d[] = {1, 2, 3, 4, 5, 6}; //initializes 1D array for reshaping
    int rows = 2, cols = 3; //specifies desired 2D array dimensions
    int arr2d[2][3]; //declares 2D array with specified dimensions
    reshape(arr1d, 6, rows, cols, arr2d); //reshapes array into 2D array
    printf("Reshaped 2D array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    //test transpose_matrix
    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}}; //initializes 2D array
    int transposed[3][2]; //declares 2D array for transposed matrix
    trans_matrix(2, 3, mat, transposed); //transposes matrix
    printf("Transposed matrix:\n");
    for (int i = 0; i < 3; i++) { //prints transposed matrix
        for (int j = 0; j < 2; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }

    //test found_duplicate
    int dup_array[] = {1, 2, 3, 4, 5, 3}; //initializes array with duplicates
    int no_dup_array[] = {1, 2, 3, 4, 5, 6}; //initializes array without duplicates
    printf("Array with duplicates: %s\n", found_duplicate(dup_array, 6) ? "Yes" : "No");
    printf("Array without duplicates: %s\n", found_duplicate(no_dup_array, 6) ? "Yes" : "No");

    return 0; //returns 0 to show successful execution
}
