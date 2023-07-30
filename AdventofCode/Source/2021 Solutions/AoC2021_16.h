template<> Number AoC<2021, 16, A>(std::istream& input)
{
  std::string line{};
  getline(input, line);

  std::string s{};
  s.reserve(line.size() * 4);
  for (const auto c : line)
  {
    switch (c)
    {
      case '0': s += "0000"; break;
      case '1': s += "0001"; break;
      case '2': s += "0010"; break;
      case '3': s += "0011"; break;
      case '4': s += "0100"; break;
      case '5': s += "0101"; break;
      case '6': s += "0110"; break;
      case '7': s += "0111"; break;
      case '8': s += "1000"; break;
      case '9': s += "1001"; break;
      case 'A': s += "1010"; break;
      case 'B': s += "1011"; break;
      case 'C': s += "1100"; break;
      case 'D': s += "1101"; break;
      case 'E': s += "1110"; break;
      case 'F': s += "1111"; break;
      default: assert(false); break;
    }

  }

  struct H
  {
  public:
    static int toInt(const std::string& s, int& off, int len)
    {
      int z{ 0 };
      for (int i = off; i < off + len; ++i)
      {
        z *= 2;
        z += s[i] - '0';
      }
      off += len;
      return z;
    }

    static int ReadPacket(const std::string& s, int& off)
    {
      int vsum{ 0 };
      int version = H::toInt(s, off, 3);
      vsum += version;
      int typeID = H::toInt(s, off, 3);
      switch (typeID)
      {
        case 4:  // literal
        {
          int flag{ 0 };
          int num{ 0 };
          do
          {
            flag = H::toInt(s, off, 1);
            num *= 16;
            num += H::toInt(s, off, 4);
          } while (flag == 1);

        }
        break;
        default: // operator
        {
          int optype = H::toInt(s, off, 1);
          if (optype == 0)
          {
            int len = H::toInt(s, off, 15);
            int doneat = off + len;
            while (off < doneat)
            {
              vsum += ReadPacket(s, off);
            }
          }
          else
          {
            int count = H::toInt(s, off, 11);
            for (int i = 0; i < count; ++i)
            {
              vsum += ReadPacket(s, off);
            }
          }
        }
        break;
      }
      return vsum;
    }
  };

  int off{ 0 };

  int vsum{ 0 };
  do
  {
    vsum += H::ReadPacket(s, off);

  } while (off + 7 < s.size());

  return vsum;
}

template<> Number AoC<2021, 16, B>(std::istream& input)
{
  using Number = long long;

  std::string line{};
  getline(input, line);

  std::string s{};
  s.reserve(line.size() * 4);
  for (const auto c : line)
  {
    switch (c)
    {
      case '0': s += "0000"; break;
      case '1': s += "0001"; break;
      case '2': s += "0010"; break;
      case '3': s += "0011"; break;
      case '4': s += "0100"; break;
      case '5': s += "0101"; break;
      case '6': s += "0110"; break;
      case '7': s += "0111"; break;
      case '8': s += "1000"; break;
      case '9': s += "1001"; break;
      case 'A': s += "1010"; break;
      case 'B': s += "1011"; break;
      case 'C': s += "1100"; break;
      case 'D': s += "1101"; break;
      case 'E': s += "1110"; break;
      case 'F': s += "1111"; break;
      default: assert(false); break;
    }

  }
  assert(s.size() == line.size() * 4);

  struct H
  {
  public:
    static int toInt(const std::string& s, int& off, int len)
    {
      int z{ 0 };
      for (int i = off; i < off + len; ++i)
      {
        z *= 2;
        z += s[i] - '0';
      }
      off += len;
      return z;
    }
    static Number ProcessValues(int typeID, Number value1, Number value2)
    {
      switch (typeID)
      {
        case 0: return value1 + value2;                                     // sum
        case 1: return value1 * value2;                                     // product
        case 2: return std::min(value1, value2);                            // min
        case 3: return std::max(value1, value2);                            //max
        case 4: assert(false); return -1;                                   // literal
        case 5: return value1 == -1 ? value2 : (value1 > value2 ? 1 : 0);   // greater than
        case 6: return value1 == -1 ? value2 : (value1 < value2 ? 1 : 0);   // less than
        case 7: return value1 == -1 ? value2 : (value1 == value2 ? 1 : 0);  // equal
        default: assert(false); return -1;
      }
    }

    static Number ReadPacket(const std::string& s, int& off)
    {
      /*int version =*/ H::toInt(s, off, 3); // not needed
      int typeID = H::toInt(s, off, 3);
      Number value{ 0 };
      //bool flag{ false };
      switch (typeID)
      {
        case 0: value = 0; break;  // sum
        case 1: value = 1; break;  // product
        case 2: value = std::numeric_limits<Number>::max(); break; // min
        case 3: value = 0; break;  //max
        case 4: value = 0; break;  // literal
        case 5: value = -1; break;  // greater than
        case 6: value = -1; break; // less than
        case 7: value = -1; break;  // equal
      }
      switch (typeID)
      {
        case 4:  // literal
        {
          int flag{ 0 };
          Number num{ 0 };
          do
          {
            flag = H::toInt(s, off, 1);
            num *= 16;
            num += H::toInt(s, off, 4);
          } while (flag == 1);
          value = num;
        }
        break;
        default: // operator
        {
          int optype = H::toInt(s, off, 1);
          if (optype == 0)
          {
            int len = H::toInt(s, off, 15);
            int doneat = off + len;
            while (off < doneat)
            {
              Number value2 = ReadPacket(s, off);
              value = ProcessValues(typeID, value, value2);
            }
          }
          else
          {
            int count = H::toInt(s, off, 11);
            for (int i = 0; i < count; ++i)
            {
              Number value2 = ReadPacket(s, off);
              value = ProcessValues(typeID, value, value2);
            }
          }
        }
        break;
      }
      return value;
    }
  };

  int off{ 0 };
  Number value{ 0 };
  do
  {
    value = H::ReadPacket(s, off);

  } while (off + 7 < s.size());

  return value;
}
