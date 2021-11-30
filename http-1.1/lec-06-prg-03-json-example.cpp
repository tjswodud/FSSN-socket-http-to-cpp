#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

int main()
{
    ptree props;
    boost::property_tree::read_json("./lec-06-prg-03-json-example.json", props);
    std::string m_attribute1 = props.get<std::string>("homeTown");
    std::string m_attribute2 = props.get<std::string>("active");

    std::cout << m_attribute1 << std::endl;
    std::cout << m_attribute2 << std::endl;

    ptree& child = props.get_child("members");
    std::vector<std::vector<std::string>> items;
    std::vector<std::string> item;

    BOOST_FOREACH (ptree::value_type& vt, child)
    {
        item.clear();
        ptree& children = vt.second.get_child("powers");
        BOOST_FOREACH (ptree::value_type& arr, children)
        {
            item.push_back(arr.second.data());
        }
        items.push_back(item);
    }
    std::cout << items[1][2] << std::endl;
}