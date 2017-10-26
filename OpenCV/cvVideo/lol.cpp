#include <iostream> // for standard I/O
#include <string>   // for strings
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program shows how to write video files."                                   << endl
        << "You can extract the R or G or B color channel of the input video."              << endl
        << "Usage:"                                                                         << endl
        << "./video-write inputvideoName [ R | G | B] [Y | N]"                              << endl
        << "------------------------------------------------------------------------------" << endl
        << endl;
}
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
int main(int argc, char *argv[])
{
    // Load input video
    cv::VideoCapture input_cap(argv[1]);
    if (!input_cap.isOpened())
    {
            std::cout << "!!! Input video could not be opened" << std::endl;
            return 0;
    }

    // Setup output video
    cv::VideoWriter output_cap(argv[2],
                   input_cap.get(CV_CAP_PROP_FOURCC),
                   input_cap.get(CV_CAP_PROP_FPS),
                   cv::Size(input_cap.get(CV_CAP_PROP_FRAME_WIDTH),
                   input_cap.get(CV_CAP_PROP_FRAME_HEIGHT)));

    if (!output_cap.isOpened())
    {
            std::cout << "!!! Output video could not be opened" << std::endl;
            return 0;
    }


    // Loop to read from input and write to output
    cv::Mat frame;
    namedWindow("Original");
    while (true)
    {
        Mat tmp;
        if (!input_cap.read(frame))
            break;
        tmp = frame.clone();
        cvtColor(frame,tmp,CV_RGB2GRAY);
        cvtColor(tmp,frame,CV_GRAY2BGR);
        output_cap.write(frame);
    }

    input_cap.release();
    output_cap.release();
}
