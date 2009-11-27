#ifndef DEBUG_GCC_HELPER
#define DEBUG_GCC_HELPER

void dump(const std::vector<int> &v)
{
   cout << "[" << v.size() << "]: ";
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << " ";
   cout << endl;
}

void dump(const std::vector<double> &v)
{
   cout << "[" << v.size() << "]: ";
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << " ";
   cout << endl;
}

void dump(const std::vector<float> &v)
{
   cout << "[" << v.size() << "]: ";
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << " ";
   cout << endl;
}

void dump(const std::vector<unsigned> &v)
{
   cout << "[" << v.size() << "]: ";
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << " ";
   cout << endl;
}

void dump(const std::vector<long> &v)
{
   cout << "[" << v.size() << "]: ";
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << " ";
   cout << endl;
}

void dump(const std::vector<std::string> &v)
{
   cout << "[" << v.size() << "]: ";
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << " ";
   cout << endl;
}

#endif
