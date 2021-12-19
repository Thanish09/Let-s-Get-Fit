#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void BBR(double[], double[], int[], char[], int, double&, double&, double&);
void oldChange(string[], string[], char[], int[], double[], double[], int);
void combiS(string[], string[], char[], int[], double[], double[], int, double[], double[], double[]);
void StatiS(char[], int[], double[], double[], int);
void myTarget(string[], double[], double[], char[], int[], int);
void bbr(double[], double[], int[], char[], int, double[], double[], double[]);

int main()
{
	cout << "\t\t\t\t*************" << endl;   // display title
	cout << "\t\t\t\tLET'S GET FIT" << endl;
	cout << "\t\t\t\t*************" << endl;

	fstream UsmStaff;
	ofstream UsmFile;
	const int size = 15;
	string file, Name[size], StaffId[size], Staff;
	char Gender[size], yesno;
	int Age[size], x = 0, y = 0, start, staf, search, com;
	double Height[size], Weight[size], bmi = 0, bmr = 0, rmr = 0, BMi[size], BMr[size], RMr[size], Bmi[size], Bmr[size], Rmr[size];
	bool ID = true;
	int menu(); // declaration of menu
	int staff(); // declaration of staff
	while (start = menu())
	{
		if (start == 3) // to exit program
		{
			cout << "Your Informations is been stored in output file." << endl;
			cout << "Thank you for using this app. :)" << endl;

			UsmFile.open("Let.txt"); // create output file

			for (int i = 0; i < y; i++)
			{
				UsmFile << Name[i] << "\t";  // stores all data in output file from arrays
				UsmFile << StaffId[i] << "\t";
				UsmFile << Gender[i] << "\t";
				UsmFile << Age[i] << "\t";
				UsmFile << Weight[i] << "\t";
				UsmFile << Height[i] << "\t";
				UsmFile << Bmi[i] << "\t";
				UsmFile << Bmr[i] << "\t";
				UsmFile << Rmr[i] << "\n";
			}
			UsmFile.close();
			break;
		}
		while (x < 1) //read file one time only;
		{
			cout << "Enter the file name(Ex:FileName): " << endl;
			cin >> file;
			cout << "Please wait while processing the file." << endl;

			while (file != "")
			{
				file += ".txt";               // adding txt automatically
				UsmStaff.open(file, ios::in); //read the file

				if (UsmStaff)
				{
					cout << "Opening the file..." << endl << endl;
					break;
				}
				else if (!UsmStaff)
				{
					cout << "There is no such file exist.\nPlease enter the file name again:\n";
					cin >> file;
				}
			}

			for (int i = 0; i < size && !UsmStaff.eof(); i++)
			{
				getline(UsmStaff, Name[i], '\t');      //stores all data from file into arrays
				UsmStaff >> StaffId[i];
				UsmStaff >> Gender[i];
				UsmStaff >> Age[i];
				UsmStaff >> Weight[i];
				UsmStaff >> Height[i];
				UsmStaff.ignore();
				y = y + 1;   //to know the how many data is there in the file;
			}
			UsmStaff.close();
			bbr(Height, Weight, Age, Gender, y, Bmi, Bmr, Rmr); //store bmi,bmr,rmr in array
			x++;
		}
		if (start == 1)
		{
			staf = staff();
			if (staf == 1)  // For data in the file
			{
				while (ID)
				{
					cout << "Enter your Staff ID: " << endl;  //Identify data in file
					cin >> Staff;

					for (int i = 0; i < size; i++)
					{
						if (Staff == StaffId[i])         //searching for same staff data 
						{
							cout << " Name: " << Name[i] << endl;
							cout << "  StaffID: " << StaffId[i] << endl;
							cout << "  Gender: " << Gender[i] << endl;
							cout << "  Age: " << Age[i] << endl;
							cout << "  Weight: " << Weight[i] << endl;
							cout << "  Height: " << Height[i] << endl << endl;
							BBR(Height, Weight, Age, Gender, i, bmi, bmr, rmr);
							cout << "Your BMI: " << bmi << endl;
							cout << "Your BMR: " << bmr << endl;
							cout << "Your RMR: " << rmr << endl;

							cout << "Do you want to change any information? (Y/N)" << endl; //Ask to change data in file
							cin >> yesno;
							while (yesno)
							{
								if (yesno == 'Y' || yesno == 'y')
								{
									oldChange(Name, StaffId, Gender, Age, Weight, Height, i);  //For edit data
									BBR(Height, Weight, Age, Gender, i, bmi, bmr, rmr);  // for calculate bmi,bmr,rmr
									cout << "Your BMI: " << bmi << endl;
									cout << "Your BMR: " << bmr << endl;
									cout << "Your RMR: " << rmr << endl;

									cout << "Do you want to change any information? (Y/N)" << endl;
									cin >> yesno;
								}
								else if (yesno == 'N' || yesno == 'n' || yesno != 'Y' || yesno != 'y')
								{
									break;
								}
							}
							ID = true;
							break;
						}
						else if (Staff != StaffId[y])  //If data cannot found in file
						{
							ID = false;
						}
					}
					while (!ID)
					{
						cout << "Your Staff Id not the the data.\nPls go to new staff and add ur information.\n";
						staff();
						ID = true;
						break;
					}
					break;
				}
			}
			else if (staf == 2)      // For user to add new data
			{
				cout << "Welcome new staff" << endl;

				cout << "Enter your name: " << endl;
				cin.ignore();
				getline(cin, Name[y]);
				cout << "Enter your Staff ID:  " << endl;
				cin >> StaffId[y];
				cout << "Enter your Gender(L/P): " << endl;
				cin >> Gender[y];
				while (Gender[y] != 'L' && Gender[y] != 'P')
				{
					cout << "Gender not relevent." << endl;
					cout << "Enter your Gender: " << endl;
					cin >> Gender[y];
				}
				cout << "Enter your age: " << endl;
				cin >> Age[y];
				while (Age[y] <= 0 || Age[y] > 160)
				{
					cout << "Age not relevent." << endl;
					cout << "Enter your age: " << endl;
					cin >> Age[y];
				}
				cout << "Enter your weight: " << endl;
				cin >> Weight[y];
				while (Weight[y] <= 10)
				{
					cout << "Weight not relevent." << endl;
					cout << "Enter your weight: " << endl;
					cin >> Weight[y];
				}
				cout << "Enter your height: " << endl;
				cin >> Height[y];
				while (Height[y] <= 10 || Height[y] > 270)
				{
					cout << "Height not relevent." << endl;
					cout << "Enter your height: " << endl;
					cin >> Height[y];
				}
				BBR(Height, Weight, Age, Gender, y, bmi, bmr, rmr);   // calculate bmi,bmr,rmr
				cout << "Your BMI: " << bmi << endl;
				cout << "Your BMR: " << bmr << endl;
				cout << "Your RMR: " << rmr << endl;

				cout << "Do you want to change any information? (Y/N)" << endl;  //ask to edit the data entered
				cin >> yesno;
				while (yesno)
				{
					if (yesno == 'Y' || yesno == 'y')      // perform editing
					{
						oldChange(Name, StaffId, Gender, Age, Weight, Height, y);
						BBR(Height, Weight, Age, Gender, y, bmi, bmr, rmr);
						cout << "Your BMI: " << bmi << endl;
						cout << "Your BMR: " << bmr << endl;
						cout << "Your RMR: " << rmr << endl;
						cout << "Do you want to change any information? (Y/N)" << endl;
						cin >> yesno;
					}
					else if (yesno == 'N' || yesno == 'n' || yesno != 'Y' || yesno != 'y')
					{
						break;
					}
				}
				y += 1;
				bbr(Height, Weight, Age, Gender, y, Bmi, Bmr, Rmr);   //to put bmi,bmr,rmr in array
			}
			else if (staf == 3)
				cout << "Thank you.You will be return to main menu in a while." << endl;
			else
				cout << "Invalid number.Please enter again." << endl;
		}
		else if (start == 2) // For search
		{
			cout << "Please enter number for type of search." << endl;
			cout << "1.Combinational Search.\n2.Statistical distributuion.\n3.My Target\n4.End" << endl;
			cin >> search;

			if (search == 1)  //combinational search
			{
				combiS(Name, StaffId, Gender, Age, Weight, Height, y, BMi, BMr, RMr);
			}
			else if (search == 2)  //Statistical search
			{
				StatiS(Gender, Age, Height, Weight, y);
			}
			else if (search == 3)   //target calculation
			{
				myTarget(StaffId, Weight, Height, Gender, Age, y);
			}
			else if (search == 4) // returning to menu
			{
				cout << "Returning to main menu..." << endl;
			}
			else if (search < 1 || search >4) // returning to menu
			{
				cout << "Invalid number.Returning to main menu." << endl;
			}
		}
	}
	return 0;

}

