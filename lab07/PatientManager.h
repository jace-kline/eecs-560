#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H

#include "Heap.h"
#include "Record.h"
#include "IO.h"
#include <fstream>

class PatientManager {
    private:
        Heap<Patient> heap;

    public:
        PatientManager();
        ~PatientManager();
        void loadRecords();
        void addPatient();
        void removePatient();
        void updateUrgency();
        void nextPatient();
        void lastPatient();
        void patientToken();
        void patientCount();
        void patientReport();
};

#endif