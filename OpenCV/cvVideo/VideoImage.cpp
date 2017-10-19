#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    char* filename = argc == 2 ? argv[1] : argv[1];

    std :: cout << filename << std :: endl;
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    VideoCapture cap(filename);
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
  		for(int j = 0; j < 10; j++)
  		{

  			for(int i = 0; i < 10; i++)
  			{
  				frame.at<Vec3d>(rand()%(frame.rows - 10) , rand()%(frame.cols)) = Vec3d(rand()%256,rand()%256,rand()%256); 
  			}
  		}
  		imshow("original",frame);
  		char c = (char)waitKey(25);
  		if(c == 27)
  			break;
  	}
  	cap.release();
    destroyAllWindows();
    return 0;
}
