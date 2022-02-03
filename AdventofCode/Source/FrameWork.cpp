#include "pch.h"

namespace AdventOfCode
{

  std::string User::AsString(ID id) { return users.at(id).name; }
  std::string User::GetSessionID(ID id) { return users.at(id).sessionID; }

  const std::unordered_map<User::ID, User::userData> User::users{
    { PW, { "PirnaschW",       "53616c7465645f5f1ec3ca7f81fdcab3fe7085dcb1ba4220c482e7c7f748df9b8df31296b284e9202c87318c7e7340c0" } },
    { FL, { "FlEndlessSummer", "53616c7465645f5f2ca3ea3650213c1351416268fa5d7ec81275033de3c5d118f7f870deca75677c14d66be8136f2734" } },
  };

  const std::string GetEventAsString(Event event) noexcept
  {
    assert(event >= 2015);
    assert(event <= 2022);
    return std::to_string(event);
  }

  const std::string GetDayAsString(Day day, bool leadingZeros) noexcept
  {
    assert(day >= 1);
    assert(day <= 25);
    if (leadingZeros)
    {
      static std::string sDay{ "00" };
      sDay[0] = '0' + day / 10;
      sDay[1] = '0' + day % 10;
      return sDay;
    }
    else return std::to_string(day);
  }

  const std::string GetPartAsString(Part part) noexcept
  {
    switch (part)
    {
      case A:  return "A";
      case B:  return "B";
      default: return "";
    }
  }

  const std::string GetInputPath(User::ID id, Event event, Day day)
  {
    return std::string{ "Input Files\\" + User::AsString(id) + "\\" + GetEventAsString(event) + " Inputs\\AoC" + GetEventAsString(event) + "_" + GetDayAsString(day,true) + ".txt" };
  }

  const std::string GetInputURL(User::ID id, Event event, Day day)
  {
    return std::string{ "http://adventofcode.com/" + GetEventAsString(event) + "/day/" + GetDayAsString(day,false) + "/input" };
  }

  void DownloadInput(const std::string& source, User::ID id, const std::string& target)
  {
    URL::Cookies cookies{};
    cookies.push_back({ "session",User::GetSessionID(id).c_str() });

    std::string s = URL::GetHTMLFromURL(source, cookies);
    std::ofstream outf(target, std::ios::out);
    outf << s;
  }

}
