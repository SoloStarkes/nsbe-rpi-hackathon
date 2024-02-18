#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "finance.h"
#include <algorithm>
#include <cmath>
#include <list>
#include <set>
#include <vector>
#include <utility>


//[book_of_wisdom : 67.48, book_of_knowledge : 35.90]
//gathers name of each textbook and their cost in a vector of pairs
std::vector<std::pair<std::string, double>> getDaBooks(std::string content) {
    std::vector<std::pair<std::string, double>> bookies;
    while(content.length() > 2) {
        int first = content.find(':');
        std::string name = content.substr(0, first);
        content = content.substr(first);
        int last = content.find(',');
        double num;
        if(last != std::string::npos) {
            num = stoi(content.substr(1, last));
        }
        else {
            num = stoi(content.substr(1));
        }
        bookies.push_back(std::pair(name, num));
        content = content.substr(last);
    }
    return bookies;
}

//sets vector of pair of each item within financial plan to be put into percentages after.
std::vector<std::pair<std::string, double>> percentages(Finance pman) { 
    std::vector<std::pair<std::string, double>> percents;
    double max = 0.0;
    std::string maxName;
    double min = 999999999.0; 
    std::string minName;
    double bookvals = 0.0;
    double totalPercent;
    for(int k = 0; k < pman.getTextbooks().size(); k++) {
        bookvals += pman.getTextbooks()[k].second;
    }
    percents.push_back(std::pair("textbooks", bookvals));
    percents.push_back(std::pair("board", pman.getBoard()));
    percents.push_back(std::pair("foodbev", pman.getFoodBev()));
    percents.push_back(std::pair("tuition", pman.getTuition()));
    percents.push_back(std::pair("transportation", pman.getTransportation()));
    percents.push_back(std::pair("investable", pman.getInvestable()));
    return percents;
}

