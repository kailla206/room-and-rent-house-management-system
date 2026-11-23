#include "tubes2.h"

int main() {
    ListParent L;
    createListParent(L);

    int choice = -1;
    int mode;
    string id, period;
    Room r;
    Payment p;
    adrParent P;
    adrChild C;

    while (choice != 0) {
        cout << endl;
        cout << "===== BOARDING HOUSE MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Tambah room" << endl;
        cout << "2. Tampilkan semua room" << endl;
        cout << "3. Cari room" << endl;
        cout << "4. Hapus room" << endl;
        cout << "5. Tambah pembayaran" << endl;
        cout << "6. Tampilkan pembayaran suatu room" << endl;
        cout << "7. Cari pembayaran" << endl;
        cout << "8. Hapus pembayaran" << endl;
        cout << "9. Tampilkan seluruh data" << endl;
        cout << "10. Jumlah dan total pembayaran suatu room" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            cout << "Room ID               : "; cin >> r.roomID;
            cout << "Nama tenant           : "; cin >> r.tenantName;
            cout << "Tipe (AC / Non-AC)    : "; cin >> r.roomType;
            cout << "Harga sewa per bulan  : "; cin >> r.monthlyRent;
            insertParent(L, createParent(r));

        } else if (choice == 2) {
            printParent(L);

        } else if (choice == 3) {
            cout << "Cari berdasarkan (1=ID, 2=Nama tenant): "; cin >> mode;
            if (mode == 1) {
                cout << "Room ID: "; cin >> id;
                P = findParent(L, id);
            } else {
                cout << "Nama tenant: "; cin >> id;
                P = findParentByTenant(L, id);
            }
            if (P == NULL) {
                cout << "Room tidak ditemukan." << endl;
            } else {
                cout << "Ditemukan: " << P->info.roomID << " | " << P->info.tenantName
                     << " | " << P->info.roomType << " | Rp" << P->info.monthlyRent << endl;
            }

        } else if (choice == 4) {
            cout << "Room ID yang dihapus: "; cin >> id;
            deleteParent(L, id);

        } else if (choice == 5) {
            cout << "Room ID                       : "; cin >> id;
            cout << "Periode (MM-YYYY)             : "; cin >> p.period;
            cout << "Nominal bayar                 : "; cin >> p.amountPaid;
            cout << "Metode (Cash / Transfer)      : "; cin >> p.method;
            cout << "Status (Paid / Late / Unpaid) : "; cin >> p.status;
            insertChild(L, id, createChild(p));

        } else if (choice == 6) {
            cout << "Room ID: "; cin >> id;
            P = findParent(L, id);
            if (P == NULL) {
                cout << "Room tidak ditemukan." << endl;
            } else {
                printChild(P);
            }

        } else if (choice == 7) {
            cout << "Room ID: "; cin >> id;
            P = findParent(L, id);
            if (P == NULL) {
                cout << "Room tidak ditemukan." << endl;
            } else {
                cout << "Periode (MM-YYYY): "; cin >> period;
                C = findChild(P, period);
                if (C == NULL) {
                    cout << "Pembayaran tidak ditemukan." << endl;
                } else {
                    cout << "Ditemukan: " << C->info.period << " | Rp" << C->info.amountPaid
                         << " | " << C->info.method << " | " << C->info.status << endl;
                }
            }

        } else if (choice == 8) {
            cout << "Room ID: "; cin >> id;
            cout << "Periode (MM-YYYY): "; cin >> period;
            deleteChild(L, id, period);

        } else if (choice == 9) {
            printAll(L);

        } else if (choice == 10) {
            cout << "Room ID: "; cin >> id;
            P = findParent(L, id);
            if (P == NULL) {
                cout << "Room tidak ditemukan." << endl;
            } else {
                cout << "Jumlah pembayaran : " << countChild(P) << endl;
                cout << "Total dibayar     : Rp" << totalPaid(P) << endl;
            }

        } else if (choice != 0) {
            cout << "Menu tidak valid." << endl;
        }
    }

    cout << "Program selesai." << endl;
    return 0;
}
