#include <iostream>
#include <vector>
#include <memory>
#include "./include/figures.h"

int main() {
    std::vector<std::unique_ptr<Figure>> figures;
    int choice;

    while (true) {
        std::cout << "\nSelect:\n";
        std::cout << "1. CIN Trapecia\n";
        std::cout << "2. CIN Romb\n";
        std::cout << "3. CIN Penta\n";
        std::cout << "4. COUT ALL FIGURES\n";
        std::cout << "5. TOTAL AREA FIGURES\n";
        std::cout << "6. DELETE FIGURE PER IDX\n";
        std::cout << "0. EXIT\n";
        std::cout << "¬: ";
        std::cin >> choice;

        switch (choice) {
            case 1: { 
                double a,b,h;
                std::cout << "CIN a, b, h: ";
                std::cin >> a >> b >> h;
                figures.push_back(std::make_unique<Trapecia>(a, b, h));
                break;
            }
            case 2:{
                double d1, d2;
                std::cout << "CIN d1,d2: ";
                std::cin >> d1 >> d2;
                figures.push_back(std::make_unique<Romb>(d1, d2));
                break;
            }
            case 3:{
                double side;
                std::cout << "Cin size ";
                std::cin >> side;
                figures.push_back(std::make_unique<Penta>(side));
                break;
            }
            case 4: {
                for (size_t i = 0; i < figures.size(); ++i) {
                    std::cout << "Figure " << i + 1<< ":\n";
                    std::cout << "Center: (" << figures[i]->center().first <<", "<< figures[i]->center().second << ")\n";
                    std::cout << "Area: " << static_cast<double>(*figures[i]) << "\n";
                }
                break;
            }
            case 5: {
                double totalArea = 0;
                for (const auto& figure : figures) {
                    totalArea += static_cast<double>(*figure);
                }
                std::cout<<"Full area: "<<totalArea<<"\n";
                break;
            }
            case 6:{
                int index;
                std::cout<<"Figures for deleted ( from 1 ): ";
                std::cin>>index;
                if (index < 1 || index > figures.size()) {
                    std::cout << "Nun idx.\n";
                } else {
                    figures.erase(figures.begin() + (index - 1));
                    std::cout << "Figure deleted\n";
                }
                break;
            }
            case 0:
                return 0;
            default:
                std::cout << "Nun";
        }
    }

    return 0;
}
