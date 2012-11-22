#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier eyes_cascade;
string window_name = "Capture - Eye Direction Deteciont";
RNG rng(12345);

int main( void )
{
  CvCapture* capture;
  Mat frame;

  //-- 1. Load the cascades
  if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

  //-- 2. Read the video stream
  capture = cvCaptureFromCAM( -1 );
  if( capture )
  {
    for(;;)
    {
      frame = cvQueryFrame( capture );

      //-- 3. Apply the classifier to the frame
      if( !frame.empty() )
       { detectAndDisplay( frame ); }
      else
       { printf(" --(!) No captured frame -- Break!"); break; }

      int c = waitKey(10);
      if( (char)c == 'c' ) { break; }

    }
  }
  return 0;
}

void detectAndDisplay( Mat frame )
{
   std::vector<Rect> faces;
   Mat frame_gray;

   cvtColor( frame, frame_gray, CV_BGR2GRAY );
   equalizeHist( frame_gray, frame_gray );
   std::vector<Rect> eyes;
   eyes_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

   for( size_t j = 0; j < eyes.size(); j++ )
   {
     Point eye_center( eyes[j].x + eyes[j].x + eyes[j].width/2, eyes[j].y + eyes[j].y + eyes[j].height/2 );
     int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
     circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
   }
   //-- Show what you got
   imshow( window_name, frame );
}
