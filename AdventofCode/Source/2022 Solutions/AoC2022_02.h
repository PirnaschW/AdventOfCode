template<> Number AoC<2022, 2, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);
  Number z = 0;

  for (const auto& line : v)
  {
    switch (line[0] - 'A' + (line[2] - 'X') * 3)
    {
      case 0:  z += 1 + 3; break;   // A X
      case 1:  z += 1 + 0; break;   // B X
      case 2:  z += 1 + 6; break;   // C X
      case 3:  z += 2 + 6; break;   // A Y
      case 4:  z += 2 + 3; break;   // B Y
      case 5:  z += 2 + 0; break;   // C Y
      case 6:  z += 3 + 0; break;   // A Z
      case 7:  z += 3 + 6; break;   // B Z
      case 8:  z += 3 + 3; break;   // C Z
      default: z = z + 0;  break;
    }
  }
  return z;
}

template<> Number AoC<2022, 2, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);
  Number z = 0;

  for (const auto& line : v)
  {
    switch (line[0] - 'A' + (line[2] - 'X') * 3)
    {
      case 0:  z += 3 + 0; break;   // A X=lose
      case 1:  z += 1 + 0; break;   // B X
      case 2:  z += 2 + 0; break;   // C X
      case 3:  z += 1 + 3; break;   // A Y=tie
      case 4:  z += 2 + 3; break;   // B Y
      case 5:  z += 3 + 3; break;   // C Y
      case 6:  z += 2 + 6; break;   // A Z=win
      case 7:  z += 3 + 6; break;   // B Z
      case 8:  z += 1 + 6; break;   // C Z
      default: z = z + 0;  break;
    }
  }
  return z;
}

