#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>
using namespace std;

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    std::copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
    return os;
}

void parse_option(int argc, char** argv, boost::program_options::variables_map& vm)
{
    namespace po = boost::program_options;
    po::options_description desc(
        "Allowed options");

    string conf_file;
    desc.add_options()
        ("help,h", "show help")
        ("name,n",po::value<string>()->required(), "the name")
        ("age,a",po::value<int>()->default_value(0), "the age")
        ("gender,g",po::value<char>(), "sex")
        ("config,c", po::value<string>(&conf_file)->default_value("po.cfg"))
        ("others",po::value<vector<string> >(), "other options")

        ("hobby.color", po::value<string>())
        ("hobby.food", po::value<string>())
        ("job.location", po::value<string>())
        ("job.salary", po::value<double>())
        ;

    po::positional_options_description pos;
    pos.add("others", -1);

    try
    {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
        po::notify(vm);
        // But what happens if the same value is specified both on the command line and in config file?
        // Usually, the value stored first is preferred.
        ifstream ifs(conf_file);
        bool allow_unregistered=true;
        po::store(po::parse_config_file(ifs, desc, allow_unregistered), vm);
        po::notify(vm);
        ifs.close();
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

int main(int argc, char *argv[])
{
    boost::program_options::variables_map vm;
    parse_option(argc,argv,vm);
    if(vm.count("others"))
        cout<<"others:\t"<<vm["others"].as<vector<string> >()<<'\n';
    vector<string> show={ "name", "age", "hobby.color", "hobby.food", "job.location", "job.salary" };
    for (auto const & i: show)
        if(vm.count(i))
        {
            try { cout<<std::right<<setw(16)<<setfill(' ')<<i<<" : "<<vm[i].as<string>()<<'\n'; } catch (...) {}
            try { cout<<std::right<<setw(16)<<setfill(' ')<<i<<" : "<<vm[i].as<int>()<<'\n'; } catch (...) {}
            try { cout<<std::right<<setw(16)<<setfill(' ')<<i<<" : "<<vm[i].as<double>()<<'\n'; } catch (...) {}
        }

    return 0;
}
