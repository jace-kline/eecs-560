#include "DoctorManager.h"

DoctorManager::DoctorManager() : heap(MIN, 3, 200) {}

DoctorManager::~DoctorManager() {}

void DoctorManager::loadRecords() {
    Record tmp;
    std::ifstream fs;
    fs.open("doctors.txt");
    std::string w;
    std::string s;
    while(fs >> w) {
        std::istringstream ss(w);
        std::getline(ss, s, ',');
        tmp.first_name = s;
        std::getline(ss, s, ',');
        tmp.last_name = s;
        std::getline(ss, s, ',');
        try {
            tmp.priority = std::stoi(s);
            heap.addNoHeapify(tmp);
        } catch (...) {}
    }
    heap.constructBottomUp();
}

void DoctorManager::addDoctor() {
    Doctor d = promptRecord(DOCTOR, NOKEY);
    if(heap.insert(d)) std::cout << "The doctor was successfully added and is available.\n";
    else std::cout << "The doctor was not successfully added. Perhaps the record was a duplicate?\n";
}

void DoctorManager::updatePatientCount() {
    Doctor d = promptRecord(DOCTOR, NOKEY);
    int index = heap.tokenOf(d) - 1;
    if(index >= 0) {
        int newcnt = promptBoundedInt("Enter a new patient count for this doctor:\n> ", 0, 25);
        heap.deleteItem(d);
        Doctor d2;
        d2.first_name = d.first_name;
        d2.last_name = d.last_name;
        d2.priority = newcnt;
        if(heap.insert(d2)) std::cout << "Successful update. Doctor's new record:\n" << d2 << '\n';
        else std::cout << "Update failed. Heap insertion failed.\n"; 
    } else std::cout << "The provided doctor record could not be found in the system.\n";
}

void DoctorManager::removeDoctor() {
    try {
        Doctor d = heap.popFront();
        std::cout << "Successfully removed the record at front of the priority queue.\n";
    } 
    catch(std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
}

void DoctorManager::nextDoctor() {
    try {
        Doctor d = heap.peekFront();
        std::cout << "Record '" << d << "' is at the front of the priority queue.\n";
    } 
    catch(std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
}

void DoctorManager::checkAvailability() {
    Doctor d = promptRecord(DOCTOR, NOKEY);
    int index = heap.tokenOf(d) - 1;
    if(index < 0) std::cout << "Doctor record not found.\n";
    else if(d.priority >= 22) std::cout << "This doctor is not available.\n";
    else {
        std::cout << "This doctor is available. They are currently serving " << heap.itemAt(index).priority << " patients.\n";
    }
}

void DoctorManager::numDoctors() {
    std::cout << "There are currently " << heap.size() << " doctors in the system.\n";
}

void DoctorManager::numAvailableDoctors() {
    int cnt = 0;
    for(int i = 0; i < heap.size(); i++) {
        if(heap.itemAt(i).priority < 22) cnt++;
    }
    std::cout << "There are currently " << cnt << " available doctors.\n";
}

void DoctorManager::availableDoctorsReport() {
    std::cout << "Available Doctors:\n";
    for(int i = 0; i < heap.size(); i++) {
        if(heap.itemAt(i).priority < 22) std::cout << heap.itemAt(i) << '\n';
    }
}

void DoctorManager::busyDoctorsReport() {
    std::cout << "Busy Doctors:\n";
    for(int i = 0; i < heap.size(); i++) {
        if(heap.itemAt(i).priority >= 22) std::cout << heap.itemAt(i) << '\n';
    }
}