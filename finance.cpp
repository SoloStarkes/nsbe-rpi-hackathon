#include "finance.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <set>

    //CONSTRUCTOR
    Finance::Finance(std::string aFirstName, std::string aLastName, int aAge, std::vector<std::pair<std::string, double>> aTextbooks, 
    double aBoard, double aFoodBev, double aTuition, double aTransportation, double aInvestable, double aTotalMoneys) { //main constructor
        FirstName = aFirstName;
        LastName = aLastName;
        Age = aAge;
        textbooks = aTextbooks;
        board = aBoard;
        foodbev = aFoodBev;
        tuition = aTuition;
        transportation = aTransportation;
        investable = aInvestable; //percentage of extra you want to invest
        spareChange = 0;
        totalMoneys = aTotalMoneys;
    }

    Finance::Finance(const Finance &copy) { //copy constructor
        if (&copy == this) { //if trying to copy same object
            return; //returns
        }
        FirstName = copy.getFirstName();
        LastName = copy.getLastName();
        Age = copy.getAge();
        std::vector<std::pair<std::string, double>> textbooks = copy.getTextbooks();;
        board = copy.getBoard();
        foodbev = copy.getFoodBev();
        tuition = copy.getTuition();
        transportation = copy.getTransportation();
        investable = copy.getInvestable();
        spareChange = copy.getSpareChange();
        totalMoneys = copy.getTotalMoneys();
    }


    //ACCESSORS
    std::string Finance::getFirstName() const {
        return FirstName;
    }

    std::string Finance::getLastName() const {
        return LastName;
    }

    int Finance::getAge() const {
        return Age;
    }

    std::vector<std::pair<std::string, double>> Finance::getTextbooks() const {
        return textbooks;
    }

    double Finance::getBoard() const {
        return board;
    }

    double Finance::getFoodBev() const {
        return foodbev;
    }

    double Finance::getTuition() const {
        return tuition;
    }

    double Finance::getTransportation() const {
        return transportation;
    }

    double Finance::getInvestable() const {
        return investable;
    }

    double Finance::getSpareChange() const {
        return spareChange;
    }

    double Finance::getTotalMoneys() const {
        return totalMoneys;
    }


    //OTHER MEMBER FUNCTIONS THAT OPERATE ON FINANCE OBJECTS
    double Finance::yearlySpare() {
        double year = totalMoneys;
        year -= board;
        year -= foodbev;
        year -= tuition;
        year -= transportation;
        for (const auto& book : textbooks) {
            year -= book.second;
        }
        return year;
    }

    double Finance::monthlySpare() {
        double month = totalMoneys/12.0;
        month -= board/12.0;
        month -= foodbev/12.0;
        month -= tuition/12.0;
        month -= transportation/12.0;
        for (const auto& book : textbooks) {
            month -= book.second/12.0;
        }
        return month;
    }

    double Finance::weeklySpare() {
        double week = totalMoneys/52.0;
        week -= board/52.0;
        week -= foodbev/52.0;
        week -= tuition/52.0;
        week -= transportation/52.0;
        for (const auto& book : textbooks) {
            week -= book.second/52.0;
        }
        return week;
    }

    double Finance::dailySpare() {
        double daily = totalMoneys/365.0;
        daily -= board/365.0;
        daily -= foodbev/365.0;
        daily -= tuition/365.0;
        daily -= transportation/365.0;
        for (const auto& book : textbooks) {
            daily -= book.second/365.0;
        }
        return daily;
    }

    void Finance::setTotalMoneys(double m) {
        totalMoneys = m;
    }


    //OUTSIDE MEMBER FUNCTIONS
    