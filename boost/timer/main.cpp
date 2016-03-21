#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/timer/timer.hpp>

using namespace std;
int main(int argc, char** argv, char** envp)
{
    boost::timer::auto_cpu_timer timer("%w clock time,%t totle program time(%p%)\n");

    cout<<boost::filesystem::current_path()<<"\n";
    cout<<boost::filesystem::system_complete(argv[0])<<endl;

    boost::this_thread::sleep(boost::posix_time::millisec(6000));

    return 0;
}
