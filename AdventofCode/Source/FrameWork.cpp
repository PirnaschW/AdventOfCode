#include "pch.h"

namespace AdventOfCode
{

  std::string User::AsString(ID id) { return users.at(id).name; }
  std::string User::GetSessionID(ID id) { return users.at(id).sessionID; }

  // Instructions:
  // log on in Chrome
  // Inspect (CTRL+Shift+I)
  // Reload (CTRL+R)
  // Application / Storage / Cookies / Session
  const std::unordered_map<User::ID, User::userData> User::users{
    { PW, { "PirnaschW",       "53616c7465645f5fb6c72779c8bc8ee0a497c573a51a4542d8dfd3365a2e077647c07e284148af81101008e21123ce5c5113dbacd173b47a4b20d0b4b304244e" } },
    { FL, { "FlEndlessSummer", "53616c7465645f5f431ff96073ab62a6c4eab244f6a1fd6971618c52b9f8f58d968e2230d16bd86f608846961045bf4175b6a6f917df7c340e78bfe0e0ca778f" } },
  };

  const std::string GetEventAsString(Event event) noexcept
  {
    assert(event >= 2015);
    assert(event <= 2024);
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
