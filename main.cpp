#include <iostream>
#include <vector>
#include <memory>
#include "./include/meta.h"
#include <iostream>
#include <memory>

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    int choice;

    while (true) {
        std::cout << "\nSelect:\n";
        std::cout << "1. Add Trapecia\n";
        std::cout << "2. Add Romb\n";
        std::cout << "3. Add Penta\n";
        std::cout << "4. Print All Figures\n";
        std::cout << "5. Total Area of Figures\n";
        std::cout << "6. Delete Figure by Index\n";
        std::cout << "0. Exit\n";
        std::cout << "¬: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                double a, b, h;
                std::cout << "Enter a, b, h: ";
                std::cin >> a >> b >> h;
                figures.add(std::make_shared<Trapecia<double>>(a, b, h));
                break;
            }
            case 2: {
                double d1, d2;
                std::cout << "Enter d1, d2: ";
                std::cin >> d1 >> d2;
                figures.add(std::make_shared<Romb<double>>(d1, d2));
                break;
            }
            case 3: {
                double side;
                std::cout << "Enter side length: ";
                std::cin >> side;
                figures.add(std::make_shared<Penta<double>>(side));
                break;
            }
            case 4: {
                for (size_t i = 0; i < figures.getSize(); ++i) {
                    figures[i]->print(std::cout);
                    std::cout << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Total area: " << figures.totalArea() << std::endl;
                break;
            }
            case 6: {
                size_t index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                figures.remove(index);
                break;
            }
            case 0:
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }

    return 0;
}
