#ifndef TOKENS_STRUCTS_H
#define TOKENS_STRUCTS_H

#include <datatypes.h>
#include <tInstream.h>

class tTokenType
{
public:
  uint32  mID;      // ID of the tokent
  char*   mName;    // name of the token
};

class tPos
{
public:
  char    *mFileName;
  uint32  mAbsOffset;
  uint32  mLineId;
  uint32  mLineOffset;
  tPos(char* aName,uint32 aAbs,uint32 aLine,uint32 aLineOffs);
  ~tPos();
};

class tTokArea
{
public:
  tPos*  mStartPos; // start pos of the token
  tPos*  mEndPos;   // end pos of the token
}; 
// token class 
class tTok
{
public:
  uint32    mID;         // ID of the token
  char*     mStr;        // string token value
  tTokArea  mArea;       // token position
// class constructor
  tTok(uint32 aID,tPos* aStart,tPos* aEnd);
// 
};

// macros
#define TOKEN(ID,Start,End) new tTok(ID,Start,End) 
#define TOK(ID)  new tTok(ID,NULL,NULL)


#endif