int main(int argc, char* argv[]) {
    std::ifstream finance_file(argv[1]); //reads in input file
    std::ofstream output0_file(argv[2]); //reads in output file
    std::string command = std::string(argv[3]);
    std::string FirstName;
    std::string LastName;
    int Age;
    std::vector<std::pair<std::string, double>> textbooks;
    double board;
    double foodbev;
    double tuition;
    double transportation;
    double investable;
    double spareChange;
    double totalMoneys;

    std::string json_content;
    std::string line;
    while (std::getline(finance_file, line)) { //loops jsonFile line by line
        json_content += line; //adds json file content 
    }
    int first = json_content.find("Textbooks") + 10;
    int last = json_content.rfind(']');
    if(last - first > 1) {
        textbooks = getDaBooks(json_content.substr(first, last-first));
    }
    FirstName = json_content.substr(json_content.find("First_Name") + 12, json_content.find("Last_Name") - 3 - (json_content.find("First_Name") + 12));
    LastName = json_content.substr(json_content.find("Last_Name") + 11, json_content.find("Age") - 3 - (json_content.find("Last_Name") + 11));
    Age = stoi(json_content.substr(json_content.find("Age") + 5, json_content.find("Textbooks") - 3 - (json_content.find("Age") + 5))); 
    board = stod(json_content.substr(json_content.find("Board") + 7, json_content.find("Foodbev") - 3 - (json_content.find("Board") + 7)));
    foodbev = stod(json_content.substr(json_content.find("Foodbev") + 9, json_content.find("Tuition") - 3 - (json_content.find("Foodbev") + 9)));
    tuition = stod(json_content.substr(json_content.find("Tuition") + 9, json_content.find("Transportation") - 3 - (json_content.find("Tuition") + 9)));
    transportation = stod(json_content.substr(json_content.find("Transportation") + 16, json_content.find("Investable") - 3 - (json_content.find("Transportation") + 16)));
    investable = stod(json_content.substr(json_content.find("Investable") + 12, json_content.find("SpareChange") - 3 - (json_content.find("Investable") + 12)));
    spareChange = stod(json_content.substr(json_content.find("SpareChange") + 13, json_content.find("TotalMoneys") - 3 - (json_content.find("SpareChange") + 13)));
    totalMoneys = stod(json_content.substr(json_content.find("TotalMoneys") + 13, json_content.find('}') - 2 - (json_content.find("TotalMoneys") + 13)));
    Finance person(FirstName, LastName, Age, textbooks, board, foodbev, tuition, investable, spareChange, totalMoneys);


    if(command == "yearly") {
        std::cout << person.getFirstName() << " " << person.getLastName() << " started the year with $" << 
        person.getTotalMoneys() << " and ended with $" << person.yearlySpare() << " due to her expenses." <<std::endl;
        person.setTotalMoneys(person.yearlySpare());
        std::vector<std::pair<std::string, double>> percents = percentages(person);

        double max = 0.0;
        std::string maxName;
        double min = 999999999.0; 
        std::string minName;
        double totalPercent;
        for(int k = 0; k < percents.size(); k++) {
            totalPercent += percents[k].second;
            if(percents[k].second > max) {
                max = percents[k].second;
                maxName = percents[k].first;
            }
            if(percents[k].second < min) {
                min = percents[k].second;
                minName = percents[k].first;
            }
        }
        std::cout << "Your most expensive payment is " << maxName << " at $" << max << " per year. This makes up for about " << max/totalPercent << "% of your yearly budget." <<std::endl;
        std::cout << "Your least expensive payment is " << minName << " at $" << min << " per year. This makes up for about " << min/totalPercent << "% of your yearly budget." <<std::endl;
    }
    else if(command == "monthly") {
        std::cout << person.getFirstName() << " " << person.getLastName() << " started the month with $" << 
        person.getTotalMoneys() << " and ended with $" << person.monthlySpare() << " due to her expenses." <<std::endl;
        person.setTotalMoneys(person.monthlySpare());
        std::vector<std::pair<std::string, double>> percents = percentages(person);

        double max = 0.0;
        std::string maxName;
        double min = 999999999.0; 
        std::string minName;
        double totalPercent;
        for(int k = 0; k < percents.size(); k++) {
            totalPercent += percents[k].second;
            if(percents[k].second > max) {
                max = percents[k].second;
                maxName = percents[k].first;
            }
            if(percents[k].second < min) {
                min = percents[k].second;
                minName = percents[k].first;
            }
        }
        std::cout << "Your most expensive payment is " << maxName << " at $" << max/12.0 << " per month. This makes up for about " << max/totalPercent << "% of your monthly budget." <<std::endl;
        std::cout << "Your least expensive payment is " << minName << " at $" << min/12.0 << " per month. This makes up for about " << min/totalPercent << "% of your monthly budget." <<std::endl;
    }
    else if(command == "weekly") {
        std::cout << person.getFirstName() << " " << person.getLastName() << " started the week with $" << 
        person.getTotalMoneys() << " and ended with $" << person.weeklySpare() << " due to her expenses." <<std::endl;
        person.setTotalMoneys(person.weeklySpare());
        std::vector<std::pair<std::string, double>> percents = percentages(person);

        double max = 0.0;
        std::string maxName;
        double min = 999999999.0; 
        std::string minName;
        double totalPercent;
        for(int k = 0; k < percents.size(); k++) {
            totalPercent += percents[k].second;
            if(percents[k].second > max) {
                max = percents[k].second;
                maxName = percents[k].first;
            }
            if(percents[k].second < min) {
                min = percents[k].second;
                minName = percents[k].first;
            }
        }
        std::cout << "Your most expensive payment is " << maxName << " at $" << max/52.0 << " per week. This makes up for about " << max/totalPercent << "% of your weekly budget." <<std::endl;
        std::cout << "Your least expensive payment is " << minName << " at $" << min/52.0 << " per week. This makes up for about " << min/totalPercent << "% of your weekly budget." <<std::endl;
    }
    else if(command == "daily") {
        std::cout << person.getFirstName() << " " << person.getLastName() << " started the day with $" << 
        person.getTotalMoneys() << " and ended with $" << person.dailySpare() << " due to her expenses." <<std::endl;
        person.setTotalMoneys(person.dailySpare());
        std::vector<std::pair<std::string, double>> percents = percentages(person);

        double max = 0.0;
        std::string maxName;
        double min = 999999999.0; 
        std::string minName;
        double totalPercent;
        for(int k = 0; k < percents.size(); k++) {
            totalPercent += percents[k].second;
            if(percents[k].second > max) {
                max = percents[k].second;
                maxName = percents[k].first;
            }
            if(percents[k].second < min) {
                min = percents[k].second;
                minName = percents[k].first;
            }
        }
        std::cout << "Your most expensive payment is " << maxName << " at $" << max/365.0 << " per day. This makes up for about " << max/totalPercent << "% of your daily budget." <<std::endl;
        std::cout << "Your least expensive payment is " << minName << " at $" << min/365.0 << " per day. This makes up for about " << min/totalPercent << "% of your daily budget." <<std::endl;
    }

}