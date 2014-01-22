// inidata.h

#ifndef PARSER_INIDATA_H_
#define PARSER_INIDATA_H_

#include <string>
#include <vector>
#include <map>

namespace parser{

namespace inner {

class Section;
class IniWriter;

// 类IniData用于保存解析的整个文件数据
class IniData {
 public:
  //构造 & 解析函数
  IniData();
  ~IniData();
  // 打印自身
  void AcceptWriter(IniWriter& iniwriter) const;
  // 清空数据
  void clear();
  // 文件中section数目
  size_t CountSections() const;
  //Section* GetWorkSection() const;
  //const std::string* GetWorkSectionName() const;
  // 根据section在文件中的位置，取得对应section_name,若index超出范围，返回空
  // 注意文件的第一个节默认为“”，其序号为0
  const std::string* GetSectionNameAt(size_t index);
  Section* GetSection(const std::string& section_name);

  // 设置work_section，若should_create为真且section不存在，创建之
  //void SetSection(const std::string& section_name, bool should_create);
  void AddSection(const std::string& section_name);
  // 设置指定section标记位
  void SetSectionIsDeleted(const std::string& section_name, bool isdeleted);
  // 判断section是否删除
  bool IsSectionDeleted(const std::string& section_name);
  // section是否存在
  bool ExistSection(const std::string& section_name);
  // 修改section名字，是section类的友元函数
  void RenameSection(const std::string& old_name, const std::string& new_name);

 private:
  //Section *work_section_; // 当前section
  std::vector<Section*> sections_; // 按在文件中位置排序的section，第一节为“”，
                                   // 无无效数据(即section *为null)
  std::map<std::string, Section*> sections_map_; //根据section_name取得相应section，
                                                 //可能有无效数据
}; // class IniData
}  //namespace inner
} // namespace parser

#endif // PARSER_INIDATA_H_