int menu() //function for menu
{
	int men;

	cout << "Enter the number for the information you want:" << endl;
	cout << "1.Staff Information\n2.Search\n3.End" << endl;
	cin >> men;
	while (men < 1 || men >3)
	{
		cout << "Invalid number.Please enter again." << endl;
		cout << "Enter the number for the information you want:" << endl;
		cout << "1.Staff Information\n2.Search\n3.End" << endl;
		cin >> men;
	}

	return men;
}

int staff() //function of staff information
{
	int sta;

	cout << "Enter the number for staff type" << endl;
	cout << "1.Old Staff\n2.New Staff\n3.End\n";
	cin >> sta;
	while (sta < 0 || sta > 3)
	{
		cout << "Invalid number.Please enter again." << endl;
		cout << "Enter the number for staff type" << endl;
		cout << "1.Old Staff\n2.New Staff\n3.End\n";
		cin >> sta;
	}

	return sta;
}

void oldChange(string name[], string staffId[], char gender[], int age[], double weight[], double height[], int n) //edit data
{
	system("CLS");
	int editnum;

	for (int i = 0; (i <= n); i++)    //editing the data for specific data entered by user
	{
		if (i == n)
		{
			cout << "Enter the info you want to edit by press the num: " << endl;
			cout << "1.Name\n2.StaffId\n3.Gender\n4.Age\n5.Weight\n6.Height" << endl;
			cin >> editnum;

			if (editnum == 1)   //edit name
			{
				cout << "Enter your name: " << endl;
				cin.ignore();
				getline(cin, name[i]);
			}
			else if (editnum == 2)  //edit Staff ID
			{
				cout << "Enter your Staff ID: " << endl;
				cin >> staffId[i];
			}
			else if (editnum == 3)   //edit gender
			{
				cout << "Enter your gender(L/P): " << endl;
				cin >> gender[i];
				while (gender[i] != 'L' && gender[i] != 'P')
				{
					cout << "Invalid gender." << endl;
					cout << "Enter your gender: " << endl;
					cin >> gender[i];
				}
			}
			else if (editnum == 4)   //edit age
			{
				cout << "Enter your age: " << endl;
				cin >> age[i];
				while (age[i] <= 0 || age[i] > 60)
				{
					cout << "Age not relevent." << endl;
					cout << "Enter your age: " << endl;
					cin >> age[i];
				}
			}
			else if (editnum == 5)   //edit weight
			{
				cout << "Enter your weight: " << endl;
				cin >> weight[i];
				while (weight[i] <= 10)
				{
					cout << "Weight not relevent." << endl;
					cout << "Enter your weight: " << endl;
					cin >> weight[i];
				}
			}
			else if (editnum == 6)  //edit height
			{
				cout << "Enter your Height: " << endl;
				cin >> height[i];
				while (height[i] <= 10 || height[i] > 270)
				{
					cout << "Height not relevent." << endl;
					cout << "Enter your Height: " << endl;
					cin >> height[i];
				}
			}

			cout << "Your changes has been saved.Thank you." << endl << endl;
			break;
		}
	}
	for (int i = 0; (i <= n); i++) //display the edited data along with all data
	{
		if (i == n)
		{
			cout << "\nName: " << name[i] << endl;
			cout << "StaffId: " << staffId[i] << endl;
			cout << "Gender: " << gender[i] << endl;
			cout << "Age: " << age[i] << endl;
			cout << "Weight: " << weight[i] << endl;
			cout << "Height: " << height[i] << endl << endl;
			break;
		}
	}
	system("PAUSE");
}

