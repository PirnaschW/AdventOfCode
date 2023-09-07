#include "pch.h"

namespace AdventOfCode
{

  std::string User::AsString(ID id) { return users.at(id).name; }
  std::string User::GetSessionID(ID id) { return users.at(id).sessionID; }

  const std::unordered_map<User::ID, User::userData> User::users{
    { PW, { "PirnaschW",       "53616c7465645f5f541814c65144c3561e653ce16fcd014005c8621d720641cab6a2b64b4c9ce32ae90a6e91731bfa2e17d42d7d76a2e3d68e60791fe116cfc9" } },
    { FL, { "FlEndlessSummer", "53616c7465645f5fe8a3700fb67cd7bbf296530cbca1e90033010fdab0ae42e59e50ca8bd879600f18c7d113da386bc30e83b4d0c6d27d7b0daf669f22295e43" } },
  };

  const std::string GetEventAsString(Event event) noexcept
  {
    assert(event >= 2015);
    assert(event <= 2023);
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

  bool DownloadInput(const std::string& source, User::ID id, const std::string& target)
  {
    URL::Cookies cookies{};
    cookies.push_back({ "session",User::GetSessionID(id).c_str() });

    std::string s = URL::GetHTMLFromURL(source, cookies);
    if (s == "Please don't repeatedly request this endpoint before it unlocks! The calendar countdown is synchronized with the server time; the link will be enabled on the calendar the instant this puzzle becomes available.\n")
      return false;
    std::ofstream outf(target, std::ios::out);
    outf << s;
    return true;
  }

}
