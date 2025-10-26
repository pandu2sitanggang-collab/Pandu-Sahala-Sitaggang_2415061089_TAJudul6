#include <iostream>
using namespace std;

const int SIZE = 10;

enum SlotState { EMPTY, OCCUPIED, DELETED };

struct Barang {
    int kode;     
    int stok;      
    SlotState state; 
};

int hashFunction(int kode) {
    return (kode % SIZE + SIZE) % SIZE;
}

void initTable(Barang table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i].state = EMPTY;
    }
}

bool insert(Barang table[], int kode, int stok) {
    int idx = hashFunction(kode);

    for (int step = 0; step < SIZE; step++) {
        int i = (idx + step) % SIZE;

        if (table[i].state == EMPTY || table[i].state == DELETED) {
            table[i].kode = kode;
            table[i].stok = stok;
            table[i].state = OCCUPIED;
            return true;
        }

        if (table[i].state == OCCUPIED && table[i].kode == kode) {
            table[i].stok = stok;
            return true;
        }
    }
    return false;
}

Barang* search(Barang table[], int kode) {
    int idx = hashFunction(kode);

    for (int step = 0; step < SIZE; step++) {
        int i = (idx + step) % SIZE;

        if (table[i].state == EMPTY) return nullptr;
        if (table[i].state == OCCUPIED && table[i].kode == kode)
            return &table[i];
    }
    return nullptr;
}

bool removeBarang(Barang table[], int kode) {
    Barang* b = search(table, kode);
    if (!b) return false;
    b->state = DELETED;
    return true;
}

void display(Barang table[]) {
    cout << "\n=== Data Barang Gudang (Hash Map: Open Addressing) ===\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << ": ";
        if (table[i].state == EMPTY) cout << "EMPTY\n";
        else if (table[i].state == DELETED) cout << "DELETED\n";
        else cout << "(Kode: " << table[i].kode << ", Stok: " << table[i].stok << ")\n";
    }
}

int main() {
    Barang table[SIZE];
    initTable(table);


    insert(table, 101, 50); 
    insert(table, 111, 20);  
    insert(table, 121, 75);   
    insert(table, 102, 15);   

    display(table);

    Barang* hasil = search(table, 111);
    if (hasil)
        cout << "\nBarang dengan kode 111 ditemukan, stok = " << hasil->stok << endl;
    else
        cout << "\nBarang dengan kode 111 tidak ditemukan\n";

    removeBarang(table, 111);
    cout << "\nSetelah menghapus barang dengan kode 111:\n";
    display(table);

    return 0;
}
