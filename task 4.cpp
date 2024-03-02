#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int MAX_TASKS = 10;
struct TaskList {
    string tasks[MAX_TASKS];
    int count;
};
void Menu() {
    cout << "\n======= To-Do List =======\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Delete Task\n";
    cout << "4. Exit\n";
    cout << "==========================\n";
    cout << "\nPlease Enter your choice: ";
}
void AddTask(TaskList& taskList) {
    if (taskList.count < MAX_TASKS) {
        string task;
        cout << "Enter task: ";
        cin.ignore();
        getline(cin, task);
        taskList.tasks[taskList.count++] = task;
        cout << "Task added successfully!\n";
    } else {
        cout << "Task limit reached. Delete tasks to add more.\n";
    }
}
void ViewTasks(const TaskList& taskList) {
    cout << "\n======= Tasks =======\n";
    for (int i = 0; i < taskList.count; ++i) {
        cout << i + 1 << ". " << taskList.tasks[i] << "\n";
    }
    cout << "=====================\n";
}
void DeleteTask(TaskList& taskList) {
    if (taskList.count > 0) {
        ViewTasks(taskList);
        int taskNumber;
        cout << "Enter the task number to delete: ";
        cin >> taskNumber;
        if (taskNumber >= 1 && taskNumber <= taskList.count) {
            for (int i = taskNumber - 1; i < taskList.count - 1; ++i) {
                taskList.tasks[i] = taskList.tasks[i + 1];
            }
            taskList.count--;
            cout << "Task deleted successfully!\n";
        } else {
            cout << "Invalid task number.\n";
        }
    } else {
        cout << "No tasks to delete.\n";
    }
}
void WriteTasks(const TaskList& taskList) {
    ofstream file("tasks.txt");
    if (file.is_open()) {
        for (int i = 0; i < taskList.count; ++i) {
            file << taskList.tasks[i] << "\n";
        }
        file.close();
        cout << "Tasks written to file successfully!\n";
    } else {
        cout << "Unable to open file for writing!\n";
    }
}
void ReadTasks(TaskList& taskList) {
    ifstream file("tasks.txt");
    if (file.is_open()) {
        string task;
        taskList.count = 0;
        while (getline(file, task) && taskList.count < MAX_TASKS) {
            taskList.tasks[taskList.count++] = task;
        }
        file.close();
        cout << "Tasks read from file successfully!\n";
    } else {
        cout << "Unable to open file for reading!\n";
    }
}
int main() {
    TaskList taskList;
    taskList.count = 0;
    int choice;
    ReadTasks(taskList);
    do {
        Menu();
        cin >> choice;
        switch (choice) {
            case 1:
                AddTask(taskList);
                break;
            case 2:
                ViewTasks(taskList);
                break;
            case 3:
                DeleteTask(taskList);
                break;
            case 4:
                WriteTasks(taskList);
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);
    return 0;
}
