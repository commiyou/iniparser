// organiser.h

#ifndef PARSER_INIORGANISER_H_
#define PARSER_INIORGANISER_H_

#include <string>

namespace parser {

namespace inner {

class IniData;
class Section;

// 类IniOrganiser用于解析时保存配置数据
class IniOrganiser {

 public:
  IniOrganiser(IniData& inidata);
  //解析时遇到section_name
  void FoundSection(const std::string& section_name);
  //解析时遇到comment
  void FoundComment(const std::string& comment);
  //解析时遇到key & value
  void FoundKeyValue(const std::string& key, const std::string& value);

 private:
  IniData *inidata_;  //保存解析到的数据
  Section *work_section_;
}; // class IniOrganiser

} // namespace inner
} // namespace parser

#endif // PARSER_ABSTRACT_ORGANISER_H_