void BBR(double height[], double weight[], int age[], char gender[], int n, double& bmi, double& bmr, double& rmr) //to return bmi,bmr,rmr
{
	int i = 0;
	while (n >= 0)
	{
		if (i == n)
		{
			bmi = weight[i] / pow(((height[i]) / 100), 2);  //calculate bmi for specific data

			if (gender[i] == 'L')
			{
				bmr = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] + 5;     // calculate bmr for male for specific data
				rmr = 88.362 + (13.397 * weight[i]) + (4.799 * height[i]) - (5.677 * age[i]);  //calculate rmr for male for specific data
				break;
			}
			else if (gender[i] == 'P')
			{
				bmr = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] - 161;  //calculate bmr for female for specific data
				rmr = 447.593 + (9.247 * weight[i]) + (3.098 * height[i]) - (4.330 * age[i]);   //calculate rmr for female for specific data
				break;
			}
		}
		i += 1;
	}
}

void combiS(string name[], string staff[], char gender[], int age[], double weight[], double height[], int n, double bmi[], double bmr[], double rmr[])
{
	system("CLS");
	int x, y, a, b = 1000, c = 0, d = 0, e = 0, f = 0, i = 0;
	double ab = 100000, ac = 0, ad = 0, ae = 0, af = 0, bb = 100000, bc = 0, bd = 0, be = 0, bf = 0;
	char k = 'L', l = 'P';

	while (i < n)
	{
		bmi[i] = weight[i] / pow(((height[i]) / 100), 2);  //calculate bmi
		if (gender[i] == 'L')
		{
			bmr[i] = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] + 5; //calculate bmr for male
			rmr[i] = 88.362 + (13.397 * weight[i]) + (4.799 * height[i]) - (5.677 * age[i]); //calculate rmr for male
		}
		else if (gender[i] == 'P')
		{
			bmr[i] = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] - 161;  //calculate bmr for female
			rmr[i] = 447.593 + (9.247 * weight[i]) + (3.098 * height[i]) - (4.330 * age[i]);  //caluclate rmr for female
		}
		i++;
	}

	cout << "Choose two informations you want to search" << endl;  //choosing data wanted to be search by user
	cout << "1.Age\n2.Gender\n3.BMI\n4.BMR\n5.RMR" << endl;
	cin >> x >> y;
	while (x < 1 || x>5 || y < 1 || y>5)
	{
		cout << "Invalid choice.Choose again." << endl;
		cout << "Choose two informations you want to search" << endl;
		cout << "1.Age\n2.Gender\n3.BMI\n4.BMR\n5.RMR" << endl;
		cin >> x >> y;
	}

	if ((x == 1 && y == 2) || (x == 2 && y == 1))  //combine  age with gender
	{
		cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
		cin >> a;
		while (a < 1 || a>4)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
			cin >> a;
		}
		if (a == 1) //age more than
		{
			cout << "Enter the value: " << endl;
			cin >> b;
			while (b < 1 || b>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> b;
			}
		}
		else if (a == 2) //age less than
		{
			cout << "Enter the value: " << endl;
			cin >> c;
			while (c < 1 || c>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> c;
			}
		}
		else if (a == 3)  //age equals to
		{
			cout << "Enter the value: " << endl;
			cin >> d;
			while (d < 1 || d>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> d;
			}
		}
		else if (a == 4)   //range of age
		{
			cout << "Enter the values: " << endl;
			cin >> e;
			cin >> f;
			while (e < 1 || e>60 || f < 1 || f < 60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> e;
				cin >> f;
			}
		}


		cout << "Enter\n1. For Male\n2. For Female" << endl;
		cin >> a;
		while (a < 1 || a > 2)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For Male\n2. For Female" << endl;
			cin >> a;
		}

		if (a == 1) //Male
		{
			k;
		}
		else if (a == 2)  //Female
		{
			l;
		}

		for (int i = 0; i < n; i++)
		{
			if (age[i] > b && gender[i] == k)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && gender[i] == k)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && gender[i] == k)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && gender[i] == k)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > b && gender[i] == l)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && gender[i] == l)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && gender[i] == l)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && gender[i] == l)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "Age: " << age[i] << endl << endl;
			}
		}
	}
	else if ((x == 1 && y == 3) || (x == 3 && y == 1)) // combine age and bmi
	{
		cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
		cin >> a;
		while (a < 1 || a>4)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
			cin >> a;
		}
		if (a == 1)  //age more than
		{
			cout << "Enter the value: " << endl;
			cin >> b;
			while (b < 1 || b>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> b;
			}
		}
		else if (a == 2)   //age less than
		{
			cout << "Enter the value: " << endl;
			cin >> c;
			while (c < 1 || c>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> c;
			}
		}
		else if (a == 3)  //age equals to
		{
			cout << "Enter the value: " << endl;
			cin >> d;
			while (d < 1 || d>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> d;
			}
		}
		else if (a == 4)  //age in range
		{
			cout << "Enter the values: " << endl;
			cin >> e;
			cin >> f;
			while (e < 1 || e>60 || f < 1 || f>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> e;
				cin >> f;
			}
		}

		cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
			cin >> a;
		}
		if (a == 1)  //bmi more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 8 || ab>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)  //bmi less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 8 || ac>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3) //bmi range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 8 || ae>100 || af < 8 || af>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (bmi[i] > ab))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (bmi[i] < ac))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (bmi[i] > ae) && (bmi[i] < af))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && bmi[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && bmi[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && bmi[i] > ae && bmi[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && bmi[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && bmi[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && bmi[i] > ae && bmi[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && bmi[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && bmi[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && bmi[i] > ae && bmi[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
	}
	else if ((x == 1 && y == 4) || (x == 4 && y == 1)) //combine age with bmr
	{
		cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
		cin >> a;
		while (a < 1 || a>4)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
			cin >> a;
		}
		if (a == 1)  //age more than
		{
			cout << "Enter the value: " << endl;
			cin >> b;
			while (b < 1 || b>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> b;
			}
		}
		else if (a == 2)   //age less than
		{
			cout << "Enter the value: " << endl;
			cin >> c;
			while (c < 1 || c>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> c;
			}
		}
		else if (a == 3)  //age equals to
		{
			cout << "Enter the value: " << endl;
			cin >> d;
			while (d < 1 || d>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> d;
			}
		}
		else if (a == 4)   //age in range
		{
			cout << "Enter the values: " << endl;
			cin >> e;
			cin >> f;
			while (e < 1 || e>60 || f < 1 || f>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> e;
				cin >> f;
			}
		}

		cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
			cin >> a;
		}
		if (a == 1)   //bmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)  //bmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3)  //bmr range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 300 || af < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (bmr[i] > ab))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (bmr[i] < ac))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (bmr[i] > ae) && (bmr[i] < af))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && bmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && bmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && bmr[i] > ae && bmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && bmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && bmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && bmr[i] > ae && bmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && bmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && bmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && bmr[i] > ae && bmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
	}
	else if ((x == 1 && y == 5) || (x == 5 && y == 1))  //compare age with rmr
	{
		cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
		cin >> a;
		while (a < 1 || a>4)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For age more than\n2. For age less than\n3. For age equals to\n4. For age range between" << endl;
			cin >> a;
		}
		if (a == 1) //age more than
		{
			cout << "Enter the value: " << endl;
			cin >> b;
			while (b < 1 || b>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> b;
			}
		}
		else if (a == 2)  //age less than
		{
			cout << "Enter the value: " << endl;
			cin >> c;
			while (c < 1 || c>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> c;
			}
		}
		else if (a == 3)  //age equals to
		{
			cout << "Enter the value: " << endl;
			cin >> d;
			while (d < 1 || d>60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> d;
			}
		}
		else if (a == 4)  //age range
		{
			cout << "Enter the values: " << endl;
			cin >> e;
			cin >> f;
			while (e < 1 || e>60 || f < 1 || f >60)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> e;
				cin >> f;
			}
		}

		cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
			cin >> a;
		}
		if (a == 1)   //rmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)   //rmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3)  //rmr range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 300 || af < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (rmr[i] > ab))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (rmr[i] < ac))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if ((age[i] > b) && (rmr[i] > ae) && (rmr[i] < af))
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && rmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && rmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] < c && rmr[i] > ae && rmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && rmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && rmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] == d && rmr[i] > ae && rmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && rmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && rmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (age[i] > e && age[i] < f && rmr[i] > ae && rmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Age: " << age[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
	}
	else if ((x == 2 && y == 3) || (x == 3 && y == 2)) // compare gender with bmi
	{
		cout << "Enter\n1. For Male\n2. For Female" << endl;
		cin >> a;
		while (a < 1 || a > 2)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For Male\n2. For Female" << endl;
			cin >> a;
		}

		if (a == 1)  //male
		{
			k;
		}
		else if (a == 2)  //female
		{
			l;
		}

		cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
			cin >> a;
		}
		if (a == 1)   //bmi more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 8 || ab>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)  //bmi less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 8 || ac>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3) //bmi range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 8 || ae>100 || af < 8 || af >100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && bmi[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && bmi[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && bmi[i] > ae && bmi[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && bmi[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && bmi[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && bmi[i] > ae && bmi[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMI: " << bmi[i] << endl << endl;
			}
		}

	}
	else if ((x == 2 && y == 4) || (x == 4 && y == 2))  // compare gender with bmr
	{
		cout << "Enter\n1. For Male\n2. For Female" << endl;
		cin >> a;
		while (a < 1 || a > 2)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For Male\n2. For Female" << endl;
			cin >> a;
		}

		if (a == 1)  //Male
		{
			k;
		}
		else if (a == 2)  //Female
		{
			l;
		}

		cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
		cin >> a;
		while (a < 1 || a>4)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
			cin >> a;
		}
		if (a == 1)  //bmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)  //bmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3)   // bmr range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 300 || af < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && bmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && bmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && bmr[i] > ae && bmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && bmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && bmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && bmr[i] > ae && bmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}

	}
	else if ((x == 2 && y == 5) || (x == 5 && y == 2)) //compare gender with rmr
	{
		cout << "Enter\n1. For Male\n2. For Female" << endl;
		cin >> a;
		while (a < 1 || a > 2)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For Male\n2. For Female" << endl;
			cin >> a;
		}

		if (a == 1)  //Male
		{
			k;
		}
		else if (a == 2)  //Female
		{
			l;
		}

		cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
			cin >> a;
		}
		if (a == 1) //rmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2) //rmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3) //rmr range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 300 || af < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && rmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && rmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == k && rmr[i] > ae && rmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && rmr[i] > ab)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && rmr[i] < ac)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (gender[i] == l && rmr[i] > ae && rmr[i] < af)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "Gender: " << gender[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
	}
	else if ((x == 3 && y == 4) || (x == 4 && y == 3)) //compare bmi with bmr
	{
		cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
			cin >> a;
		}
		if (a == 1)  // bmi more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 8 || ab>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)  //bmi less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 8 || ac>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3)  // bmi range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 8 || ae>100 || af < 8 || af>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
			cin >> a;
		}
		if (a == 1)   //bmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> bb;
			while (bb < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> bb;
			}
		}
		else if (a == 2)   //bmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> bc;
			while (bc < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> bc;
			}
		}
		else if (a == 3)  //bmr range
		{
			cout << "Enter the values: " << endl;
			cin >> be;
			cin >> bf;
			while (be < 300 || bf < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> be;
				cin >> bf;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ab && bmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ab && bmr[i] < bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ab && bmr[i] > be && bmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] < ac && bmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] < ac && bmr[i] > bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] < ac && bmr[i] > be && bmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ae && bmi[i] < af && bmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ae && bmi[i] < af && bmr[i] > bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ae && bmi[i] < af && bmr[i] > be && bmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "BMR: " << bmr[i] << endl << endl;
			}
		}
	}
	else if ((x == 3 && y == 5) || (x == 5 && y == 3)) //compare bmi with bmr
	{
		cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMI more than\n2. For BMI less than\n3. For BMI range between" << endl;
			cin >> a;
		}
		if (a == 1) //bmi more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 8 || ab>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)  //bmi less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 8 || ac>100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3)   //bmi range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 8 || ae>100 || af < 8 || af >100)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
			cin >> a;
		}
		if (a == 1)  //rmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> bb;
			while (bb < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> bb;
			}
		}
		else if (a == 2)   //rmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> bc;
			while (bc < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> bc;
			}
		}
		else if (a == 3)  //rmr range
		{
			cout << "Enter the values: " << endl;
			cin >> be;
			cin >> bf;
			while (be < 300 || bf < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> be;
				cin >> bf;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ab && rmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ab && rmr[i] < bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ab && rmr[i] > be && rmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] < ac && rmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] < ac && rmr[i] > bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] < ac && rmr[i] > be && rmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ae && bmi[i] < af && rmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ae && bmi[i] < af && rmr[i] > bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmi[i] > ae && bmi[i] < af && rmr[i] > be && rmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMI: " << bmi[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
	}
	else if ((x == 4 && y == 5) || (x == 5 && y == 4))  //compare bmr with rmr
	{
		cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
		cin >> a;
		while (a < 1 || a>4)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For BMR more than\n2. For BMR less than\n3. For BMR range between" << endl;
			cin >> a;
		}
		if (a == 1)   // bmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> ab;
			while (ab < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ab;
			}
		}
		else if (a == 2)  //bmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> ac;
			while (ac < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ac;
			}
		}
		else if (a == 3)  //bmr range
		{
			cout << "Enter the values: " << endl;
			cin >> ae;
			cin >> af;
			while (ae < 300 || af < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> ae;
				cin >> af;
			}
		}

		cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
		cin >> a;
		while (a < 1 || a>3)
		{
			cout << "Invalid input.Choose again." << endl;
			cout << "Enter\n1. For RMR more than\n2. For RMR less than\n3. For RMR range between" << endl;
			cin >> a;
		}
		if (a == 1)   //rmr more than
		{
			cout << "Enter the value: " << endl;
			cin >> bb;
			while (bb < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> bb;
			}
		}
		else if (a == 2)  //rmr less than
		{
			cout << "Enter the value: " << endl;
			cin >> bc;
			while (bc < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> bc;
			}
		}
		else if (a == 3)  //rmr range
		{
			cout << "Enter the values: " << endl;
			cin >> be;
			cin >> bf;
			while (be < 300 || bf < 300)
			{
				cout << "Invalid value.Enter again." << endl;
				cout << "Enter the value: " << endl;
				cin >> be;
				cin >> bf;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (bmr[i] > ab && rmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] > ab && rmr[i] < bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] > ab && rmr[i] > be && rmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] < ac && rmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] < ac && rmr[i] > bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] < ac && rmr[i] > be && rmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] > ae && bmr[i] < af && rmr[i] > bb)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] > ae && bmr[i] < af && rmr[i] > bc)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (bmr[i] > ae && bmr[i] < af && rmr[i] > be && rmr[i] < bf)
			{
				cout << "Name: " << name[i] << endl;
				cout << "Staff ID: " << staff[i] << endl;
				cout << "BMR: " << bmr[i] << endl;
				cout << "RMR: " << rmr[i] << endl << endl;
			}
		}
	}

	system("PAUSE");
}

