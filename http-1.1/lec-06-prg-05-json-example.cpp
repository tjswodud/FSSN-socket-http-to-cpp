#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

int main()
{
    ptree pt;
    ptree children, power;

    ptree member1, member2, member3;
    ptree powers1, powers2, powers3;
    ptree power1, power2, power3, power4, power5;

    member1.put("name", "Molecule Man");
    member1.put("age", 29);
    member1.put("secretIdentity", "Dan Jukes");
    
    member2.put("name", "Madame Uppercut");
    member2.put("age", 39);
    member2.put("secretIdentity", "Jane Wilson");

    member3.put("name", "Eternal Flame");
    member3.put("age", 1000000);
    member3.put("secretIdentity", "Unknown");

    power1.put("", "Radiation resistance");
    power2.put("", "Turning tiny");
    power3.put("", "Radiation blast");
    powers1.push_back(std::make_pair("", power1));
    powers1.push_back(std::make_pair("", power2));
    powers1.push_back(std::make_pair("", power3));

    power1.put("", "Million tonne punch");
    power2.put("", "Damage resistance");
    power3.put("", "Superhuman reflexes");
    powers2.push_back(std::make_pair("", power1));
    powers2.push_back(std::make_pair("", power2));
    powers2.push_back(std::make_pair("", power3));

    power1.put("", "Immortality");
    power2.put("", "Heat Immunity");
    power3.put("", "Inferno");
    power4.put("", "Teleportation");
    power5.put("", "Interdimensional travel");
    powers3.push_back(std::make_pair("", power1));
    powers3.push_back(std::make_pair("", power2));
    powers3.push_back(std::make_pair("", power3));
    powers3.push_back(std::make_pair("", power4));
    powers3.push_back(std::make_pair("", power5));
    
    member1.put_child("powers", powers1);
    member2.put_child("powers", powers2);
    member3.put_child("powers", powers3);
    children.push_back(std::make_pair("", member1));
    children.push_back(std::make_pair("", member2));
    children.push_back(std::make_pair("", member3));

    pt.put("squadName", "Super hero squad");
    pt.put("homeTown", "Metro City");
    pt.put("formed", 2016);
    pt.put("secretBase", "Super tower");
    pt.put("active", true);
    pt.add_child("members", children);

    children.add_child("members.powers", member1.get_child("powers"));
    children.add_child("members.powers", member2.get_child("powers"));
    children.add_child("members.powers", member3.get_child("powers"));

    write_json("./lec-06-prg-04-json-example.json", pt);

    std::ifstream file("./lec-06-prg-04-json-example.json");
    std::string buffer;

    while (file.peek() != EOF)
    {
        getline(file, buffer);
        std::cout << buffer << std::endl;
    }
}