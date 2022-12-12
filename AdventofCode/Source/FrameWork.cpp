#include "pch.h"

namespace AdventOfCode
{

  std::string User::AsString(ID id) { return users.at(id).name; }
  std::string User::GetSessionID(ID id) { return users.at(id).sessionID; }

  const std::unordered_map<User::ID, User::userData> User::users{
    { PW, { "PirnaschW",       "53616c7465645f5fd89943d19def2da32c3194c79b371e2a59473d4453d247126134630eacdf8ccddc62d652b303a217645a23787674e7a6f748f457eb34abf0" } },
    { FL, { "FlEndlessSummer", "53616c7465645f5fbfaa82a010cddb8197a6f11c9364a7efada8c6948bbb729c698a37064aa173b974e7b608ccebcf83cd4984663d1d7559a121c1144ff88dd5" } },
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
