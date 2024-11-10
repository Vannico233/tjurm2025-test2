#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::Mat edge;
    cv::Canny(gray, edge, 100, 200);
    std::vector<std::vector<cv::Point>> ct;
    cv::findContours(edge, ct, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    double max_area = 0;
    std::vector<cv::Point> largest_contour;
    for (const auto& contour : ct) {
        double area = cv::contourArea(contour);
        if (area > max_area) {
            max_area = area;
            largest_contour = contour;
        }
    }
    if (!largest_contour.empty()) {
        cv::Rect bounding_rect = cv::boundingRect(largest_contour);
        cv::RotatedRect min_area_rect = cv::minAreaRect(largest_contour);

        res = std::make_pair(bounding_rect, min_area_rect);
    }

    return res;
}