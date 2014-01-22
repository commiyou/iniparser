// keyvalue.cc

#include "keyvalue.h"
#include <string>
#include "iniwriter.h"

using std::string;

namespace parser{

namespace inner {

KeyValue::KeyValue() : key_(), value_(), isdeleted_(false) {
}

KeyValue::KeyValue(const string& key, const string& value) : key_(key),
                                                             value_(value),
                                                             isdeleted_(false) {
}

void KeyValue::AcceptWriter(IniWriter& iniwriter) const {
  iniwriter.VisitKeyValue(*this);
}

bool KeyValue::isdeleted() const {
  return isdeleted_;
}

void KeyValue::set_isdeleted(bool isdeleted) {
  isdeleted_ = isdeleted;
}

const string* KeyValue::key() const {
  return &key_;
}

const std::string* KeyValue::value() const {
  return &value_;
}

void KeyValue::set_value(const std::string& value) {
  value_ = value;
}

void KeyValue::set_key(const std::string& key) {
  key_ = key;
}
} // namespace inner
} // namespace parser
