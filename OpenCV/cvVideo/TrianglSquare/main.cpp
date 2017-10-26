#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
using namespace cv;
using namespace std;
void drawTriangle(const Point2f & p1,const Point2f & p2,const Point2f & p3,Mat & img)
{
    Point2f u = p2 - p1;
    std :: cout << p3;
    //line(img,Point(1,1),Point(100,100),Scalar(0,0,0));
    double t = 0;
    while(t < 1)
    {
        std :: cout << t << std :: endl;
        Point2f tmp = p1 + t*u;
        std :: cout << tmp << std :: endl;
        std :: cout << p3 << " p3 " << std :: endl;
        line(img,p3,tmp,Scalar(0,0,0));
        t += 1.0/(10*norm(u));
    }
}
void drawFigures(int amount, Mat & img)
{
    srand(time(0));
    for(int i = 0; i < amount; i++)
    {
        int left = i*img.cols/amount;
        int right = (i + 1)*img.cols/amount;
        for(int j = 0; j < amount; j++)
        {
            int up = j*(double)img.rows/(double)amount;
            int down = (j + 1)*(double)img.rows/(double)amount;
            Point p1(left + rand()%(right - left),up + rand()%(down - up));
            Point p2(left + rand()%(right - left),up + rand()%(down - up));
            if(rand()%2)
                rectangle(img,p1,p2,Scalar(0,0,0),CV_FILLED);
            else
            {
                p1.x = (p1.x + p2.x)/2;
                p1.y = (p1.y + p2.y)/2;
                circle(img,p1,norm(p1-p2)/2,Scalar(0,0,0),CV_FILLED);
            }
        }
    }
}
void isRectangle(Mat & image,int x, int y,Point & leftUp, Point & leftDown, Point & rightUp, Point & rightDown)
{
    if(x <= leftUp.x && y <= leftUp.y)
    {
        leftUp.x = x;
        leftUp.y = y;
    }
    else if(x <= leftDown.x && y >= leftDown.y)
    {
        leftDown.x = x;
        leftDown.y = y;
    }
    else if(x >= rightUp.x && y <= rightUp.y)
    {
        rightUp.x = x;
        rightUp.y = y;
    }
    else if(x >= rightDown.x && y >= rightDown.y)
    {
        rightDown.x = x;
        rightDown.y = y;
    }
    image.at<uchar>(x,y) = 255;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(image.at<uchar>(x + i , y + j) == 0)
                isRectangle(image,x + i,y + j,leftUp,leftDown,rightUp,rightDown);
        }
    }
}
int main()
{
    Mat image = Mat::zeros(800,800,CV_8UC3);
    image.setTo(cv::Scalar(255,0,128));
    Mat output = image.clone();
    namedWindow("Original");
    drawFigures(4,image);
    imshow("Original",image);
    GaussianBlur( image, output, Size( 51, 51 ), 0, 0 );
    namedWindow("GaussianBlur");
    imshow("GaussianBlur",output);
    Mat gray ;
    cvtColor(image,gray,CV_RGB2GRAY);
    Mat result;
    cv::threshold(gray, result, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    namedWindow("Result otsu");
    imshow("Result otsu",result);
    int counterCircle = 0;
    int counterSquare = 0;
    for(int i = 0; i < result.cols; i++)
    {
        for(int j = 0; j < result.rows; j++)
        {
            if(result.at<uchar>(i,j) == 0)
            {
                Point leftUp(INT32_MAX,INT32_MAX),leftDown(INT32_MAX,0),rightUp(0,INT32_MAX),rightDown(0,0);
                isRectangle(result,i,j,leftUp,leftDown,rightUp,rightDown);
                //std :: cout << rightUp.y - leftUp.y << std :: endl;
                if(rightUp.y - leftUp.y == 0)
                    counterSquare++;
                else
                    counterCircle++;
            }
        }
    }
    std :: cout << counterCircle << " circle" << std :: endl;
    std :: cout << counterSquare << " square " << std :: endl;
    waitKey(0);
    destroyAllWindows();
    return 0;
}
