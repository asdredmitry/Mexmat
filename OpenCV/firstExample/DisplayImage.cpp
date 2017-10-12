#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
Vec3b mult(double * matrix, Mat & image,int x,int y)
{
    Vec3b tmp(0,0,0);
    double val1 = 0;
    double val2 = 0;
    double val3 = 0;
    //std :: cout << matrix << std :: endl;
    for(int i = -1; i <= 1; i++)
    {
        //tmp = Vec3b(0,0,0);
        for(int j = -1; j <= 1; j++)
        {
             if(x + i < image.cols && y + j < image.rows && x + i >= 0 && y + j>= 0)
             {
                //tmp += image.at<Vec3b>(y + j,x + i)*matrix[(j + 1)*3 + i + 1];
                 val1 += image.at<Vec3b>(y + j,x + i)[0]*matrix[(j + 1)*3 + i + 1];
                 val2 += image.at<Vec3b>(y + j,x + i)[1]*matrix[(j + 1)*3 + i + 1];
                 val3 += image.at<Vec3b>(y + j,x + i)[2]*matrix[(j + 1)*3 + i + 1];
             }
        }
    }
    if(val1 < 0)
        val1 = 0;
    if(val2 < 0)
        val2 = 0;
    if(val3 < 0)
        val3 = 0;
    if(val3 > 255)
        val3 = 255;
    if(val2 > 255)
        val2 = 255;
    if(val1 > 255)
        val1 = 255;
    tmp[0] = val1;
    tmp[1] = val2;
    tmp[2] = val3;
    return tmp;
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    Mat image2;
    //image2 = image.clone();
    image = imread( argv[1], 1 );
    image2 = image.clone();
    double matrix[9] = {-1.0, -1.0, -1.0, -1.0, 9.0, -1.0, -1.0, -1.0, -1.0};
    std :: cout << matrix << std :: endl;
    for(int x = 0; x < image.cols ; x++)
    {
        for(int y = 0; y < image.rows; y++)
        {
            image2.at<Vec3b>(y,x) = mult(matrix,image,x,y);
        }
    }
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image2);

    waitKey(0);

    return 0;
}
