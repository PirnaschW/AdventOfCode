void AoC2020_18A(std::istream& input)
{
  using Type = long long;

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct H
  {
    static Type Evaluate(const std::string& line, int& eat)
    {
      Type total{ 0 };
      int i{ 0 };
      Type num{ 0 };
      char lastop{ 0 };
      while (i < line.size())
      {
        char next = line[i];
        switch (next)
        {
          case '+':
          case '*':
            switch (lastop)
            {
              case 0:
                total = num;
                break;
              case '+':
                total += num;
                break;
              case '*':
                total *= num;
                break;
              default:
                assert(false);
                break;
            }
            num = 0;
            lastop = next;
            break;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            num *= 10;
            num += next - '0';
            break;
          case '(':
            {
              int eataway = 0;
              num = Evaluate(line.substr(i + 1, line.size() - i - 1), eataway);
              i += eataway;
            }
            break;
          case ')':
            switch (lastop)
            {
              case 0:
                total = num;
                break;
              case '+':
                total += num;
                break;
              case '*':
                total *= num;
                break;
              default:
                assert(false);
                break;
            }
            eat = i + 1;
            return total;
            break;
          case ' ':
            break;
          default:
            assert(false);
            break;
        }
        ++i;
      }

      switch (lastop)
      {
        case 0:
          total = num;
          break;
        case '+':
          total += num;
          break;
        case '*':
          total *= num;
          break;
        default:
          assert(false);
          break;
      }
      eat = i;
      return total;
    }
  };

  Type z{ 0 };
  for (const auto& line : v)
  {
    int eat{ 0 };
    Type total = H::Evaluate(line, eat);
    assert(eat == line.size());
    z += total;
  }

  std::cout << z << std::endl;
}

void AoC2020_18B(std::istream& input)
{
  using Type = long long;

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Token
  {
    Token(int i) : isoper(false), value(i) {}
    Token(Type v) : isoper(false), value(v) {}
    Token(char o) : isoper(true), oper(o) {}
    bool isoper{};
    char oper{ 0 };
    Type value{ 0 };
  };

  struct H
  {
    static Type Process(std::list<Token>& tokens)
    {
      ProcessOper(tokens, '+');
      ProcessOper(tokens, '*');
      assert(tokens.size() == 1);
      assert(!tokens.begin()->isoper);
      return tokens.begin()->value;
    }

    static void ProcessOper(std::list<Token>& tokens, char oper)
    {
      for (auto it = tokens.begin(); it != tokens.end(); ++it)
      {
        if (it->isoper && it->oper == oper)
        {
          assert(!std::next(it, -1)->isoper);
          assert(!std::next(it, +1)->isoper);
          switch (oper)
          {
            case '+': it = tokens.insert(it, std::next(it, -1)->value + std::next(it, +1)->value); break; // insert result value before current, 'it' points now to new entry
            case '*': it = tokens.insert(it, std::next(it, -1)->value * std::next(it, +1)->value); break; // insert result value before current, 'it' points now to new entry
            default: assert(false);                                                           break;
          }
          tokens.erase(std::next(it, -1));  // delete first number
          tokens.erase(std::next(it, +1));  // delete old oper
          tokens.erase(std::next(it, +1));  // delete second number
        }
      }
      assert(tokens.size() > 0);
      assert(!tokens.begin()->isoper);
    }

    static Type Evaluate(const std::string& line, int& eat)
    {
      int i{ 0 };
      Type number{ 0 };
      std::list<Token> tokens{};
      //tokens.push_back(0);
      //tokens.push_back('+');
      while (i < line.size())
      {
        char next = line[i];
        switch (next)
        {
          case '+':
          case '*':
            tokens.push_back(number);
            tokens.push_back(next);
            number = 0;
            break;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            number *= 10;
            number += next - '0';
            break;
          case '(':
            {
              int eataway = 0;
              number = Evaluate(line.substr(i + 1, line.size() - i - 1), eataway);
              i += eataway;
            }
            break;
          case ')':
            eat = i + 1;
            tokens.push_back(number);
            return Process(tokens);
            break;
          case ' ':
            break;
          default:
            assert(false);
            break;
        }
        ++i;
      }

      tokens.push_back(number);
      eat = i;
      return Process(tokens);
    }
  };

  Type z{ 0 };
  for (const auto& line : v)
  {
    int eat{ 0 };
    Type total = H::Evaluate(line, eat);
    assert(eat == line.size());
    z += total;
  }

  std::cout << z << std::endl;
}
