#include <iostream>
#include <vector>
#include <string>
#include <iomanip>   // For formatting the table
#include <algorithm> // For max_element

// Base class for Employee
class Employee
{
protected:
    std::string name;

public:
    virtual void displayInfo() const = 0;
    virtual ~Employee() = default;
};

// Class for Team Members
class TeamMember : public Employee
{
    std::string job;
    int hoursWorked;
    double contribution;

public:
    TeamMember(std::string n, std::string j, int h, double c) : job(j), hoursWorked(h), contribution(c)
    {
        name = n;
    }
    void displayInfo() const override
    {
        std::cout << std::setw(15) << name
                  << std::setw(20) << job
                  << std::setw(10) << hoursWorked
                  << std::setw(15) << contribution << std::endl;
    }
    std::string getName() const
    {
        return name;
    }
    double getContribution() const
    {
        return contribution;
    }
    void modifyJob(const std::string &newJob)
    {
        job = newJob;
    }
    void modifyHours(int newHours)
    {
        hoursWorked = newHours;
    }
    void modifyContribution(double newContribution)
    {
        contribution = newContribution;
    }
};

// Class for CTOs
class CTO : public Employee
{
    std::string field;
    std::vector<TeamMember> team;

public:
    CTO(std::string n, std::string f) : field(f)
    {
        name = n;
    }
    void addTeamMember(const TeamMember &member)
    {
        team.push_back(member);
    }
    void displayInfo() const override
    {
        std::cout << "CTO: " << name << " - Field: " << field << std::endl;
        std::cout << std::setw(15) << "Name"
                  << std::setw(20) << "Job"
                  << std::setw(10) << "Hours"
                  << std::setw(15) << "Contribution" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        for (const auto &member : team)
        {
            member.displayInfo();
        }
    }
    std::string getName() const
    {
        return name;
    }
    double getTotalContribution() const
    {
        double total = 0;
        for (const auto &member : team)
        {
            total += member.getContribution();
        }
        return total;
    }
    void addNewMember(const TeamMember &member)
    {
        team.push_back(member);
    }
    void modifyTeamMember(const std::string &memberName, const std::string &newJob, int newHours, double newContribution)
    {
        for (auto &member : team)
        {
            if (member.getName() == memberName)
            {
                member.modifyJob(newJob);
                member.modifyHours(newHours);
                member.modifyContribution(newContribution);
                break;
            }
        }
    }
    void removeTeamMember(const std::string &memberName)
    {
        team.erase(std::remove_if(team.begin(), team.end(), [&](const TeamMember &member)
                                  { return member.getName() == memberName; }),
                   team.end());
    }
};

// Class for CEO
class CEO : public Employee
{
    std::vector<CTO> ctoList;

public:
    CEO(std::string n)
    {
        name = n;
    }
    void addCTO(const CTO &cto)
    {
        ctoList.push_back(cto);
    }
    void displayInfo() const override
    {
        std::cout << "CEO: " << name << std::endl;
        for (const auto &cto : ctoList)
        {
            cto.displayInfo();
            std::cout << std::endl;
        }
    }
    CTO *getCTO(const std::string &ctoName)
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
    void determineTopCTO()
    {
        if (ctoList.empty())
        {
            std::cout << "No CTOs available to determine the top contributor.\n";
            return;
        }

        auto topCTO = std::max_element(ctoList.begin(), ctoList.end(), [](const CTO &a, const CTO &b)
                                       { return a.getTotalContribution() < b.getTotalContribution(); });

        std::cout << "\nThe CTO whose team contributed the most is: " << topCTO->getName()
                  << " with a total contribution of " << topCTO->getTotalContribution() << ".\n";
        name = topCTO->getName();
    }
};

void displayMenu()
{
    std::cout << "\n--- Employee Management System ---\n";
    std::cout << "1. Add CTO\n";
    std::cout << "2. Add Team Member to CTO\n";
    std::cout << "3. Modify Team Member\n";
    std::cout << "4. Remove Team Member\n";
    std::cout << "5. Display Organization\n";
    std::cout << "6. Determine Top-Contributing CTO\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

int main()
{
    CEO ceo("Your Company CEO");
    int choice;

    do
    {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            std::string ctoName, field;
            std::cout << "Enter CTO Name: ";
            std::getline(std::cin, ctoName);
            std::cout << "Enter Field of Expertise: ";
            std::getline(std::cin, field);
            ceo.addCTO(CTO(ctoName, field));
            break;
        }
        case 2:
        {
            std::string ctoName, memberName, job;
            int hours;
            double contribution;
            std::cout << "Enter CTO Name: ";
            std::getline(std::cin, ctoName);
            CTO *cto = ceo.getCTO(ctoName);
            if (cto)
            {
                std::cout << "Enter Team Member Name: ";
                std::getline(std::cin, memberName);
                std::cout << "Enter Job: ";
                std::getline(std::cin, job);
                std::cout << "Enter Hours Worked: ";
                std::cin >> hours;
                std::cout << "Enter Contribution Amount: ";
                std::cin >> contribution;
                std::cin.ignore(); // Clear input buffer
                cto->addNewMember(TeamMember(memberName, job, hours, contribution));
            }
            else
            {
                std::cout << "CTO not found!\n";
            }
            break;
        }
        case 3:
        {
            std::string ctoName, memberName, newJob;
            int newHours;
            double newContribution;
            std::cout << "Enter CTO Name: ";
            std::getline(std::cin, ctoName);
            CTO *cto = ceo.getCTO(ctoName);
            if (cto)
            {
                std::cout << "Enter Team Member Name: ";
                std::getline(std::cin, memberName);
                std::cout << "Enter New Job: ";
                std::getline(std::cin, newJob);
                std::cout << "Enter New Hours Worked: ";
                std::cin >> newHours;
                std::cout << "Enter New Contribution Amount: ";
                std::cin >> newContribution;
                std::cin.ignore(); // Clear input buffer
                cto->modifyTeamMember(memberName, newJob, newHours, newContribution);
            }
            else
            {
                std::cout << "CTO not found!\n";
            }
            break;
        }
        case 4:
        {
            std::string ctoName, memberName;
            std::cout << "Enter CTO Name: ";
            std::getline(std::cin, ctoName);
            CTO *cto = ceo.getCTO(ctoName);
            if (cto)
            {
                std::cout << "Enter Team Member Name: ";
                std::getline(std::cin, memberName);
                cto->removeTeamMember(memberName);
            }
            else
            {
                std::cout << "CTO not found!\n";
            }
            break;
        }
        case 6:
        {
            ceo.determineTopCTO(); // Correct method to determine top CTO
            break;
        }
        case 7:
        {
            std::cout << "Exiting...\n";
            break;
        }
        default:
            std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
