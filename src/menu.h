// menu.h

#ifndef MENU_H_
#define MENU_H_

#include <string>

namespace parser {

class IniFile;

//类 Menu用来处理对应菜单项

class Menu {
 public:
  // 命令h(print help)
  static void ProcPrinHelp(IniFile& inifile);
  //
  // 文件保存相关命令
  //
  // 命令l(load a ini file)
  static void ProcLoadFile(IniFile& inifile);
  // 命令w(write data to a file)
  static void ProcWriteData(IniFile& inifile);
  // 命令c(clear all current data)
  static void ProcClearData(IniFile& inifile);
  //
  // Sections相关命令
  //
  // 命令s (select one section as the work section)
  static void ProcSelectWorkSection(IniFile& inifile);
  // 命令p(print the sections)
  static void ProcPrintSections(IniFile& inifile);
  // 命令a(add a new section and seclect it as the work section)
  static void ProcAddSection(IniFile& inifile);
  // 命令d(delete section by index)
  static void ProcDeleteSection(IniFile& inifile);
  // 命令u(undeleted section)
  static void ProcUndeleteSection(IniFile& inifile);
  // 命令r(rename work section)
  static void ProcRenameWorkSection(IniFile& inifile);
  //
  // Key & value相关命令
  //
  // 命令P(print all key & values of work section)
  static void ProcPrintKeyValues(IniFile& inifile);
  // 命令A(add key & value into work section)
  static void ProcAddKeyValue(IniFile& inifile);
  // 命令D(delete key & value in work section)
  static void ProcDeleteKeyValue(IniFile& inifile);
  // 命令U(undeleted key & value in work section)
  static void ProcUndeleteKeyValue(IniFile& inifile);
  // 命令R
  static void ProcRenameKey(IniFile& inifile);
  // 命令V(modify value by key in work section)
  static void ProcModifyValue(IniFile& inifile);
  // 通用
  // 接收用户按键，promt为提示语，reply为输入行
  static bool GetUserReply(const std::string &promt, std::string& reply);
  //
  // 相应menu对应按键
  //
  static const char menu_print_help = 'h';
  static const char menu_load_file = 'l';
  static const char menu_write_data = 'w';
  static const char menu_quit = 'q';
  static const char menu_clear_data = 'c';
  static const char menu_print_sections = 'p';
  static const char menu_add_section = 'a';
  static const char menu_delete_section = 'd';
  static const char menu_undelete_section = 'u';
  static const char menu_rename_work = 'r';
  static const char menu_select_work = 's';
  static const char menu_print_keyvalues = 'P';
  static const char menu_add_keyvalue = 'A';
  static const char menu_delete_keyvalue = 'D';
  static const char menu_undelete_keyvalue = 'U';
  static const char menu_rename_key = 'R';
  static const char menu_modify_value = 'V';

 private:
  //判断ch是不是y或者Y
  static inline bool ReplyIsYes(char ch) { return ch == 'y' || ch == 'Y'; }
  // 去除str前部分的空白字符，若str为空，则修改为" "
  static void LeftTrimString(std::string &str);
};
} // namespace parser

#endif // MENU_H_
