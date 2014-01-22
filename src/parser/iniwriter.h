// iniwriter.h

#ifndef PARSER_INIWRITER_H_
#define PARSER_INIWRITER_H_

#include <string>
#include <iostream>

namespace parser {

namespace inner {

class IniData;
class Section;
class KeyValue;

class IniWriter{

 public:
  IniWriter();
  // visiter
  void VisitData(const IniData& inidata) const;
  void VisitSection(const Section& section) const;
  void VisitKeyValue(const KeyValue& keyvalue) const;
  // setter
  void set_outputstream(std::ostream& outputstream);
  void set_comment_char(char comment_char);
  void set_delimiter_char_(char delimiter_char);

 private:
  char comment_char_;
  char delimiter_char_;
  std::ostream *outputstream_;
}; // class IniWriter

} // namespace inner
} // namespace parser

#endif // PARSER_INIWRITER_H_

