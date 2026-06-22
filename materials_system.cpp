#include <iostream>
#include <cstring>

class Material {
public:
    double mass_density;
    char batch_code[20];
    int defect_count;

    Material(double density, const char* code, int defects) {
        mass_density = density;
        strcpy(batch_code, code);
        defect_count = defects;
    }
};class Inventory {
private:
    Material** items; // Raw pointer array as per Master_Resume.pdf
    int capacity;
    int count;

public:
    Inventory(int cap) {
        capacity = cap;
        items = new Material*[capacity];
        count = 0;
    }

    // Custom destructor mechanism matching Master_Resume.pdf
    ~Inventory() {
        for (int i = 0; i < count; i++) {
            delete items[i]; 
        }
        delete[] items;
        std::cout << "\n[System] Inventory memory cleared completely. Zero leaks.\n";
    }

    void addMaterial(double density, const char* code, int defects) {
        if (count < capacity) {
            items[count++] = new Material(density, code, defects);
        }
    }

    // Automated tolerance interface filtering 
    void verifyBatch(double minDensity, int maxDefects) {
        std::cout << "\n--- Quality Control Filtering ---\n";
        for (int i = 0; i < count; i++) {
            if (items[i]->mass_density >= minDensity && items[i]->defect_count <= maxDefects) {
                std::cout << "Batch " << items[i]->batch_code << ": PASSED\n";
            } else {
                std::cout << "Batch " << items[i]->batch_code << ": FAILED (Outside Tolerances)\n";
            }
        }
    }
};int main() {
    Inventory inv(5);
    
    // Log sample manufacturing batches
    inv.addMaterial(7.85, "STEEL-01", 1);
    inv.addMaterial(2.70, "ALUM-02", 5); // High defects
    inv.addMaterial(7.90, "STEEL-03", 0);

    // Run automated QC evaluation against structural parameters
    inv.verifyBatch(7.0, 2); 

    return 0; // Triggers custom destructor automatically
}