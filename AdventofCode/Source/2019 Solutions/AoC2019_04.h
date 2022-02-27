template<> Number AoC<2019, 4, A>(std::istream& input)
{
  auto v = ReadWords(input, '-');

  auto TryDigits = [minCode = v[0], maxCode = v[1]](auto self, std::string start, int digit, bool same)->Number
  {
    assert(digit < 6);

    Number z{ 0 };
    std::string nexttry = start;
    char begin = digit > 0 ? start[digit - 1] : start[digit];
    for (char d = begin; d <= '9'; ++d)
    {
      nexttry[digit] = d;
      if (nexttry < minCode) continue;
      if (nexttry > maxCode) return z;
      if (digit == 5)
      {
        if (same || d == begin)   // otherwise, no two equals are in the string
        {
          assert(nexttry >= minCode);
          assert(nexttry <= maxCode);
          assert(nexttry[0] <= nexttry[1]);
          assert(nexttry[1] <= nexttry[2]);
          assert(nexttry[2] <= nexttry[3]);
          assert(nexttry[3] <= nexttry[4]);
          assert(nexttry[4] <= nexttry[5]);
          assert((nexttry[0] == nexttry[1]) ||
                 (nexttry[1] == nexttry[2]) ||
                 (nexttry[2] == nexttry[3]) ||
                 (nexttry[3] == nexttry[4]) ||
                 (nexttry[4] == nexttry[5]));
          ++z;
        }
      }
      else z += self(self, nexttry, digit + 1, same || d == begin);
    }
    return z;
  };

  Number z = TryDigits(TryDigits, v[0], 0, false);

  return z;
}

template<> Number AoC<2019, 4, B>(std::istream& input)
{
  auto v = ReadWords(input, '-');

  auto Twin = [](const std::string& s) -> bool
  {
    if (s.size() != 6) return false;
    int count{ 0 };
    char prev{ 0 };
    for (const char& c : s)
    {
      ++count;
      if (c != prev)
      {
        if (count == 2) return true;
        prev = c;
        count = 0;
      }
    }
    return (count == 1) ? true : false;
  };

  auto TryDigits = [minCode = v[0], maxCode = v[1], &Twin](auto self, std::string start, int digit)->Number
  {
    assert(digit < 6);

    Number z{ 0 };
    std::string nexttry = start;
    char begin = digit > 0 ? start[digit - 1] : start[digit];
    for (char d = begin; d <= '9'; ++d)
    {
      nexttry[digit] = d;
      if (nexttry < minCode) continue;
      if (nexttry > maxCode) return z;

      if (digit == 5)
      {
        if (Twin(nexttry))   // otherwise, no two equals are in the string
        {
          assert(nexttry >= minCode);
          assert(nexttry <= maxCode);
          assert(nexttry[0] <= nexttry[1]);
          assert(nexttry[1] <= nexttry[2]);
          assert(nexttry[2] <= nexttry[3]);
          assert(nexttry[3] <= nexttry[4]);
          assert(nexttry[4] <= nexttry[5]);
          assert((nexttry[0] == nexttry[1]) ||
                 (nexttry[1] == nexttry[2]) ||
                 (nexttry[2] == nexttry[3]) ||
                 (nexttry[3] == nexttry[4]) ||
                 (nexttry[4] == nexttry[5]));
          assert((                              (nexttry[0] == nexttry[1]) && (nexttry[1] != nexttry[2])) ||
                 ((nexttry[0] != nexttry[1]) && (nexttry[1] == nexttry[2]) && (nexttry[2] != nexttry[3])) ||
                 ((nexttry[1] != nexttry[2]) && (nexttry[2] == nexttry[3]) && (nexttry[3] != nexttry[4])) ||
                 ((nexttry[2] != nexttry[3]) && (nexttry[3] == nexttry[4]) && (nexttry[4] != nexttry[5])) ||
                 ((nexttry[3] != nexttry[4]) && (nexttry[4] == nexttry[5])                              ));
          ++z;
        }
      }
      else z += self(self, nexttry, digit + 1);
    }
    return z;
  };

  Number z = TryDigits(TryDigits, v[0], 0);

  return z;
}
