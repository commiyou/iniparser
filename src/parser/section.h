// section.h

#ifndef PARSER_SECTION_H_
#define PARSER_SECTION_H_
#include <string>
#include <cstddef>
#include <vector>
#include <map>
#include "inidata.h"

namespace parser{

namespace inner {

class KeyValue;
class IniWriter;

// 类Section用来保存每一节的数据
class Section{
 friend void IniData::RenameSection(const std::string& old_name,
                                    const std::string& new_name);
 public:
  // 构造和解析函数
  Section();
  explicit Section(const std::string& name);
  ~Section();
  // 打印自身及其键值对，若isdeleted_为真，不打印
  void AcceptWriter(IniWriter& iniwriter) const;
  // 本节中键值对数目
  size_t CountKeyValues() const;
  // 根据在节中的顺序取得键的内容，超出范围则返回null
  const std::string* GetKeyAt(size_t index);
  // 根据key取value，若key不存在返回null
  const std::string* GetValue(const std::string& key);
  // 新增keyvalue
  void AddKeyValue(const std::string& key,const std::string& value);
  // 设置与key对应的value
  void SetKeyValue(const std::string& key,const std::string& value);
  // 根据delete_or_not的值设置对应key的删除位
  void SetKeyIsDeleted(const std::string& key, bool isdeleted);
  // 查看对应key是否已删除，仅当key存在且未删除返回true
  bool IsKeyDeleted(const std::string& key);
  // 判断对应key是否存在
  bool ExistKey(const std::string& key);
  // 设置对应key的新名字
  void RenameKey(const std::string& old_name, const std::string& new_name);
  // getter & setter
  const std::string* name() const;
  bool isdeleted() const;
  void set_isdeleted(bool isdeleted);

 private:
  //section的name不可随便改变，需要由inidata专门函数改变
  void set_name(const std::string& name);
  bool isdeleted_;    // 节是否删除标志位
  std::string name_;  // 节名
  std::vector<KeyValue *> keyvalues_;  //按索引保存键值对，无无效数据（即KeyValue *为空)
  std::map<std::string, KeyValue *> keyvalues_map_;  // 用于按key查找键值对，
                                                     // 可能有无效数据
}; // class Section
} // namespace inner
} // namespace parser

#endif // PARSER_SECTION_H_

