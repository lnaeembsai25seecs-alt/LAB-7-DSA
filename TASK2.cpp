
#include <iostream>
#include <string>
using namespace std;

struct Student {
	int studentID;
	string name;
	float GPA;
	Student* left;
	Student* right;
};

class StudentBST {
private:
	Student* root;

	Student* insert(Student* node, int id, string name, float gpa) {
		if (node == nullptr) {
			Student* newStudent = new Student;
			newStudent->studentID = id;
			newStudent->name = name;
			newStudent->GPA = gpa;
			newStudent->left = nullptr;
			newStudent->right = nullptr;
			return newStudent;
		}

		if (id < node->studentID) {
			node->left = insert(node->left, id, name, gpa);
		}
		else if (id > node->studentID) {
			node->right = insert(node->right, id, name, gpa);
		}
		else {
			cout << "This student ID already exists.\n";
		}

		return node;
	}

	Student* search(Student* node, int id) {
		if (node == nullptr || node->studentID == id) {
			return node;
		}

		if (id < node->studentID) {
			return search(node->left, id);
		}

		return search(node->right, id);
	}

	Student* findMin(Student* node) {
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	Student* deleteStudent(Student* node, int id) {
		if (node == nullptr) {
			return nullptr;
		}

		if (id < node->studentID) {
			node->left = deleteStudent(node->left, id);
		}
		else if (id > node->studentID) {
			node->right = deleteStudent(node->right, id);
		}
		else {
			if (node->left == nullptr) {
				Student* temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == nullptr) {
				Student* temp = node->left;
				delete node;
				return temp;
			}

			Student* temp = findMin(node->right);

			node->studentID = temp->studentID;
			node->name = temp->name;
			node->GPA = temp->GPA;

			node->right = deleteStudent(node->right, temp->studentID);
		}

		return node;
	}

	void inorder(Student* node) {
		if (node == nullptr) {
			return;
		}

		inorder(node->left);

		cout << "ID: " << node->studentID
			<< " | Name: " << node->name
			<< " | GPA: " << node->GPA << endl;

		inorder(node->right);
	}

	int countStudents(Student* node) {
		if (node == nullptr) {
			return 0;
		}

		return 1 + countStudents(node->left)
			+ countStudents(node->right);
	}

	void highestGPA(Student* node, Student*& best) {
		if (node == nullptr) {
			return;
		}

		if (best == nullptr || node->GPA > best->GPA) {
			best = node;
		}

		highestGPA(node->left, best);
		highestGPA(node->right, best);
	}

	void lowestGPA(Student* node, Student*& best) {
		if (node == nullptr) {
			return;
		}

		if (best == nullptr || node->GPA < best->GPA) {
			best = node;
		}

		lowestGPA(node->left, best);
		lowestGPA(node->right, best);
	}

	void showAboveGPA(Student* node, float limit, bool& found) {
		if (node == nullptr) {
			return;
		}

		showAboveGPA(node->left, limit, found);

		if (node->GPA > limit) {
			cout << "ID: " << node->studentID
				<< " | Name: " << node->name
				<< " | GPA: " << node->GPA << endl;
			found = true;
		}

		showAboveGPA(node->right, limit, found);
	}

	void clearTree(Student* node) {
		if (node == nullptr) {
			return;
		}

		clearTree(node->left);
		clearTree(node->right);
		delete node;
	}

public:
	StudentBST() {
		root = nullptr;
	}

	~StudentBST() {
		clearTree(root);
	}

	void Insert(int id, string name, float gpa) {
		if (gpa < 0.0f || gpa > 4.0f) {
			cout << "GPA must be between 0.0 and 4.0.\n";
			return;
		}

		if (search(root, id) != nullptr) {
			cout << "This student ID already exists.\n";
			return;
		}

		root = insert(root, id, name, gpa);
		cout << "Student record added successfully.\n";
	}

	void Search(int id) {
		Student* student = search(root, id);

		if (student == nullptr) {
			cout << "Student record not found.\n";
		}
		else {
			cout << "\nStudent Details\n";
			cout << "ID: " << student->studentID << endl;
			cout << "Name: " << student->name << endl;
			cout << "GPA: " << student->GPA << endl;
		}
	}

	void Delete(int id) {
		if (search(root, id) == nullptr) {
			cout << "Student record not found.\n";
			return;
		}

		root = deleteStudent(root, id);
		cout << "Student record deleted successfully.\n";
	}

	void displayStudents() {
		if (root == nullptr) {
			cout << "No student records available.\n";
			return;
		}

		cout << "\nStudent Records (Sorted by ID)\n";
		inorder(root);
	}

	void totalStudents() {
		cout << "Total students: " << countStudents(root) << endl;
	}

	void showHighestGPA() {
		Student* best = nullptr;
		highestGPA(root, best);

		if (best == nullptr) {
			cout << "No student records available.\n";
		}
		else {
			cout << "\nStudent with Highest GPA\n";
			cout << "ID: " << best->studentID << endl;
			cout << "Name: " << best->name << endl;
			cout << "GPA: " << best->GPA << endl;
		}
	}

	void showLowestGPA() {
		Student* best = nullptr;
		lowestGPA(root, best);

		if (best == nullptr) {
			cout << "No student records available.\n";
		}
		else {
			cout << "\nStudent with Lowest GPA\n";
			cout << "ID: " << best->studentID << endl;
			cout << "Name: " << best->name << endl;
			cout << "GPA: " << best->GPA << endl;
		}
	}

	void studentsAboveGPA(float limit) {
		if (limit < 0.0f || limit > 4.0f) {
			cout << "Enter a GPA between 0.0 and 4.0.\n";
			return;
		}

		bool found = false;

		cout << "\nStudents with GPA above " << limit << ":\n";
		showAboveGPA(root, limit, found);

		if (!found) {
			cout << "No students found above this GPA.\n";
		}
	}
};

int main() {
	StudentBST bst;
	int choice, id;
	string name;
	float gpa, limit;

	// Adding a few student records to start with
	bst.Insert(103, "Ali", 3.5f);
	bst.Insert(101, "Ahmed", 3.2f);
	bst.Insert(105, "Sara", 3.9f);
	bst.Insert(102, "Ayesha", 2.8f);
	bst.Insert(104, "Usman", 3.7f);

	do {
		cout << "\n===== Student Record Management System =====\n";
		cout << "1. Add Student\n";
		cout << "2. Search Student\n";
		cout << "3. Delete Student\n";
		cout << "4. Display All Students\n";
		cout << "5. Count Students\n";
		cout << "6. Show Highest GPA\n";
		cout << "7. Show Lowest GPA\n";
		cout << "8. Show Students Above a GPA\n";
		cout << "9. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter student ID: ";
			cin >> id;

			cout << "Enter student name: ";
			getline(cin >> ws, name);

			cout << "Enter GPA: ";
			cin >> gpa;

			bst.Insert(id, name, gpa);
			break;

		case 2:
			cout << "Enter student ID to search: ";
			cin >> id;
			bst.Search(id);
			break;

		case 3:
			cout << "Enter student ID to delete: ";
			cin >> id;
			bst.Delete(id);
			break;

		case 4:
			bst.displayStudents();
			break;

		case 5:
			bst.totalStudents();
			break;

		case 6:
			bst.showHighestGPA();
			break;

		case 7:
			bst.showLowestGPA();
			break;

		case 8:
			cout << "Enter GPA threshold: ";
			cin >> limit;
			bst.studentsAboveGPA(limit);
			break;

		case 9:
			cout << "Program ended.\n";
			break;

		default:
			cout << "Invalid choice. Please try again.\n";
		}

	} while (choice != 9);

	return 0;
}
