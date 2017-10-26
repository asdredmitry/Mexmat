#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace cv;
using namespace std;
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
int main(int argc, char* argv[])
{
    char* filename = argc == 2 ? argv[1] : argv[1];
    double matrix[9] = {-1.0, -1.0, -1.0, -1.0, 9.0, -1.0, -1.0, -1.0, -1.0};
    std :: cout << filename << std :: endl;
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    VideoCapture cap(filename);
    std :: cout << cap.get(CV_CAP_PROP_FPS) << std :: endl;;
    cv::VideoWriter output_cap(argv[2],
                   cap.get(CV_CAP_PROP_FOURCC),
                   cap.get(CV_CAP_PROP_FPS)/3,
                   cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH),
                   cap.get(CV_CAP_PROP_FRAME_HEIGHT)));

    if (!output_cap.isOpened())
    {
            std::cout << "!!! Output video could not be opened" << std::endl;
            return 0;
    }
  	if(!cap.isOpened())
  	{
  		std :: cout << "Error opening filestream" << std :: endl;
  		return -1;
  	}
  	while(1)
  	{
  		timespec t;
  		clock_gettime(CLOCK_REALTIME,&t);
  		Mat frame;
  		cap >> frame;
  		if(frame.empty())
  			break;
  		srand(t.tv_nsec);
                /*for(int i = 0; i < 100; i++)
                {
                    for(int j =0; j < 100; j++)
                        //frame.at<Vec3b>((rand()%(frame.rows - 1))*frame.cols + rand()%(frame.cols - 1)) = Vec3b(0,0,0);
                }
                */
                /*Mat image2 = frame.clone();
                for(int y = 0; y < frame.rows; y++)
  		{

                        for(int x = 0; x < frame.cols; x++)
  			{
                                image2.at<Vec3b>(y,x) = mult(matrix,frame,x,y);
  			}
  		}
                */
                output_cap << frame;
                //imshow("original",image2);
                //char c = (char)waitKey(25);
                //if(c == 27)
                //	break;
  	}
  	cap.release();
         output_cap.release();
    destroyAllWindows();
    return 0;
}
