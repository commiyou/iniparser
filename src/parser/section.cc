// section.cpp

#include "section.h"
#include <string>
#include "keyvalue.h"
#include "iniwriter.h"

using std::string;
using std::vector;
using std::map;

namespace parser{

namespace inner {

Section::Section() : isdeleted_(false), name_() {
}

Section::Section(const string& name) : isdeleted_(false), name_(name) {
}


Section::~Section() {
  for (std::vector<KeyValue *>::iterator it = keyvalues_.begin();
       it != keyvalues_.end(); ++it) {
    delete (*it);
  }
}

void Section::AcceptWriter(IniWriter& iniwriter) const {
  iniwriter.VisitSection(*this);
  if (isdeleted_) return; //若节已删除，不输出节下键值对
  for(vector<KeyValue *>::const_iterator it = keyvalues_.begin();
      it != keyvalues_.end(); ++it) {
    (*it)->AcceptWriter(iniwriter);
  }
}

size_t Section::CountKeyValues() const {
  return keyvalues_.size();
}

const string* Section::GetKeyAt(size_t index){
  if (CountKeyValues() > index) {
    KeyValue *keyvalue = keyvalues_[index];
    return keyvalue->key();
  }
  return NULL;
}

const string* Section::GetValue(const string& key){
  KeyValue *keyvalue = keyvalues_map_[key];
  if (keyvalue) {
    return keyvalue->value();
  }
  return NULL;
}

void Section::AddKeyValue(const string& key, const string& value) {
  KeyValue *keyvalue = keyvalues_map_[key];
  if (!keyvalue) {
    KeyValue *new_keyvalue = new KeyValue(key, value);
    keyvalues_.push_back(new_keyvalue);
    keyvalues_map_[key] = new_keyvalue;
  }
}

void Section::SetKeyValue(const string& key,
                          const string& value) {
  KeyValue *keyvalue = keyvalues_map_[key];
  if (keyvalue) {
    keyvalue->set_value(value);
  }
}

void Section::SetKeyIsDeleted(const string& key, bool isdeleted) {
  KeyValue *keyvalue = keyvalues_map_[key];
  if (keyvalue) {
    keyvalue->set_isdeleted(isdeleted);
  }
}

bool Section::IsKeyDeleted(const string& key) {
  KeyValue *keyvalue = keyvalues_map_[key];
  if (keyvalue) {
    return keyvalue->isdeleted();
  }
  return false;
}


bool Section::ExistKey(const string& key){
  return NULL != keyvalues_map_[key];
}

void Section::RenameKey(const string& old_name, const string& new_name) {
  if (ExistKey(new_name)) {
    // 目标key已经存在
    return;
  }
  map<string, KeyValue *>::iterator it = keyvalues_map_.find(old_name);
  if (it != keyvalues_map_.end()) {
    KeyValue *old_key = it->second;
    keyvalues_map_.erase(it); // 由于其他操作可能会导致map内有多余数据
    if (old_key) {            // 需要判断keyvalue指针是否为空
      old_key->set_key(new_name);
      keyvalues_map_[new_name] = old_key;
    }
  }
}

const string* Section::name() const {
  return &name_;
}


bool Section::isdeleted() const {
  return isdeleted_;
}

void Section::set_isdeleted(bool isdeleted) {
  isdeleted_ = isdeleted;
  for(vector<KeyValue *>::iterator it = keyvalues_.begin();
      it != keyvalues_.end(); ++it) {
      (*it)->set_isdeleted(isdeleted);
  }
}

void Section::set_name(const string& name) {
  name_ = name;
}

} // namespace inner
} // namespace parser
