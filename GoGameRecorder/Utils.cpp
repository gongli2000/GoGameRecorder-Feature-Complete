//
//  Utils.cpp
//  GoGameRecorder
//
//  Created by Larry on 7/8/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#include "Utils.h"
int Utils::findPointClosestToOrigin(std::vector<cv::Point> rect)
{
    
    int i =0,retindex=0;
    float maxdist = -1;
    for(auto &p : rect){
        float dist = p.x*p.x+p.y+p.y;
        if(dist > maxdist){
            maxdist = dist;
            retindex=i;
        }
        i++;
    }
    return retindex;
}

int Utils::findNumLiberties(vector< vector<int> > &boardData, vector< cv::Point> &group)
{
    std::set<int> pts;
    for(int i=0;i< group.size();i++){
        cv::Point &p = group[i];
        int x[] = {p.x-1,p.x+1,p.x,p.x};
        int y[] = {p.y,p.y,p.y-1,p.y+1};
        for(int a =0;a<4;a++){
            if(x[a]<0 || x[a] >= boardData.size() || y[a]<0 || y[a] >= boardData.size())continue;
            if(boardData[y[a]][x[a]] == 0){
                int val=y[a]*100+x[a];
                pts.insert(val);
            }
        }
    }
    return (int)pts.size();
}



