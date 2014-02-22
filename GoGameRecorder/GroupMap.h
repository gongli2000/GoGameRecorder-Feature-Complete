//
//  GroupMap.h
//  GoGameRecorder
//
//  Created by Larry on 7/13/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#ifndef __GoGameRecorder__GroupMap__
#define __GoGameRecorder__GroupMap__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"
#include "Constants.h"
#include "GroupNode.h"

using namespace std;


class GroupMap{
    
public:
    int maxindex;
    map<int,GroupNode*> _groups;
    void init();
    int addgroup(StoneColor color,vector<cv::Point>  &group,int numlibs);
    void deletegroup(int groupnum);
    void merge( StoneColor color,vector<vector<int> > &boardData,cv::Point p, vector<int> &groups);
    void incLiberties( int groupnum);
    int decLiberties(int groupnum);
    void addpoint2group(StoneColor color, vector<vector<int> > &boardData, cv::Point movept,int groupindex);
};


#endif /* defined(__GoGameRecorder__GroupMap__) */
