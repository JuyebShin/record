#include <opencv/cv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    // Create a VideoCapture object and use camera to capture the video
    VideoCapture cap(0);

    // Check if camera opened successfully
    if(!cap.isOpened())
    {
        cout << "Error opening video stream" << endl;
        return -1;
    }

    // Default resolution of the frame is obtained.The default resolution is system dependent.
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "frame width: " << frame_width << endl;
    cout << "frame height: " << frame_height << endl;

    int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));

    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    VideoWriter video("/home/robit/catkin_ws/src/record/output/output.avi", ex, cap.get(CV_CAP_PROP_FPS), Size(frame_width,frame_height), true);

    if(!video.isOpened())
    {
        cout << "Could not open the output video" << endl;
        return -1;
    }

    while(1)
    {
        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Write the frame into the file 'outcpp.avi'
        video.write(frame);

        // Display the resulting frame
        imshow( "Frame", frame );

        // Press  ESC on keyboard to  exit
        char c = (char)waitKey(1);
        if( c == 27 )
            break;
    }

    // When everything done, release the video capture and write object
    cap.release();
    video.release();

    // Closes all the windows
    destroyAllWindows();
    return 0;
}
