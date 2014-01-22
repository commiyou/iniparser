#include "menu.h"
#include <iostream>
#include <cstdlib>
#include <boost/iterator/iterator_concepts.hpp>
#include "inifile.h"
#include "include/debug.h"

using std::cout;
using std::cerr;
using std::endl;
using std::exit;
using std::string;
using parser::IniFile;

namespace parser {

void Menu::ProcPrinHelp(IniFile& inifile) {
  cout<<"\nHelp:";

  cout<<"\n  Load Save & Exit"<<endl;
  cout<<"    "<<menu_load_file<<"\tload a ini file"<<endl;
  cout<<"    "<<menu_write_data<<"\twrite data to a file"<<endl;
  cout<<"    "<<menu_quit<<"\tquit without saving changes"<<endl;
  cout<<"    "<<menu_clear_data<<"\tclear all current data"<<endl;

  cout<<"\n  Sections Operations"<<endl;
  cout<<"    "<<menu_print_sections<<"\tprint the sections"<<endl;
  cout<<"    "<<menu_select_work<<"\tselect one section as the work section"<<endl;
  cout<<"    "<<menu_add_section<<"\tadd section and seclect it as the work section"<<endl;
  cout<<"    "<<menu_delete_section<<"\tdelete section by index"<<endl;
  cout<<"    "<<menu_undelete_section<<"\tundelete section by index"<<endl;
  cout<<"    "<<menu_rename_work<<"\trename work section"<<endl;

  cout<<"\n  Key & Value Operations"<<endl;
  cout<<"    "<<menu_print_keyvalues<<"\tprint all key & values of work section"<<endl;
  cout<<"    "<<menu_add_keyvalue<<"\tadd key & value into work section"<<endl;
  cout<<"    "<<menu_delete_keyvalue<<"\tdelete key & value in work section"<<endl;
  cout<<"    "<<menu_undelete_keyvalue<<"\tundelete key & value in work section"<<endl;
  cout<<"    "<<menu_rename_key<<"\trename key by index in work section"<<endl;
  cout<<"    "<<menu_modify_value<<"\tmodify value by key in work section"<<endl;

  cout<<"\n  Others"<<endl;
  cout<<"    "<<menu_print_help<<"\tprint this menu"<<endl;
}

void Menu::ProcLoadFile(IniFile& inifile) {
  string reply;
  if (*inifile.file_path() != "") {
    string warn("Already load file ");
    warn+=*inifile.file_path();
    warn+=".\nReally want to reload? (current data will lost): ";
    GetUserReply(warn, reply);
    if (!ReplyIsYes(reply[0])) {
      return;
    }
  }
  //加载文件
  static string promt("Load inifile from (default default.ini): ");
  GetUserReply(promt,reply);
  if (reply[0] == ' ') {
    reply = "default.ini";
  }
  DEBUG_MSG("loading file from "<<reply);
  if (!inifile.LoadFile(reply)) {
    cerr<<*inifile.error_str()<<endl;
  }
}

void Menu::ProcWriteData(IniFile& inifile) {
  DEBUG_MSG("proc write file");
  string reply;
  static string prompt("write data to (default the current file if have been loaded, or else default.ini) ");
  GetUserReply(prompt, reply);
  if (reply[0] == ' ') {
    reply = *inifile.file_path();
    if (reply == "") {
      reply = "default.ini";
    }
  }
  DEBUG_MSG("writting data to file "<<reply);
  if (!inifile.SaveFile(reply)) {
    cerr<<*inifile.error_str()<<endl;
  }
}

void Menu::ProcClearData(IniFile& inifile) {
  DEBUG_MSG("proc clear data");
  inifile.clear();
}

void Menu::ProcSelectWorkSection(IniFile& inifile) {
  DEBUG_MSG("proc select work");
  string reply;
  static string promt("section index (default current work section): ");
  GetUserReply(promt, reply);
  if (reply[0] != ' ') {
    DEBUG_MSG("select work: "<<reply);
    int index = atoi(reply.c_str());
    const string *section_name = inifile.GetSectionNameAt(index);
    if (section_name) {
      inifile.SetWorkSection(*section_name);
    }
    else {
      cerr<<"invalid input"<<endl;
    }
  }
}

void Menu::ProcPrintSections(IniFile& inifile) {
  DEBUG_MSG("proc print sections");
  size_t size = inifile.CountSections();
  cout<<"Current File: "<<*inifile.file_path()<<endl;
  cout<<"Work Section: "<<*inifile.GetWorkSectionName()<<endl<<endl;
  cout<<"index\tsection (the ones marked by * are deleted)"<<endl;
  for (int i = 0; i < size; i++){
    // 已保证inifile的两个函数不会返回错误
    const string *section_name = inifile.GetSectionNameAt(i);
    bool isdeleted = inifile.IsSectionDeleted(*section_name);
    cout<<i<<"\t["<<*section_name<<(isdeleted?"] [*]":"]")<<endl;
  }
}

void Menu::ProcAddSection(IniFile& inifile) {
  DEBUG_MSG("proc add section");
  string reply;
  static string promt("section name: ");
  GetUserReply(promt, reply);
  if (reply[0] != ' ' && !inifile.ExistSection(reply)) {
    DEBUG_MSG("add section: "<<reply);
    inifile.AddSection(reply);
  }
}

void Menu::ProcDeleteSection(IniFile& inifile) {
  DEBUG_MSG("proc delete section");
  string reply;
  static string promt("section index (default no action): ");
  GetUserReply(promt, reply);
  bool ret(true);
  if (reply[0] != ' ') {
    DEBUG_MSG("delete section index: "<<reply);
    int index = atoi(reply.c_str());
    const string *section_name = inifile.GetSectionNameAt(index);
    if (section_name) {
      inifile.SetSectionIsDeleted(*section_name, true);
    }
    else {
      cerr<<"invalid input"<<endl;
    }
  }
}

void Menu::ProcUndeleteSection(IniFile& inifile) {
  DEBUG_MSG("proc recover section");
  string reply;
  static string promt("section index (default no action): ");
  GetUserReply(promt, reply);
  if (reply[0] != ' ') {
    DEBUG_MSG("recover section index: "<<reply);
    int index = atoi(reply.c_str());
    const string *section_name = inifile.GetSectionNameAt(index);
    if (section_name) {
      inifile.SetSectionIsDeleted(*section_name, false);
    }
    else {
      cerr<<"invalid input"<<endl;
    }
  }
}

void Menu::ProcRenameWorkSection(IniFile& inifile) {
  DEBUG_MSG("proc modify work section name");
  string reply;
  static string promt("name (default no action): ");
  GetUserReply(promt, reply);
  if (reply[0] != ' ') {
    DEBUG_MSG("modify section name: "<<reply);
    inifile.RenameSection(*inifile.GetWorkSectionName(), reply);
  }
}

void Menu::ProcPrintKeyValues(IniFile& inifile) {
  DEBUG_MSG("proc print key values");
  const string *section_name = inifile.GetWorkSectionName();
  size_t size = inifile.WorkSectionCountKeyValues();
  cout<<"Work Section: "<<*section_name<<"\nKey counts: "<<size<<" (marked by * is deleted)\n"<<endl;
  for (size_t i = 0; i<size; i++) {
    const string *key = inifile.WorkSectionGetKeyAt(i);
    const string *value = inifile.WorkSectionGetValue(*key);
    bool isdeleted = inifile.WorkSectionIsKeyDeleted(*key);
    cout<<"\""<<*key<<"\" "<<inifile.delimiter_char()<<" \""<<*value<<(isdeleted?"\" [*]":"\"")<<endl;
  }
}

void Menu::ProcAddKeyValue(IniFile& inifile) {
  DEBUG_MSG("proc add key value");
  string key;
  static string promt_key("key (default none): ");
  GetUserReply(promt_key, key);
  if (key[0] != ' ') {
    DEBUG_MSG("key: "<<key);
  }
  string value;
  static string promt_value("value (default none): ");
  GetUserReply(promt_value, value);
  if (value[0] != ' ') {
    DEBUG_MSG("value: "<<value);
  }
  inifile.WorkSectionAddKeyValue(key, value);
}

void Menu::ProcDeleteKeyValue(IniFile& inifile) {
  DEBUG_MSG("proc delete key value");
  string key;
  static string promt_key("key (default no action): ");
  GetUserReply(promt_key, key);
  bool ret(true);
  if (key[0] != ' ') {
    DEBUG_MSG("key: "<<key);
    inifile.WorkSectionSetKeyIsDeleted(key, true);
  }
}

void Menu::ProcUndeleteKeyValue(IniFile& inifile) {
  DEBUG_MSG("proc recover key");
  string key;
  static string promt_key("key (default no action): ");
  GetUserReply(promt_key, key);
  if (key[0] != ' ') {
    DEBUG_MSG("key: "<<key);
    inifile.WorkSectionSetKeyIsDeleted(key, false);
  }
}

void Menu::ProcRenameKey(IniFile& inifile) {
  DEBUG_MSG("proc modify key name");
  string reply;
  static string promt("key to be renamed (default no action): ");
  GetUserReply(promt, reply);
  if (reply[0] != ' ') {
    DEBUG_MSG("key to be renamed: "<<reply);
    string new_name;
    static string prompt_new_name("new name of key ");
    GetUserReply(prompt_new_name+reply, new_name);
    inifile.RenameSection(reply, new_name);
  }
}

void Menu::ProcModifyValue(IniFile& inifile) {
  DEBUG_MSG("proc modify key value");
  string key;
  static string promt_key("key (default none): ");
  GetUserReply(promt_key, key);
  if (key[0] != ' ') {
    DEBUG_MSG("key: "<<key);
  }
  string value;
  static string promt_value("value (default none): ");
  GetUserReply(promt_value, value);
  if (value[0] != ' ') {
    DEBUG_MSG("value: "<<value);
  }
  inifile.WorkSectionSetKeyValue(key, value);
}


bool Menu::GetUserReply(const string &promt, string& reply) {
  do {
    cout<<promt;
    if (!std::getline(std::cin, reply)) {
      exit(1);
    }
    else
      break;
  } while (1);
  DEBUG_MSG("User reply:"<<reply);
  LeftTrimString(reply);
  return true;
}

void Menu::LeftTrimString(string &str) {
  int size = str.size();
  int i = 0;
  while (i<size && (str[i] == ' ' || str[i] == '\t'))  ++i;
  if (i == size ) {
    str = " ";
  }
  else {
    str = str.substr(i);
  }
}

} // namespace parser
