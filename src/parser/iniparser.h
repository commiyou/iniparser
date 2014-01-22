#ifndef PARSER_INIPARSER_H_
#define PARSER_INIPARSER_H_

#include <string>
#include <iostream>

namespace parser {

namespace inner {

class IniOrganiser;

// 类IniParser用于解析数据流
class IniParser{
 public:
  IniParser();
  // 设置注释标识符
  void set_comment_char(char comment_char);
  // 设置key value分割符
  void set_delimiter_char(char delimiter_char);
  // 获取出错信息
  const std::string* error_str() const;
  // 解析数据流，并通知IniOrganiser
  bool Parse(std::istream& inputstream, IniOrganiser& organiser);

 private:
  inline bool IsEOL(int ch);
  inline bool IsWhiteSpace(int ch);
  void set_error_str(const std::string& error_str);
  void StripTrailing(std::string& str);
  char comment_char_;
  char delimiter_char_;
  std::string error_str_;

}; // class IniParser

bool IniParser::IsEOL(int ch) {
  return ch == '\n';
}

bool IniParser::IsWhiteSpace(int ch) {
  return ch == ' ' || ch == '\t';
}

} // namespace inner
} // namespace parser

#endif // PARSER_PARSER_H_
