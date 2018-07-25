#include "tokens.h"
#include <stdio.h>
#include <string.h>

// pos constructor
tPos::tPos(char* aName,uint32 aAbs,uint32 aLine,uint32 aLineOffs)
{
  // name of the document
  this->mFileName = new char[strlen(aName)+1];
  strcpy(this->mFileName,aName);
  // position parameters
  this->mAbsOffset = aAbs;
  this->mLineId = aLine;
  this->mLineOffset = aLineOffs;
}

// pos destructor
tPos::~tPos()
{
  delete this->mFileName;
}

// token constructor
tTok::tTok(uint32 aID,tPos* aStart,tPos* aEnd)
{ 
  this->mID = aID;
  this->mArea.mStartPos = aStart;
  this->mArea.mEndPos = aEnd;
}
