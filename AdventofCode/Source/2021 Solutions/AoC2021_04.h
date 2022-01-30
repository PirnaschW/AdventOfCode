#define NEW_CODE

#ifdef NEW_CODE

constexpr size_t BingoCardSize = 5;
using Card = std::array<int, BingoCardSize * BingoCardSize>;

class BingoCard
{
public:
  static BingoCard Create(std::istream& input);                 // construct by reading the numbers from input
  std::size_t DrawNumbers(const std::vector<int>& n) noexcept;  // draw numbers till 'bingo'
  int GetRemainder() const noexcept;                            // get sum of numbers remaining after 'bingo'

private:
  BingoCard(Card& n) noexcept : number(n) {}                    // constructor
  bool HasBingo() const noexcept;                               // check for 'bingo'


private:
  const Card number;                                            // numbers on the bingo card
  std::array<bool, BingoCardSize* BingoCardSize> hit{ false };  // flags if a number was hit
};

BingoCard BingoCard::Create(std::istream& input)
{
  Card n;
  for (int i = 0; i < n.size(); ++i) input >> n[i];
  return BingoCard(n);
}

bool BingoCard::HasBingo(void) const noexcept  // check for 'bingo'. note: diagonals are NOT considered 'bingo'
{
  for (int i = 0; i < BingoCardSize; ++i)
  {
    bool row{ true };
    bool col{ true };
    for (int j = 0; j < BingoCardSize; ++j)
    {
      row &= hit[BingoCardSize * i + j];   // check along row
      col &= hit[i + BingoCardSize * j];   // check along column
    }
    if (row || col) return true;
  }
  return false;
}

std::size_t BingoCard::DrawNumbers(const std::vector<int>& draw) noexcept
{
  for (int n = 0; n < draw.size(); ++n)
  {
    for (int j = 0; j < BingoCardSize * BingoCardSize; ++j)
    {
      if (number[j] == draw[n])
      {
        hit[j] = true;
        if (HasBingo()) return n;
        break;
      }
    }
  }
  return draw.size();
}

int BingoCard::GetRemainder(void) const noexcept
{
  int sum{ 0 };
  for (int i = 0; i < BingoCardSize * BingoCardSize; ++i)
  {
    if (!hit[i]) sum += number[i];
  }
  return sum;
}


void AoC2021_04A(std::istream& input)
{
  std::string line{};

  // read all numbers drawn during the game
  std::vector<int> draw{};
  getline(input, line);
  std::istringstream str(line);
  int z0{ 0 };
  while (str >> z0) {
    draw.emplace_back(z0);
    char comma{};
    str >> comma; // read the comma and ignore it
  }

  // read all Bingocards
  std::vector<BingoCard> board{};
  while (getline(input, line))     // the success of this blank line read means there is another board coming
  {
    board.emplace_back(BingoCard::Create(input));
  }

  // find the BingoCards with the earliest [Part 1] and latest [Part 2] 'bingo' (that is, the minimum / maximum of DrawNumbers return value)
  size_t min{ std::numeric_limits<size_t>::max() };
  size_t mini{ 0 };
  size_t max{ 0 };
  size_t maxi{ 0 };
  for (int i = 0; i < board.size(); ++i)
  {
    auto n = board[i].DrawNumbers(draw);
    if (n < min)
    {
      min = n;
      mini = i;
    }
    if (n > max)
    {
      max = n;
      maxi = i;
    }
  }

  int z1 = board[mini].GetRemainder() * draw[min];  // AoC solution is min BingoCard's remainder times the winning number
  std::cout << "AoC2021 Day 4 Part 1: " << z1 << std::endl;

  int z2 = board[maxi].GetRemainder() * draw[max];  // AoC solution is max BingoCard's remainder times the winning number
  std::cout << "AoC2021 Day 4 Part 2: " << z2 << std::endl;
}


#else

