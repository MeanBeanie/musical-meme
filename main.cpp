#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>

uint64_t currentHour() {
  const std::time_t now = std::time(nullptr);
  const std::tm calendar_time = *std::localtime(std::addressof(now));
  return calendar_time.tm_hour;
}

bool bet(int value, int l, int h, bool inclusive = true){
  if(inclusive){
    return l <= value && value <= h;
  }
  else{
    return l < value && value < h;
  }
}

//TODO Work on this more
void field_detection(cv::Mat image){
    for (int y = 0; y < image.rows; y++) {
      for (int x = 0; x < image.cols; x++) {
        cv::Vec3b color_prime = image.at<cv::Vec3b>(cv::Point(x, y));
        if(bet(color_prime[0], 160, 180) && bet(color_prime[1], 200, 220) && bet(color_prime[2], 200, 220)){
          cv::circle(image, cv::Point(x, y), 1, cv::Scalar(120, 0, 110), 2, cv::LINE_8);
          cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x,y));
          if(bet(color[0], 100, 120) && bet(color[1], 200, 220) && bet(color[2], 120, 130)){
            cv::circle(image, cv::Point(x, y), 1, cv::Scalar(140, 140, 0), 2, cv::LINE_8);
          }
        }
      }
    }
}

cv::Mat n_light_detect(cv::Mat image){
  for(int y = 0; y < image.rows; y++){
    for(int x = 0; x < image.cols; x++){
      // Blue = R(28, 40), G(35, 50), B(65, 75)
      // Green = R(60, 106), G(116, 170), B(103, 153)
      cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x, y));
      if(bet(color[0], 60, 80) && bet(color[1], 35, 50) && bet(color[2], 20, 40)){
        cv::circle(image, cv::Point(x, y), 1, cv::Scalar(0, 200, 200), 2, cv::LINE_8);
        for(int i = 1; i <= 50; i++){
          if(x + i < image.cols && y + i < image.rows && x - i > 0 && y - i > 0){
            cv::Vec3b color2 = image.at<cv::Vec3b>(cv::Point(x+i, y+i));
            if(bet(color2[0], 90, 153) && bet(color2[1], 106, 170) && bet(color2[2], 50, 106)){
              cv::circle(image, cv::Point(x+i, y+i), 1, cv::Scalar(200, 0, 200), 2, cv::LINE_8);
            }
            color2 = image.at<cv::Vec3b>(cv::Point(x+i, y-i));
            if(bet(color2[0], 103, 153) && bet(color2[1], 116, 170) && bet(color2[2], 60, 106)){
              cv::circle(image, cv::Point(x+i, y-i), 1, cv::Scalar(200, 0, 200), 2, cv::LINE_8);
            }
            color2 = image.at<cv::Vec3b>(cv::Point(x-i, y+i));
            if(bet(color2[0], 103, 153) && bet(color2[1], 116, 170) && bet(color2[2], 60, 106)){
              cv::circle(image, cv::Point(x-i, y+i), 1, cv::Scalar(200, 0, 200), 2, cv::LINE_8);
            }
            color2 = image.at<cv::Vec3b>(cv::Point(x-i, y-i));
            if(bet(color2[0], 103, 153) && bet(color2[1], 116, 170) && bet(color2[2], 60, 106)){
              cv::circle(image, cv::Point(x-i, y-i), 1, cv::Scalar(200, 0, 200), 2, cv::LINE_8);
            }
          }
        }
      }
    }
  }
  return image;
}

int main() {
  cv::Mat image;

  cv::VideoCapture cap(0);

  while (true) {
    cap >> image;

    image = n_light_detect(image);
    // field_detection(image);

    cv::imshow("Webcam", image);

    auto key = cv::waitKey(25);

    if (key == 113) { // q
      break;
    }
  }

  return 0;
}
