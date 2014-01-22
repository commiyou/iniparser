#ifndef INIFILE_H_
#define INIFILE_H_
#include <string>

namespace parser {

namespace inner {
  class IniParser;
  class IniData;
  class IniWriter;
  class Section;
}

class IniFile {
 public:
  IniFile();
  ~IniFile();
  //清空所有数据
  void clear();
  // 加载并解析指定为file_path的ini文件
  bool LoadFile(const std::string &file_path);
  // 加载指定流
  bool LoadStream(std::istream& instream);
  // 保存改动到指定file_path
  bool SaveFile(const std::string& file_path);
  bool SaveStream(std::ostream& outstream);
  //
  // Section相关操作
  //
  size_t CountSections() const;
  const std::string* GetWorkSectionName() const;
  // 根据section在文件中的位置，取得对应section_name,若index超出范围，返回空
  // 注意文件的第一个节默认为“”，其序号为0
  const std::string* GetSectionNameAt(size_t index);
  // 设置work_section_
  void SetWorkSection(const std::string& section_name);
  // 创建新section
  void AddSection(const std::string& section_name);
  // 设置指定section标记位
  void SetSectionIsDeleted(const std::string& section_name, bool isdeleted);
  // 判断section是否删除
  bool IsSectionDeleted(const std::string& section_name);
  // section是否存在
  bool ExistSection(const std::string& section_name);
  // 修改section名字，是section类的友元函数
  void RenameSection(const std::string& old_name, const std::string& new_name);
  //
  // work_section_中KeyValue相关操作
  //
  size_t WorkSectionCountKeyValues() const;
  // 根据在节中的顺序取得键的内容，超出范围则返回null
  const std::string* WorkSectionGetKeyAt(size_t index);
  // 根据key取value，若key不存在返回null
  const std::string* WorkSectionGetValue(const std::string& key);
  // 创建keyvalue
  void WorkSectionAddKeyValue(const std::string& key, const std::string& value);
  // 设置与key对应的value
  void WorkSectionSetKeyValue(const std::string& key, const std::string& value);
  // 根据delete_or_not的值设置对应key的删除位
  void WorkSectionSetKeyIsDeleted(const std::string& key, bool isdeleted);
  // 查看对应key是否已删除，仅当key存在且未删除返回true
  bool WorkSectionIsKeyDeleted(const std::string& key);
  // 判断对应key是否存在
  bool WorkSectionExistKey(const std::string& key);
  // 设置对应key的新名字
  void WorkSectionRenameKey(const std::string& old_name, const std::string& new_name);

  // 获得错误信息
  const std::string* const error_str();
  // 获取当前ini文件名
  std::string* const file_path();

  // getter & setter
  char comment_char() const;
  void set_comment_char(char comment_char);
  char delimiter_char();
  void set_delimiter_char(char delimiter_char);

 private:
  void SetErrorString(const std::string& error_str);
  char comment_char_;
  char delimiter_char_;
  std::string file_path_;
  std::string error_str_;
  parser::inner::IniData *inidata_;
  parser::inner::Section *work_section_;
  parser::inner::IniParser *iniparser_;
  parser::inner::IniWriter *iniwriter_;

}; // class IniFile
} // namespace parser



#endif // INIFILE_H_
