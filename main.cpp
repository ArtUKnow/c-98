#include "lab.h"
#include <iostream>
#include <memory>

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;

    while (true) {
        int choice;
        std::cout << "1. Add Trapecia\n"
                  << "2. Add Romb\n"
                  << "3. Add Penta\n"
                  << "4. Print all figures\n"
                  << "5. Total area\n"
                  << "6. Remove by index\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice == 0) break;

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
            std::cout << "Enter side: ";
            std::cin >> side;
            figures.add(std::make_shared<Penta<double>>(side));
            break;
        }
        case 4: {
            for (size_t i = 0; i < figures.getSize(); ++i) {
                figures[i]->print(std::cout);
                std::cout << "\nCenter: ";
                figures[i]->center()->print(std::cout);
                std::cout << "\nArea: " << static_cast<double>(*figures[i]) << "\n";
            }
            break;
        }
        case 5: {
            double totalArea = 0;
            for (size_t i = 0; i < figures.getSize(); ++i) {
                totalArea += static_cast<double>(*figures[i]);
            }
            std::cout << "Total area: " << totalArea << "\n";
            break;
        }
        case 6: {
            size_t index;
            std::cout << "Enter index: ";
            std::cin >> index;
            if (index >= figures.getSize()) {
                std::cout << "Invalid index\n";
            } else {
                figures.remove(index);
                std::cout << "Figure removed.\n";
            }
            break;
        }
        default:
            std::cout << "Invalid choice\n";
        }
    }

    return 0;
}
