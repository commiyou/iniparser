#include "inifile.h"

#include <iostream>
#include <fstream>
#include <cassert>

#include "include/debug.h"
#include "parser/inidata.h"
#include "parser/iniparser.h"
#include "parser/iniorganiser.h"
#include "parser/iniwriter.h"
#include "parser/section.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using parser::inner::IniData;
using parser::inner::IniParser;
using parser::inner::IniOrganiser;
using parser::inner::IniWriter;

namespace parser {

IniFile::IniFile() : comment_char_(';'),
                     delimiter_char_('='),
                     file_path_(""),
                     error_str_() {
  inidata_ = new IniData();
  work_section_ = inidata_->GetSection("");
  iniparser_ = new IniParser();
  iniwriter_ = new IniWriter();
}

IniFile::~IniFile() {
  delete iniparser_;
  delete inidata_;
  delete iniwriter_;
}


void IniFile::clear() {
  inidata_->clear();
  work_section_ = inidata_->GetSection("");
}

bool IniFile::LoadFile(const string& file_path) {
  DEBUG_MSG("Load inifile from "<<file_path);
  ifstream  istream(file_path.c_str());
  if (istream) {
    bool ret = LoadStream(istream);
    if (ret) {
      file_path_ = file_path;
    }
    istream.close();
    return ret;
  }

  string error_str("Could not load file ");
  error_str+=file_path;
  SetErrorString(error_str);
  return false;
}

bool IniFile::LoadStream(std::istream& instream) {
  iniparser_->set_comment_char(comment_char_);
  iniparser_->set_delimiter_char(delimiter_char_);

  IniData *tmp_inidata = new IniData();
  IniOrganiser organiser(*tmp_inidata);

  if (iniparser_->Parse(instream, organiser)) {
    delete(inidata_);  //释放原有数据
    inidata_ = tmp_inidata;
    SetWorkSection("");
    return true;
  }
  else {
    SetErrorString(*(iniparser_->error_str()));
    return false;
  }
}

bool IniFile::SaveFile(const string& file_path) {
  ofstream ostream(file_path.c_str());
  if (ostream) {
    bool ret = SaveStream(ostream);
    ostream.close();
    return ret;
  }

  string error_str("Could not open file ");
  error_str+=file_path;
  error_str+=" for writing";
  SetErrorString(error_str);
  return false;
}

bool IniFile::SaveStream(std::ostream& outstream) {
  iniwriter_->set_comment_char(comment_char_);
  iniwriter_->set_delimiter_char_(delimiter_char_);
  iniwriter_->set_outputstream(outstream);

  inidata_->AcceptWriter(*iniwriter_);
}

size_t IniFile::CountSections() const {
  return inidata_->CountSections();
}

const string* IniFile::GetWorkSectionName() const {
  return work_section_->name();
}

const string* IniFile::GetSectionNameAt(size_t index) {
  return inidata_->GetSectionNameAt(index);
}

void IniFile::SetWorkSection(const string& section_name) {
  if (inidata_->ExistSection(section_name)) {
    work_section_ = inidata_->GetSection(section_name);
  }
}

void IniFile::AddSection(const string& section_name) {
  if (!inidata_->ExistSection(section_name)) {
    inidata_->AddSection(section_name);
    SetWorkSection(section_name);
  }
}

void IniFile::SetSectionIsDeleted(const string& section_name, bool isdeleted) {
  inidata_->SetSectionIsDeleted(section_name, isdeleted);
}

bool IniFile::IsSectionDeleted(const string& section_name) {
  return inidata_->IsSectionDeleted(section_name);
}

bool IniFile::ExistSection(const string& section_name) {
  return inidata_->ExistSection(section_name);
}

void IniFile::RenameSection(const string& old_name, const string& new_name) {
  inidata_->RenameSection(old_name, new_name);
}

size_t IniFile::WorkSectionCountKeyValues() const {
  return work_section_->CountKeyValues();
}

const string* IniFile::WorkSectionGetKeyAt(size_t index) {
  return work_section_->GetKeyAt(index);
}

const string* IniFile::WorkSectionGetValue(const string& key) {
  return work_section_->GetValue(key);
}

void IniFile::WorkSectionAddKeyValue(const string& key, const string& value) {
  work_section_->AddKeyValue(key, value);
}

void IniFile::WorkSectionSetKeyValue(const string& key, const string& value) {
  work_section_->SetKeyValue(key, value);
}

void IniFile::WorkSectionSetKeyIsDeleted(const string& key, bool isdeleted) {
  work_section_->SetKeyIsDeleted(key, isdeleted);
}

bool IniFile::WorkSectionIsKeyDeleted(const string& key) {
  return work_section_->IsKeyDeleted(key);
}

bool IniFile::WorkSectionExistKey(const string& key) {
  return work_section_->ExistKey(key);
}


void IniFile::WorkSectionRenameKey(const string& old_name, const string& new_name) {
  work_section_->RenameKey(old_name, new_name);
}

const string* const IniFile::error_str() {
  return &error_str_;
}

string* const IniFile::file_path() {
  return &file_path_;
}

char IniFile::comment_char() const {
  return comment_char_;
}

void IniFile::set_comment_char(char comment_char) {
  comment_char_ = comment_char;
}

char IniFile::delimiter_char() {
  return delimiter_char_;
}

void IniFile::set_delimiter_char(char delimiter_char) {
  delimiter_char_ = delimiter_char;
}

void IniFile::SetErrorString(const string& error_str) {
  error_str_ = error_str;
}

} // namespace parser
