#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 20 

void first_diff(unsigned char *buf, int len){
    int i, n, n_1, n_diff; 
    for(i = 0;i<len;i++){
        if(i>55){
            n = buf[i];
            n_1 = buf[i+1];  
            n_diff = n_1 - n;
            if(abs(n_diff)>THRESHOLD){

                buf[i-2] = 0x00;
                buf[i-1] = 0x00;
                buf[i] = 0x00;
                //buf[i+1] = 0x80;
            } else {
                buf[i] = 0xFF;
                //buf[i+1] = 0xFF;
                //buf[i+2] = 0xFF;
            }
        }
    }
}

void grayscale(unsigned char *buf2, unsigned char *buf1, int len){
    int i; 
    int ind = 0;    
    int R,G,B;
    int newval = 0;

    for(i=0;i<len;i++){
        buf2[i] = buf1[i];
        if(i<=55){
            // Header parsing here
        } else {
            if(ind == 0){        // red channel
                ind = ind + 1;
                R = buf1[i];
            } else if(ind == 1){ // green channel
                ind = ind + 1;
                G = buf1[i];
            } else if(ind == 2){ // blue channel
                ind = 0;
                B = buf1[i];
                
                //newval = (int)(0.299 * R + 0.587 * G + 0.114 * B); // From Mathworks example

                newval = (R>>2) + (G>>1) + (B>>2); // bitwise division to approximate formula above
                
                buf2[i-3] = newval;
                buf2[i-2] = newval;
                buf2[i-1] = newval;
            }   
        }
    }
}

int main(int argc, char* args[])
{

    FILE *writeptr, *greyptr, *readptr;    

    unsigned char *buf1;
    unsigned char *buf2;
    long filelen;
    int i = 0;

    readptr = fopen("blackbuck.bmp", "rb");  // Open file to read in binary mode
    greyptr = fopen("greyscale.bmp", "wb");  // Open file to write in binary mode
    writeptr = fopen("out.bmp", "wb");  // Open file to write in binary mode

    fseek(readptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(readptr);             // Get the current byte offset in the file
    rewind(readptr);                      // Jump back to the beginning of the file

    buf1 = (char *)malloc(filelen * sizeof(char)); // memory for the file being read
    buf2 = (char *)malloc(filelen * sizeof(char)); // memory for the file being written

    fread(buf1, filelen, 1, readptr); // Read in the entire file

    grayscale(buf2, buf1, filelen); // convert to grayscale 

    fwrite(buf2, filelen, 1, greyptr);  // write greyscale file

    first_diff(buf2, filelen); // perform first-diff

    fwrite(buf2, filelen, 1, writeptr); // output first-diff results to file

    fclose(readptr); // Close file being read 
    fclose(writeptr); // Close file being written
    fclose(greyptr); // Close file being written

    return 0;
}
