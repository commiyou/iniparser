// inifile.cc
#include "inidata.h"
#include "iniwriter.h"
#include "section.h"

using std::string;
using std::vector;
using std::map;

namespace parser{

namespace inner {

IniData::IniData() {
  Section *work_section = new Section("");
  sections_.push_back(work_section);
  sections_map_[""] = work_section;
}

IniData::~IniData() {
  for (vector<Section *>::iterator it = sections_.begin();
       it != sections_.end(); ++it) {
    delete (*it);
  }
}

void IniData::AcceptWriter(IniWriter& iniwriter) const {
  iniwriter.VisitData(*this);

  for(vector<Section *>::const_iterator it = sections_.begin();
      it != sections_.end(); ++it) {
    (*it)->AcceptWriter(iniwriter);
  }
}

void IniData::clear() {
  for(vector<Section *>::iterator it = sections_.begin();
      it != sections_.end(); ++it) {
    delete (*it);
  }
  sections_.clear();
  sections_map_.clear();
  // 清空后仍需设置个""节
  Section *work_section = new Section("");
  sections_.push_back(work_section);
  sections_map_[""] = work_section;
}

size_t IniData::CountSections() const {
  return sections_.size();
}


const string* IniData::GetSectionNameAt(size_t index) {
  if (CountSections() > index) {
    Section *section = sections_[index];
    return section->name();
  }
  return NULL;
}

Section* IniData::GetSection(const string& section_name) {
  Section *section = sections_map_[section_name];
  return section;
}

void IniData::AddSection(const string& section_name) {
  Section *section = sections_map_[section_name];
  if (!section) {
    Section *new_section = new Section(section_name);
    sections_.push_back(new_section);
    sections_map_[section_name] = new_section;
  }
}

void IniData::SetSectionIsDeleted(const string& section_name, bool isdeleted) {
  Section *section = sections_map_[section_name];
  if (section) {
    section->set_isdeleted(isdeleted);
  }
}

bool IniData::IsSectionDeleted(const string& section_name) {
  Section *section = sections_map_[section_name];
  if (section) {
    return section->isdeleted();
  }
  return false;
}


bool IniData::ExistSection(const string& section_name) {
  return NULL != sections_map_[section_name];
}

void IniData::RenameSection(const string& old_name, const string& new_name) {
  if (ExistSection(new_name)) {
    // 目标section已经存在
    return;
  }
  map<string, Section *>::iterator it = sections_map_.find(old_name);
  if (it != sections_map_.end()) {
    Section *old_section = it->second;
    sections_map_.erase(it); // 由于其他操作可能会导致map内有多余数据
    if (old_section) {            // 需要判断keyvalue指针是否为空
      old_section->set_name(new_name);
      sections_map_[new_name] = old_section;
    }
  }
}

} // namespace inner
} // namespace parser
