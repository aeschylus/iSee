CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

object_detection:
	g++ $(CFLAGS) $(LIBS) objectDetection.cpp -g -I /usr/local/include/opencv2 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

% : %.cpp
	        g++ $(CFLAGS) $(LIBS) -o $@ $<
					