void StatiS(char gender[], int age[], double height[], double weight[], int n)  //calculate statistical distribution using age, gender, and weight category
{
	system("CLS");
	double bmi = 0;
	int cat, p = 0, a = 0, b = 0;
	char g;

	cout << "Choose category for weight." << endl;  //choose category
	cout << "1. Underweight\n2. Normal Weight\n3. Overweight\n4. Obese" << endl;
	cin >> cat;
	while (cat < 1 || cat >4)
	{
		cout << "Invalid choice.Choose again." << endl;
		cout << "Choose category for weight." << endl;
		cout << "1. Underweight\n2. Normal Weight\n3. Overweight\n4. Obese" << endl;
		cin >> cat;
	}

	cout << "Choose Gender: 'L' / 'P'" << endl;  //Choose gneder
	cin >> g;
	while (g != 'L' && g != 'P' && g != 'l' && g != 'p')
	{
		cout << "Invalid gender.Choose again." << endl;
		cout << "Choose Gender: 'L' / 'P'" << endl;
		cin >> g;
	}

	cout << "Enter range for the age: " << endl;   //Enter range for the age
	cin >> a;
	cin >> b;
	while (a < 0 || b < 0 || a>60 || b >60)
	{
		cout << "Invalid age range.Enter again." << endl;
		cout << "Enter range for the age: " << endl;
		cin >> a;
		cin >> b;
	}

	if (cat == 1)  //For Underweight
	{
		for (int i = 0; i < n; i++)
		{
			if (gender[i] = g && age[i] > a && age[i] < b)
			{
				bmi = weight[i] / pow(((height[i]) / 100), 2);
				if (bmi < 20)
				{
					p += 1;
				}
			}
		}
		cout << "Number of people BMI <20: " << p << endl;
	}
	else if (cat == 2)  //For Normal weight
	{
		for (int i = 0; i < n; i++)
		{
			if (gender[i] = g && age[i] > a && age[i] < b)
			{
				bmi = weight[i] / pow(((height[i]) / 100), 2);
				if (bmi >= 20 && bmi < 25)
				{
					p += 1;
				}
			}
		}
		cout << "Number of people 20<= BMI <25: " << p << endl;
	}
	else if (cat == 3)   //For Overweight
	{
		for (int i = 0; i < n; i++)
		{
			if (gender[i] = g && age[i] > a && age[i] < b)
			{
				bmi = weight[i] / pow(((height[i]) / 100), 2);
				if (bmi >= 25 && bmi < 30)
				{
					p += 1;
				}
			}
		}
		cout << "Number of people 25<= BMI <30: " << p << endl;
	}
	else if (cat == 4)   //For Obese
	{
		for (int i = 0; i < n; i++)
		{
			if (gender[i] = g && age[i] > a && age[i] < b)
			{
				bmi = weight[i] / pow(((height[i]) / 100), 2);
				if (bmi >= 30)
				{
					p += 1;
				}
			}
		}
		cout << "Number of people BMI >=30: " << p << endl;
	}
	system("PAUSE");
}

