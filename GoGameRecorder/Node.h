//
//  Node.h
//  GoGameRecorder
//
//  Created by Larry on 7/1/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

@interface Node : NSObject
{
    @public
    bool isblack;
    int groupNum;
    cv::Point coord;
}

@end
