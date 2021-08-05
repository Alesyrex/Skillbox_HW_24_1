#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>

void end_task(std::ofstream &file,std::string &name,std::time_t &startTime) {

    double diff = std::difftime(std::time(nullptr),startTime);
    std::time_t executionTime = (std::time_t)diff;
    std::tm* local_execution = std::localtime(&executionTime);
    local_execution->tm_hour -= 3;
    file.open("save.txt", std::ios::app);
    file << name << " " << std::put_time(local_execution,"%H:%M:%S") << std::endl;
    file.close();
}

int main() {

    const std::vector<std::string> action = {"begin","end","status","exit"};

    std::string userAction;
    std::string task;

    bool findAction = false;
    bool taskActive = false;
    std::time_t startTime = std::time(nullptr);
    std::ofstream file;

    do {
        std::cout << "Enter 'begin' to create a new task; \n'end' to complete the current task;\n";
        std::cout << "'status' to display information about all tasks; \n'exit' to exit the program." << std::endl;
        std::cout << ">";

        do {
            std::cin >> userAction;
            for (int i=0;i < action.size();++i) {
                if (userAction == action[i]){
                    findAction = true;
                }
            }
            if (!findAction) std::cout << "Incorrect input! Repeat.\n>";
        } while (!findAction);

        if (userAction == "begin") {

            if (taskActive) {
                end_task(file,task,startTime);
                taskActive = false;
                std::cout << "Task " << task << " completed." << std::endl;
            }

            std::cout << "Enter a name for the new task:";
            std::cin >> task;
            startTime = std::time(nullptr);
            taskActive = true;
        }

        if (userAction == "end") {
            if (taskActive) {
                end_task(file,task,startTime);
                taskActive = false;
                std::cout << "Task " << task << " completed." << std::endl;
            }
        }

        if (userAction == "status") {
            std::ifstream file;
            file.open("save.txt");
            int count = 0;
            char buffer[20];
            while(!file.eof()){
                file.read(buffer, sizeof(buffer) - 1);
                count = file.gcount();
                buffer[count] = 0;
                std::cout << buffer;
            }
            file.close();
            if(taskActive) {
                std::cout << "Active task --> " << task << std::endl;
                std::cout << std::endl;
            }
            else std::cout << "No active tasks." << std::endl;
            std::cout << std::endl;
        }
        if (userAction == "exit") {
            file.open("save.txt");
            file.clear();
            file.close();
        }

    } while (userAction != "exit");

    return 0;
}
