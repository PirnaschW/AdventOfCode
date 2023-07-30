template<> Number AoC<2021, 23, A>(std::istream& input)
{
  struct H
  {
    int nCases{};
    int minE{ std::numeric_limits<int>::max() };
  };
  static H result;

  class Cave
  {
  public:
    Cave(void) {}
  public:
    std::array<char, 15> cave{ '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };
    int level{ 0 };
    bool CanMoveThrough(int i1 = -1, int i2 = -1, int i3 = -1, int i4 = -1, int i5 = -1, int i6 = -1)
    {
      return
        (i1 == -1 || cave[i1] == '.') &&
        (i2 == -1 || cave[i2] == '.') &&
        (i3 == -1 || cave[i3] == '.') &&
        (i4 == -1 || cave[i4] == '.') &&
        (i5 == -1 || cave[i5] == '.') &&
        (i6 == -1 || cave[i6] == '.');
    }

    Cave Move(int from, int to)
    {
      Cave c = *this;
      std::swap(c.cave[from], c.cave[to]);
      //std::cout << level << std::string(level * 2, ' ') << "Move " << c.cave[to] << " from " << from << " to " << to << std::endl;
      if (++result.nCases % 1'000'000 == 0)
      {
//        std::cout << result.nCases << std::endl;
      }
      return c;
    }

    static int GetCost(char c)
    {
      switch (c)
      {
        case 'A': return 1;
        case 'B': return 10;
        case 'C': return 100;
        case 'D': return 1000;
        default: assert(false); return 0;
      }
    }
    bool Finished(int e)
    {
      if (cave[7] == 'A' && cave[8] == 'A' &&
          cave[9] == 'B' && cave[10] == 'B' &&
          cave[11] == 'C' && cave[12] == 'C' &&
          cave[13] == 'D' && cave[14] == 'D')
      {
        if (e < result.minE)
        {
          result.minE = e;
//          std::cout << "new min: " << result.minE << std::endl;
        }
        return true;
      }
      return false;
    }

    void TryAll(int e)
    {
      if (Finished(e)) return;
      if (e >= result.minE) return; // can only get worse!
      ++level;
      TryAll00(e);
      TryAll01(e);
      TryAll02(e);
      TryAll03(e);
      TryAll04(e);
      TryAll05(e);
      TryAll06(e);
      TryAll07(e);
      TryAll08(e);
      TryAll09(e);
      TryAll10(e);
      TryAll11(e);
      TryAll12(e);
      TryAll13(e);
      TryAll14(e);
      --level;
    }

    void TryAll00(int e)
    {
      constexpr int i = 0;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(1, 7, 8)) Move(i, 8).TryAll(e + 4 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(1, 7)) Move(i, 7).TryAll(e + 3 * GetCost(ch));
          break;
        case 'B':
          if (CanMoveThrough(1, 2, 9, 10)) Move(i, 10).TryAll(e + 6 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(1, 2, 9)) Move(i, 9).TryAll(e + 5 * GetCost(ch));
          break;
        case 'C':
          if (CanMoveThrough(1, 2, 3, 11, 12)) Move(i, 12).TryAll(e + 8 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(1, 2, 3, 11)) Move(i, 11).TryAll(e + 7 * GetCost(ch));
          break;
        case 'D':
          if (CanMoveThrough(1, 2, 3, 4, 13, 14)) Move(i, 14).TryAll(e + 10 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(1, 2, 3, 4, 13)) Move(i, 13).TryAll(e + 9 * GetCost(ch));
          break;
        default: assert(false); break;
      }
    }
    
    void TryAll01(int e)
    {
      constexpr int i = 1;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(7, 8)) Move(i, 8).TryAll(e + 3 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(7)) Move(i, 7).TryAll(e + 2 * GetCost(ch));
          break;
        case 'B':
          if (CanMoveThrough(2, 9, 10)) Move(i, 10).TryAll(e + 5 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(2, 9)) Move(i, 9).TryAll(e + 4 * GetCost(ch));
          break;
        case 'C':
          if (CanMoveThrough(2, 3, 11, 12)) Move(i, 12).TryAll(e + 7 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(2, 3, 11)) Move(i, 11).TryAll(e + 6 * GetCost(ch));
          break;
        case 'D':
          if (CanMoveThrough(2, 3, 4, 13, 14)) Move(i, 14).TryAll(e + 9 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(2, 3, 4, 13)) Move(i, 13).TryAll(e + 8 * GetCost(ch));
          break;
        default: assert(false); break;
      }
    }
    
    void TryAll02(int e)
    {
      constexpr int i = 2;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(7, 8)) Move(i, 8).TryAll(e + 3 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(7)) Move(i, 7).TryAll(e + 2 * GetCost(ch));
          break;
        case 'B':
          if (CanMoveThrough(9, 10)) Move(i, 10).TryAll(e + 3 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(9)) Move(i, 9).TryAll(e + 2 * GetCost(ch));
          break;
        case 'C':
          if (CanMoveThrough(3, 11, 12)) Move(i, 12).TryAll(e + 5 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(3, 11)) Move(i, 11).TryAll(e + 4 * GetCost(ch));
          break;
        case 'D':
          if (CanMoveThrough(3, 4, 13, 14)) Move(i, 14).TryAll(e + 7 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(3, 4, 13)) Move(i, 13).TryAll(e + 6 * GetCost(ch));
          break;
        default: assert(false); break;
      }
    }

    void TryAll03(int e)
    {
      constexpr int i = 3;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(2, 7, 8)) Move(i, 8).TryAll(e + 5 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(2, 7)) Move(i, 7).TryAll(e + 4 * GetCost(ch));
          break;
        case 'B':
          if (CanMoveThrough(9, 10)) Move(i, 10).TryAll(e + 3 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(9)) Move(i, 9).TryAll(e + 2 * GetCost(ch));
          break;
        case 'C':
          if (CanMoveThrough(11, 12)) Move(i, 12).TryAll(e + 3 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(11)) Move(i, 11).TryAll(e + 2 * GetCost(ch));
          break;
        case 'D':
          if (CanMoveThrough(4, 13, 14)) Move(i, 14).TryAll(e + 5 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(4, 13)) Move(i, 13).TryAll(e + 4 * GetCost(ch));
          break;
        default: assert(false); break;
      }
    }

    void TryAll04(int e)
    {
      constexpr int i = 4;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(2, 3, 7, 8)) Move(i, 8).TryAll(e + 7 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(2, 3, 7)) Move(i, 7).TryAll(e + 6 * GetCost(ch));
          break;
        case 'B':
          if (CanMoveThrough(3, 9, 10)) Move(i, 10).TryAll(e + 5 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(3, 9)) Move(i, 9).TryAll(e + 4 * GetCost(ch));
          break;
        case 'C':
          if (CanMoveThrough(11, 12)) Move(i, 12).TryAll(e + 3 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(11)) Move(i, 11).TryAll(e + 2 * GetCost(ch));
          break;
        case 'D':
          if (CanMoveThrough(13, 14)) Move(i, 14).TryAll(e + 3 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(13)) Move(i, 13).TryAll(e + 2 * GetCost(ch));
          break;
        default: assert(false); break;
      }
    }

    void TryAll05(int e)
    {
      constexpr int i = 5;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(2, 3, 4, 7, 8)) Move(i, 8).TryAll(e + 9 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(2, 3, 4, 7)) Move(i, 7).TryAll(e + 8 * GetCost(ch));
          break;
        case 'B':
          if (CanMoveThrough(3, 4, 9, 10)) Move(i, 10).TryAll(e + 7 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(3, 4, 9)) Move(i, 9).TryAll(e + 6 * GetCost(ch));
          break;
        case 'C':
          if (CanMoveThrough(4, 11, 12)) Move(i, 12).TryAll(e + 5 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(4, 11)) Move(i, 11).TryAll(e + 4 * GetCost(ch));
          break;
        case 'D':
          if (CanMoveThrough(13, 14)) Move(i, 14).TryAll(e + 3 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(13)) Move(i, 13).TryAll(e + 2 * GetCost(ch));
          break;
        default: assert(false); break;
      }
    }

    void TryAll06(int e)
    {
      constexpr int i = 6;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(2, 3, 4, 5, 7, 8)) Move(i, 8).TryAll(e + 10 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(2, 3, 4, 5, 7)) Move(i, 7).TryAll(e + 9 * GetCost(ch));
          break;
        case 'B':
          if (CanMoveThrough(3, 4, 5, 9, 10)) Move(i, 10).TryAll(e + 8 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(3, 4, 5, 9)) Move(i, 9).TryAll(e + 7 * GetCost(ch));
          break;
        case 'C':
          if (CanMoveThrough(4, 5, 11, 12)) Move(i, 12).TryAll(e + 6 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(4, 5, 11)) Move(i, 11).TryAll(e + 5 * GetCost(ch));
          break;
        case 'D':
          if (CanMoveThrough(5, 13, 14)) Move(i, 14).TryAll(e + 4 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(5, 13)) Move(i, 13).TryAll(e + 3 * GetCost(ch));
          break;
        default: assert(false); break;
      }
    }

    void TryAll07(int e)
    {
      constexpr int i = 7;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(8)) Move(i, 8).TryAll(e + 1 * GetCost(ch));
          else if (cave[8] == ch); // no legal moves
          else trymoveout = true;
          break;
        case 'B':
          if (CanMoveThrough(2, 9, 10)) Move(i, 10).TryAll(e + 5 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(2, 9)) Move(i, 9).TryAll(e + 4 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'C':
          if (CanMoveThrough(2, 3, 11, 12)) Move(i, 12).TryAll(e + 7 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(2, 3, 11)) Move(i, 11).TryAll(e + 6 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'D':
          if (CanMoveThrough(2, 3, 4, 13, 14)) Move(i, 14).TryAll(e + 9 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(2, 3, 4, 13)) Move(i, 13).TryAll(e + 8 * GetCost(ch));
          else trymoveout = true;
          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(1, 0))          Move(i, 0).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(1))             Move(i, 1).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(2))             Move(i, 2).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(2, 3))          Move(i, 3).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4))       Move(i, 4).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4, 5))    Move(i, 5).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4, 5, 6)) Move(i, 6).TryAll(e + 9 * GetCost(ch));
      }
    }

    void TryAll08(int e)
    {
      constexpr int i = 8;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          break; // no legal moves
        case 'B':
          if (!CanMoveThrough(7)); // no legal moves
          else if (CanMoveThrough(2, 9, 10)) Move(i, 10).TryAll(e + 6 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(2, 9)) Move(i, 9).TryAll(e + 5 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'C':
          if (!CanMoveThrough(7)); // no legal moves
          else if (CanMoveThrough(2, 3, 11, 12)) Move(i, 12).TryAll(e + 8 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(2, 3, 11)) Move(i, 11).TryAll(e + 7 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'D':
          if (!CanMoveThrough(7)); // no legal moves
          else if (CanMoveThrough(2, 3, 4, 13, 14)) Move(i, 14).TryAll(e + 10 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(2, 3, 4, 13)) Move(i, 13).TryAll(e + 9 * GetCost(ch));
          else trymoveout = true;
          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(1, 0))          Move(i, 0).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(1))             Move(i, 1).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(2))             Move(i, 2).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(2, 3))          Move(i, 3).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4))       Move(i, 4).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4, 5))    Move(i, 5).TryAll(e + 9 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4, 5, 6)) Move(i, 6).TryAll(e + 10 * GetCost(ch));
      }
    }

    void TryAll09(int e)
    {
      constexpr int i = 9;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(2, 7, 8)) Move(i, 8).TryAll(e + 5 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(2, 7)) Move(i, 7).TryAll(e + 4 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'B':
          if (CanMoveThrough(10)) Move(i, 10).TryAll(e + 1 * GetCost(ch));
          else if (cave[10] == ch); // no legal moves
          else trymoveout = true;
          break;
        case 'C':
          if (CanMoveThrough(3, 11, 12)) Move(i, 12).TryAll(e + 5 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(3, 11)) Move(i, 11).TryAll(e + 4 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'D':
          if (CanMoveThrough(3, 4, 13, 14)) Move(i, 14).TryAll(e + 7 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(3, 4, 13)) Move(i, 13).TryAll(e + 6 * GetCost(ch));
          else trymoveout = true;
          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(2, 1, 0))       Move(i, 0).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(2, 1))          Move(i, 1).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(2))             Move(i, 2).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(3))             Move(i, 3).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(3, 4))          Move(i, 4).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(3, 4, 5))       Move(i, 5).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(3, 4, 5, 6))    Move(i, 6).TryAll(e + 7 * GetCost(ch));
      }
    }

    void TryAll10(int e)
    {
      constexpr int i = 10;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          if (!CanMoveThrough(9)); // no legal moves
          else if (CanMoveThrough(2, 7, 8)) Move(i, 8).TryAll(e + 6 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(2, 7)) Move(i, 7).TryAll(e + 5 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'B':
          break; // no legal moves
        case 'C':
          if (!CanMoveThrough(9)); // no legal moves
          else if (CanMoveThrough(3, 11, 12)) Move(i, 12).TryAll(e + 6 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(3, 11)) Move(i, 11).TryAll(e + 5 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'D':
          if (!CanMoveThrough(9)); // no legal moves
          else if (CanMoveThrough(3, 4, 13, 14)) Move(i, 14).TryAll(e + 8 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(3, 4, 13)) Move(i, 13).TryAll(e + 7 * GetCost(ch));
          else trymoveout = true;
          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(2, 1, 0))       Move(i, 0).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(2, 1))          Move(i, 1).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(2))             Move(i, 2).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(3))             Move(i, 3).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(3, 4))          Move(i, 4).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(3, 4, 5))       Move(i, 5).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(3, 4, 5, 6))    Move(i, 6).TryAll(e + 8 * GetCost(ch));
      }
    }

    void TryAll11(int e)
    {
      constexpr int i = 11;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(3, 2, 7, 8)) Move(i, 8).TryAll(e + 7 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(3, 2, 7)) Move(i, 7).TryAll(e + 6 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'B':
          if (CanMoveThrough(3, 9, 10)) Move(i, 10).TryAll(e + 5 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(3, 9)) Move(i, 9).TryAll(e + 4 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'C':
          if (CanMoveThrough(12)) Move(i, 12).TryAll(e + 1 * GetCost(ch));
          else if (cave[12] == ch); // no legal moves
          else trymoveout = true;
          break;
        case 'D':
          if (CanMoveThrough(4, 13, 14)) Move(i, 14).TryAll(e + 5 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(4, 13)) Move(i, 13).TryAll(e + 4 * GetCost(ch));
          else trymoveout = true;
          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(3, 2, 1, 0))       Move(i, 0).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(3, 2, 1))          Move(i, 1).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(3, 2))             Move(i, 2).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(3))                Move(i, 3).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(4))                Move(i, 4).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(4, 5))             Move(i, 5).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(4, 5, 6))          Move(i, 6).TryAll(e + 5 * GetCost(ch));
      }
    }

    void TryAll12(int e)
    {
      constexpr int i = 12;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          if (!CanMoveThrough(11)); // no legal moves
          else if (CanMoveThrough(3, 2, 7, 8)) Move(i, 8).TryAll(e + 8 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(3, 2, 7)) Move(i, 7).TryAll(e + 7 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'B':
          if (!CanMoveThrough(11)); // no legal moves
          else if (CanMoveThrough(3, 9, 10)) Move(i, 10).TryAll(e + 6 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(3, 9)) Move(i, 9).TryAll(e + 5 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'C':
          break; // no legal moves
        case 'D':
          if (!CanMoveThrough(11)); // no legal moves
          else if (CanMoveThrough(4, 13, 14)) Move(i, 14).TryAll(e + 6 * GetCost(ch));
          else if (cave[14] == ch && CanMoveThrough(4, 13)) Move(i, 13).TryAll(e + 5 * GetCost(ch));
          else trymoveout = true;
          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(3, 2, 1, 0))       Move(i, 0).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(3, 2, 1))          Move(i, 1).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(3, 2))             Move(i, 2).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(3))                Move(i, 3).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(4))                Move(i, 4).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(4, 5))             Move(i, 5).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(4, 5, 6))          Move(i, 6).TryAll(e + 6 * GetCost(ch));
      }
    }

    void TryAll13(int e)
    {
      constexpr int i = 13;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          if (CanMoveThrough(4, 3, 2, 7, 8)) Move(i, 8).TryAll(e + 9 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(4, 3, 2, 7)) Move(i, 7).TryAll(e + 8 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'B':
          if (CanMoveThrough(4, 3, 9, 10)) Move(i, 10).TryAll(e + 7 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(4, 3, 9)) Move(i, 9).TryAll(e + 6 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'C':
          if (CanMoveThrough(4, 11, 12)) Move(i, 12).TryAll(e + 5 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(4, 11)) Move(i, 11).TryAll(e + 4 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'D':
          if (CanMoveThrough(14)) Move(i, 14).TryAll(e + 1 * GetCost(ch));
          else if (cave[14] == ch); // no legal moves
          else trymoveout = true;
          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(4, 3, 2, 1, 0))    Move(i, 0).TryAll(e + 9 * GetCost(ch));
        if (CanMoveThrough(4, 3, 2, 1))       Move(i, 1).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(4, 3, 2))          Move(i, 2).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(4, 3))             Move(i, 3).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(4))                Move(i, 4).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(5))                Move(i, 5).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(5, 6))             Move(i, 6).TryAll(e + 3 * GetCost(ch));
      }
    }

    void TryAll14(int e)
    {
      constexpr int i = 14;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = false;
      switch (ch)
      {
        case 'A':
          if (!CanMoveThrough(13)); // no legal moves
          else if (CanMoveThrough(4, 3, 2, 7, 8)) Move(i, 8).TryAll(e + 10 * GetCost(ch));
          else if (cave[8] == ch && CanMoveThrough(4, 3, 2, 7)) Move(i, 7).TryAll(e + 9 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'B':
          if (!CanMoveThrough(13)); // no legal moves
          else if (CanMoveThrough(4, 3, 9, 10)) Move(i, 10).TryAll(e + 8 * GetCost(ch));
          else if (cave[10] == ch && CanMoveThrough(4, 3, 9)) Move(i, 9).TryAll(e + 7 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'C':
          if (!CanMoveThrough(13)); // no legal moves
          else if (CanMoveThrough(4, 11, 12)) Move(i, 12).TryAll(e + 6 * GetCost(ch));
          else if (cave[12] == ch && CanMoveThrough(4, 11)) Move(i, 11).TryAll(e + 5 * GetCost(ch));
          else trymoveout = true;
          break;
        case 'D':
          break; // no legal moves
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(4, 3, 2, 1, 0))    Move(i, 0).TryAll(e + 10 * GetCost(ch));
        if (CanMoveThrough(4, 3, 2, 1))       Move(i, 1).TryAll(e + 9 * GetCost(ch));
        if (CanMoveThrough(4, 3, 2))          Move(i, 2).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(4, 3))             Move(i, 3).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(4))                Move(i, 4).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(5))                Move(i, 5).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(5, 6))             Move(i, 6).TryAll(e + 4 * GetCost(ch));
      }
    }


  };

  //using Cave = std::array<char, 15>;
  //Cave c{ '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };


  Cave c{};

  std::string line{};
  getline(input, line);  // #############
  getline(input, line);  // #...........#
  getline(input, line);  // ###D#A#C#A###
  c.cave[ 7] = line[3];
  c.cave[ 9] = line[5];
  c.cave[11] = line[7];
  c.cave[13] = line[9];
  getline(input, line);  //   #D#C#B#B#
  c.cave[ 8] = line[3];
  c.cave[10] = line[5];
  c.cave[12] = line[7];
  c.cave[14] = line[9];
  getline(input, line);  //   #########

  c.TryAll(0);

  int z = result.minE;
  return z;
}

