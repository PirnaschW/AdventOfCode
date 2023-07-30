void AoC2020_14A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  long long maskset{ 0 };
  long long maskclear{ 0 };
  std::unordered_map<int, long long> mem{};
  for (const auto& line : v)
  {
    switch (line[1])
    {
      case 'a': // mask
        {
          std::string m = line.substr(7, 36);
          long long factor = 1LL << 36LL;
          maskset = 0LL;
          maskclear = factor - 1LL;
          for (int i = 0; i < m.size(); ++i)
          {
            factor >>= 1;
            switch (m[i])
            {
              case 'X': break;
              case '1': maskset += factor; break;
              case '0': maskclear -= factor; break;
              default: break;
            }
          }
        }
        break;
      case 'e': // mem
        // mem[26882] = 5857155
        {
          std::istringstream str(line);
          char spacer1[5]{};
          int index{ 0 };
          std::string spacer2{};
          std::string spacer3{};
          long long value{ 0LL };
          str >> spacer1 >> index >> spacer2 >> spacer3 >> value;
          value |= maskset;
          value &= maskclear;
          mem[index] = value;
        }
        break;
      default:
        break;
    }
  }

  long long z{ 0 };
  for (const auto& it : mem)
  {
    z += it.second;
  }
  std::cout << z << std::endl;
}
void AoC2020_14B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  long long masksethard{ 0LL };
  std::vector<long long> maskset{};
  long long maskpreclear{};
  std::unordered_map<long long, long long> mem{};
  for (const auto& line : v)
  {
    switch (line[1])
    {
      case 'a': // mask
        {
          std::string m = line.substr(7, 36);
          long long factor = 1LL << 36LL;
          maskset.clear();
          maskset.emplace_back(0LL);
          masksethard = 0LL;
          maskpreclear = factor - 1LL;
          for (int i = 0; i < m.size(); ++i)
          {
            factor >>= 1;
            switch (m[i])
            {
              case 'X':
                {
                  auto maskset0 = maskset;
                  for (auto& mm : maskset0) mm |= factor;
                  maskset.insert(maskset.end(), maskset0.begin(), maskset0.end());
                  maskpreclear &= ~factor;
                }
                break;
              case '1':
                masksethard |= factor;
                break;
              case '0': break;
              default: break;
            }
          }
        }
        break;
      case 'e': // mem
        // mem[26882] = 5857155
        {
          std::istringstream str(line);
          char spacer1[5]{};
          long long index{ 0LL };
          std::string spacer2{};
          std::string spacer3{};
          long long value{ 0LL };
          str >> spacer1 >> index >> spacer2 >> spacer3 >> value;
          index |= masksethard;
          index &= maskpreclear;
          for (int i = 0; i < maskset.size(); ++i)
          {
            mem[index | maskset[i]] = value;
          }
        }
        break;
      default:
        break;
    }
  }

  long long z{ 0 };
  for (const auto& it : mem)
  {
    z += it.second;
  }
  std::cout << z << std::endl;
}
