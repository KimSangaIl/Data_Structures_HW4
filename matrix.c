#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [Kim Sangil]  [2019038041] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    int** matrix;       //행렬을 저장할 이중 포인터 변수 선언
    
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col\n");  //행이나 열의 값이 0이하일 경우 오류 메시지 출력
        return NULL;    //비정상적인 종료를 뜻하는 값 리턴
    }
    
    matrix = (int **)malloc(sizeof(int*) * row);    //행의 개수 만큼 int형 변수를 저장할 메모리 할당
    for (int i = 0; i < row; i++) matrix[i]=(int*)malloc(sizeof(int) * col);    //각 행에 열의 개수 만큼 int형 변수를 저장할 메모리 할당

    if (matrix == NULL) {
        printf("Memory allocation failed.\n");  //행렬을 저장할 변수에 값이 존재하지 않으면 오류 메시지 출력
        return NULL;    //비정상적인 종료를 뜻하는 값 리턴
    }

    return matrix;  //메모리를 할당한 행렬 변수 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) printf("Check the size of row and col\n");    //행이나 열의 값이 0이하일 경우 오류 메시지 출력

    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++) printf("%d\t", matrix[i][j]);  //행렬의 i-1행 j-1열의 값을 출력
        printf("\n");   //모든 열의 값이 출력되면 줄을 띄워서 행을 구분
    }

    if (matrix == NULL) printf("Memory allocation failed.\n");  //행렬을 저장할 변수에 값이 존재하지 않으면 오류 메시지 출력
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col\n");  //행이나 열의 값이 0이하일 경우 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    for (int i = 0; i < row; i++) free(matrix[i]);  //각 행에 할당한 메모리를 해제
    free(matrix);   //행렬에 할당한 메모리를 해제

    return 1;   //정상적인 종료를 뜻하는 값 리턴
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col\n");  //행이나 열의 값이 0이하일 경우 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) matrix[i][j] = rand() % 20;   //행렬의 i-1행 j-1열의 값을 0 ~ 19 사이의 난수로 초기화
    }

    if (matrix == NULL) {
        printf("Memory allocation failed.\n");  //행렬을 저장할 변수에 값이 존재하지 않으면 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    return 1;   //정상적인 종료를 뜻하는 값 리턴
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** add_matrix = create_matrix(row, col); //행렬의 합을 저장할 이중 포인터 변수를 선언하고 행열을 생성하는 함수를 호출하여 값을 초기화

    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col\n");  //행이나 열의 값이 0이하일 경우 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) add_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];   //행렬의 합을 저장하는 변수의 i-1행 j-1열의 값을 matrix_a i-1행 j-1열과 matrix_b i-1행 j-1열을 더한 값으로 초기화
    }

    if (matrix_a == NULL || matrix_b == NULL) {
        printf("Memory allocation failed.\n");  //행렬을 저장할 변수에 값이 존재하지 않으면 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    print_matrix(add_matrix, row, col); //행렬을 출력하는 함수를 호출해 행렬의 합을 출력
    free_matrix(add_matrix, row, col);  //행렬에 할당된 메모리를 해제하는 함수를 호출해 행렬의 합이 저장된 변수의 메모리를 해제
    return 1;   //정상적인 종료를 뜻하는 값 리턴
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** sub_matrix = create_matrix(row, col); //행렬의 차를 저장할 이중 포인터 변수를 선언하고 행열을 생성하는 함수를 호출하여 값을 초기화

    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col\n");  //행이나 열의 값이 0이하일 경우 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) sub_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j];   //행렬의 차를 저장하는 변수의 i-1행 j-1열의 값을 matrix_a i-1행 j-1열을 matrix_b i-1행 j-1열로 뺀 값으로 초기화
    }

    if (matrix_a == NULL || matrix_b == NULL) {
        printf("Memory allocation failed.\n");  //행렬을 저장할 변수에 값이 존재하지 않으면 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    print_matrix(sub_matrix, row, col); //행렬을 출력하는 함수를 호출해 행렬의 차를 출력
    free_matrix(sub_matrix, row, col);  //행렬에 할당된 메모리를 해제하는 함수를 호출해 행렬의 차가 저장된 변수의 메모리를 해제
    return 1;   //정상적인 종료를 뜻하는 값 리턴
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col\n");  //행이나 열의 값이 0이하일 경우 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) matrix_t[i][j] = matrix[j][i];    //matrix_t i-1행 j-1열의 값을 matrix j-1행 i-1열값으로 초기화
    }

    if (matrix == NULL || matrix_t == NULL) {
        printf("Memory allocation failed.\n");  //행렬을 저장할 변수에 값이 존재하지 않으면 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    return 1;   //정상적인 종료를 뜻하는 값 리턴
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** mul_matrix = create_matrix(row, row); //행렬의 곱을 저장할 이중 포인터 변수를 선언하고 행열을 생성하는 함수를 호출하여 값을 초기화

    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col\n");  //행이나 열의 값이 0이하일 경우 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            int temp = 0;   //임시 값을 저장할 변수 선언 및 초기화
            for (int k = 0; k < col; k++) temp += matrix_a[i][k] * matrix_t[k][j];  //matrix_a i-1행 k-1열과 matrix_t k-1행 j-1열의 곱한 값을 반복해서 더한 후 temp에 저장
            mul_matrix[i][j] = temp;    //행렬의 곱을 저장하는 변수의 i-1행 j-1열의 값을 temp값으로 초기화
        }
    }

    if (matrix_t == NULL || mul_matrix == NULL) {
        printf("Memory allocation failed.\n");  //행렬을 저장할 변수에 값이 존재하지 않으면 오류 메시지 출력
        return -1;  //비정상적인 종료를 뜻하는 값 리턴
    }

    print_matrix(mul_matrix, row, row); //행렬을 출력하는 함수를 호출해 행렬의 곱을 출력
    free_matrix(mul_matrix, row, col);  //행렬에 할당된 메모리를 해제하는 함수를 호출해 행렬의 곱이 저장된 변수의 메모리를 해제
    return 1;   //정상적인 종료를 뜻하는 값 리턴
}

