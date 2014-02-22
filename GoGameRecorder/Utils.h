//
//  Utils.h
//  GoGameRecorder
//
//  Created by Larry on 7/4/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#ifndef __GoGameRecorder__Utils__
#define __GoGameRecorder__Utils__

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;



class Utils{
public:
    static int findPointClosestToOrigin(std::vector<cv::Point> rect);
    static int findNumLiberties(vector< vector<int> > &boardData, vector< cv::Point> &group);
  
};



#endif /* defined(__GoGameRecorder__Utils__) */
