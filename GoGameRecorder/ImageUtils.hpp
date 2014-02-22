//
//  ImageUtils.h
//  testopenv
//
//  Created by Larry on 6/29/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#ifndef __testopenv__ImageUtils__
#define __testopenv__ImageUtils__

#include <iostream>
#include <opencv2/opencv.hpp>

#define matdatatype CV_8UC1
#define matdatatypecolor CV_8UC4

void grabframe(cv::VideoCapture *cap, cv::Mat &theframe, int scale=1);
void processFrame1(cv::Mat &grayFrame, cv::Mat &map);
int diffFrames(cv::Mat &image1, cv::Mat &image2, cv::Mat &diff);
void doDilate( int dilation_size , cv::Mat &src, cv::Mat &dst );
void doErode( int erosion_size, cv::Mat &src, cv::Mat &dst );
#endif /* defined(__testopenv__ImageUtils__) */
