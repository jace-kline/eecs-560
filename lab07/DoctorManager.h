#ifndef DOCTOR_MANAGER_H
#define DOCTOR_MANAGER_H

#include "Heap.h"
#include "IO.h"
#include <iostream>
#include <fstream>

class DoctorManager {
    private:
        Heap<Doctor> heap;

    public:
        DoctorManager();
        ~DoctorManager();
        void loadRecords();
        void addDoctor();
        void updatePatientCount();
        void removeDoctor();
        void nextDoctor();
        void checkAvailability();
        void numDoctors();
        // prints # of doctors with patient count < 22
        void numAvailableDoctors();
        void availableDoctorsReport();
        void busyDoctorsReport();
};

#endif