template<> Number AoC<2021, 23, B>(std::istream& input)
{
  struct H
  {
    int nCases{};
    int minE{ std::numeric_limits<int>::max() };
  };
  static H result;
  result.nCases = 0;
  result.minE = std::numeric_limits<int>::max();

  using HomeIndex = std::array<int,4>;

  class Cave
  {
  public:
    Cave(void) {}
  public:
    std::array<char, 23> cave{ '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };
    int level{ 0 };
    bool CanMoveThrough(int i1 = -1, int i2 = -1, int i3 = -1, int i4 = -1, int i5 = -1, int i6 = -1, int i7 = -1, int i8 = -1, int i9 = -1, int i10 = -1)
    {
      return
        (i1 == -1 || cave[i1] == '.') &&
        (i2 == -1 || cave[i2] == '.') &&
        (i3 == -1 || cave[i3] == '.') &&
        (i4 == -1 || cave[i4] == '.') &&
        (i5 == -1 || cave[i5] == '.') &&
        (i6 == -1 || cave[i6] == '.') &&
        (i7 == -1 || cave[i7] == '.') &&
        (i8 == -1 || cave[i8] == '.') &&
        (i9 == -1 || cave[i9] == '.') &&
        (i10 == -1 || cave[i10] == '.');
    }

    Cave Move(int from, int to)
    {
      Cave c = *this;
      std::swap(c.cave[from], c.cave[to]);
      //if (level > 100)
      //  std::cout << level << std::string(level * 2, ' ') << "Move " << c.cave[to] << " from " << from << " to " << to << std::endl;
      //if (++result.nCases % 1'000'000 == 0)
      //{
      //  std::cout << result.nCases << std::endl;
      //}
      return c;
    }

    constexpr static int GetCost(char c)
    {
      switch (c)
      {
        case 'A': return 1;
        case 'B': return 10;
        case 'C': return 100;
        case 'D': return 1000;
        default: assert(false); return 0;
      }
    }

    bool Finished(int e)
    {
      if (HomeFilled('A', 4) && HomeFilled('B', 4) && HomeFilled('C', 4) && HomeFilled('D', 4))
      {
        if (e < result.minE)
        {
          result.minE = e;
          //std::cout << "new min: " << result.minE << std::endl;
        }
        return true;
      }
      return false;
    }

    void TryAll(int e)
    {
      if (Finished(e)) return;
      if (e >= result.minE) return; // can only get worse!
      ++level;
      TryAll00(e);
      TryAll01(e);
      TryAll02(e);
      TryAll03(e);
      TryAll04(e);
      TryAll05(e);
      TryAll06(e);
      TryAll07(e);
      TryAll08(e);
      TryAll09(e);
      TryAll10(e);
      TryAll11(e);
      TryAll12(e);
      TryAll13(e);
      TryAll14(e);
      TryAll15(e);
      TryAll16(e);
      TryAll17(e);
      TryAll18(e);
      TryAll19(e);
      TryAll20(e);
      TryAll21(e);
      TryAll22(e);
      --level;
    }

    constexpr static HomeIndex GetIndex(char ch)
    {
      constexpr HomeIndex indexA{  7,  8, 15, 16 };
      constexpr HomeIndex indexB{  9, 10, 17, 18 };
      constexpr HomeIndex indexC{ 11, 12, 19, 20 };
      constexpr HomeIndex indexD{ 13, 14, 21, 22 };
      switch (ch)
      {
        case 'A': return indexA;
        case 'B': return indexB;
        case 'C': return indexC;
        case 'D': return indexD;
        default: assert(false); return indexA;
      }
    }

    bool TryFillHome(int e, int from, int e0, char ch)
    {
      const HomeIndex index = GetIndex(ch);
      if (CanMoveThrough(index[0], index[1], index[2], index[3]))
      {
        Move(from, index[3]).TryAll(e + (e0 + 3) * GetCost(ch));
        return true;
      }
      if (cave[index[3]] != ch) return false;
      if (CanMoveThrough(index[0], index[1], index[2]))
      {
        Move(from, index[2]).TryAll(e + (e0 + 2) * GetCost(ch));
        return true;
      }
      if (cave[index[2]] != ch) return false;
      if (CanMoveThrough(index[0], index[1]))
      {
        Move(from, index[1]).TryAll(e + (e0 + 1) * GetCost(ch));
        return true;
      }
      if (cave[index[1]] != ch) return false;
      if (CanMoveThrough(index[0]))
      {
        Move(from, index[0]).TryAll(e + e0 * GetCost(ch));
        return true;
      }
      return false;
    }

    bool HomeFilled(char ch, int n)
    {
      const HomeIndex index = GetIndex(ch);
      switch (n)
      {
        case 1: return cave[index[3]] == ch;
        case 2: return cave[index[3]] == ch && cave[index[2]] == ch;
        case 3: return cave[index[3]] == ch && cave[index[2]] == ch && cave[index[1]] == ch;
        case 4: return cave[index[3]] == ch && cave[index[2]] == ch && cave[index[1]] == ch && cave[index[0]] == ch;
        default: assert(false); return false;
      }
    }

    void TryAll00(int e)
    {
      constexpr int i = 0;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A': if (CanMoveThrough(1))          TryFillHome(e, i, 3, ch); break;
        case 'B': if (CanMoveThrough(1, 2))       TryFillHome(e, i, 5, ch); break;
        case 'C': if (CanMoveThrough(1, 2, 3))    TryFillHome(e, i, 7, ch); break;
        case 'D': if (CanMoveThrough(1, 2, 3, 4)) TryFillHome(e, i, 9, ch); break;
        default: assert(false); break;
      }
    }

    void TryAll01(int e)
    {
      constexpr int i = 1;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':                              TryFillHome(e, i, 2, ch); break;
        case 'B': if (CanMoveThrough(2))       TryFillHome(e, i, 4, ch); break;
        case 'C': if (CanMoveThrough(2, 3))    TryFillHome(e, i, 6, ch); break;
        case 'D': if (CanMoveThrough(2, 3, 4)) TryFillHome(e, i, 8, ch); break;
        default: assert(false); break;
      }
    }

    void TryAll02(int e)
    {
      constexpr int i = 2;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A':                              TryFillHome(e, i, 2, ch); break;
        case 'B':                              TryFillHome(e, i, 2, ch); break;
        case 'C': if (CanMoveThrough(3))       TryFillHome(e, i, 4, ch); break;
        case 'D': if (CanMoveThrough(3, 4))    TryFillHome(e, i, 6, ch); break;
        default: assert(false); break;
      }
    }

    void TryAll03(int e)
    {
      constexpr int i = 3;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A': if (CanMoveThrough(2))       TryFillHome(e, i, 4, ch); break;
        case 'B':                              TryFillHome(e, i, 2, ch); break;
        case 'C':                              TryFillHome(e, i, 2, ch); break;
        case 'D': if (CanMoveThrough(4))       TryFillHome(e, i, 4, ch); break;
        default: assert(false); break;
      }
    }

    void TryAll04(int e)
    {
      constexpr int i = 4;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A': if (CanMoveThrough(3, 2)) TryFillHome(e, i, 6, ch); break;
        case 'B': if (CanMoveThrough(3))    TryFillHome(e, i, 4, ch); break;
        case 'C':                           TryFillHome(e, i, 2, ch); break;
        case 'D':                           TryFillHome(e, i, 2, ch); break;
        default: assert(false); break;
      }
    }

    void TryAll05(int e)
    {
      constexpr int i = 5;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A': if (CanMoveThrough(4, 3, 2)) TryFillHome(e, i, 8, ch); break;
        case 'B': if (CanMoveThrough(4, 3))    TryFillHome(e, i, 6, ch); break;
        case 'C': if (CanMoveThrough(4))       TryFillHome(e, i, 4, ch); break;
        case 'D':                              TryFillHome(e, i, 2, ch); break;
        default: assert(false); break;
      }
    }

    void TryAll06(int e)
    {
      constexpr int i = 6;
      char ch = cave[i];
      if (ch == '.') return;
      switch (ch)
      {
        case 'A': if (CanMoveThrough(5, 4, 3, 2)) TryFillHome(e, i, 9, ch); break;
        case 'B': if (CanMoveThrough(5, 4, 3))    TryFillHome(e, i, 7, ch); break;
        case 'C': if (CanMoveThrough(5, 4))       TryFillHome(e, i, 5, ch); break;
        case 'D': if (CanMoveThrough(5))          TryFillHome(e, i, 3, ch); break;
        default: assert(false); break;
      }
    }


    void TryAll07(int e)
    {
      constexpr int i = 7;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = !HomeFilled(ch, 3);                                               break;
        case 'B': trymoveout = (!CanMoveThrough(2)       || !TryFillHome(e, i, 4, ch));          break;
        case 'C': trymoveout = (!CanMoveThrough(2, 3)    || !TryFillHome(e, i, 6, ch));          break;
        case 'D': trymoveout = (!CanMoveThrough(2, 3, 4) || !TryFillHome(e, i, 8, ch));          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(1, 0))          Move(i, 0).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(1))             Move(i, 1).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(2))             Move(i, 2).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(2, 3))          Move(i, 3).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4))       Move(i, 4).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4, 5))    Move(i, 5).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(2, 3, 4, 5, 6)) Move(i, 6).TryAll(e + 9 * GetCost(ch));
      }
    }

    void TryAll08(int e)
    {
      constexpr int i = 8;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = !HomeFilled(ch, 2);                                               break;
        case 'B': trymoveout = (!CanMoveThrough(7, 2)       || !TryFillHome(e, i, 5, ch));       break;
        case 'C': trymoveout = (!CanMoveThrough(7, 2, 3)    || !TryFillHome(e, i, 7, ch));       break;
        case 'D': trymoveout = (!CanMoveThrough(7, 2, 3, 4) || !TryFillHome(e, i, 9, ch));       break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(7, 1, 0))          Move(i, 0).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(7, 1))             Move(i, 1).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(7, 2))             Move(i, 2).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(7, 2, 3))          Move(i, 3).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(7, 2, 3, 4))       Move(i, 4).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(7, 2, 3, 4, 5))    Move(i, 5).TryAll(e + 9 * GetCost(ch));
        if (CanMoveThrough(7, 2, 3, 4, 5, 6)) Move(i, 6).TryAll(e + 10 * GetCost(ch));
      }
    }

    void TryAll15(int e)
    {
      constexpr int i = 15;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = !HomeFilled(ch, 1);                                               break;
        case 'B': trymoveout = (!CanMoveThrough(8, 7, 2)       || !TryFillHome(e, i,  6, ch));   break;
        case 'C': trymoveout = (!CanMoveThrough(8, 7, 2, 3)    || !TryFillHome(e, i,  8, ch));   break;
        case 'D': trymoveout = (!CanMoveThrough(8, 7, 2, 3, 4) || !TryFillHome(e, i, 10, ch));   break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(8, 7, 1, 0))          Move(i, 0).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(8, 7, 1))             Move(i, 1).TryAll(e +  4 * GetCost(ch));
        if (CanMoveThrough(8, 7, 2))             Move(i, 2).TryAll(e +  4 * GetCost(ch));
        if (CanMoveThrough(8, 7, 2, 3))          Move(i, 3).TryAll(e +  6 * GetCost(ch));
        if (CanMoveThrough(8, 7, 2, 3, 4))       Move(i, 4).TryAll(e +  8 * GetCost(ch));
        if (CanMoveThrough(8, 7, 2, 3, 4, 5))    Move(i, 5).TryAll(e + 10 * GetCost(ch));
        if (CanMoveThrough(8, 7, 2, 3, 4, 5, 6)) Move(i, 6).TryAll(e + 11 * GetCost(ch));
      }
    }

    void TryAll16(int e)
    {
      constexpr int i = 16;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = false;                                                              break; // no legal moves
        case 'B': trymoveout = (!CanMoveThrough(15, 8, 7, 2)       || !TryFillHome(e, i,  7, ch)); break;
        case 'C': trymoveout = (!CanMoveThrough(15, 8, 7, 2, 3)    || !TryFillHome(e, i,  9, ch)); break;
        case 'D': trymoveout = (!CanMoveThrough(15, 8, 7, 2, 3, 4) || !TryFillHome(e, i, 11, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(15, 8, 7, 1, 0))          Move(i, 0).TryAll(e +  6 * GetCost(ch));
        if (CanMoveThrough(15, 8, 7, 1))             Move(i, 1).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(15, 8, 7, 2))             Move(i, 2).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(15, 8, 7, 2, 3))          Move(i, 3).TryAll(e +  7 * GetCost(ch));
        if (CanMoveThrough(15, 8, 7, 2, 3, 4))       Move(i, 4).TryAll(e +  9 * GetCost(ch));
        if (CanMoveThrough(15, 8, 7, 2, 3, 4, 5))    Move(i, 5).TryAll(e + 11 * GetCost(ch));
        if (CanMoveThrough(15, 8, 7, 2, 3, 4, 5, 6)) Move(i, 6).TryAll(e + 12 * GetCost(ch));
      }
    }


    void TryAll09(int e)
    {
      constexpr int i = 9;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(2)   || !TryFillHome(e, i, 4, ch)); break;
        case 'B': trymoveout = !HomeFilled(ch, 3);                                  break;
        case 'C': trymoveout = (!CanMoveThrough(3)   || !TryFillHome(e, i, 4, ch)); break;
        case 'D': trymoveout = (!CanMoveThrough(3,4) || !TryFillHome(e, i, 6, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(2, 1, 0))       Move(i, 0).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(2, 1))          Move(i, 1).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(2))             Move(i, 2).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(3))             Move(i, 3).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(3, 4))          Move(i, 4).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(3, 4, 5))       Move(i, 5).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(3, 4, 5, 6))    Move(i, 6).TryAll(e + 7 * GetCost(ch));
      }
    }

    void TryAll10(int e)
    {
      constexpr int i = 10;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(9, 2)    || !TryFillHome(e, i, 5, ch)); break;
        case 'B': trymoveout = !HomeFilled(ch, 2);                                     break;
        case 'C': trymoveout = (!CanMoveThrough(9, 3)    || !TryFillHome(e, i, 5, ch)); break;
        case 'D': trymoveout = (!CanMoveThrough(9, 3, 4) || !TryFillHome(e, i, 7, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(9, 2, 1, 0))       Move(i, 0).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(9, 2, 1))          Move(i, 1).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(9, 2))             Move(i, 2).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(9, 3))             Move(i, 3).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(9, 3, 4))          Move(i, 4).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(9, 3, 4, 5))       Move(i, 5).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(9, 3, 4, 5, 6))    Move(i, 6).TryAll(e + 8 * GetCost(ch));
      }
    }

    void TryAll17(int e)
    {
      constexpr int i = 17;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(10, 9, 2)   || !TryFillHome(e, i, 6, ch)); break;
        case 'B': trymoveout = !HomeFilled(ch, 1);                                         break;
        case 'C': trymoveout = (!CanMoveThrough(10, 9, 3)   || !TryFillHome(e, i, 6, ch)); break;
        case 'D': trymoveout = (!CanMoveThrough(10, 9, 3,4) || !TryFillHome(e, i, 8, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(10, 9, 2, 1, 0))       Move(i, 0).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(10, 9, 2, 1))          Move(i, 1).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(10, 9, 2))             Move(i, 2).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(10, 9, 3))             Move(i, 3).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(10, 9, 3, 4))          Move(i, 4).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(10, 9, 3, 4, 5))       Move(i, 5).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(10, 9, 3, 4, 5, 6))    Move(i, 6).TryAll(e + 9 * GetCost(ch));
      }
    }

    void TryAll18(int e)
    {
      constexpr int i = 18;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(17, 10, 9, 2)    || !TryFillHome(e, i, 7, ch)); break;
        case 'B': trymoveout = false;                                                           break; // no legal moves                        
        case 'C': trymoveout = (!CanMoveThrough(17, 10, 9, 3)    || !TryFillHome(e, i, 7, ch)); break;
        case 'D': trymoveout = (!CanMoveThrough(17, 10, 9, 3, 4) || !TryFillHome(e, i, 9, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(17, 10, 9, 2, 1, 0))       Move(i, 0).TryAll(e +  8 * GetCost(ch));
        if (CanMoveThrough(17, 10, 9, 2, 1))          Move(i, 1).TryAll(e +  7 * GetCost(ch));
        if (CanMoveThrough(17, 10, 9, 2))             Move(i, 2).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(17, 10, 9, 3))             Move(i, 3).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(17, 10, 9, 3, 4))          Move(i, 4).TryAll(e +  7 * GetCost(ch));
        if (CanMoveThrough(17, 10, 9, 3, 4, 5))       Move(i, 5).TryAll(e +  9 * GetCost(ch));
        if (CanMoveThrough(17, 10, 9, 3, 4, 5, 6))    Move(i, 6).TryAll(e + 10 * GetCost(ch));
      }
    }


    void TryAll11(int e)
    {
      constexpr int i = 11;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(3, 2) || !TryFillHome(e, i, 6, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(3)    || !TryFillHome(e, i, 4, ch)); break;
        case 'C': trymoveout = !HomeFilled(ch, 3);                                   break;
        case 'D': trymoveout = (!CanMoveThrough(4)    || !TryFillHome(e, i, 4, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(3, 2, 1, 0))       Move(i, 0).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(3, 2, 1))          Move(i, 1).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(3, 2))             Move(i, 2).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(3))                Move(i, 3).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(4))                Move(i, 4).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(4, 5))             Move(i, 5).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(4, 5, 6))          Move(i, 6).TryAll(e + 5 * GetCost(ch));
      }
    }

    void TryAll12(int e)
    {
      constexpr int i = 12;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(11, 3, 2) || !TryFillHome(e, i, 7, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(11, 3)    || !TryFillHome(e, i, 5, ch)); break;
        case 'C': trymoveout = !HomeFilled(ch, 2);                                       break;
        case 'D': trymoveout = (!CanMoveThrough(11, 3, 4) || !TryFillHome(e, i, 5, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(11, 3, 2, 1, 0))       Move(i, 0).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(11, 3, 2, 1))          Move(i, 1).TryAll(e + 7 * GetCost(ch));
        if (CanMoveThrough(11, 3, 2))             Move(i, 2).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(11, 3))                Move(i, 3).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(11, 4))                Move(i, 4).TryAll(e + 3 * GetCost(ch));
        if (CanMoveThrough(11, 4, 5))             Move(i, 5).TryAll(e + 5 * GetCost(ch));
        if (CanMoveThrough(11, 4, 5, 6))          Move(i, 6).TryAll(e + 6 * GetCost(ch));
      }
    }

    void TryAll19(int e)
    {
      constexpr int i = 19;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(12, 11, 3, 2) || !TryFillHome(e, i, 8, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(12, 11, 3)    || !TryFillHome(e, i, 6, ch)); break;
        case 'C': trymoveout = !HomeFilled(ch, 1);                                           break;
        case 'D': trymoveout = (!CanMoveThrough(12, 11, 3, 4) || !TryFillHome(e, i, 6, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(12, 11, 3, 2, 1, 0))       Move(i, 0).TryAll(e + 9 * GetCost(ch));
        if (CanMoveThrough(12, 11, 3, 2, 1))          Move(i, 1).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(12, 11, 3, 2))             Move(i, 2).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(12, 11, 3))                Move(i, 3).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(12, 11, 4))                Move(i, 4).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(12, 11, 4, 5))             Move(i, 5).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(12, 11, 4, 5, 6))          Move(i, 6).TryAll(e + 7 * GetCost(ch));
      }
    }

    void TryAll20(int e)
    {
      constexpr int i = 20;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(19, 12, 11, 3, 2) || !TryFillHome(e, i, 9, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(19, 12, 11, 3)    || !TryFillHome(e, i, 7, ch)); break;
        case 'C': trymoveout = false;                                                            break;
        case 'D': trymoveout = (!CanMoveThrough(19, 12, 11, 3, 4) || !TryFillHome(e, i, 7, ch)); break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(19, 12, 11, 3, 2, 1, 0))       Move(i, 0).TryAll(e + 10 * GetCost(ch));
        if (CanMoveThrough(19, 12, 11, 3, 2, 1))          Move(i, 1).TryAll(e +  9 * GetCost(ch));
        if (CanMoveThrough(19, 12, 11, 3, 2))             Move(i, 2).TryAll(e +  7 * GetCost(ch));
        if (CanMoveThrough(19, 12, 11, 3))                Move(i, 3).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(19, 12, 11, 4))                Move(i, 4).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(19, 12, 11, 4, 5))             Move(i, 5).TryAll(e +  7 * GetCost(ch));
        if (CanMoveThrough(19, 12, 11, 4, 5, 6))          Move(i, 6).TryAll(e +  8 * GetCost(ch));
      }
    }


    void TryAll13(int e)
    {
      constexpr int i = 13;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(4, 3, 2) || !TryFillHome(e, i, 8, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(4, 3)    || !TryFillHome(e, i, 6, ch)); break;
        case 'C': trymoveout = (!CanMoveThrough(4)       || !TryFillHome(e, i, 4, ch)); break;
        case 'D': trymoveout = !HomeFilled(ch, 3);                                      break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(4, 3, 2, 1, 0))    Move(i, 0).TryAll(e + 9 * GetCost(ch));
        if (CanMoveThrough(4, 3, 2, 1))       Move(i, 1).TryAll(e + 8 * GetCost(ch));
        if (CanMoveThrough(4, 3, 2))          Move(i, 2).TryAll(e + 6 * GetCost(ch));
        if (CanMoveThrough(4, 3))             Move(i, 3).TryAll(e + 4 * GetCost(ch));
        if (CanMoveThrough(4))                Move(i, 4).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(5))                Move(i, 5).TryAll(e + 2 * GetCost(ch));
        if (CanMoveThrough(5, 6))             Move(i, 6).TryAll(e + 3 * GetCost(ch));
      }
    }

    void TryAll14(int e)
    {
      constexpr int i = 14;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(13, 4, 3, 2) || !TryFillHome(e, i, 9, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(13, 4, 3)    || !TryFillHome(e, i, 7, ch)); break;
        case 'C': trymoveout = (!CanMoveThrough(13, 4)       || !TryFillHome(e, i, 5, ch)); break;
        case 'D': trymoveout = !HomeFilled(ch, 2);                                          break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(13, 4, 3, 2, 1, 0))    Move(i, 0).TryAll(e + 10 * GetCost(ch));
        if (CanMoveThrough(13, 4, 3, 2, 1))       Move(i, 1).TryAll(e +  9 * GetCost(ch));
        if (CanMoveThrough(13, 4, 3, 2))          Move(i, 2).TryAll(e +  7 * GetCost(ch));
        if (CanMoveThrough(13, 4, 3))             Move(i, 3).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(13, 4))                Move(i, 4).TryAll(e +  3 * GetCost(ch));
        if (CanMoveThrough(13, 5))                Move(i, 5).TryAll(e +  3 * GetCost(ch));
        if (CanMoveThrough(13, 5, 6))             Move(i, 6).TryAll(e +  4 * GetCost(ch));
      }
    }

    void TryAll21(int e)
    {
      constexpr int i = 21;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(14, 13, 4, 3, 2) || !TryFillHome(e, i, 10, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(14, 13, 4, 3)    || !TryFillHome(e, i,  8, ch)); break;
        case 'C': trymoveout = (!CanMoveThrough(14, 13, 4)       || !TryFillHome(e, i,  6, ch)); break;
        case 'D': trymoveout = !HomeFilled(ch, 1);                                               break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(14, 13, 4, 3, 2, 1, 0))    Move(i, 0).TryAll(e + 11 * GetCost(ch));
        if (CanMoveThrough(14, 13, 4, 3, 2, 1))       Move(i, 1).TryAll(e + 10 * GetCost(ch));
        if (CanMoveThrough(14, 13, 4, 3, 2))          Move(i, 2).TryAll(e +  8 * GetCost(ch));
        if (CanMoveThrough(14, 13, 4, 3))             Move(i, 3).TryAll(e +  6 * GetCost(ch));
        if (CanMoveThrough(14, 13, 4))                Move(i, 4).TryAll(e +  4 * GetCost(ch));
        if (CanMoveThrough(14, 13, 5))                Move(i, 5).TryAll(e +  4 * GetCost(ch));
        if (CanMoveThrough(14, 13, 5, 6))             Move(i, 6).TryAll(e +  5 * GetCost(ch));
      }
    }

    void TryAll22(int e)
    {
      constexpr int i = 22;
      char ch = cave[i];
      if (ch == '.') return;
      bool trymoveout = true;
      switch (ch)
      {
        case 'A': trymoveout = (!CanMoveThrough(21, 14, 13, 4, 3, 2) || !TryFillHome(e, i, 11, ch)); break;
        case 'B': trymoveout = (!CanMoveThrough(21, 14, 13, 4, 3)    || !TryFillHome(e, i,  9, ch)); break;
        case 'C': trymoveout = (!CanMoveThrough(21, 14, 13, 4)       || !TryFillHome(e, i,  7, ch)); break;
        case 'D': trymoveout = false;                                                                break;
        default: assert(false); break;
      }
      if (trymoveout)
      {
        if (CanMoveThrough(21, 14, 13, 4, 3, 2, 1, 0))    Move(i, 0).TryAll(e + 12 * GetCost(ch));
        if (CanMoveThrough(21, 14, 13, 4, 3, 2, 1))       Move(i, 1).TryAll(e + 11 * GetCost(ch));
        if (CanMoveThrough(21, 14, 13, 4, 3, 2))          Move(i, 2).TryAll(e +  9 * GetCost(ch));
        if (CanMoveThrough(21, 14, 13, 4, 3))             Move(i, 3).TryAll(e +  7 * GetCost(ch));
        if (CanMoveThrough(21, 14, 13, 4))                Move(i, 4).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(21, 14, 13, 5))                Move(i, 5).TryAll(e +  5 * GetCost(ch));
        if (CanMoveThrough(21, 14, 13, 5, 6))             Move(i, 6).TryAll(e +  6 * GetCost(ch));
      }
    }

  };

  //using Cave = std::array<char, 15>;
  //Cave c{ '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };


  Cave c{};

  std::string line{};
  getline(input, line);  // #############
  getline(input, line);  // #...........#
  getline(input, line);  // ###D#A#C#A###
  c.cave[7] = line[3];
  c.cave[9] = line[5];
  c.cave[11] = line[7];
  c.cave[13] = line[9];
  getline(input, line);  //   #D#C#B#B#
  c.cave[16] = line[3];
  c.cave[18] = line[5];
  c.cave[20] = line[7];
  c.cave[22] = line[9];
  getline(input, line);  //   #########

  c.cave[ 8] = 'D';
  c.cave[10] = 'C';
  c.cave[12] = 'B';
  c.cave[14] = 'A';
  c.cave[15] = 'D';
  c.cave[17] = 'B';
  c.cave[19] = 'A';
  c.cave[21] = 'C';

  c.TryAll(0);

  Number z = result.minE;
  return z;
}
