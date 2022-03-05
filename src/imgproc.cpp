//
// Created by yaione on 2/26/2022.
//

#include "imgproc.h"

namespace rm {
    void CalcRatio(cv::Mat &input, cv::Mat &output, cv::Point2f srcPts[4], cv::Point2f dstPts[4]) {
        cv::Mat tmp;
        auto warp = cv::getAffineTransform(srcPts, dstPts);
        cv::warpAffine(input, tmp, warp, tmp.size());
        cv::Rect roi(0, 0, (int) dstPts[1].x, (int) dstPts[1].x);
        tmp(roi).copyTo(output);
    }

    void CalcGamma(cv::Mat &input, cv::Mat &output, float gamma) {
        cv::Mat lookUpTable(1, 256, CV_8U);
        uchar *p = lookUpTable.ptr();
        for (int i = 0; i < 256; ++i) {
            p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        }

        cv::LUT(input, lookUpTable, output);
    }

    void ExtractColor(cv::Mat &input, cv::Mat &output, rm::CampType enemy) {
        cv::Mat hsv;
        cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);

        if (enemy == rm::CAMP_BLUE) {
            // TODO: test blue extraction
        } else if (enemy == rm::CAMP_RED) {
            // TODO: test red extraction
        }

        cv::Mat bin;
        cv::adaptiveThreshold(bin, bin, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25, 5);
    }
}
