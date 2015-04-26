#include "sector.h"

Sector::Sector()
{

}

Sector::~Sector()
{

}

Sector::setXloc(int x){

    xloc =x;
}

Sector::setYloc(int y){
    yloc = y;
}


Sector::setWidthi(int w){
    widthi = w;
}

Sector::setHeighti(int h){
    heighti = h;
}

Sector::setStartAnglei(int sa){
    startAnglei = sa;
}

Sector::setEndAnglei(int ea){
    endAnglei = ea;
}

Sector::setArcCalNumi(int n){
    arcCalNumi = n;
}

Sector::setArcCalWidthi(int w){
    radCalWidthi = w;
}

Sector::setRadCalNumi(int n){
    radCalNumi = n;
}

Sector::setRadCalWidthi(int w){
    radCalWidthi = w;
}


Sector::setArcStaVali(int s){
    arcStaVali = s;
}

Sector::setArcValPerScalei(int p){
    arcValPerScalei = p;
}

Sector::setArcSpaceScalei(int scales){
    arcSpaceScalei = scales;
}


Sector::setRadStaVali(int s){
    radStaVali = s;
}

Sector::setRadValPerScalei(int p){
    radValPerScalei = p;
}

Sector::setRadSpaceScalei(int scales){
    radSpaceScalei = scales;
}


Sector::getXloc( ){
    return xloc;
}

Sector::getYloc( ){
    return yloc;
}


Sector::getWidthi( ){
    return widthi;
}

Sector::getHeighti( ){return heighti;}

Sector::getStartAnglei( ){return startAnglei;}

Sector::getEndAnglei( ){return endAnglei;}

Sector::getArcCalNumi( ){return arcCalNumi;}

Sector::getRadCalWidthi( ){reutrn radCalWidthi;}

Sector::getRadCalNumi( ){return radCalNumi;}

Sector::getRadCalWidthi( ){return radCalWidthi;}


Sector::getArcStaVali(){
    return arcStaVali;
}

Sector::getArcValPerScalei(){
    return arcValPerScalei;
}

Sector::getArcSpaceScalei(){
    return arcSpaceScalei;
}


Sector::getRadStaVali(){
    return radStaVali;
}

Sector::getRadValPerScalei(){
    return radValPerScalei;
}

Sector::getRadSpaceScalei(){
    return radSpaceScalei;
}
