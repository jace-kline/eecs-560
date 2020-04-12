#include "PatientManager.h"

int promptBoundedInt(std::string msg, int low = INT32_MIN, int high = INT32_MAX);

PatientManager::PatientManager() : heap(MAX, 3, 200) {}

PatientManager::~PatientManager() {}

void PatientManager::loadRecords() {
    Record tmp;
    std::ifstream fs;
    fs.open("patients.txt");
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

void PatientManager::addPatient() {
    Patient p = promptRecord(PATIENT, KEY);
    if(heap.insert(p)) std::cout << "The patient was successfully added to the heap.\n";
    else std::cout << "The patient was not successfully added. Perhaps the record was a duplicate?\n";
}

void PatientManager::removePatient() {
    try {
        Patient p = heap.popFront();
        std::cout << "Successfully removed the record at front of the priority queue.\n";
    } 
    catch(std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
}

void PatientManager::updateUrgency() {
    Patient p = promptRecord(PATIENT, NOKEY);
    int index = heap.tokenOf(p) - 1;
    if(index >= 0) {
        int newcnt = promptBoundedInt("Enter a new urgency for this patient:\n> ", 0);
        heap.deleteItem(p);
        Patient p2;
        p2.first_name = p.first_name;
        p2.last_name = p.last_name;
        p2.priority = newcnt;
        if(heap.insert(p2)) std::cout << "Successful update. Patient's new record:\n" << p2 << '\n';
        else std::cout << "Update failed. Heap insertion failed.\n"; 
    } else std::cout << "The provided patient record could not be found in the system.\n";
}

void PatientManager::nextPatient() {
    try {
        Patient p = heap.peekFront();
        std::cout << "Record '" << p << "' is at the front of the priority queue.\n";
    } 
    catch(std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
}

void PatientManager::lastPatient() {
    if(heap.isEmpty()) std::cout << "The heap is empty.\n";
    Patient p = heap.itemAtSorted(heap.size() - 1);
    std::cout << "The last patient in the priority queue is: " << p << '\n';
}

void PatientManager::patientToken() {
    Patient p = promptRecord(PATIENT, NOKEY);
    int token = heap.tokenOfSorted(p);
    if(token == -1) std::cout << "No record found with the given informatation.\n";
    else std::cout << "This patient has priority rank " << token << " in the queue.\n";
}

void PatientManager::patientCount() {
    std::cout << "There are " << heap.size() << " patients currently in the system.\n";
}

void PatientManager::patientReport() {
    std::cout << "Patient Report:\n";
    for(int i = 0; i < heap.size(); i++) {
        std::cout << heap.itemAt(i) << '\n';
    }
}
