
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

class Date
{
private:
    unsigned day;
    unsigned month;
    unsigned year;

public:
    void operator!() const;
    void errmsg(const char* msg);
    static unsigned int DaysPerMonth[13];
    static string monthNames[13];
    Date();
    Date(unsigned int, unsigned int, unsigned int);
    Date(const char* mm_dd_yy);
    void display() const;
    bool isA_LeapYear() const;
    friend ostream& operator<<(ostream&,const Date&);
    Date operator+(int); // Plus operator used as date1 + 5
    Date operator-(int); // subtraction operator used as date1 - 5
    const int operator-(Date &b);
    friend Date operator + (int, Date);
    Date& operator++();
    Date& operator--();
    string operator>(Date d);
    string operator<(Date d);
};

unsigned int Date::DaysPerMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
string Date::monthNames[13] = {" ","January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November","December"};
Date::Date()
{
    time_t now = time(0);
    struct tm* ptr2tm;
    ptr2tm = localtime(&now);

    day = ptr2tm->tm_mday;
    month = ptr2tm->tm_mon+1;
    year = ptr2tm->tm_year+1900;
}
Date::Date(unsigned int month1, unsigned int day1, unsigned int year1):day(day1), month(month1), year(year1)
{
    if(year < 100)
    {
        year+=2000;
    }
}
Date::Date(const char* mm_dd_yy)
{
    char* temp;
    char copy[9];

    // assume user enters date as mm/dd/yy
    if (strlen(mm_dd_yy) != 8) errmsg(mm_dd_yy);

    // use a copy of mm_dd_yy		What is the impact to the function?
    strcpy(copy,mm_dd_yy);

    // parse the date and get the month
    temp = strtok(copy,"-/");	// strtok() replaces the "/" with a NULL
    if (temp != NULL) month = atoi(temp);	// atoi() converts a string to an int
    else errmsg(copy);

    // parse the date and get the day
    temp = strtok(NULL,"-/");	// strtok() finds the next "/"
    if (temp != NULL) day = atoi(temp);
    else errmsg(copy);

    // parse the date and get the year
    temp = strtok(NULL,"-/");
    if (temp != NULL) year = atoi(temp);
    else errmsg(copy);

    // Make a Y2K correction for a 2-digit year
    if (year < 50) year += 2000;
    else if (year < 100) year += 1900;
    else {} ;	// assume the year is right
}
void Date::errmsg(const char* msg)
{
    cerr << "Invalid date format: " << msg << endl;
    exit(EXIT_FAILURE);
}

void Date::operator!() const
{
    cout << monthNames[month] << " " << setfill('0') << setw(2) << day << ","  << year <<endl ;
}

ostream& operator<<(ostream& s,const Date& c)
{
    s << setfill('0') << setw(2) << c.month << '/' << setfill('0') << setw(2) << c.day << '/' << setfill('0') << setw(2) << c.year;
    return s;
}

bool Date::isA_LeapYear() const
{
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

Date& Date::operator++()
{
    if(isA_LeapYear())
        DaysPerMonth[2] = 29;
    else
        DaysPerMonth[2] = 28;

    day++;

    if(day > DaysPerMonth[month] && month != 12)
    {
        month++;
        day = 1;
    }

    if(day > DaysPerMonth[month] && month == 12)
    {
        month = 1;
        day = 1;
        year++;
    }
    return *this;
}

Date& Date::operator--()
{
    if(isA_LeapYear())
        DaysPerMonth[2] = 29;
    else
        DaysPerMonth[2] = 28;

    day--;

    if(day < 1)
    {
        month--;
        day = DaysPerMonth[month];
    }

    if(day < 1 && month == 0)
    {
        month = 12;
        day = DaysPerMonth[month];
        year--;
    }
    return *this;
}

// + operator overloaded for the date. Used as date1 + 5
Date Date::operator + (int numberOfDays)
{
    Date temp = *this;
    for (int i = 1; i <= numberOfDays; i++)
    {
        ++(temp);  // calling the pre increment operator
    }
    return (temp);
}

// + operator overloaded for the date. Used as 5 + date1
Date operator + (int numberOfDays, Date c)
{
    Date temp = c;
    for (int i = 1; i <= numberOfDays; i++)
    {
        ++(temp);  // calling the pre increment operator
    }
    return temp;
}
// - operator overloaded for the date. Used as date1 - 5
Date Date::operator-(int numberOfDays)
{
    Date temp = *this;
    for (int i = 1; i <= numberOfDays; i++)
    {
        --(temp);
    }
    return (temp);
}

//get the amount of days between two dates
const int Date::operator-(Date &b)
{
    int count = 0;
    Date temp = b;

    if ((*this > b)=="true") {
      while ((temp.month != month || temp.day != day || temp.year != year)) {
        ++temp;
        ++count;
      }
    }
    else if ((b > *this)=="true") {
      while ((temp.month != month || temp.day != day || temp.year != year)) {
        --temp;
        --count;
      }
    }

    return count;
}

string Date::operator>(Date d)
{
    string t = "true";
    string f = "false";
    if ( year > d.year )
// if year is greater date is greater
    {
        return t;
    }
    else if ( year == d.year) //if years are equal check month
    {
        if ( month > d.month ) // if month is greater date is greater
        {
            return t;
        }
        else if ( month == d.month) // if months are equal check dates
        {
            if(day > d.day)
                return t;
            else         // otherwise return false
                return f;
        }
        else
            return f;
    }
    else
    {
        return f;
    }
}

string Date::operator<(Date d)
{
    string t = "true";
    string f = "false";
    if ( year < d.year )
// if year is less date is lesser
    {
        return t;
    }
    else if ( year == d.year) //if years are equal check month
    {
        if ( month < d.month ) // if month is less date is lesser
        {
            return t;
        }
        else if ( month == d.month) // if months are equal check dates
        {
            if(day < d.day)
                return t;
            else         // otherwise return false
                return f;
        }
        else
            return f;
    }
    else
    {
        return f;
    }
}

int main()
{
    // Constructors
    Date today;
    Date feb2815(2,28,15);
    Date feb2800("02-28-00");
    Date NewYearsDay("01/01/18");
    // Increment and decrement operators
    cout << today << endl;
    ++today;
    cout << today << endl;
    --today;
    cout << today << endl << endl;

    cout << feb2815 << endl;
    cout << ++feb2815 << endl;
    cout << --feb2815 << endl << endl;

    cout << feb2800 << endl;
    cout << ++feb2800 << endl;
    cout << --feb2800 << endl << endl;

    cout << NewYearsDay << endl;
    --NewYearsDay;
    cout << NewYearsDay << endl;
    ++NewYearsDay;
    cout << NewYearsDay << endl << endl;
    // Test plus operators
    cout << "30 days from now: " << today + 30 << endl;
    cout << "one hundred days from now: " << 100 + today << endl << endl;


    // Test minus operators
    Date twentyYearsAgo = today - static_cast<int>(round(20 * 365.25));
    Date final("12/11/17");
    cout << "Days until the final = " << final - today << endl;

    // Test the ! operator
    cout << "Today is ";
    !today;
    cout << "Twenty years ago was ";
    !twentyYearsAgo;
    cout << endl;

    // Test logic operators
    cout << boolalpha;
    cout << feb2800 << " < " << NewYearsDay << " ? " << (feb2800 < NewYearsDay) << endl;
    cout << feb2815 << " < " << NewYearsDay << " ? " << (feb2815 < NewYearsDay) << endl;
    cout << feb2815 << " > " << NewYearsDay << " ? " << (feb2815 > NewYearsDay) << endl;

}

