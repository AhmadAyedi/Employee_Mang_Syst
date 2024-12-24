#include <iostream>
#include <vector>
#include <string>
#include <iomanip>   // For formatting the table
#include <algorithm> // For std::remove_if

using namespace std; // Avoid writing std::

// Base class for Employee
class Employee
{
protected:
    string name;

public:
    virtual void displayInfo() const = 0;
    virtual ~Employee() = default;
};

// Class for Team Members
class TeamMember : public Employee
{
    string job;
    int hoursWorked;

public:
    TeamMember(string n, string j, int h) : job(j), hoursWorked(h)
    {
        name = n;
    }
    void displayInfo() const override
    {
        cout << setw(15) << name
             << setw(20) << job
             << setw(10) << hoursWorked << endl;
    }
    string getName() const
    {
        return name;
    }
    void modifyJob(const string &newJob)
    {
        job = newJob;
    }
    void modifyHours(int newHours)
    {
        hoursWorked = newHours;
    }
};

// Class for CTOs
class CTO : public Employee
{
    string field;
    vector<TeamMember> team;

public:
    CTO(string n, string f) : field(f)
    {
        name = n;
    }
    void addTeamMember(const TeamMember &member)
    {
        team.push_back(member);
    }
    void displayInfo() const override
    {
        cout << "CTO: " << name << " - Field: " << field << endl;
        cout << setw(15) << "Name"
             << setw(20) << "Job"
             << setw(10) << "Hours" << endl;
        cout << string(45, '-') << endl;
        for (const auto &member : team)
        {
            member.displayInfo();
        }
    }
    string getName() const
    {
        return name;
    }
    void addNewMember(const TeamMember &member)
    {
        team.push_back(member);
    }
    void modifyTeamMember(const string &memberName, const string &newJob, int newHours)
    {
        for (auto &member : team)
        {
            if (member.getName() == memberName)
            {
                member.modifyJob(newJob);
                member.modifyHours(newHours);
                break;
            }
        }
    }
    void removeTeamMember(const string &memberName)
    {
        team.erase(remove_if(team.begin(), team.end(), [&](const TeamMember &member)
                             { return member.getName() == memberName; }),
                   team.end());
    }
};

// Class for CEO
class CEO : public Employee
{
    vector<CTO> ctoList;

public:
    CEO(string n)
    {
        name = n;
    }
    void addCTO(const CTO &cto)
    {
        ctoList.push_back(cto);
    }
    void displayInfo() const override
    {
        cout << "CEO: " << name << endl;
        for (const auto &cto : ctoList)
        {
            cto.displayInfo();
            cout << endl;
        }
    }
    CTO *getCTO(const string &ctoName)
    {
        for (auto &cto : ctoList)
        {
            if (cto.getName() == ctoName)
            {
                return &cto;
            }
        }
        return nullptr;
    }
};

void displayMenu()
{
    cout << "\n--- Employee Management System ---\n";
    cout << "1. Add CTO\n";
    cout << "2. Add Team Member to CTO\n";
    cout << "3. Modify Team Member\n";
    cout << "4. Remove Team Member\n";
    cout << "5. Display Organization\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    CEO ceo("Ahmad Ayedi");
    int choice;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            string ctoName, field;
            cout << "Enter CTO Name: ";
            getline(cin, ctoName);
            cout << "Enter Field of Expertise: ";
            getline(cin, field);
            ceo.addCTO(CTO(ctoName, field));
            break;
        }
        case 2:
        {
            string ctoName, memberName, job;
            int hours;
            cout << "Enter CTO Name: ";
            getline(cin, ctoName);
            CTO *cto = ceo.getCTO(ctoName);
            if (cto)
            {
                cout << "Enter Team Member Name: ";
                getline(cin, memberName);
                cout << "Enter Job: ";
                getline(cin, job);
                cout << "Enter Hours Worked: ";
                cin >> hours;
                cin.ignore(); // Clear input buffer
                cto->addNewMember(TeamMember(memberName, job, hours));
            }
            else
            {
                cout << "CTO not found!\n";
            }
            break;
        }
        case 3:
        {
            string ctoName, memberName, newJob;
            int newHours;
            cout << "Enter CTO Name: ";
            getline(cin, ctoName);
            CTO *cto = ceo.getCTO(ctoName);
            if (cto)
            {
                cout << "Enter Team Member Name: ";
                getline(cin, memberName);
                cout << "Enter New Job: ";
                getline(cin, newJob);
                cout << "Enter New Hours Worked: ";
                cin >> newHours;
                cin.ignore(); // Clear input buffer
                cto->modifyTeamMember(memberName, newJob, newHours);
            }
            else
            {
                cout << "CTO not found!\n";
            }
            break;
        }
        case 4:
        {
            string ctoName, memberName;
            cout << "Enter CTO Name: ";
            getline(cin, ctoName);
            CTO *cto = ceo.getCTO(ctoName);
            if (cto)
            {
                cout << "Enter Team Member Name to Remove: ";
                getline(cin, memberName);
                cto->removeTeamMember(memberName);
            }
            else
            {
                cout << "CTO not found!\n";
            }
            break;
        }
        case 5:
            ceo.displayInfo();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
