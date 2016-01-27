/* Time-stamp: <2016-01-14 16:59:20 scinart>
 * created at 2016-01-12 15:31:08
 * asio.cpp
 * by akubeej@gmail.com
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "taskqueue.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/program_options.hpp>

using namespace std;

double param = 1;
boost::mutex param_update_mutex;

void update_param(double delta)
{
    boost::mutex::scoped_lock lock(param_update_mutex);
    param+=delta;
    cout<<"base is now "<<param<<endl;
}

class Randgen
{
public:
    static double get_rand_double(double b_closed,double e_open)
    {
        std::uniform_real_distribution<> dist(b_closed, e_open); // b≤x<e
        return dist(e2);
    }
    static int get_rand_int(int b_closed,int e_closed)
    {
        std::uniform_int_distribution<> dist(b_closed, e_closed); // b≤x≤e
        return dist(e2);
    }

private:
    static std::random_device rd;
    static std::mt19937 e2;
};
std::random_device Randgen::rd;
std::mt19937 Randgen::e2(Randgen::rd());


struct calculate_task {
    typedef void result_type;
    result_type operator()() {
        boost::mutex::scoped_lock lock(param_update_mutex);
        base = param; // save a copy of global param.
        lock.unlock();
        boost::this_thread::sleep_for(boost::chrono::milliseconds(Randgen::get_rand_int(50,100)));
        update_param(1.0/base);
    }
    double base;
};

void parse_option(int argc, char** argv, boost::program_options::variables_map& vm)
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "show help")
        ("base,b", po::value<double>()->default_value(1), "base for test")
        ("ntasks,t", po::value<int>()->default_value(10), "ntasks for test")
        ("nqueues,q", po::value<int>()->default_value(4), "nqueues for test")
        ;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << endl;
            exit(1);
        }
    }
    catch(po::error& e)
    {
        cerr << e.what() << endl;
        cout << desc << endl;
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    boost::program_options::variables_map vm;
    parse_option(argc, argv, vm);

    param = vm["base"].as<double>();
    int batch_num = vm["ntasks"].as<int>();

    TaskQueue<calculate_task> task_queue(vm["nqueues"].as<int>());

    // if batch_num is too large.
    // it may not be propriate to push all tasks in Queue
    // you can do
    // if (i%1000 == 999)
    //     task_queue.WaitForAllThread();
    for(int i=0;i<batch_num;i++)
    {
        task_queue.QueueTask(calculate_task());
    }

    task_queue.WaitForAllThread();

    return 0;
}
