#include "DoctorManager.h"
#include "PatientManager.h"

void mainMenu();
void displayMainMenu();

void patientMenu();
void displayPatientMenu();

void doctorMenu();
void displayDoctorMenu();

// Global variables
PatientManager pm;
DoctorManager dm;

int main() {
    pm.loadRecords();
    dm.loadRecords();
    mainMenu();
    return 0;
}

void mainMenu() {
    int input = 0;
    while(input != 3) {
        displayMainMenu();
        input = promptResponse();
        switch (input)
        {
            case 1: patientMenu(); break;
            case 2: doctorMenu(); break;
            case 3: std::cout << "Exiting program.\n"; return;
            default:
                std::cout << "Invalid menu number. Please try again.\n";
                break;
        }
    }
}

void displayMainMenu() {
    std::cout << "\nManagement System - Main Menu:"
              << "\n\n1. Patient Management\n"
              << "2. Doctor Assignment\n"
              << "3. Exit\n\n";
}

void patientMenu() {
    int input = 0;
    while(input != 9) {
        displayPatientMenu();
        input = promptResponse();
        switch (input)
        {
            case 1: pm.addPatient(); break;
            case 2: pm.removePatient(); break;
            case 3: pm.updateUrgency(); break;
            case 4: pm.nextPatient(); break;
            case 5: pm.lastPatient(); break;
            case 6: pm.patientToken(); break;
            case 7: pm.patientCount(); break;
            case 8: pm.patientReport(); break;
            case 9: break;
            default:
                std::cout << "Invalid menu number. Please try again.\n";
                break;
        }
    }
}

void displayPatientMenu() {
    std::cout << "\nPatient Management System:"
              << "\n\n1. New Patient\n"
              << "2. Treat Patient\n"
              << "3. Change Urgency\n"
              << "4. Next Patient\n"
              << "5. Last Patient\n"
              << "6. Patient Token\n"
              << "7. Patient Count\n"
              << "8. Patient Report\n"
              << "9. Go Back to Menu\n\n";
}

void doctorMenu() {
    int input = 0;
    while(input != 10) {
        displayDoctorMenu();
        input = promptResponse();
        switch (input)
        {
            case 1: dm.addDoctor(); break;
            case 2: dm.updatePatientCount(); break;
            case 3: dm.removeDoctor(); break;
            case 4: dm.nextDoctor(); break;
            case 5: dm.checkAvailability(); break;
            case 6: dm.numDoctors(); break;
            case 7: dm.numAvailableDoctors(); break;
            case 8: dm.availableDoctorsReport(); break;
            case 9: dm.busyDoctorsReport(); break;
            case 10: break;
            default:
                std::cout << "Invalid menu number. Please try again.\n";
                break;
        }
    }
}

void displayDoctorMenu() {
    std::cout << "\nDoctor Management System:"
            << "\n\n1. New Doctor\n"
            << "2. Update Patients\n"
            << "3. Remove Doctor\n"
            << "4. Next Available Doctor\n"
            << "5. Check Availability\n"
            << "6. Total Doctor Count\n"
            << "7. Available Doctor Count\n"
            << "8. Available Doctors Report\n"
            << "9. Busy Doctors List\n"
            << "10. Go Back to Menu\n\n";
}