void myTarget(string staff[], double weight[], double height[], char gender[], int age[], int n)  //calculate the target weight
{
	system("CLS");
	string st;
	double bmr = 0, win = 0, remain = 0, newbmr = 0;
	int days;

	cout << "Enter StaffID: " << endl;   //ask for specific staff id
	cin >> st;
	for (int i = 0; i < n; i++)
	{
		if (st == staff[i])      //search or the specific staff id
		{
			if (gender[i] == 'L')
			{
				bmr = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] + 5;  //calculate bmr
				newbmr = 0.75 * bmr;   // calculate calories
			}
			else if (gender[i] == 'P')
			{
				bmr = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] - 161;  //calculate bmr
				newbmr = 0.75 * bmr;    // calculate calories
			}

			cout << "Enter your ideal weight: " << endl;  //ask for ideal weight
			cin >> win;
			while (win < 10)
			{
				cout << "Invalid weight.Enter again." << endl;
				cout << "Enter your ideal weight: " << endl;
				cin >> win;
			}

			if (weight[i] > win)  //if weight more than ideal weight
			{
				remain = weight[i] - win;  //difference of weight
				days = remain / (0.5 / 7);

				cout << "You need to consume " << newbmr << " in order to lose " << remain << "kg in " << days << " days." << endl << endl;
			}
			else if (weight[i] < win)  //if weight less than ideal weight
			{
				remain = win - weight[i];   //difference of weight
				days = remain / (0.5 / 7);

				cout << "You need to consume " << newbmr << " in order to gain " << remain << "kg in " << days << " days." << endl << endl;
			}
			break;
		}
	}
	system("PAUSE");
}

void bbr(double height[], double weight[], int age[], char gender[], int n, double bmi[], double bmr[], double rmr[])  //function to calculate all bmi,bmr,rmr of all data
{
	for (int i = 0; i < n; i++)
	{

		bmi[i] = weight[i] / pow(((height[i]) / 100), 2);  //calculate bmi for all  data and store in array

		if (gender[i] == 'L')
		{
			bmr[i] = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] + 5;    //calculate bmr for all male  data and store in array
			rmr[i] = 88.362 + (13.397 * weight[i]) + (4.799 * height[i]) - (5.677 * age[i]);    //calculate rmr for all male data and store in array
		}
		else if (gender[i] == 'P')
		{
			bmr[i] = 10 * weight[i] + 6.25 * height[i] - 5 * age[i] - 161;    //calculate bmr for all female  data and store in array
			rmr[i] = 447.593 + (9.247 * weight[i]) + (3.098 * height[i]) - (4.330 * age[i]);    //calculate rmr for all female data and store in array
		}
	}
}