#include "./include/meta.h"
#include <iostream>
#include <memory>

int main() {
    DynamicArray<std::shared_ptr<Figure<double>>> figures;
    int choice;

    while (true) {
        std::cout << "\nMenu:\n"
                  << "1. Add Trapecia\n"
                  << "2. Add Romb\n"
                  << "3. Add Penta\n"
                  << "4. Print Figures\n"
                  << "5. Total Area\n"
                  << "6. Remove Figure\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                double a, b, h;
                std::cout << "Enter a, b, h: ";
                std::cin >> a >> b >> h;
                figures.addFigure(std::make_shared<Trapecia<double>>(a, b, h));
                break;
            }
            case 2: {
                double d1, d2;
                std::cout << "Enter d1, d2: ";
                std::cin >> d1 >> d2;
                figures.addFigure(std::make_shared<Romb<double>>(d1, d2));
                break;
            }
            case 3: {
                double side;
                std::cout << "Enter side: ";
                std::cin >> side;
                figures.addFigure(std::make_shared<Penta<double>>(side));
                break;
            }
            case 4:
                figures.printFigures();
                break;
            case 5:
                std::cout << "Total Area: " << figures.totalArea() << "\n";
                break;
            case 6: {
                size_t index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                try {
                    figures.removeFigure(index - 1);
                    std::cout << "Figure removed.\n";
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            default:
                std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}