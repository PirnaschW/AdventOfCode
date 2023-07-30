template<> Number AoC<2020, 25, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };
  //  using Number = long long;

  Number pubkeyc{};
  Number pubkeyd{};
  Number subj{ 7 };
  input >> pubkeyc >> pubkeyd;

  Number zc{ 1 };
  int loopc{ 0 };
  do
  {
    zc *= subj;
    zc %= 20201227;
    ++loopc;
  } while (zc != pubkeyc);

  Number zd{ 1 };
  int loopd{ 0 };
  do
  {
    zd *= subj;
    zd %= 20201227;
    ++loopd;
  } while (zd != pubkeyd);

  zc = 1;
  for (int i = 0; i < loopc; ++i)
  {
    zc *= pubkeyd;
    zc %= 20201227;
  }
  zd = 1;
  for (int i = 0; i < loopd; ++i)
  {
    zd *= pubkeyc;
    zd %= 20201227;
  }
  assert(zd == zc);

  return zc;
}

template<> Number AoC<2020, 25, B>(std::istream& /*input*/)
{
  throw ' ';
}
