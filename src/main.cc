#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "inifile.h"
#include "include/debug.h"
#include "menu.h"

using std::cout;
using std::cerr;
using std::endl;
using std::exit;
using std::string;
using parser::IniFile;
using parser::Menu;


static int ParseMenu(IniFile& inifile){
  cout<<endl;
  string reply;
  static string menu_prompt="Command (h for help): ";
  Menu::GetUserReply(menu_prompt, reply);
  char key = reply[0];
  switch (key) {
    case Menu::menu_load_file : {
      Menu::ProcLoadFile(inifile);
      break;
    }
    case Menu::menu_write_data : {
      Menu::ProcWriteData(inifile);
      break;
    }
    case Menu::menu_quit : {
      exit(0);
      break;
    }
    case Menu::menu_clear_data : {
      Menu::ProcClearData(inifile);
      break;
    }
    case Menu::menu_print_sections : {
      Menu::ProcPrintSections(inifile);
      break;
    }
    case Menu::menu_select_work : {
      Menu::ProcSelectWorkSection(inifile);
      break;
    }
    case Menu::menu_add_section : {
      Menu::ProcAddSection(inifile);
      break;
    }
    case Menu::menu_delete_section : {
      Menu::ProcDeleteSection(inifile);
      break;
    }
    case Menu::menu_undelete_section : {
      Menu::ProcUndeleteSection(inifile);
      break;
    }
    case Menu::menu_rename_work : {
      Menu::ProcRenameWorkSection(inifile);
      break;
    }
    case Menu::menu_print_keyvalues : {
      Menu::ProcPrintKeyValues(inifile);
      break;
    }
    case Menu::menu_add_keyvalue : {
      Menu::ProcAddKeyValue(inifile);
      break;
    }
    case Menu::menu_delete_keyvalue : {
      Menu::ProcDeleteKeyValue(inifile);
      break;
    }
    case Menu::menu_undelete_keyvalue : {
      Menu::ProcUndeleteKeyValue(inifile);
      break;
    }
    case Menu::menu_modify_value : {
      Menu::ProcModifyValue(inifile);
      break;
    }
    case Menu::menu_print_help : {
     Menu::ProcPrinHelp(inifile);
     break;
    }
    default : {
      cout<<"unknown command"<<endl;
      Menu::ProcPrinHelp(inifile);
      break;
    }
  }

}

int main(int argc, char **argv) {
  if (argc != 1) {
    cout<<"Usage: iniparser\n"<<endl;
    return 1;
  }
  cout<<"Welcome to iniparser."<<endl;

  IniFile inifile;

  while (1) {
    ParseMenu(inifile);
  }

  return 0;
}
