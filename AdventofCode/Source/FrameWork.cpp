#include "pch.h"

namespace AdventOfCode
{

  std::string User::AsString(ID id) { return users.at(id).name; }
  std::string User::GetSessionID(ID id) { return users.at(id).sessionID; }

  const std::unordered_map<User::ID, User::userData> User::users{
    { PW, { "PirnaschW",       "53616c7465645f5f47619d50ab3d5395b68542a3e548e1e3fa2714b553dde49577e481d6cf5e825253ca7ab1a635cb434343acac93abfa5f3e7e210abd1a614a" } },
    { FL, { "FlEndlessSummer", "53616c7465645f5fd1e0e605918017998e1f92356cdef62d922ff404f09222962b00a30ad7d37cf148c61b48fa425bddabbecfc775a263af83868cf2dd1143bb" } },
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
      sDay[0] = '0' + static_cast<char>(day / 10);
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

  const std::string GetInputURL(Event event, Day day)
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
