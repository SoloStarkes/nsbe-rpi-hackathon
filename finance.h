#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <list>
#include <set>
#include <vector>
#include <utility>

class Finance {
    public:
    Finance(std::string aFirstName, std::string aLastName, int aAge, std::vector<std::pair<std::string, double>> aTextbooks, 
    double aBoard, double aFoodBev, double aTuition, double aTransportation, double aInvestable, double aTotalMoneys);
    Finance(const Finance &copy);

    //ACCESSORS
    std::string getFirstName() const;
    std::string getLastName() const;
    int getAge() const;
    std::vector<std::pair<std::string, double>> getTextbooks() const;
    double getBoard() const;
    double getFoodBev() const; 
    double getTuition() const;
    double getTransportation() const;
    double getInvestable() const;
    double getSpareChange() const;
    double getTotalMoneys() const;
    

    //OTHER MEMBER FUNCTIONS THAT OPERATE ON DRIVER OBJECTS
    double yearlySpare();
    double monthlySpare();
    double weeklySpare();
    double dailySpare();
    void setTotalMoneys(double m);
    
    //PRIVATE VARIABLES
    private:
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
};

//OUTSIDE MEMBER FUNCTIONS
// std::ostream& operator<< (std::ostream& out, const Driver& d);
// bool operator== (const Driver &a, const Driver &b);
// bool operator!= (const Driver &a, const Driver &b);