bool hasbingo(const std::vector<int>& v)
{
  for (int i = 0; i < 5; ++i)
  {
    if (
      v[5 * i + 0] == -1 &&
      v[5 * i + 1] == -1 &&
      v[5 * i + 2] == -1 &&
      v[5 * i + 3] == -1 &&
      v[5 * i + 4] == -1) return true;
    if (
      v[i + 5 * 0] == -1 &&
      v[i + 5 * 1] == -1 &&
      v[i + 5 * 2] == -1 &&
      v[i + 5 * 3] == -1 &&
      v[i + 5 * 4] == -1) return true;
  }
  //if (
  //  v[0] == -1 &&
  //  v[6] == -1 &&
  //  v[12] == -1 &&
  //  v[18] == -1 &&
  //  v[24] == -1) return true;

  //if (
  //  v[4] == -1 &&
  //  v[8] == -1 &&
  //  v[12] == -1 &&
  //  v[16] == -1 &&
  //  v[20] == -1) return true;
  return false;
}

int bingo(const std::vector<int>& v, const std::vector<int>& n)
{
  auto b = v;
  for (int i = 0; i < n.size(); ++i)
  {
    for (int j = 0; j < 25; ++j)
    {
      if (b[j] == n[i])
      {
        b[j] = -1;
        break;
      }
    }
    if (hasbingo(b)) return i;
  }
  return std::numeric_limits<int>::max();
}

int remainder(const std::vector<int>& v, const std::vector<int>& n, int z)
{
  auto b = v;
  for (int i = 0; i < z; ++i)
  {
    for (int j = 0; j < 25; ++j)
    {
      if (b[j] == n[i])
      {
        b[j] = 0;
        break;
      }
    }
  }

  int sum{ 0 };
  for (int j = 0; j < 25; ++j)
  {
    sum += b[j];
  }
  return sum;
}


void AoC2021_04A(std::istream& input)
{
  //std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  //std::vector<std::string> v = ReadWords()                 // read all words into vector 

  std::string line{};
  std::string dummy{};
  getline(input, line);

  std::vector<int> z{};

  std::istringstream str(line);
  int z0{ 0 };
  while (str >> z0) {
    z.emplace_back(z0);
    char comma{};
    str >> comma;
  }

  std::vector<std::vector<int>> board{};
  while (getline(input, dummy))
  {
    {
      std::vector<int> v{};
      v.resize(25);
      for (int i = 0; i < 25; ++i) input >> v[i];
      if (v[0] != 0 || v[1] != 0) board.emplace_back(v);
    }
  }

  std::vector<int> n{};
  n.resize(board.size());
  int min{ std::numeric_limits<int>::max() };
  int mini{ -1 };
  for (int i = 0; i < board.size(); ++i)
  {
    n[i] = bingo(board[i], z);
    if (n[i] < min)
    {
      min = n[i];
      mini = i;
    }
  }

  int sum = remainder(board[mini], z, n[mini] + 1);
  std::cout << z[min] * sum << std::endl;
}

void AoC2021_04B(std::istream& input)
{
  //std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  //std::vector<std::string> v = ReadWords()                 // read all words into vector 

  std::string line{};
  std::string dummy{};
  getline(input, line);

  std::vector<int> z{};

  std::istringstream str(line);
  int z0{ 0 };
  while (str >> z0) {
    z.emplace_back(z0);
    char comma{};
    str >> comma;
  }

  std::vector<std::vector<int>> board{};
  while (getline(input, dummy))
  {
    {
      std::vector<int> v{};
      v.resize(25);
      for (int i = 0; i < 25; ++i) input >> v[i];
      if (v[0] != 0 || v[1] != 0) board.emplace_back(v);
    }
  }

  std::vector<int> n{};
  n.resize(board.size());
  int max{ 0 };
  int maxi{ -1 };
  for (int i = 0; i < board.size(); ++i)
  {
    n[i] = bingo(board[i], z);
    if (n[i] > max)
    {
      max = n[i];
      maxi = i;
    }
  }

  int sum = remainder(board[maxi], z, n[maxi] + 1);
  std::cout << z[max] * sum << std::endl;
}

#endif // NEW_CODE
