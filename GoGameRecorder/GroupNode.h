//
//  GroupNode.h
//  GoGameRecorder
//
//  Created by Larry on 7/13/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#ifndef __GoGameRecorder__GroupNode__
#define __GoGameRecorder__GroupNode__

#include <iostream>
#include <opencv2/opencv.hpp>

class GroupNode{
    public:
    bool isblack;
    int numLiberties;
    std::vector<cv::Point> elements;
    
    GroupNode(bool b ,int n, std::vector<cv::Point> e){
        numLiberties=n;
        elements = e;
        isblack =b;
    }
};

#endif /* defined(__GoGameRecorder__GroupNode__) */
