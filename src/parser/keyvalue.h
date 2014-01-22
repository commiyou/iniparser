// keyvalue.h

#ifndef PARSER_KEYVALUE_H_
#define PARSER_KEYVALUE_H_

#include <string>
#include "section.h"

namespace parser{

namespace inner {

class IniWriter;

// 类KeyValue用来保存键值对
class KeyValue{
 friend void Section::RenameKey(const std::string& old_name,
                                const std::string& new_name);
 public:
  KeyValue();
  KeyValue(const std::string& key, const std::string& value);
  // 打印自身
  void AcceptWriter(IniWriter& iniwriter) const;
  // getter & setter
  bool isdeleted() const;
  void set_isdeleted(bool isdeleted);
  const std::string* key() const;
  const std::string* value() const;
  void set_value(const std::string& value);

 private:
  // key的值不能随便改变，需要由section类专门函数改变
  void set_key(const std::string& key);
  bool isdeleted_;    // 是否删除标志位
  std::string key_;   // key
  std::string value_; // value
}; // class KeyValue
} // namespace inner
} // namespace parser

#endif // PARSER_KEYVALUE_H_

