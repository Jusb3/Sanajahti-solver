#include "ocr.hpp"
#include <QtDebug>
#include <iostream>
#include <cmath>

OCR::OCR(QString path)
{
    img.load(path);
    matrix.resize((unsigned long)img.width());
    for ( int i = 0 ; i < img.width() ; i++ )
       matrix[i].resize((unsigned long)img.height());
    findDots();
    getGridSize();
}

void OCR::findDots()
{
    std::pair<std::pair<int,int>,std::pair<int,int>> temp;
    for(int a=0;a<img.width();a++)
        for(int b=0;b<img.height();b++){
            QColor col(img.pixel(a,b));
            if(dot_color==col){
                temp=track_dot(a,b);
                dot_coordinates.push_back(std::make_pair((temp.first.first+temp.second.first)/2,(temp.first.second+temp.second.second)/2));
            }
        }
}

std::string OCR::identifyLetter(int x, int y)
{

    std::pair<int,int> best=std::make_pair(0,0);
    int temp;
    std::pair<std::pair<int,int>,std::pair<int,int>> rect =std::make_pair(std::make_pair(-1,-1),std::make_pair(-1,-1));
    int zero_x=dot_coordinates.at(0).first+x*grid_size;
    int zero_y=dot_coordinates.at(0).second+y*grid_size;
    for(int a=0;a<grid_size;a++)
        for(int b=0;b<grid_size;b++){
            QColor col(img.pixel(a+zero_x,b+zero_y));
            if(col==text_color){
                if(rect.first.first==-1)
                    rect=std::make_pair(std::make_pair(a+zero_x,b+zero_y),std::make_pair(a+zero_x,b+zero_y));
                else
                    rect= merge(rect,a+zero_x,b+zero_y);
                matrix[a+zero_x][b+zero_y]=1;
            }
        }
    for(unsigned a=0;a<letters.size();a++){
        temp = countMatches(rect,a);
        if(temp>best.first)
            best=std::make_pair(temp,a);
    }
    if(best.second<26)
        return std::string(1,(char)('A'+best.second));
    else if(best.second==26)
        return "Å";
    else if(best.second==27)
        return "Ä";
    else
        return "Ö";
}

int OCR::countMatches(std::pair<std::pair<int,int>,std::pair<int,int>> rect, int index)
{
    int width=rect.second.first-rect.first.first+1;
    int height=rect.second.second-rect.first.second+1;
    int count = 0;
       for(int a=0;a<height;a++){
           for(int b=0;b<width;b++){
            if(matrix[rect.first.first+b][a+rect.first.second]==letters[index][a*letters[index].size()/height][b*letters[index][0].size()/width])
                count++;
        }
    }
    return count;
}

void OCR::getGridSize()
{
    int dist=0;
    int size=0;
    for(std::pair<int,int>& obj : dot_coordinates)
        for(auto obj2 : dot_coordinates){
            dist=(int)std::sqrt((obj.first-obj2.first)*(obj.first-obj2.first)+(obj.second-obj2.second)*(obj.second-obj2.second));
            if((dist<size || size==0)&&dist!=0)
                size=dist;
        }
    grid_size=size;

}

std::pair<std::pair<int,int>,std::pair<int,int>> OCR::track_dot(int x,int y)
{
    img.setPixel(x,y,qRgb(0,255,0));
    std::pair<std::pair<int,int>,std::pair<int,int>> rect;
    rect.first= std::make_pair(x,y);
    rect.second= std::make_pair(x,y);
    for(int a=-1;a<=1;a++)
        for(int b=-1;b<=1;b++)
            if((a==0||b==0)&&a!=b){
                QColor col(img.pixel(a+x,b+y));
                if(col==dot_color)
                    rect=merge(rect,track_dot(x+a,y+b));
            }
    return rect;
}

std::pair<std::pair<int,int>,std::pair<int,int> > OCR::merge(std::pair<std::pair<int,int>,std::pair<int,int> > a, int x, int y)
{
    if(x < a.first.first)
        a.first.first = x;
    if(y < a.first.second)
        a.first.second = y;
    if(x > a.second.first)
        a.second.first = x;
    if(y > a.second.second)
        a.second.second = y;
    return a;
}

std::pair<std::pair<int,int>,std::pair<int,int> > OCR::merge(std::pair<std::pair<int,int>,std::pair<int,int> > a, std::pair<std::pair<int,int>,std::pair<int,int> > b)
{
    if(b.first.first < a.first.first)
        a.first.first = b.first.first;
    if(b.first.second < a.first.second)
        a.first.second = b.first.second;
    if(b.second.first > a.second.first)
        a.second.first = b.second.first;
    if(b.second.second > a.second.second)
        a.second.second = b.second.second;
    return a;
}
