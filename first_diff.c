#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 10 
#define BLUR_THRESH 255 

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

/*

###
#0#
###

*/
void box_blur(unsigned char *buf2, unsigned char *buf3, int len){
    unsigned char *buft;
    buft = (char *)malloc(len * sizeof(char)); // memory for the file being written

    int r,c,i, sum;
    int count = 1; 

    int offset = 56; // HEADER byte count + 1

    int cols = 512;
    int rows = 512;

    int byte_i = offset+1; 

    int tl, tm, tr, cl, cen, cr, bl, bm, br, avg, j;

    int buf_i = 0;
    
    for(i=0;i<=55;i++){
        buf3[i] = buf2[i];
    }
    for(i=offset;i<=len;i=i+3){
        buft[buf_i] = buf2[i];
        buf_i++;
    }
    printf("bytes: %d \r\n", buf_i);

    for(r=0;r<rows;r++){ // row
        //if(r>=1 && r<512){ // avoiding edges for now
            for(c=0;c<cols;c++){ // cols
                //if(c>=1 && c<512){ // avoiding edges for now
            
                    //if(r == 1 && c<4){
                    
                    //printf("\r\nc: %d r: %d \r\n", c, r);

                    if(c==0 && r==0){ // left edge, top row
                        //printf("1 \r\n");
                        tl = buft[((r+1)*512)+(c+1)];
                        tm = buft[((r+1)*512)+(c)];
                        tr = buft[((r+1)*512)+(c+1)];
                        cl = buft[((r)*512)+(c+1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c+1)];
                        bl = buft[((r+1)*512)+(c+1)];
                        bm = buft[((r+1)*512)+(c)];
                        br = buft[((r+1)*512)+(c+1)];
                    } else if(c==511 && r==0){ // right edge, top row
                        //printf("2 \r\n");
                        tl = buft[((r+1)*512)+(c-1)];
                        tm = buft[((r+1)*512)+(c)];
                        tr = buft[((r+1)*512)+(c-1)];
                        cl = buft[((r)*512)+(c-1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c-1)];
                        bl = buft[((r+1)*512)+(c-1)];
                        bm = buft[((r+1)*512)+(c)];
                        br = buft[((r+1)*512)+(c-1)];
                    } else if(c==0) { // left edge
                        //printf("3 \r\n");
                        tl = buft[((r-1)*512)+(c+1)];
                        tm = buft[((r-1)*512)+(c)];
                        tr = buft[((r-1)*512)+(c+1)];
                        cl = buft[((r)*512)+(c+1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c+1)];
                        bl = buft[((r+1)*512)+(c+1)];
                        bm = buft[((r+1)*512)+(c)];
                        br = buft[((r+1)*512)+(c+1)];
                    } else if(c==511){ // right edge
                        //printf("4 \r\n");
                        tl = buft[((r-1)*512)+(c-1)];
                        tm = buft[((r-1)*512)+(c)];
                        tr = buft[((r-1)*512)+(c-1)];
                        cl = buft[((r)*512)+(c-1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c-1)];
                        bl = buft[((r+1)*512)+(c-1)];
                        bm = buft[((r+1)*512)+(c)];
                        br = buft[((r+1)*512)+(c-1)];
                    } else if(c==0 && r==511) { // left edge bottom row
                        //printf("5 \r\n");
                        tl = buft[((r-1)*512)+(c+1)];
                        tm = buft[((r-1)*512)+(c)];
                        tr = buft[((r-1)*512)+(c+1)];
                        cl = buft[((r)*512)+(c+1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c+1)];
                        bl = buft[((r-1)*512)+(c+1)];
                        bm = buft[((r-1)*512)+(c)];
                        br = buft[((r-1)*512)+(c+1)];
                    } else if(c==511 && r==511) { // right edge bottom row
                        //printf("6 \r\n");
                        tl = buft[((r-1)*512)+(c-1)];
                        tm = buft[((r-1)*512)+(c)];
                        tr = buft[((r-1)*512)+(c-1)];
                        cl = buft[((r)*512)+(c-1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c-1)];
                        bl = buft[((r-1)*512)+(c-1)];
                        bm = buft[((r-1)*512)+(c)];
                        br = buft[((r-1)*512)+(c-1)];
                    } else if(c!= 0 && c!=511 && r==0){ // top row
                        //printf("7 \r\n");
                        tl = buft[((r+1)*512)+(c-1)];
                        tm = buft[((r+1)*512)+(c)];
                        tr = buft[((r+1)*512)+(c+1)];
                        cl = buft[((r)*512)+(c-1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c+1)];
                        bl = buft[((r+1)*512)+(c-1)];
                        bm = buft[((r+1)*512)+(c)];
                        br = buft[((r+1)*512)+(c+1)];
                    } else { // top row
                        //printf("8 \r\n");
                        //printf("%d \r\n", ((r-1)*512)+(c-1));
                        tl = buft[((r-1)*512)+(c-1)];
                        tm = buft[((r-1)*512)+(c)];
                        tr = buft[((r-1)*512)+(c+1)];
                        cl = buft[((r)*512)+(c-1)];
                        cen = buft[((r)*512)+(c)];
                        cr = buft[((r)*512)+(c+1)];
                        bl = buft[((r+1)*512)+(c-1)];
                        bm = buft[((r+1)*512)+(c)];
                        br = buft[((r+1)*512)+(c+1)];
                        //printf("tl: %d \r\n", tm);
                    }

                    sum = (tl + tm + tr + cl + cen + cr + bl + bm + br);
                    avg = sum/9;
                    
                    for(j=0;j<3;j++){
                        buf3[byte_i++] = avg;

                        /*if(cen<BLUR_THRESH){
                            printf("\r\n avg: %d \r\n", avg);
                            printf("cen: %d \r\n", cen);
                            printf("row: %d col: %d \r\n", r, c);
                            printf("current: %d \r\n", cen);
                            printf("avg: %d \r\n", avg);
                            printf("buf: %d \r\n", buft[((r)*512)+(c)]);
                                
                        } else {
                            buf3[byte_i++] = cen;
                        }*/
                    }
            }
            
           //printf("\r\n");
        }
   
    printf("count: %d\r\n\r\n",count);
    printf("rows: %d\r\n\r\n", rows);
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

    FILE *writeptr, *blurptr, *greyptr, *readptr;    

    unsigned char *buf1;
    unsigned char *buf2;
    unsigned char *buf3;

    long filelen;
    int i = 0;

    readptr = fopen("blackbuck.bmp", "rb");  // Open file to read in binary mode
    greyptr = fopen("greyscale.bmp", "wb");  // Open file to write in binary mode
    blurptr = fopen("blur.bmp", "wb");  // Open file to write in binary mode
    writeptr = fopen("out.bmp", "wb");  // Open file to write in binary mode

    fseek(readptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(readptr);             // Get the current byte offset in the file
    rewind(readptr);                      // Jump back to the beginning of the file

    buf1 = (char *)malloc(filelen * sizeof(char)); // memory for the file being read
    buf2 = (char *)malloc(filelen * sizeof(char)); // memory for the file being written
    buf3 = (char *)malloc(filelen * sizeof(char)); // memory for the file being written

    fread(buf1, filelen, 1, readptr); // Read in the entire file

    grayscale(buf2, buf1, filelen); // convert to grayscale 

    box_blur(buf2, buf3, filelen);
    fwrite(buf3, filelen, 1, blurptr);  // write blur file

    fwrite(buf2, filelen, 1, greyptr);  // write greyscale file

    first_diff(buf3, filelen); // perform first-diff

    fwrite(buf3, filelen, 1, writeptr); // output first-diff results to file

    fclose(readptr); // Close file being read 
    fclose(writeptr); // Close file being written
    fclose(greyptr); // Close file being written

    return 0;
}
