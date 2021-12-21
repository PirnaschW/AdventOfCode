void AoC2021_18A(std::istream& input)
{
  struct Token
  {
    bool isNumber{ true };
    int number{ 0 };
    char code{ 0 };

    Token(char c) {
      switch (c)
      {
        case '[':
        case ']':
        case ',':
          isNumber = false;
          code = c;
          break;
        default:
          isNumber = true;
          number = c - '0';
          break;
      }
    }
  };

  using List = std::list<Token>;


  struct H
  {
    static List Parse(const std::string& line)
    {
      List l{};
      int p{ 0 };
      while (p < line.size())
      {
        l.push_back(Token(line[p++]));
      }

      return l;
    }
    static void Print(const List& l)
    {
      //for (auto it = l.begin(); it != l.end(); ++it)
      //{
      //  if (it->isNumber) std::cout << it->number;
      //  else std::cout << it->code;
      //}
      //std::cout << std::endl;
    }
    static List Add(const List& l1, const List& l2)
    {
      if (l1.size() == 0) return l2;
      if (l2.size() == 0) return l1;

      List l{ l1 };
      l.push_front(Token('['));
      l.push_back(Token(','));
      l.insert(l.end(), l2.begin(), l2.end());
      l.push_back(Token(']'));
      return l;
    }
    static void Reduce(List& l)
    {
      int nBracket{ 0 };
      bool reparse{ false };
      do
      {
        Print(l);
        nBracket = 0;
        reparse = false;
        for (auto it = l.begin(); !reparse && it != l.end(); ++it)
        {
          if (!it->isNumber)
          {
            switch (it->code)
            {
              case '[': ++nBracket; break;
              case ']': --nBracket; break;
              case ',':
                if (nBracket > 4)
                {
                  if (Explode(l, it))
                  {
                    reparse = true;
                    break;
                  }
                }
                break;
            }
          }
        }
        for (auto it = l.begin(); !reparse && it != l.end(); ++it)
        {
          if (it->isNumber && it->number > 9)
          {
            Split(l, it);
            reparse = true;
            break;
          }
        }
      }
      while (reparse);
      Print(l);
    }
    static bool Explode(List& l, const List::iterator& it)
    {
      auto prev = it;
      assert(prev != l.begin());
      --prev;
      auto next = it;
      assert(next != l.end());
      ++next;
      assert(next != l.end());

      if (!prev->isNumber || !next->isNumber) return false; // cannot explode

      int np = prev->number;
      int nn = next->number;
      while (--prev != l.begin())
      {
        if (prev->isNumber)
        {
          prev->number += np;
          break;
        }
      }
      while (++next != l.end())
      {
        if (next->isNumber)
        {
          next->number += nn;
          break;
        }
      }

      it->isNumber = true;
      it->number = 0;
      EraseLeft(l, it);
      EraseLeft(l, it);
      EraseRight(l, it);
      EraseRight(l, it);
      return true;
    }
    static void EraseLeft(List& l, const List::iterator it)
    {
      auto it0 = it;
      assert(it0 != l.begin());
      --it0;
      l.erase(it0);
    }
    static void EraseRight(List& l, const List::iterator it)
    {
      auto it0 = it;
      assert(it0 != l.end());
      ++it0;
      assert(it0 != l.end());
      l.erase(it0);
    }
    static void Split(List& l, const List::iterator& it)
    {
      int n = it->number;
      auto next = it;
      ++next;
      l.insert(next, Token('0' + n / 2));
      l.insert(next, Token(','));
      l.insert(next, Token('0' + (n + 1) / 2));
      l.insert(next, Token(']'));
      it->isNumber = false;
      it->code = '[';
    }
    static Number Magnitude(const List& l, List::iterator& it)
    {
      for (; it != l.end(); ++it)
      {
        assert(!it->isNumber);
        assert(it->code == '[');
        ++it;
        Number left{ 0 };
        if (it->isNumber) left = it->number;
        else
        {
          assert(it->code == '[');
          left = Magnitude(l, it);
        }

        ++it;
        assert(!it->isNumber);
        assert(it->code == ',');

        ++it;
        Number right{ 0 };
        if (it->isNumber) right = it->number;
        else
        {
          assert(it->code == '[');
          right = Magnitude(l, it);
        }

        ++it;
        assert(!it->isNumber);
        assert(it->code == ']');

        return 3 * left + 2 * right;
      }
      return 0;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  List list{};
  for (const auto& line : v)
  {
    List l = H::Parse(line);
    list = H::Add(list, l);
    H::Reduce(list);
  }

  auto ll = list.begin();
  Number m = H::Magnitude(list,ll);
  std::cout << m << std::endl;
}

void AoC2021_18B(std::istream& input)
{
  struct Token
  {
    bool isNumber{ true };
    int number{ 0 };
    char code{ 0 };

    Token(char c) {
      switch (c)
      {
        case '[':
        case ']':
        case ',':
          isNumber = false;
          code = c;
          break;
        default:
          isNumber = true;
          number = c - '0';
          break;
      }
    }
  };

  using List = std::list<Token>;


  struct H
  {
    static List Parse(const std::string& line)
    {
      List l{};
      int p{ 0 };
      while (p < line.size())
      {
        l.push_back(Token(line[p++]));
      }

      return l;
    }
    static void Print(const List& l)
    {
      //for (auto it = l.begin(); it != l.end(); ++it)
      //{
      //  if (it->isNumber) std::cout << it->number;
      //  else std::cout << it->code;
      //}
      //std::cout << std::endl;
    }
    static List Add(const List& l1, const List& l2)
    {
      if (l1.size() == 0) return l2;
      if (l2.size() == 0) return l1;

      List l{ l1 };
      l.push_front(Token('['));
      l.push_back(Token(','));
      l.insert(l.end(), l2.begin(), l2.end());
      l.push_back(Token(']'));
      return l;
    }
    static void Reduce(List& l)
    {
      int nBracket{ 0 };
      bool reparse{ false };
      do
      {
        Print(l);
        nBracket = 0;
        reparse = false;
        for (auto it = l.begin(); !reparse && it != l.end(); ++it)
        {
          if (!it->isNumber)
          {
            switch (it->code)
            {
              case '[': ++nBracket; break;
              case ']': --nBracket; break;
              case ',':
                if (nBracket > 4)
                {
                  if (Explode(l, it))
                  {
                    reparse = true;
                    break;
                  }
                }
                break;
            }
          }
        }
        for (auto it = l.begin(); !reparse && it != l.end(); ++it)
        {
          if (it->isNumber && it->number > 9)
          {
            Split(l, it);
            reparse = true;
            break;
          }
        }
      } while (reparse);
      Print(l);
    }
    static bool Explode(List& l, const List::iterator& it)
    {
      auto prev = it;
      assert(prev != l.begin());
      --prev;
      auto next = it;
      assert(next != l.end());
      ++next;
      assert(next != l.end());

      if (!prev->isNumber || !next->isNumber) return false; // cannot explode

      int np = prev->number;
      int nn = next->number;
      while (--prev != l.begin())
      {
        if (prev->isNumber)
        {
          prev->number += np;
          break;
        }
      }
      while (++next != l.end())
      {
        if (next->isNumber)
        {
          next->number += nn;
          break;
        }
      }

      it->isNumber = true;
      it->number = 0;
      EraseLeft(l, it);
      EraseLeft(l, it);
      EraseRight(l, it);
      EraseRight(l, it);
      return true;
    }
    static void EraseLeft(List& l, const List::iterator it)
    {
      auto it0 = it;
      assert(it0 != l.begin());
      --it0;
      l.erase(it0);
    }
    static void EraseRight(List& l, const List::iterator it)
    {
      auto it0 = it;
      assert(it0 != l.end());
      ++it0;
      assert(it0 != l.end());
      l.erase(it0);
    }
    static void Split(List& l, const List::iterator& it)
    {
      int n = it->number;
      auto next = it;
      ++next;
      l.insert(next, Token('0' + n / 2));
      l.insert(next, Token(','));
      l.insert(next, Token('0' + (n + 1) / 2));
      l.insert(next, Token(']'));
      it->isNumber = false;
      it->code = '[';
    }
    static Number Magnitude(const List& l, List::iterator& it)
    {
      for (; it != l.end(); ++it)
      {
        assert(!it->isNumber);
        assert(it->code == '[');
        ++it;
        Number left{ 0 };
        if (it->isNumber) left = it->number;
        else
        {
          assert(it->code == '[');
          left = Magnitude(l, it);
        }

        ++it;
        assert(!it->isNumber);
        assert(it->code == ',');

        ++it;
        Number right{ 0 };
        if (it->isNumber) right = it->number;
        else
        {
          assert(it->code == '[');
          right = Magnitude(l, it);
        }

        ++it;
        assert(!it->isNumber);
        assert(it->code == ']');

        return 3 * left + 2 * right;
      }
      return 0;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  std::vector<List> lists{};
  for (const auto& line : v)
  {
    List l = H::Parse(line);
    H::Reduce(l);
    lists.emplace_back(l);
  }

  Number maxm{ 0 };
  for (int i = 0; i < lists.size(); i++)
  {
//    std::cout << i << " of " << lists.size() << std::endl;
    for (int j = 0; j < lists.size(); j++)
    {
      if (i == j) continue;

      List l = H::Add(lists[i], lists[j]);
      H::Reduce(l);
      auto ll = l.begin();
      Number m = H::Magnitude(l, ll);
      if (m > maxm) maxm = m;
    }
  }
  std::cout << maxm << std::endl;
}
