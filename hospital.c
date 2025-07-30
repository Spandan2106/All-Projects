// c code for hospital management system
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_PATIENTS 1000
#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define MAX_PHONE_LENGTH 15
#define MAX_DISEASE_LENGTH 50
#define MAX_DOCTOR_NAME_LENGTH 50
#define MAX_DATE_LENGTH 11
#define MAX_BLOOD_GROUP_LENGTH 5
#define MAX_MEDICINE_LENGTH 50
#define MAX_MEDICINE_COUNT 10
#define MAX_MEDICINE_NAME_LENGTH 50
#define MAX_MEDICINE_DOSAGE_LENGTH 20
#define MAX_MEDICINE_FREQUENCY_LENGTH 20
#define MAX_MEDICINE_DURATION_LENGTH 20
#define MAX_MEDICINE_INSTRUCTION_LENGTH 100
#define MAX_MEDICINE_SIDE_EFFECTS_LENGTH 100
#define MAX_MEDICINE_ADDITIONAL_INFO_LENGTH 100
#define MAX_MEDICINE_PRESCRIPTION_LENGTH 500
#define MAX_MEDICINE_PRESCRIPTION_COUNT 10
#define MAX_MEDICINE_PRESCRIPTION_NAME_LENGTH 50
#define MAX_MEDICINE_PRESCRIPTION_DOSAGE_LENGTH 20
#define MAX_MEDICINE_PRESCRIPTION_FREQUENCY_LENGTH 20
#define MAX_MEDICINE_PRESCRIPTION_DURATION_LENGTH 20
#define MAX_MEDICINE_PRESCRIPTION_INSTRUCTION_LENGTH 100
#define MAX_MEDICINE_PRESCRIPTION_SIDE_EFFECTS_LENGTH 100
#define MAX_MEDICINE_PRESCRIPTION_ADDITIONAL_INFO_LENGTH 100
#define MAX_MEDICINE_PRESCRIPTION_COUNT 10
#define MAX_MEDICINE_PRESCRIPTION_NAME_LENGTH 50
#define MAX_MEDICINE_PRESCRIPTION_DOSAGE_LENGTH 20
#define MAX_DOCTOR_SPECIALIZATION_LENGTH 50
#define MAX_DOCTOR_PHONE_LENGTH 15
#define MAX_DOCTOR_EMAIL_LENGTH 50
#define MAX_DOCTOR_ADDRESS_LENGTH 100
#define MAX_DOCTOR_COUNT 100
#define MAX_APPOINTMENT_DATE_LENGTH 11
#define MAX_APPOINTMENT_TIME_LENGTH 6
#define MAX_APPOINTMENT_REASON_LENGTH 100
#define MAX_APPOINTMENT_COUNT 100
typedef struct {
    char name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char disease[MAX_DISEASE_LENGTH];
    char doctorName[MAX_DOCTOR_NAME_LENGTH];
    char dateOfAdmission[MAX_DATE_LENGTH];
    char bloodGroup[MAX_BLOOD_GROUP_LENGTH];
} Patient;
typedef struct {
    char name[MAX_MEDICINE_NAME_LENGTH];
    char dosage[MAX_MEDICINE_DOSAGE_LENGTH];
    char frequency[MAX_MEDICINE_FREQUENCY_LENGTH];
    char duration[MAX_MEDICINE_DURATION_LENGTH];
    char instruction[MAX_MEDICINE_INSTRUCTION_LENGTH];
    char sideEffects[MAX_MEDICINE_SIDE_EFFECTS_LENGTH];
    char additionalInfo[MAX_MEDICINE_ADDITIONAL_INFO_LENGTH];
} Medicine;
typedef struct {
    char name[MAX_DOCTOR_NAME_LENGTH];
    char specialization[MAX_DOCTOR_SPECIALIZATION_LENGTH];
    char phone[MAX_DOCTOR_PHONE_LENGTH];
    char email[MAX_DOCTOR_EMAIL_LENGTH];
    char address[MAX_DOCTOR_ADDRESS_LENGTH];
} Doctor;
typedef struct {
    char date[MAX_APPOINTMENT_DATE_LENGTH];
    char time[MAX_APPOINTMENT_TIME_LENGTH];
    char reason[MAX_APPOINTMENT_REASON_LENGTH];
} Appointment;
typedef struct {
    Patient patients[MAX_PATIENTS];
    int patientCount;
    Medicine medicines[MAX_MEDICINE_COUNT];
    int medicineCount;
    Doctor doctors[MAX_DOCTOR_COUNT];
    int doctorCount;
    Appointment appointments[MAX_APPOINTMENT_COUNT];
    int appointmentCount;
} HospitalManagementSystem;
void initializeHospitalManagementSystem(HospitalManagementSystem *hms) {
    hms->patientCount = 0;
    hms->medicineCount = 0;
    hms->doctorCount = 0;
    hms->appointmentCount = 0;
}
void addPatient(HospitalManagementSystem *hms, Patient patient) {
    if (hms->patientCount < MAX_PATIENTS) {
        hms->patients[hms->patientCount++] = patient;
    } else {
        printf("Maximum patient limit reached.\n");
    }
}
void addMedicine(HospitalManagementSystem *hms, Medicine medicine) {
    if (hms->medicineCount < MAX_MEDICINE_COUNT) {
        hms->medicines[hms->medicineCount++] = medicine;
    } else {
        printf("Maximum medicine limit reached.\n");
    }
}
void addDoctor(HospitalManagementSystem *hms, Doctor doctor) {
    if (hms->doctorCount < MAX_DOCTOR_COUNT) {
        hms->doctors[hms->doctorCount++] = doctor;
    } else {
        printf("Maximum doctor limit reached.\n");
    }
}
void addAppointment(HospitalManagementSystem *hms, Appointment appointment) {
    if (hms->appointmentCount < MAX_APPOINTMENT_COUNT) {
        hms->appointments[hms->appointmentCount++] = appointment;
    } else {
        printf("Maximum appointment limit reached.\n");
    }
}
void displayPatients(const HospitalManagementSystem *hms) {
    printf("Patients:\n");
    for (int i = 0; i < hms->patientCount; i++) {
        printf("Name: %s, Address: %s, Phone: %s, Disease: %s, Doctor: %s, Date of Admission: %s, Blood Group: %s\n",
               hms->patients[i].name,
               hms->patients[i].address,
               hms->patients[i].phone,
               hms->patients[i].disease,
               hms->patients[i].doctorName,
               hms->patients[i].dateOfAdmission,
               hms->patients[i].bloodGroup);
    }
}
void displayMedicines(const HospitalManagementSystem *hms) {
    printf("Medicines:\n");
    for (int i = 0; i < hms->medicineCount; i++) {
        printf("Name: %s, Dosage: %s, Frequency: %s, Duration: %s, Instruction: %s, Side Effects: %s, Additional Info: %s\n",
               hms->medicines[i].name,
               hms->medicines[i].dosage,
               hms->medicines[i].frequency,
               hms->medicines[i].duration,
               hms->medicines[i].instruction,
               hms->medicines[i].sideEffects,
               hms->medicines[i].additionalInfo);
    }
}
void displayDoctors(const HospitalManagementSystem *hms) {
    printf("Doctors:\n");
    for (int i = 0; i < hms->doctorCount; i++) {
        printf("Name: %s, Specialization: %s, Phone: %s, Email: %s, Address: %s\n",
               hms->doctors[i].name,
               hms->doctors[i].specialization,
               hms->doctors[i].phone,
               hms->doctors[i].email,
               hms->doctors[i].address);
    }
}
void displayAppointments(const HospitalManagementSystem *hms) {
    printf("Appointments:\n");
    for (int i = 0; i < hms->appointmentCount; i++) {
        printf("Date: %s, Time: %s, Reason: %s\n",
               hms->appointments[i].date,
               hms->appointments[i].time,
               hms->appointments[i].reason);
    }
}
void saveDataToFile(const HospitalManagementSystem *hms, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(hms, sizeof(HospitalManagementSystem), 1, file);
    fclose(file);
    printf("Data saved to %s successfully.\n", filename);
}
void loadDataFromFile(HospitalManagementSystem *hms, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    fread(hms, sizeof(HospitalManagementSystem), 1, file);
    fclose(file);
    printf("Data loaded from %s successfully.\n", filename);
}
int main() {
    HospitalManagementSystem hms;
    initializeHospitalManagementSystem(&hms);
    int choice;
    do {
        printf("\nHospital Management System Menu:\n");
        printf("1. Add Patient\n");
        printf("2. Add Medicine\n");
        printf("3. Add Doctor\n");
        printf("4. Add Appointment\n");
        printf("5. Display Patients\n");
        printf("6. Display Medicines\n");
        printf("7. Display Doctors\n");
        printf("8. Display Appointments\n");
        printf("9. Save Data to File\n");
        printf("10. Load Data from File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                Patient patient;
                printf("Enter patient name: ");
                scanf("%s", patient.name);
                printf("Enter address: ");
                scanf("%s", patient.address);
                printf("Enter phone: ");
                scanf("%s", patient.phone);
                printf("Enter disease: ");
                scanf("%s", patient.disease);
                printf("Enter doctor name: ");
                scanf("%s", patient.doctorName);
                printf("Enter date of admission (DD/MM/YYYY): ");
                scanf("%s", patient.dateOfAdmission);
                printf("Enter blood group: ");
                scanf("%s", patient.bloodGroup);
                addPatient(&hms, patient);
                break;
            }
            case 2: {
                Medicine medicine;
                printf("Enter medicine name: ");
                scanf("%s", medicine.name);
                printf("Enter dosage: ");
                scanf("%s", medicine.dosage);
                printf("Enter frequency: ");
                scanf("%s", medicine.frequency);
                printf("Enter duration: ");
                scanf("%s", medicine.duration);
                printf("Enter instruction: ");
                scanf("%s", medicine.instruction);
                printf("Enter side effects: ");
                scanf("%s", medicine.sideEffects);
                printf("Enter additional info: ");
                scanf("%s", medicine.additionalInfo);
                addMedicine(&hms, medicine);
                break;
            }
            case 3: {
                Doctor doctor;
                printf("Enter doctor name: ");
                scanf("%s", doctor.name);
                printf("Enter specialization: ");
                scanf("%s", doctor.specialization);
                printf("Enter phone: ");
                scanf("%s", doctor.phone);
                printf("Enter email: ");
                scanf("%s", doctor.email);
                printf("Enter address: ");
                scanf
("%s", doctor.address);
                addDoctor(&hms, doctor);
                break;
            }
            case 4: {
                Appointment appointment;
                printf("Enter appointment date (DD/MM/YYYY): ");
                scanf("%s", appointment.date);
                printf("Enter appointment time (HH:MM): ");
                scanf("%s", appointment.time);
                printf("Enter reason for appointment: ");
                scanf("%s", appointment.reason);
                addAppointment(&hms, appointment);
                break;
            }
            case 5:
                displayPatients(&hms);
                break;
            case 6:

                displayMedicines(&hms);
                break;
            case 7:
                displayDoctors(&hms);
                break;
            case 8:
                displayAppointments(&hms);
                break;
            case 9: {
                char filename[100];
                printf("Enter filename to save data: ");
                scanf("%s", filename);
                saveDataToFile(&hms, filename);
                break;
            }
            case 10: {
                char filename[100];
                printf("Enter filename to load data: ");
                scanf("%s", filename);
                loadDataFromFile(&hms, filename);
                break;
            }
            case 0:
                printf("Exiting the program.\n");
                break;
            default:

                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
    return 0;
}