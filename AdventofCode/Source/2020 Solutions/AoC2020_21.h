void AoC2020_21A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<std::string> mlist{};
  std::unordered_multimap<std::string, std::string> all{};
  for (const auto& line : v)
  {
    std::istringstream str(line);
    std::unordered_set<std::string> ingr{};
    std::string word{};
    while (true)
    {
      if (!(str >> word)) break;
      if (word[0] == '(') break;
      ingr.insert(word);
      mlist.emplace_back(word);
    }

    while (str >> word)
    {
      word.pop_back();

      const auto [it1, it2] = all.equal_range(word);
      if (it1 == all.end())   // new allergen, add all possibilities
      {
        for (auto& in : ingr)
          all.insert({ word, in });
      }
      else // we had this allergen before
      {
        for (auto it = it1; it != it2; )
        {
          auto it0 = it++;
          if (!ingr.contains(it0->second))
          {
            all.erase(it0);
          }
        }
      }
    }
  }

  size_t n{ 0 };
  bool again{};
  do
  {
    again = false;
    for (auto& it : all)
    {
      if (all.count(it.first) == 1)  // found a sure match
      {
        size_t nn = std::erase_if(all, [it](const auto& item) { const auto& [key, value] = item; return key != it.first && value == it.second; });
        if (nn > 0)
        {
          again = true;
          n += nn;
          break;
        }
      }
    }
  } while (again);

  n = 0;
  for (auto& it : all)
  {
    n += std::erase_if(mlist, [it](const auto& item) { return item == it.second; });
  }


  auto z = mlist.size();
  std::cout << z << std::endl;
}

void AoC2020_21B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<std::string> mlist{};
  std::unordered_multimap<std::string, std::string> all{};
  for (const auto& line : v)
  {
    std::istringstream str(line);
    std::unordered_set<std::string> ingr{};
    std::string word{};
    while (true)
    {
      if (!(str >> word)) break;
      if (word[0] == '(') break;
      ingr.insert(word);
      mlist.emplace_back(word);
    }

    while (str >> word)
    {
      word.pop_back();

      const auto [it1, it2] = all.equal_range(word);
      if (it1 == all.end())   // new allergen, add all possibilities
      {
        for (auto& in : ingr)
          all.insert({ word, in });
      }
      else // we had this allergen before
      {
        for (auto it = it1; it != it2; )
        {
          auto it0 = it++;
          if (!ingr.contains(it0->second))
          {
            all.erase(it0);
          }
        }
      }
    }
  }

  size_t n{ 0 };
  bool again{};
  do
  {
    again = false;
    for (auto& it : all)
    {
      if (all.count(it.first) == 1)  // found a sure match
      {
        size_t nn = std::erase_if(all, [it](const auto& item) { const auto& [key, value] = item; return key != it.first && value == it.second; });
        if (nn > 0)
        {
          again = true;
          n += nn;
          break;
        }
      }
    }
  } while (again);

  n = 0;
  for (auto& it : all)
  {
    n += std::erase_if(mlist, [it](const auto& item) { return item == it.second; });
  }

  std::map<std::string, std::string> sall{};
  for (auto& it : all)
  {
    sall.insert({ it.first,it.second });
  }

  std::string result{};
  for (auto& it : sall)
  {
    result += it.second + ',';
  }
  result.pop_back();

  std::cout << result << std::endl;

}
