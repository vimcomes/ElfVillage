#include <iostream>
#include <ctime>

class Branch {
private:
    int branchCount = 0;
    std::string name = "Unknown";
    Branch** middleBranch = nullptr;
public:
    Branch() {
        std::cout << "Enter elf name on the middle branch: ";
        std::cin >> name;
    }

    Branch(std::string& in_name) : name(in_name) {
        branchCount = std::rand() % 2 + 2;
        middleBranch = new Branch * [branchCount];
        for (int i = 0; i < branchCount; i++) {
            middleBranch[i] = new Branch;
        }
    }

    std::string getName() {
        return name;
    }

    Branch** getMiddleBranch() {
        return middleBranch;
    }

    int getBranchCount() {
        return branchCount;
    }

    void clear() {

    }
};

class Tree {
private:
    int branchCount = 0;
    Branch** bigBranch = nullptr;
public:
    Tree() {
        std::srand(std::time(nullptr));
        branchCount = std::rand() % 3 + 3;
        bigBranch = new Branch * [branchCount];
        for (int i = 0; i < branchCount; i++) {
            std::string elfName;
            std::cout << "Enter elf name on the big branch: ";
            std::cin >> elfName;
            bigBranch[i] = new Branch(elfName);
        }
    }

    int elfSearching(std::string& in_name, bool& presence) {
        for (int i = 0; i < branchCount; i++) {
            int countNeighbors = 0;
            if (bigBranch[i]->getName() != "None" && bigBranch[i]->getName() != in_name) {
                countNeighbors++;
            }
            else if (bigBranch[i]->getName() == in_name) {
                presence = true;
            }

            for (int j = 0; j < bigBranch[i]->getBranchCount(); j++) {
                if (bigBranch[i]->getMiddleBranch()[j]->getName() != "None" && bigBranch[i]->getMiddleBranch()[j]->getName() != in_name) {
                    countNeighbors++;
                }
                else if (bigBranch[i]->getMiddleBranch()[j]->getName() == in_name) {
                    presence = true;
                }
            }
            if (presence) {
                return countNeighbors;
            }
        }
        return 0;
    }

    void show() {
        std::cout << std::endl << std::endl;
        for (int i = 0; i < branchCount; i++) {
            std::cout << "Big branch: " << bigBranch[i]->getName() << std::endl;
            for (int j = 0; j < bigBranch[i]->getBranchCount(); j++) {
                std::cout << " Middle branch: " << bigBranch[i]->getMiddleBranch()[j]->getName() << std::endl;
            }
        }
    }

    void clear() {

    }
};

int main() {
    std::string elfName;
    Tree* tree = new Tree[2];
    std::cout << "****************************" << std::endl;
    std::cout << "*  Enter elf name to find  *" << std::endl;
    std::cout << "****************************" << std::endl;
    std::cin >> elfName;
    for (int i = 0; i < 2; i++) {
        tree[i].show();
    }

    for (int i = 0; i < 2; i++) {
        bool presence = false;
        int countNeighbors = tree[i].elfSearching(elfName, presence);
        if (presence) {
            std::cout << "Elf name: " << elfName << std::endl;
            std::cout << "Count of neighbors: " << countNeighbors;
            break;
        }
        else if (!presence && i == 1) {
            std::cout << "There is no such elf";
        }
    }
    delete[] tree;
    return 0;
}