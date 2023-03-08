CC = g++
NAME = cam_hand_motion_detection
FILES = *.cpp
CFLAGS = -std=c++20 -I/usr/local/include \
-L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_objdetect \
-lopencv_imgcodecs -lopencv_highgui  -lopencv_videoio \
-framework AVFoundation -framework QuartzCore \
-framework CoreMedia -framework Cocoa -framework QTKit

nwarn:
	$(CC) $(FILES) -o $(NAME) $(CFLAGS) -Wall -w

warn:
	$(CC) $(FILES) -o $(NAME) $(CFLAGS)
