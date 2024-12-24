#include <iostream>
#include <vector>
#include <string>

// Base class for Employee
class Employee
{
protected:
    std::string name;

public:
    virtual void displayInfo() const = 0; // Pure virtual function marked as const
    virtual ~Employee() = default;
};

// Class for Team Members
class TeamMember : public Employee
{
    std::string job;
    int hoursWorked;

public:
    TeamMember(std::string n, std::string j, int h) : job(j), hoursWorked(h)
    {
        name = n;
    }
    void displayInfo() const override
    { // Marked as const
        std::cout << "Name: " << name << ", Job: " << job << ", Hours: " << hoursWorked << std::endl;
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
    { // Marked as const
        std::cout << "CTO: " << name << ", Field: " << field << std::endl;
        for (const TeamMember &member : team)
        {
            member.displayInfo(); // Call const member function
        }
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
    { // Marked as const
        std::cout << "CEO: " << name << std::endl;
        for (const CTO &cto : ctoList)
        {
            cto.displayInfo(); // Call const member function
        }
    }
};

// Class to manage job statuses
class JobSystem
{
    struct Job
    {
        std::string description;
        bool isCompleted;
    };
    std::vector<Job> jobs;

public:
    void addJob(const std::string &description, bool isCompleted)
    {
        jobs.push_back({description, isCompleted});
    }
    void displayJobs() const
    {
        std::cout << "Job Status:\n";
        for (const auto &job : jobs)
        {
            std::cout << "- " << job.description << " ["
                      << (job.isCompleted ? "Completed" : "In Progress") << "]\n";
        }
    }
};

// Main function
int main()
{
    // Create CEO
    CEO ceo("Alice");

    // Create CTOs
    CTO ctoFrontend("Bob", "Frontend Development");
    CTO ctoBackend("Charlie", "Backend Development");
    CTO ctoAI("Diana", "AI Development");
    CTO ctoDevOps("Eve", "DevOps");
    CTO ctoCloud("Frank", "Cloud Infrastructure");

    // Add team members to CTOs
    ctoFrontend.addTeamMember(TeamMember("John", "React Developer", 40));
    ctoFrontend.addTeamMember(TeamMember("Jane", "Vue.js Developer", 35));

    ctoBackend.addTeamMember(TeamMember("Jim", "Node.js Developer", 38));
    ctoBackend.addTeamMember(TeamMember("Jill", "Java Developer", 42));

    ctoAI.addTeamMember(TeamMember("Anne", "Machine Learning Engineer", 45));
    ctoAI.addTeamMember(TeamMember("Paul", "Data Scientist", 37));

    ctoDevOps.addTeamMember(TeamMember("Sam", "AWS Specialist", 40));
    ctoDevOps.addTeamMember(TeamMember("Lily", "Kubernetes Expert", 36));

    ctoCloud.addTeamMember(TeamMember("Mark", "Azure Specialist", 41));
    ctoCloud.addTeamMember(TeamMember("Nina", "GCP Engineer", 39));

    // Add CTOs to CEO
    ceo.addCTO(ctoFrontend);
    ceo.addCTO(ctoBackend);
    ceo.addCTO(ctoAI);
    ceo.addCTO(ctoDevOps);
    ceo.addCTO(ctoCloud);

    // Display organization hierarchy
    std::cout << "Organization Hierarchy:\n";
    ceo.displayInfo();

    // Manage and display job statuses
    JobSystem jobSystem;
    jobSystem.addJob("Develop Frontend Dashboard", false);
    jobSystem.addJob("Set up Backend API", true);
    jobSystem.addJob("Train AI Model", false);
    jobSystem.addJob("Deploy to Kubernetes", true);
    jobSystem.addJob("Optimize Cloud Infrastructure", false);

    std::cout << "\nJob Status:\n";
    jobSystem.displayJobs();

    return 0;
}
