#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
using namespace cv;
using namespace std;
void kuwaharaFiltr(Mat & frame)
{
    Mat tmp = frame.clone();
    int r = 4;
    for(int x = 0; x < tmp.cols; x++)
    {\
        for(int y = 0; y < tmp.rows; y++)
        {
            //std :: cout << x << " " << y << " : ";
            double mid[4] = {0,0,0,0};
            double dis[4] = {0,0,0,0};
            for(int t = 0; t < 4; t++)
            {
               int x_(x),y_(y);
               if(t == 0)
               {
                   x_ -= r;
                   y_ -= r;
               }
               else if(t == 1)
               {
                   x_ += 1;
                   y_ -= r;
               }
               else if(t == 2)
               {
                   x_ -= r;
                   y_ += 1;
               }
               else if(t == 3)
               {
                   x_++;
                   y_++;
               }
               if(x_ >= 0 && x_ + r < tmp.cols && y_ >= 0 && y_ + r < tmp.rows)
               {
                   //std :: cout << "I am here " << std :: endl;
                    for(int ix = 0; ix < r; ix++)
                    {
                        for(int iy = 0; iy < r; iy++)
                        {
                            mid[t] += tmp.at<uchar>(Point(x_ + ix,y_ + iy));
                        }
                    }
                    mid[t] /= r*r;
                    for(int ix = 0; ix < r; ix++)
                    {
                        for(int iy = 0; iy < r; iy++)
                        {
                            dis[t] += ((double)(tmp.at<uchar>(Point(x_ + ix,y_ + iy))) - mid[t])*((double)(tmp.at<uchar>(Point(x_ + ix,y_ + iy))) - mid[t]);
                        }
                    }
               }
               else
                   dis[t] = DBL_MAX;
            }
            double min;
            int s(0);
            for(int i = 0; i < 4; i++)
            {
                if(i == 0)
                    min = dis[i];
                else
                {
                    if(min > dis[i])
                    {
                        min = dis[i];
                        s = i;
                    }
                }
            }
            frame.at<uchar>(Point(x,y)) = mid[s];
        }
    }
}
int main(int argc, char ** argv)
{
    Mat image = imread(argv[1]);
    Mat gray;
    namedWindow("Original");
    namedWindow("Filtr");
    cvtColor(image,gray,CV_RGB2GRAY);
    imshow("Original",gray);
    kuwaharaFiltr(gray);
    imshow("Filtr",gray);
    char c = waitKey(0);
    destroyAllWindows();
    return 0;
}
