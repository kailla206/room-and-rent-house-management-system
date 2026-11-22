#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

/* ===================== INFO TYPE ===================== */
// Info Parent: Room
struct Room {
    string roomID; 
    string tenantName;
    string roomType;   // "AC" / "Non-AC"
    long long monthlyRent;   // UBAH: int -> long long
};

// Info Child: Rent Payment
struct Payment {
    string period;     // format "MM-YYYY", contoh "01-2027"
    long long amountPaid;    // UBAH: int -> long long
    string method;     // "Cash" / "Transfer"
    string status;     // "Paid" / "Late" / "Unpaid"
};

/* ===================== ELEMENT ===================== */
typedef struct ElmChild *adrChild;
typedef struct ElmParent *adrParent;

struct ElmChild {
    Payment info;
    adrChild next;
};

struct ElmParent {
    Room info;
    adrChild firstChild;   // penghubung ke Child List milik parent ini
    adrParent next;
};

/* ===================== LIST ===================== */
struct ListParent {
    adrParent first;
};

/* ===================== PRIMITIVES ===================== */
void createListParent(ListParent &L);
bool isEmptyParent(ListParent L);
bool isEmptyChild(adrParent P);

/* ===================== PARENT OPERATIONS ===================== */
adrParent createParent(Room info);
void insertParent(ListParent &L, adrParent P);          // insert last, ID unik
bool deleteParent(ListParent &L, string roomID);        // hapus parent + seluruh child-nya
adrParent findParent(ListParent L, string key);         // cari by Room ID
adrParent findParentByTenant(ListParent L, string name);// cari by nama penghuni
void printParent(ListParent L);

/* ===================== CHILD OPERATIONS ===================== */
adrChild createChild(Payment info);
bool insertChild(ListParent L, string roomID, adrChild C);   // insert last pada parent tertentu
bool deleteChild(ListParent L, string roomID, string period);// hapus child pada parent tertentu
adrChild findChild(adrParent P, string period);              // cari child by periode
void printChild(adrParent P);

/* ===================== PRINT ALL ===================== */
void printAll(ListParent L);

/* ===================== EXTRA FEATURES ===================== */
int countChild(adrParent P);
long long totalPaid(adrParent P);                        // UBAH: int -> long long
void printRoomsWithArrears(ListParent L);          // kamar dengan status "Late"
long long monthlyIncome(ListParent L, string period);    // UBAH: int -> long long
adrParent roomWithMostPayments(ListParent L);

/* ===================== FORMAT ===================== */
string formatRupiah(long long n);                        // BARU

#endif // MLL_H_INCLUDED