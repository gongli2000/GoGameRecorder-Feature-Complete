//
//  Group.cpp
//  GoGameRecorder
//
//  Created by Larry on 7/8/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//
#include "Constants.h"
#include "Group.h"


void Group::init(){
    blackGroups.clear();
    whiteGroups.clear();
    blackLiberties.clear();
    whiteLiberties.clear();
}

void Group::deletegroup(StoneColor color,int groupnum)
{
    switch(color){
        case StoneColor::BLACK:
            blackLiberties.erase(blackLiberties.begin()+groupnum);
            blackGroups.erase(blackGroups.begin()+groupnum);
            break;
        case StoneColor::WHITE:
            whiteGroups.erase(whiteGroups.begin()+groupnum);
            whiteLiberties.erase(whiteLiberties.begin()+groupnum);
            break;
        default:
            break;
    }
}



int Group::addgroup(StoneColor color, vector<cv::Point> &group,int numlibs){
    int index;
    switch(color){
        case StoneColor::BLACK:
            blackLiberties.push_back(numlibs);
            blackGroups.push_back(group);
            index = blackGroups.size();
            break;
        case StoneColor::WHITE:
            whiteGroups.push_back(group);
            whiteLiberties.push_back(numlibs);
            index=whiteGroups.size();
            break;
        default:
            index=-1;
            break;
    }
    return index;
}

void Group::incLiberties(StoneColor color,int groupnum)
{
    switch(color){
        case StoneColor::BLACK:
                blackLiberties[groupnum]++;
            break;
        case StoneColor::WHITE:
                whiteLiberties[groupnum]++;
            break;
        default:
            break;
    }

}

int Group::decLiberties(StoneColor color,int groupnum)
{
    int deadgroupindex=-1;
    switch(color){
        case StoneColor::BLACK:
            if(blackLiberties[groupnum] > 0){
                blackLiberties[groupnum]--;
                if(blackLiberties[groupnum] == 0){
                    deadgroupindex=groupnum;
                }
            }
            break;
        case StoneColor::WHITE:
            if(whiteLiberties[groupnum] > 0){
                whiteLiberties[groupnum]--;
                if(whiteLiberties[groupnum] == 0){
                    deadgroupindex=groupnum;
                }
            }
            break;
        default:
            break;
    }
    return deadgroupindex;
}




void Group::addpoint2group(StoneColor color, vector<vector<int> > &boardData, cv::Point movept,int groupindex, int mult)
{
    int groupindex2 = groupindex-1;
    switch(color){
        case StoneColor::BLACK:
            boardData[movept.y][movept.x] = mult* groupindex;
            blackGroups[groupindex2].push_back(movept);
            blackLiberties[groupindex2]=Utils::findNumLiberties(boardData,blackGroups[groupindex2]);
            break;
        case StoneColor::WHITE:
            boardData[movept.y][movept.x] = mult* groupindex;
            whiteGroups[groupindex2].push_back(movept);
            whiteLiberties[groupindex2]= Utils::findNumLiberties(boardData,whiteGroups[groupindex2]);
        case StoneColor::BOARD:
            break;
    }
}
void Group::merge( StoneColor color,vector<vector<int> > &boardData,
                 cv::Point p, vector<int> &groups)
{
    vector <cv::Point> mergedGroups;
    int groupnum;
    vector< cv::Point > group;
  
    for(int i =0;i< groups.size();i++)
    {
        switch(color){
            case StoneColor::BLACK:
              
                group = blackGroups[groups[i]-1];
                mergedGroups.insert(mergedGroups.end(), group.begin(),group.end());
                blackGroups.erase(blackGroups.begin() + groups[i]-1 );
                blackLiberties.erase(blackLiberties.begin()+groups[i]-1);
                break;
            case StoneColor::WHITE:
                group = whiteGroups[groups[i]-1];
                mergedGroups.insert(mergedGroups.end(), group.begin(),group.end());
                whiteGroups.erase(whiteGroups.begin() + groups[i]-1 );
                whiteLiberties.erase(whiteLiberties.begin()+ groups[i]-1);
                break;
            default:
                break;
        }
    }
    mergedGroups.push_back(p);
    int mult;
    switch(color) {
        case StoneColor::BLACK:
            blackGroups.push_back(mergedGroups);
            groupnum =  (int)blackGroups.size();
            mult = -1;
            boardData[p.y][p.x] = (-1)* groupnum;
            break;
        case StoneColor::WHITE:
            mult=1;
            whiteGroups.push_back(mergedGroups);
            groupnum =  (int)whiteGroups.size();
            boardData[p.y][p.x] = groupnum;
            break;
        default:
            break;
    }
    
    int numgrouplibs = Utils::findNumLiberties(boardData,mergedGroups);
    switch(color){
        case StoneColor::BLACK:
            blackLiberties.push_back(numgrouplibs);
            break;
        case StoneColor::WHITE:
            whiteLiberties.push_back(numgrouplibs);
            break;
        default:
            break;
    }
    for(int k=0;k< mergedGroups.size();k++){
        cv::Point &p = mergedGroups[k];
        boardData[p.y][p.x]=groupnum*mult;
    }

}