#include <iostream>
#include <opencv2/opencv.hpp>

bool colorClamp(cv::Vec3b c, int l, int h){
  return c[0] >= l && c[0] <= h && c[1] >= l && c[1] <= h && c[2] >= l && c[2] <= h;
}

int main() {
  cv::Mat image;

  cv::VideoCapture cap(0);

  while (true) {
    cap >> image;

    for (int y = 0; y < image.rows; y++) {
      for (int x = 0; x < image.cols; x++) {
        cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x,y));
        if(color[0] > color[1] && color[0] > color[2] && color[0] > 50 && color[0] < 70 && color[1] < 40 && color[2] < 50){
          cv::circle(image, cv::Point(x, y), 3, cv::Scalar(255, 128, 0), cv::FILLED, cv::LINE_8);

          for(int i = 1; i <= 1; i++){
            cv::Vec3b color2 = image.at<cv::Vec3b>(cv::Point(x+1,y+1));
          if(color2[0] > 150 && color2[1] > 150 && color2[2] > 150){
            cv::circle(image, cv::Point(x, y), 3, cv::Scalar(0, 255, 50), cv::FILLED, cv::LINE_8);
          }
          color2 = image.at<cv::Vec3b>(cv::Point(x+1,y-1));
          if(color2[0] > 150 && color2[1] > 150 && color2[2] > 150){
            cv::circle(image, cv::Point(x, y), 3, cv::Scalar(0, 255, 50), cv::FILLED, cv::LINE_8);
          }
          color2 = image.at<cv::Vec3b>(cv::Point(x-1,y+1));
          if(color2[0] > 150 && color2[1] > 150 && color2[2] > 150){
            cv::circle(image, cv::Point(x, y), 3, cv::Scalar(0, 255, 50), cv::FILLED, cv::LINE_8);
          }
          color2 = image.at<cv::Vec3b>(cv::Point(x-1,y-1));
          if(color2[0] > 150 && color2[1] > 150 && color2[2] > 150){
            cv::circle(image, cv::Point(x, y), 3, cv::Scalar(0, 255, 50), cv::FILLED, cv::LINE_8);
          }
          }
        }
      }
    }

    cv::imshow("Webcam", image);

    auto key = cv::waitKey(25);

    if (key == 113) { // q
      break;
    }
  }

  return 0;
}
