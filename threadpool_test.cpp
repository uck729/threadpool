#include "threadpool.h"

#include <iostream>

#include <pthread.h>
#include <unistd.h>

using namespace std;

void hello(void* arg)
{
  int* x = (int*) arg;
  cout << "Hello " << *x << endl;
//  cout << "\n";
}

int main(int argc, char* argv[])
{
    ThreadPool tp(2);
    int ret = tp.initialize_threadpool();
    if (ret == -1) {
        cerr << "Failed to initialize thread pool!" << endl;
        return 0;
    }
      
    while (true)
    {
        sleep(2);
        int tasknum = 0;
        cout << "Please enter an integer value: ";
        cin >> tasknum;
        cout << "The value you entered is " << tasknum << endl;
        if (tasknum == 0)
        {
            break;
        }
        for (int i = 0; i < tasknum; i++)
        {
            int* x = new int();
            *x = i+1;
            Task* t = new Task(&hello, (void*) x);
            //    cout << "Adding to pool, task " << i+1 << endl;
            tp.add_task(t);
            //    cout << "Added to pool, task " << i+1 << endl;
        }
    }
        
    sleep(2);
        
    tp.destroy_threadpool();
    cout << "Exiting app..." << endl;
   
    return 0;
}
