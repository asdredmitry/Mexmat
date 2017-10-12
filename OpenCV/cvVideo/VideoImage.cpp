#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

IplImage* frame =0;

int main(int argc, char* argv[])
{
    char* filename = argc == 2 ? argv[1] : argv[1];

    printf("[i] file: %s\n", filename);
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    std :: cout <<  " I am here " << std :: endl;
    VideoCapture capture(filename);
    std :: cout <<" and i am here too" << std :: endl;
    while(1){
        std :: cout << " I am here now inside while" << std :: endl;
        capture.read(frame);
        std :: cout << " a little bit lower "<< std :: endl;

        cvShowImage( "original", frame );

        char c = cvWaitKey(33);
        if (c == 27) {
            break;
        }
    }

    //cvReleaseCapture( &capture );
    cvDestroyWindow("original");
    return 0;
}
