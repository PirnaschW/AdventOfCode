template<> Number AoC<2021, 21, A>(std::istream& input)
{
  struct H
  {
    static int Roll(void)
    {
    }
  };

  std::string line{};
  getline(input, line);
  int z{0};
  int p1{ 0 };
  assert(sscanf_s(line.c_str(), "Player %d starting position : %d", &z, &p1) == 2);
  getline(input, line);
  int p2{ 0 };
  assert(sscanf_s(line.c_str(), "Player %d starting position : %d", &z, &p2) == 2);

  int die{ 0 };

  int score1 = { 0 };
  int score2 = { 0 };
  int n{ 0 };
  while (true)
  {
    p1 += ++die;
    die %= 100;
    p1 += ++die;
    die %= 100;
    p1 += ++die;
    die %= 100;
    ++n;
    score1 += (p1 - 1) % 10 + 1;
    if (score1 >= 1000)break;
    p2 += ++die;
    die %= 100;
    p2 += ++die;
    die %= 100;
    p2 += ++die;
    die %= 100;
    ++n;
    score2 += (p2 - 1) % 10 + 1;
    if (score2 >= 1000)break;
  }
  int zz = (score1 > 1000 ? score2 : score1)* n * 3;

  return zz;
}

template<> Number AoC<2021, 21, B>(std::istream& input)
{
  struct H
  {
    static int Roll(void)
    {
    }
  };

  std::string line{};
  getline(input, line);
  int z{ 0 };
  int p1{ 0 };
  assert(sscanf_s(line.c_str(), "Player %d starting position : %d", &z, &p1) == 2);
  getline(input, line);
  int p2{ 0 };
  assert(sscanf_s(line.c_str(), "Player %d starting position : %d", &z, &p2) == 2);

  //int die{ 0 };

  //int score1 = { 0 };
  //int score2 = { 0 };
  //int n{ 0 };


  struct Scores
  {
    int score;
    Number n{};
  };


  auto* ppositions = new std::array<std::array< std::array<std::array<Number, 21>, 10>, 21>, 10>{};    // pos[P1position][P1score][P2position][P2score]
  auto& positions = *ppositions;

  positions[p1 % 10][0][p2 % 10][0] = 1;
  auto newpositions = *(new std::array<std::array< std::array<std::array<Number, 21>, 10>, 21>, 10>{});    // pos[P1position][P1score][P2position][P2score]

  std::vector<Number> dd{ 1,3,6,7,6,3,1 }; // chance to roll 3, 4, 5, 6, 7, 8, 9

  Number p1wins{ 0 };
  Number p2wins{ 0 };
  bool more = true;
  while (more)
  {
    newpositions = { 0 };
    more = false;

    for (int p1pos = 0; p1pos < 10; ++p1pos)
    {
      for (int p1score = 0; p1score < 21; ++p1score)
      {
        for (int p2pos = 0; p2pos < 10; ++p2pos)
        {
          for (int p2score = 0; p2score < 21; ++p2score)
          {
            if (positions[p1pos][p1score][p2pos][p2score] == 0) continue;

            for (int p1r = 0; p1r < 7; ++p1r)  // all possible throws for p1
            {
              int newp1pos = (p1pos + p1r + 3) % 10;
              int newp1score = p1score + (newp1pos + 9) % 10 + 1;
              Number newcount1 = positions[p1pos][p1score][p2pos][p2score] * dd[p1r];
              if (newp1score >= 21)
              {
                p1wins += newcount1;
              }
              else
              {
                for (int p2r = 0; p2r < 7; ++p2r)  // all possible throws for p2
                {
                  int newp2pos = (p2pos + p2r + 3) % 10;
                  int newp2score = p2score + (newp2pos + 9) % 10 + 1;
                  Number newcount2 = newcount1 * dd[p2r];
                  if (newp2score >= 21)
                  {
                    p2wins += newcount2;
                  }
                  else
                  {
                    newpositions[newp1pos][newp1score][newp2pos][newp2score] += newcount2;
                    more = true;
                  }
                }
              }
            }
          }
        }
      }
    }
    positions = newpositions;

    Number remaining{ 0 };
    for (int p1pos = 0; p1pos < 10; ++p1pos)
      for (int p1score = 0; p1score < 21; ++p1score)
        for (int p2pos = 0; p2pos < 10; ++p2pos)
          for (int p2score = 0; p2score < 21; ++p2score)
            remaining += positions[p1pos][p1score][p2pos][p2score];
  //std::cout << "remaining: " << remaining << std::endl;
  }

  Number m = std::max(p1wins, p2wins);
  return m;
}
