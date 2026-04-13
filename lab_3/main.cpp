#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

omp_lock_t lock;

int func()
{
  int a;
  for (size_t i = 0; i < 50000; i++)
  {
    a = rand();
  }

  return a;
}

int main()
{
  int array[1000] = {};
  omp_set_num_threads(2);
  std::cout << "\nThread working: " << omp_get_num_threads() << '\n';

  #pragma omp parallel for
  for (int i = 0; i < 100; i++)
  {
    std::cout << 0;
    func();
  }

  #pragma omp parallel
  {
    #pragma omp master
    {
      std::cout << "\nThread working: " << omp_get_num_threads() << '\n';
    }

    #pragma omp sections nowait
    {
      #pragma omp section
      for (size_t i= 0; i < 10; i++)
      {
        std::cout << 1;
        func();
      }

      #pragma omp section
      for (size_t i = 0; i < 20; i++)
      {
        std::cout << 2;
        func();
      }
    }

    #pragma omp barrier
    for (size_t i = 0; i < 10; i++)
    {
      std::cout << 3;
      func();
    }
  }

  #pragma omp master
  {
    std::cout << '\n';
  }
    
  #pragma omp parallel for ordered
  for (int i = 0; i < 1000; i++)
  {
    double value = i * i;
    #pragma omp ordered
    {
      array[i] = func();
      std::cout << "Index: " << i << " res: " << array[i] << '\n';
    };
  }

  std::cout << '\n';

  int n;
  omp_init_lock(&lock);
  #pragma omp parallel private (n)
  { 
    n = omp_get_thread_num();
    omp_set_lock(&lock);
    std::cout << "Start of locked section: " << n << '\n';
    sleep(3);
    std::cout << "End of locked section: " << n << '\n';
    omp_unset_lock(&lock);
  }
  omp_destroy_lock(&lock); 
}
