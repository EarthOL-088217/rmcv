//
// Created by yaione on 2/26/2022.
//

#ifndef RMCV_CORE_H
#define RMCV_CORE_H

#include "utils.h"

namespace rm {
    enum CampType {
        CAMP_RED = 0, CAMP_BLUE = 1, CAMP_GUIDELIGHT = 2, CAMP_NEUTRAL = -1
    };

    enum AimMode {
        AIM_COMBAT = 0, AIM_BUFF = 1, AIM_SNIPE = 2
    };

    typedef std::vector<cv::Point> Contour;

    class LightBlob {
    public:
        float angle = 0;                      /// Rotation angle of the light blob (vertical when the angle is 90)
        rm::CampType camp = rm::CAMP_NEUTRAL; /// Camp this light blob belongs to
        cv::Point2f center;                   /// Mass center of the light blob
        cv::Point2f vertices[4];              /// Four vertices around the light blob
        cv::Size2f size;                      /// Width and height of the light blob

        LightBlob() = default;

        explicit LightBlob(cv::RotatedRect box, rm::CampType camp = rm::CAMP_NEUTRAL);
    };

    class Armour {
    public:
        float rank = 0;                          /// A value help in sorting multiple armours
        rm::CampType camp = rm::CAMP_NEUTRAL;    /// Camp this armour belongs to
        cv::Point2f icon[4];                     /// Vertices of icon area
        cv::Point2f vertices[4];                 /// Vertices of armour (square with light blob as side length for better PNP result)

        Armour() = default;

        explicit Armour(std::vector<rm::LightBlob> lightBlobs, float rank = 0, rm::CampType camp = rm::CAMP_NEUTRAL);
    };

    class Package {
    public:
        rm::CampType camp = rm::CAMP_NEUTRAL;  /// Self camp
        rm::AimMode mode = rm::AIM_COMBAT;     /// Aim mode
        unsigned char speed = 0;               /// Bullet speed
        float pitch = 0;                       /// Pitch angle
        cv::Mat frame;
        cv::Mat binary;
        std::vector<rm::Armour> armours;

        Package(rm::CampType camp, rm::AimMode mode, unsigned char speed, float pitch, const cv::Mat &inputFrame,
                const cv::Mat &inputBinary);

        explicit Package(const std::shared_ptr<rm::Package> &input);
    };

}

#endif //RMCV_CORE_H
