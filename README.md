# 🚨 Emergency Dispatch System (C Implementation)

## Overview
This project is a console-based simulation of an **Emergency Dispatch System** implemented in C. It manages a fleet of emergency vehicles (Ambulance, Fire, Police) and processes incoming incidents based on a priority queue system (High, Medium, Low severity). It also utilizes a **Binary Search Tree (BST)** to manage different operational zones.

## ✨ Features

* **Vehicle Management:** Add, display, and release (mark as available) emergency vehicles (Ambulance, Fire, Police) using **Singly Linked Lists**.
* **Zone Management:** Initialize and display geographical zones using a **Binary Search Tree** for efficient storage and retrieval.
* **Incident Handling:** Add new incidents, specifying severity, required vehicle type, and location (Zone Name).
* **Priority Queues:** Incidents are automatically queued into **High, Medium, or Low priority queues** based on severity (3, 2, or 1).
* **Incident Processing:** Incidents are processed by dequeuing from the highest priority queue first (High $\rightarrow$ Medium $\rightarrow$ Low) and assigning an available vehicle of the required type.

## 🧱 Data Structures Used

| Component | C Implementation | Details |
| :--- | :--- | :--- |
| **Vehicles** | Linked Lists (`AmbHead`, `FireHead`, `PolHead`) | Stores vehicle type, ID, zone, and availability status. |
| **Zones** | Binary Search Tree (`zoneRoot`) | Stores Zone ID and Name. Sorted by **Zone ID**. |
| **Incidents** | Three separate Queues (`highQ`, `medQ`, `lowQ`) | Implemented as a fixed-size array-based queue to hold incidents based on their severity. |

## 🛠️ Build and Run

### Prerequisites
* A C compiler (e.g., GCC)

### Compilation

1.  Save the provided code as a file named `dispatch_system.c`.
2.  Open your terminal or command prompt.
3.  Compile the source code using a C compiler:



### Execution

Run the compiled executable:

```bash
./dispatch_system
