#ifndef DECREMENT_PARSER_H
#define DECREMENT_PARSER_H

#include <map>
#include <sstream>
#include <boost/spirit.hpp>
#include <boost/spirit/dynamic.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/any.hpp>
#include <boost/lambda/construct.hpp>
#include "Structs.h"

using namespace std;
using namespace boost;
using namespace boost::spirit;
using namespace boost::lambda;

#define ACT(method) bind(&tDecrValParser::method, ref(self), bind<string>(constructor<string>(), _1, _2) )

struct tDecrValParser : public grammar<tDecrValParser>
{
  template <typename ScannerT>
  struct definition
  {
    typedef rule<ScannerT> RuleT;
    RuleT root, identifier, sep,
          inst_decr_exp,inst_incr_exp,
          digit,hex_val,dig_val,
          instruction, instruction_punct, 
          inst_addr_decr, inst_addr_incr,
          decrementer, inst_decrement;

		RuleT const& start() const { return root; }

    definition(tDecrValParser const& self)
    {
      root = *(instruction - end_p ) >> end_p[ ACT(End) ];
      // Instruction
      instruction = inst_addr_decr[ACT(Instruction)] | instruction_punct[ACT(JustOut)];
      instruction_punct = +(anychar_p - inst_addr_decr);
      // ari -= 100 -> 
      // ari = ari - 100; 
      inst_addr_decr = identifier[ ACT(InstructionContent) ] >>
                       inst_decr_exp[ ACT(ReplaceNegative) ] >>
                       digit[ ACT(NegativeDigit) ];
      // decrement or increment
      inst_decr_exp = str_p("-=") | ch_p('-');
      digit = +(digit_p);
      // Misc
      identifier = lexeme_d[(alpha_p|ch_p('_')) >> *(alpha_p|digit_p|ch_p('_'))];
      sep = ch_p(';');
    }
  };

	// External objects for communication between parsers
	ostream &m_streamOut;
	//tIdentMap &m_mapIdent;

	// Temporary object for local parsing
	mutable tInstruction m_instruction;

  tDecrValParser(ostream &os) : m_streamOut(os)
  { 
  		m_instruction.clear();
 	}

  static string Process(string &strIn)
  {
    stringstream os;
    if( !::parse(strIn.c_str(), tDecrValParser(os),  blank_p).full )
       throw runtime_error("Can't expand special instruction constructions");
     return os.str();
  }

	////////////////////////////////////////////////////////////////////////////////
	// Miscellaneous functions
	////////////////////////////////////////////////////////////////////////////////
    void NegativeDigit(string& str) const
    {
  		ECHO();
      m_instruction.content.push_back("-"+ str);
    }

    void ReplaceNegative(string &str) const 
    { 
  		ECHO();
      // get previouse identifier
      if(str== "-=")
        m_instruction.content.push_back("+=");
      else // str == "-"
        m_instruction.content.push_back("+");
    }
	////////////////////////////////////////////////////////////////////////////////
	// INSTUCTION semantic actions
	////////////////////////////////////////////////////////////////////////////////

    void Instruction(string &str) const 
    { 
		  ECHO();
		  m_instruction.body = str;

		  for(size_t i=0; i<m_instruction.content.size(); i++)
			  m_streamOut << m_instruction.content[i] << " ";
	 		m_instruction.print();
	  	m_instruction.clear();
    }

    void JustOut(string &str) const 
    {
      m_streamOut << str.c_str();
    }

	  void InstructionContent(string &str) const 
    { 
      ECHO();
		  m_instruction.content.push_back(str);
    }

	////////////////////////////////////////////////////////////////////////////////
	// End of stream semantic action
	////////////////////////////////////////////////////////////////////////////////

	void End(string &str) const 
  {
    ECHO();
  }
};


#endif