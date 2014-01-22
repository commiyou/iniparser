// iniparser.cc

#include "iniparser.h"

//#include <cstdlib>
#include <cstdio>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include "../utf8.h"
#include "../include/debug.h"
#include "iniorganiser.h"

using std::string;
using std::getline;
using std::istream;
using std::back_inserter;

namespace parser {

namespace inner {

IniParser::IniParser() : comment_char_(';'),
                         delimiter_char_('='),
                         error_str_(){
}

void IniParser::set_comment_char(char comment_char) {
  comment_char_ = comment_char;
}

void IniParser::set_delimiter_char(char delimiter_char) {
  delimiter_char_ = delimiter_char;
}

const string* IniParser::error_str() const {
  return &error_str_;
}


enum ParserState {
  STATE_NONE = 0,

  STATE_COMMENT,
  STATE_END_COMMENT,

  STATE_SECTION_START,
  STATE_SECTION_NAME,
  STATE_SECTION_END,
  STATE_END_SECTION,

  STATE_KEY_START,
  STATE_KEY,
  STATE_VALUE_START,
  STATE_VALUE,
  STATE_KEYVALUE_END,
  STATE_END_KEYVALUE,
  STATE_ERROR,
};

bool IniParser::Parse(istream& inputstream, IniOrganiser& organiser) {
#ifdef DEBUG
  int line_cnt = 0;
#endif
  string line;
  DEBUG_MSG("delimiter_char_ "<<delimiter_char_<<" comment_char_ "<<comment_char_);
  while (getline(inputstream, line)) {
#ifdef DEBUG
    ++line_cnt;
#endif
    // 判断是否编码正确
    DEBUG_MSG("Parsing line "<<line_cnt<<": "<<line);
    line+='\n'; // 作为行结束的哨兵，防止utf8相关操作抛出异常
    string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
    if (end_it != line.end()) {
      this->set_error_str("Invalid UTF-8 encoding detected during parsing");
    }

    string::iterator it = line.begin();
    register int ch;
    //跳过行首空白
    while ((it != end_it) && (ch = utf8::next(it, end_it))) {
      if (!IsWhiteSpace(ch)) break;
    }
    if (it == end_it) continue; // 如果此行全为空，跳过
    DEBUG_MSG("the first non-whitespace char of line "<<line_cnt<< " is "<<ch);

    // 解析此行
    if ('[' == ch) { // section开始
      register ParserState current_state = STATE_SECTION_START;
      string section_name = "";

      while (STATE_END_SECTION != current_state) {
        switch (current_state) {
          case STATE_SECTION_START: {
            ch = utf8::peek_next(it, end_it);
            if(IsEOL(ch)) {
              set_error_str("End of line found before section name");
              current_state = STATE_ERROR;
            }
            else if(']' == ch) {
              utf8::next(it, end_it);
              current_state = STATE_SECTION_END;
            }
            else {
              current_state = STATE_SECTION_NAME;
            }
            break;
          }
          case STATE_SECTION_NAME : {
            ch = utf8::peek_next(it, end_it);
            if(IsEOL(ch)) {
              set_error_str("End of line found before section end");
              current_state = STATE_ERROR;
            }
            else if(']' == ch) {
              utf8::next(it, end_it);
              current_state = STATE_SECTION_END;
            }
            else {
              // back_inserter(section_name)用于向section_name中动态增加内容哦
              utf8::append(utf8::next(it, end_it), back_inserter(section_name));
            }
            break;
          }
          case STATE_SECTION_END : {
            StripTrailing(section_name);  // 去除节名后面的空白符
            organiser.FoundSection(section_name);
            current_state = STATE_END_SECTION;
            break;
          }
          case STATE_ERROR : {
            return false;
          }
          default : {
          }
        }
      }
    }
    else if (comment_char_ == ch) { // comment开始
      organiser.FoundComment(line);
    } // end else if (comment_char_ == ch)
    else { // keyvalue开始
      register ParserState current_state = STATE_KEY;
      string key("");
      string value("");
      if (ch == delimiter_char_) {
        //如果遇到的第一个字符是'='
        current_state = STATE_VALUE_START;
      }else {
        //否则遇到的第一个字属于key
        utf8::append(ch, back_inserter(key));
        DEBUG_MSG("the key's first char is "<<ch);
      }

      while (STATE_END_KEYVALUE != current_state) {
        switch (current_state) {
          case STATE_KEY : {
            ch = utf8::peek_next(it, end_it);
            if(IsEOL(ch)) {
              current_state = STATE_KEYVALUE_END;
            }
            else if(delimiter_char_ == ch) {
              utf8::next(it, end_it);
              current_state = STATE_VALUE_START;
            }
            else {
              utf8::append(utf8::next(it, end_it), back_inserter(key));
            }
            break;
          }
          case STATE_VALUE_START : {
            ch = utf8::peek_next(it, end_it);
            if(IsEOL(ch)) {
              set_error_str("End of line  before found value");
              current_state = STATE_ERROR;
            }
            else if (IsWhiteSpace(ch)) { // 跳过value开始前的空白字符
              utf8::next(it, end_it);
            }
            else {
              current_state = STATE_VALUE;
            }
            break;
          }
          case STATE_VALUE : {
            ch = utf8::peek_next(it, end_it);
            if(IsEOL(ch)) {
              current_state = STATE_KEYVALUE_END;
            }
            else {
              utf8::append(utf8::next(it, end_it), back_inserter(value));
            }
            break;
          }
          case STATE_KEYVALUE_END : {
            StripTrailing(key);
            StripTrailing(value);
            organiser.FoundKeyValue(key, value);
            current_state = STATE_END_KEYVALUE;
            break;
          }
          case STATE_ERROR : {
            return false;
          }
          default : {
            assert(false);
          }
        }
      }
    }
  } //while

  return true;
}

void IniParser::set_error_str(const string& error_str) {
  error_str_ = error_str;
}

void IniParser::StripTrailing(string& str) {
  string::reverse_iterator it=str.rbegin();
  for (; it!= str.rend(); ++it) {
    if (!IsWhiteSpace(*it)) break;
  }
  str.assign(str.begin(),it.base());
}

} // namespace inner
} // namespace parser
