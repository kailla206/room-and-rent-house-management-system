#include "tubes2.h"

/* ===================== FORMAT ===================== */
// BARU: ubah angka jadi format ribuan, contoh 2000000 -> "2.000.000"
string formatRupiah(long long n) {
    string s = to_string(n);
    int i = (int)s.length() - 3;
    while (i > 0) {
        s.insert(i, ".");
        i -= 3;
    }
    return s;
}

/* ===================== PRIMITIVES ===================== */
void createListParent(ListParent &L) {
    L.first = NULL;
}

bool isEmptyParent(ListParent L) {
    return L.first == NULL;
} 

bool isEmptyChild(adrParent P) {
    return P->firstChild == NULL;
}

/* ===================== PARENT OPERATIONS ===================== */
adrParent createParent(Room info) {
    adrParent P = new ElmParent;
    P->info = info;
    P->firstChild = NULL;
    P->next = NULL;
    return P;
}

void insertParent(ListParent &L, adrParent P) {
    // Insert last. Jika ID sudah ada, batalkan agar data tidak ganda.
    if (findParent(L, P->info.roomID) != NULL) {
        cout << "[!] Room ID " << P->info.roomID << " sudah ada. Data dibatalkan." << endl;
        delete P;
        return;
    }
    if (isEmptyParent(L)) {
        L.first = P;
    } else {
        adrParent Q = L.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
    cout << "[+] Room " << P->info.roomID << " berhasil ditambahkan." << endl;
}

bool deleteParent(ListParent &L, string roomID) {
    if (isEmptyParent(L)) {
        cout << "[!] List room kosong." << endl;
        return false;
    }
    adrParent P = L.first;
    adrParent prev = NULL;
    while (P != NULL && P->info.roomID != roomID) {
        prev = P;
        P = P->next;
    }
    if (P == NULL) {
        cout << "[!] Room " << roomID << " tidak ditemukan." << endl;
        return false;
    }

    // Lepas parent dari list utama (first / tengah / last ditangani sekaligus)
    if (prev == NULL) {
        L.first = P->next;
    } else {
        prev->next = P->next;
    }

    // Hapus seluruh child milik parent ini agar tidak terjadi memory leak
    adrChild C = P->firstChild;
    while (C != NULL) {
        adrChild temp = C;
        C = C->next;
        delete temp;
    }
    delete P;
    cout << "[-] Room " << roomID << " beserta riwayat pembayarannya berhasil dihapus." << endl;
    return true;
}

adrParent findParent(ListParent L, string key) {
    adrParent P = L.first;
    while (P != NULL) {
        if (P->info.roomID == key) return P;
        P = P->next;
    }
    return NULL;
}

adrParent findParentByTenant(ListParent L, string name) {
    adrParent P = L.first;
    while (P != NULL) {
        if (P->info.tenantName == name) return P;
        P = P->next;
    }
    return NULL;
}

void printParent(ListParent L) {
    if (isEmptyParent(L)) {
        cout << "[!] Belum ada data room." << endl;
        return;
    }
    cout << "=== DAFTAR ROOM ===" << endl;
    adrParent P = L.first;
    int no = 1;
    while (P != NULL) {
        cout << no++ << ". ID: " << P->info.roomID
             << " | Tenant: " << P->info.tenantName
             << " | Type: " << P->info.roomType
             << " | Rent: Rp" << formatRupiah(P->info.monthlyRent) << "/month" << endl;   // UBAH
        P = P->next;
    }
}

/* ===================== CHILD OPERATIONS ===================== */
adrChild createChild(Payment info) {
    adrChild C = new ElmChild;
    C->info = info;
    C->next = NULL;
    return C;
}

bool insertChild(ListParent L, string roomID, adrChild C) {
    adrParent P = findParent(L, roomID);
    if (P == NULL) {
        cout << "[!] Room " << roomID << " tidak ditemukan. Pembayaran dibatalkan." << endl;
        delete C;
        return false;
    }
    if (findChild(P, C->info.period) != NULL) {
        cout << "[!] Pembayaran periode " << C->info.period
             << " sudah tercatat pada room " << roomID << "." << endl;
        delete C;
        return false;
    }
    // Insert last pada child list milik P saja
    if (isEmptyChild(P)) {
        P->firstChild = C;
    } else {
        adrChild Q = P->firstChild;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = C;
    }
        cout << "[+] Pembayaran periode " << C->info.period
         << " (" << C->info.status << ")"
         << " berhasil dicatat pada room " << roomID << "." << endl;
    return true;
}

bool deleteChild(ListParent L, string roomID, string period) {
    adrParent P = findParent(L, roomID);
    if (P == NULL) {
        cout << "[!] Room " << roomID << " tidak ditemukan." << endl;
        return false;
    }
    if (isEmptyChild(P)) {
        cout << "[!] Room " << roomID << " belum memiliki riwayat pembayaran." << endl;
        return false;
    }
    adrChild C = P->firstChild;
    adrChild prev = NULL;
    while (C != NULL && C->info.period != period) {
        prev = C;
        C = C->next;
    }
    if (C == NULL) {
        cout << "[!] Pembayaran periode " << period << " tidak ditemukan." << endl;
        return false;
    }
    if (prev == NULL) {
        P->firstChild = C->next;
    } else {
        prev->next = C->next;
    }
    delete C;
    cout << "[-] Pembayaran periode " << period << " pada room " << roomID << " berhasil dihapus." << endl;
    return true;
}

adrChild findChild(adrParent P, string period) {
    if (P == NULL) return NULL;
    adrChild C = P->firstChild;
    while (C != NULL) {
        if (C->info.period == period) return C;
        C = C->next;
    }
    return NULL;
}

void printChild(adrParent P) {
    if (P == NULL) {
        cout << "[!] Room tidak ditemukan." << endl;
        return;
    }
    if (isEmptyChild(P)) {
        cout << "    (Belum ada riwayat pembayaran)" << endl;
        return;
    }
    adrChild C = P->firstChild;
    int no = 1;
    while (C != NULL) {
        cout << "    " << no++ << ". Period: " << C->info.period
             << " | Paid: Rp" << formatRupiah(C->info.amountPaid)   // UBAH
             << " | Method: " << C->info.method
             << " | Status: " << C->info.status << endl;
        C = C->next;
    }
}

/* ===================== PRINT ALL ===================== */
void printAll(ListParent L) {
    if (isEmptyParent(L)) {
        cout << "[!] Data kosong. Belum ada room." << endl;
        return;
    }
    cout << "=========== SEMUA DATA KOS ===========" << endl;
    adrParent P = L.first;
    while (P != NULL) {
        cout << "Room " << P->info.roomID
             << " | " << P->info.tenantName
             << " | " << P->info.roomType
             << " | Rp" << formatRupiah(P->info.monthlyRent) << "/month" << endl;   // UBAH
        printChild(P);
        cout << "--------------------------------------" << endl;
        P = P->next;
    }
}

/* ===================== EXTRA FEATURES ===================== */
int countChild(adrParent P) {
    int n = 0;
    if (P == NULL) return 0;
    adrChild C = P->firstChild;
    while (C != NULL) {
        n++;
        C = C->next;
    }
    return n;
}

long long totalPaid(adrParent P) {   // UBAH: int -> long long
    long long total = 0;             // UBAH: int -> long long
    if (P == NULL) return 0;
    adrChild C = P->firstChild;
    while (C != NULL) {
        total += C->info.amountPaid;
        C = C->next;
    }
    return total;
}

void printRoomsWithArrears(ListParent L) {
    if (isEmptyParent(L)) {
        cout << "[!] Belum ada data room." << endl;
        return;
    }
    bool found = false;
    cout << "=== ROOM DENGAN TUNGGAKAN (status Late) ===" << endl;
    adrParent P = L.first;
    while (P != NULL) {
        int late = 0;
        adrChild C = P->firstChild;
        while (C != NULL) {
            if (C->info.status == "Late") late++;
            C = C->next;
        }
        if (late > 0) {
            cout << "Room " << P->info.roomID << " (" << P->info.tenantName
                 << ") - " << late << " pembayaran telat" << endl;
            found = true;
        }
        P = P->next;
    }
    if (!found) cout << "Tidak ada room dengan tunggakan." << endl;
}

long long monthlyIncome(ListParent L, string period) {   // UBAH: int -> long long
    long long total = 0;                                 // UBAH: int -> long long
    adrParent P = L.first;
    while (P != NULL) {
        adrChild C = findChild(P, period);
        if (C != NULL) total += C->info.amountPaid;
        P = P->next;
    }
    return total;
}

adrParent roomWithMostPayments(ListParent L) {
    adrParent best = NULL;
    int bestCount = -1;
    adrParent P = L.first;
    while (P != NULL) {
        int c = countChild(P);
        if (c > bestCount) {
            bestCount = c;
            best = P;
        }
        P = P->next;
    }
    return best;
}