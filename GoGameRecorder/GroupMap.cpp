//
//  GroupMap.cpp
//  GoGameRecorder
//
//  Created by Larry on 7/13/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#include "GroupMap.h"

#include "Constants.h"



void GroupMap::init(){
    maxindex=0;
    _groups.clear();
}

void GroupMap::deletegroup(int groupnum)
{
    _groups.erase(groupnum);
}


int GroupMap::addgroup(StoneColor color, vector<cv::Point> &group,int numlibs){
    maxindex++;
    bool isblack = StoneColor::BLACK==color;
    int index= isblack?-maxindex:maxindex;
    _groups[index] = new GroupNode(isblack,numlibs,group);
    
    return index;
}

void GroupMap::incLiberties(int groupnum)
{
    GroupNode* g= _groups[groupnum];
    g->numLiberties++;
}

int GroupMap::decLiberties(int groupnum)
{
    int deadgroupindex=-1;
    GroupNode* g = _groups[groupnum];
    if(g->numLiberties > 0){
        g->numLiberties--;
        if(g->numLiberties == 0){
            deadgroupindex = groupnum;
        }
    }
    return deadgroupindex;
}




void GroupMap::addpoint2group(StoneColor color, vector<vector<int> > &boardData, cv::Point movept,int groupindex)
{
  
    boardData[movept.y][movept.x] = groupindex;
    GroupNode* g = _groups[groupindex];
    g->elements.push_back(movept);
    g->numLiberties = Utils::findNumLiberties(boardData,g->elements);
}


void GroupMap::merge( StoneColor color,vector<vector<int> > &boardData,
                  cv::Point p, vector<int> &groups)
{
    vector <cv::Point> mergedGroups;
    
    vector< cv::Point > group;
    
    for(int i =0;i< groups.size();i++)
    {
        GroupNode* g = _groups[groups[i]];
        mergedGroups.insert(mergedGroups.end(), g->elements.begin(),g->elements.end());
        _groups.erase(groups[i]);
    }
    mergedGroups.push_back(p);
    boardData[p.y][p.x]=color==StoneColor::BLACK? -1:1;
    int numlibs = Utils::findNumLiberties(boardData,mergedGroups);
    int groupnum  = this->addgroup(color, mergedGroups, numlibs);

    for(int k=0;k< mergedGroups.size();k++){
        cv::Point &pp = mergedGroups[k];
        boardData[pp.y][pp.x]=groupnum;
    }
 
    
}