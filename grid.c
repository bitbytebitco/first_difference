#include <stdio.h>
#include <stdlib.h>

#define WIDTH 4
#define HEIGHT 4
#define THRESHOLD 3 


void first_diff_2d(int frame[WIDTH][WIDTH], int output[WIDTH][WIDTH]){
    int i,j,rd,cd;

    for(i=0;i<HEIGHT;i++){
        for(j=0;j<WIDTH;j++){
            //printf("%d ", (frame[i][j] - frame[i][j+1]));

            // row diff
            if((frame[i][j] - frame[i][j+1])> THRESHOLD){
                rd = 1;
            } else {
                rd = 0; 
            }

            // col diff
            if((frame[i][j] - frame[i+1][j]) > THRESHOLD){
                cd = 1; 
            } else {
                cd = 0;
            }
            output[i][j] = (rd||cd) ? 1 : 0;
        }
        //printf("\r\n");
    }
}


void bytes_to_array(int data[], unsigned int byte_count){
    int i, j;


    int target_row = 3;
    int target_col = 2;
    int row = 0;
    int col = 0;

    int frame[HEIGHT][WIDTH] = { 0 };
    int output[HEIGHT][WIDTH] = { 0 };
    
    for(i=0;i<byte_count;i++){
            //printf("%d, %d  ", row, col);
        frame[row][col] = data[i];

        if((i>0) && ((i+1) % WIDTH == 0)){ // Increment row
            row++;
            col = 0;
        } else if(col != WIDTH-1){ // Increment column  
            col++;
        }
    }

    printf("\r\nrows: %d \r\n", row);
    first_diff_2d(frame, output);

    for(i=0;i<HEIGHT;i++){
        for(j=0;j<WIDTH;j++){
            printf("%d ", output[i][j]);
        }
        printf("\r\n");
    }
} 

int main(){
    //int data[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; 
    int data[] = {7,7,7,9,0,7,0,9,0,0,0,9,0,0,0,9}; 
    
    unsigned int n = sizeof(data) / sizeof(data[0]);
    bytes_to_array(data, n);    

    return 0;
}
