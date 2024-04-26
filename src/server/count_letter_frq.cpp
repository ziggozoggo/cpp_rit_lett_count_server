#include "count_letter_frq.h"


static std::string get_table_data(const char letter, int count);
static bool is_msg_has_letters(const std::string& msg);

/**
 * @brief Подсчёт частоты букв латинского алфавита в переданной строке
 * @param str Строка
 * @return Таблица заданного формата
 */
std::string count_letter_frequency(const std::string& str) {
  std::map<char, int> letters_dict;
  std::map<char, int>::iterator iter;

  std::string result = get_table_header(str);
  if (!is_msg_has_letters(str)) {
    return result;
  }
  
  for(std::size_t i = 0; i < str.length(); i++) {
    if (isalpha(str[i])) {
      letters_dict[str[i]]++;
    }
  }

  for(iter = letters_dict.begin(); iter != letters_dict.end(); iter++) {
    std::string column = get_table_data(iter->first, iter->second);
    result += column;
  }

  return result;
}

/**
 * @brief Сформировать заголовок таблицы
 * @param str Строка
 * @return Строка таблицы заданного формата
 */
std::string get_table_header(const std::string& msg) {
  const char *message = "Message";
  const char *sep = "|";

  char buff[BUFSIZ] = {0};
  sprintf(buff, "\n%-8s %s %s\n", message, sep, msg.c_str());

  std::string result = buff;
  return result;
}

std::string get_table_data(const char letter, int count) {
  char buff[BUFSIZ] = {0};

  const char *sep = "|";
  sprintf(buff, "%-8c %s %d\n", letter, sep, count);

   std::string result = buff;
   return result;
}

bool is_msg_has_letters(const std::string& msg) {
  bool result = false;
  for(const char& c : msg) {
    if (isalpha(c)) {
      result = true;
      break;
    }
  }
  return result;
}