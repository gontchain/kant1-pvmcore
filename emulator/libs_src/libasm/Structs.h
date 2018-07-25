#pragma once

#include <map>
#include <string>
#include <vector>
#include <list>
#include <iostream>
//#include <boost/any.hpp>

using namespace std;
//using namespace boost;

#define OBJ_ECHO 1

struct tMacro
{
	string name;
	vector<string> params;
	string body;

	void clear() { name.clear(); params.clear(); body.clear(); }
	void print()
	{
		#ifdef OBJ_ECHO
		cout << "MACRO: " << name << "(";
		for(size_t i=0; i<params.size(); i++)
		{
			if( i>0 ) cout << ',';
			cout << params[i];
		}
		cout << ")" << endl << "{" << endl;
		cout << body << endl;
		cout << "}" << endl;
		#endif
	}
};

struct tLabel
{
	enum EScope { eDefault, eOwn, eExtern, eUnknown };
	string name;
	int ip;
	EScope scope;

	void clear() { name.clear(); ip=-1; scope=eDefault; }
	void print() 
	{ 
		#ifdef OBJ_ECHO
		cout << "LABEL: " << name << "=" << ip << "(" << scope << ")" << endl; 
		#endif
	}
};

struct tConstant
{
	string name;
	string value;

	void clear() { name.clear(); value.clear(); }
	void print() 
	{ 
		#ifdef OBJ_ECHO
		cout << "CONST: " << name << "=" << value << endl; 
		#endif
	}
};

struct tVariable
{
	string name;
	string type;
	string value;
  unsigned int ArrSize;
//	string addr;
  int ip;
  int scope;

	void clear() { name.clear(); type.clear(); value.clear(); ip = -1; ArrSize = 1;}
	void print() 
	{ 
		#ifdef OBJ_ECHO
		cout << "VAR: " << name << ":" << type << "=" << ip << "[" << value << "]" << endl; 
		#endif
	}
};

struct tInstruction
{
	string body;
  string postfix;
	int expsize;
	vector<string> content;

	void clear() { body.clear(); content.clear(); postfix.clear(); expsize=-1; }
	void print() 
	{ 
		#ifdef OBJ_ECHO
		cout << "INSTRUCTION: {" << body << "}" << "SIZE=" << expsize << endl;
		#endif
	}
};

struct tMacroEx
{
	string name;
	vector<string> params;

	void clear() { name.clear(); params.clear(); }

	void print()
	{
		#ifdef OBJ_ECHO
		cout << "EXPAND MACRO: " << name << "(";
		for(size_t i=0; i<params.size(); i++)
		{
			if( i>0 ) cout << ',';
			cout << params[i];
		}
		cout << ")" << endl;
		#endif
	}
};

struct tMacroParams
{
	string macro_name;
	map<string, string> params;
};

//typedef map<string, any> tIdentMap;
typedef list<tMacroParams> tMacroNesting;
