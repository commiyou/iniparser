// organiser.cc
#include "iniorganiser.h"
#include <string>
#include <cstdlib>
#include "../include/debug.h"
#include "inidata.h"
#include "section.h"
#ifdef DEBUG
#include <iostream>
#endif

using std::string;

namespace parser{

namespace inner {

IniOrganiser::IniOrganiser(IniData& inidata) {
  inidata_ = &inidata;
}
void IniOrganiser::FoundSection(const string& section_name) {
  if (inidata_->ExistSection(section_name)) {
    DEBUG_MSG("found duplicated section: \""<<section_name<<"\",ignored");
    return;
  }
  DEBUG_MSG("found new section: \""<<section_name<<"\"");
  inidata_->AddSection(section_name);
  Section *section = inidata_->GetSection(section_name);
  if (NULL == section) {
    DEBUG_MSG("parser failed: \""<<comment<<"\"");
    exit(1);
  }
  work_section_ = section;
}

void IniOrganiser::FoundComment(const string& comment) {
  DEBUG_MSG("found comment: \""<<comment<<"\"");
}

void IniOrganiser::FoundKeyValue(const string& key, const string& value) {
  if (work_section_) {
    work_section_->AddKeyValue(key, value);
  }
}
} // namespace inner
} // namespace parser
