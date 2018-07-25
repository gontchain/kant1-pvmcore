#ifndef TOKEN_RULES_H
#define TOKEN_RULES_H

#include "tokens.h"
#include "trees.h"
#include "stack.h"

class tRuleType
{
  virtual void* Rule(tInStream& aStream){return NULL;};
};

template<class vElemType> 
class tState: public tGraphNode<vElemType>
{
protected:
  tRuleType* mRule; // state rule
public: 
  // class constructor
 /* tState(vElemType& aElem,tRule aRule=NULL):tGraphNode(aElem)
  {
    mRule = aRule; // init rule (if any)
  }*/
  // switch to the next state
  virtual tState<vElemType>* GetNextState(vElemType& aElem)
  {
    return (tState<vElemType>*)this->NextNode(aElem);
  } 
  // return 1 if the rule is exist to reduce this state
  inline int IsRule(){ return (tRule!=NULL); }
  // process rule 
  vElemType* Rule(tStack *aStack)
  {
    // assert if rule is called 
    assert(this->mRule!=NULL);
    // convert rule
    return this->Rule(tStack *aStack);
  }
}; 


// state machine 
template<class vTokType,class vStreamType>
class tStateMachine
{
  typedef tState<vTokType> tStateType;
  // initial state 
  tStateType* mInitState; 
  int Process(vStreamType& aStr)
  {
    tStateType st = this->mInitState;
    //  
    while(true)
    {
          
    }
    return 1;
  }// end of the function Processs
};




#if 0
// Rule
//    expression list
int ProcessState(tInStream& aStr)
{
  tState*   state;   // state of the system
  tStack    stack;   // token stack
  tTok*     tok;
 
  while(tok = tokens->GetTok(aStr)) // parsing without prioritization
  {
    state = state->GetState(tok);   
    if(state->IsRule)
    {
      tTok* result = state->Rule(stack);
      if(result!=NULL) // 
      {
        stack.push(result);
        state = InitState->GetState(result);
      }
      else
      {
        state = InitState;
      }
    } // 
  }
}

int ProcessPriority(tInStream& aStr)
{
  tState*   state;   // state of the system
  tStack    stack;   
  tTok*     tok;
  tRule*    cur_rule;
  while((tok = GetTok(aStr))!=NULL) // parsing without prioritization
  {
    state = state->GetState(tok);
    if(state->IsRule()) // if the state have a conversion rule
    {
      if(cur_rule==NULL)
      {   
        cur_rule = state->GetRule(stack);
        state = state->GetOr(cur_rule->TokType);
      }
      else if(cur_rule->priority < state->GetRule())
      {
        // push the rule into a stack
        stack.push(cur_rule);
        // set new rule 
        cur_rule = state->GetRule();
      }
      else // process previouse rule
      {
        cur_rule->Rule(stack);
      }
    }
    else // state has no priority
    {
    
    }
  }
  CONV_LAST();
}
#endif


#endif