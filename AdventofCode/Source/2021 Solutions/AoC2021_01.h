void AoC2021_01A(std::istream& input)
{
  auto start = std::chrono::steady_clock::now();

  int z = std::numeric_limits<int>::max();
  int p = z;
  int n = 0;
  while (input >> z)
  {
    if (z > p) ++n;
    p = z;
  }

  std::cout << n << std::endl;
  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << n << " (" << duration << ")" << std::endl;

}

void AoC2021_01B(std::istream& input)
{
  int z = std::numeric_limits<int>::max();
  int p1 = z;
  int p2 = z;
  int p3 = z;
  int n = 0;
  while (input >> z)
  {
    if (z > p3) ++n;
    p3 = p2;
    p2 = p1;
    p1 = z;
  }
  std::cout << n << std::endl;
}

