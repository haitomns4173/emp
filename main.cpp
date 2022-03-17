#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <conio.h>
#include <direct.h>
#include <windows.h>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

// Deceleration of Global Variables
MYSQL* connection;
short int login_fail = 1;
int menu_select;
char retry_key;
char user_type[2] = "3";
int exit_status = 0;

// Use to set the Pointer
void setPointer(short int xpnt, short int ypnt)
{
	COORD position = { xpnt, ypnt };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// Use to print TopPart
void top_printing()
{
	system("CLS");
	setPointer(60, 12);
	cout << "EMPLOYEE MANAGEMENT SYSTEM" << endl;
}

// Use to open the program in FullScreen
void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0); //Press down Alt
	keybd_event(VK_RETURN, 0x1c, 0, 0); //Press down Enter

	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); //Release Alternate
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);//Release Enter
}

// Class for handling the Database
class Mysql
{
public:

    MYSQL_ROW row;
    MYSQL_RES* res;

    // Making the connection
    int mysql_connection()
    {
        connection = mysql_init(0);
        connection = mysql_real_connect(connection, "localhost", "root", "", "cpp_test", 3306 , NULL, 0);
        if (connection)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }

    }

    // Query Executor for Insertion
    int query_executor(const char* final_query)
    {
        int query_state = 0;
        query_state = mysql_query(connection, final_query);

        if(query_state == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // Query For select
    void query_select(const char* final_query)
    {
        if(connection)
        {
            int qstate = mysql_query(connection, final_query);
            if(!qstate)
            {
                res = mysql_store_result(connection);
            }
        }
    }
};

class Admin
{
    Mysql adminMain;

public:
    void admin_panel()
    {
	re_try_admin:

		top_printing();
		setPointer(60, 17);
		cout << "Admin Panel";
		setPointer(60, 19);
		cout << "1. Search Employee";
		setPointer(60, 21);
		cout << "2. Register Employee";
		setPointer(60, 23);
		cout << "3. Update Employee";
		setPointer(60, 25);
		cout << "4. Delete Employee";
		setPointer(60, 27);
		cout << "5. Employee Salary";
		setPointer(60, 29);
		cout << "6. View Salary";
		setPointer(60, 31);
		cout << "7. Work Assignment";
		setPointer(60, 33);
		cout << "8. Advance Salary";
        setPointer(60, 35);
		cout << "9. Username/Password Change";
        setPointer(60, 37);
		cout << "10. Notice";
		setPointer(92, 19);
		cout << "11. View Work";
		setPointer(92, 21);
		cout << "12. View Notice";
		setPointer(92, 23);
		cout << "13. Delete Notice";
		setPointer(92, 25);
		cout << "14. Logout";
		setPointer(60, 39);
		cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		switch (menu_select)
		{
		case 1:
		    employee_searching();
			break;
		case 2:
		    employee_registration();
			break;
		case 3:
		    employee_update();
			break;
		case 4:
		    employee_delete();
			break;
		case 5:
		    employee_salary();
			break;
		case 6:
		    view_salary();
			break;
        case 7:
            work_assignment();
			break;
        case 8:
            advance_salary();
			break;
        case 9:
            username_password_change();
			break;
        case 10:
            notice();
			break;
        case 11:
            view_work();
            break;
        case 12:
            view_notice();
            break;
        case 13:
            notice_delete();
            break;
        case 14:
            logout();
            break;
		default:
			setPointer(60, 42);
			cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  re_try_admin;
			}
		}
    }

    void employee_searching()
    {
        int search_id = 0, search_post = 0, rows_in_employee = 0, table_y = 22;
        string search_name;

        top_printing();
		setPointer(60, 17);
		cout << "Search Method";
		setPointer(60, 19);
		cout << "1. By Employee ID";
		setPointer(60, 21);
		cout << "2. By Name";
		setPointer(60, 23);
		cout << "3. By Post";
		setPointer(60, 26);
        cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		if(menu_select == 1)
        {
            setPointer(60, 29);
            cout << "Employee ID : ";
            fflush(stdin);
            cin >> search_id;


            stringstream query_holder;
            query_holder << "select * from employee where id = "<<search_id<<"";
            string temp_query = query_holder.str();
            const char* final_query = temp_query.c_str();

            adminMain.query_select(final_query);
            rows_in_employee = mysql_num_rows(adminMain.res);

            if(rows_in_employee==0)
            {
                setPointer(60, 32);
                cout << "No Record Found";
            }
            else
            {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(30, 20);
                cout << "ID" << setw(40) << "Name" << setw(20) << "Age" << setw(20) << "Post Code" << setw(20) << "Phone";
                setPointer(30, 21);
                cout << "------------------------------------------------------------------------------------------------------";
                while((adminMain.row = mysql_fetch_row(adminMain.res)))
                {
                    setPointer(30,table_y++);
                    cout <<adminMain.row[0]<< setw(40) <<adminMain.row[1]<< setw(20) <<adminMain.row[2]<< setw(20) <<adminMain.row[3] << setw(20) << adminMain.row[4];
                }
            }
        }
        else if (menu_select == 2)
        {
            setPointer(60, 29);
            cout << "Employee Name : ";
            fflush(stdin);
            getline(cin, search_name);

            stringstream query_holder;
            query_holder << "select * from employee where name = '"<<search_name<<"'";
            string temp_query = query_holder.str();
            const char* final_query = temp_query.c_str();

            adminMain.query_select(final_query);
            rows_in_employee = mysql_num_rows(adminMain.res);

            if(rows_in_employee == 0)
            {
                setPointer(60, 32);
                cout << "No Record Found";
            }
            else
            {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(30, 20);
                cout << "ID" << setw(40) << "Name" << setw(20) << "Age" << setw(20) << "Post Code" << setw(20) << "Phone";
                setPointer(30, 21);
                cout << "------------------------------------------------------------------------------------------------------";
                while((adminMain.row = mysql_fetch_row(adminMain.res)))
                {
                    setPointer(30,table_y++);
                    cout <<adminMain.row[0]<< setw(40) <<adminMain.row[1]<< setw(20) <<adminMain.row[2]<< setw(20) <<adminMain.row[3] << setw(20) << adminMain.row[4];
                }
            }
        }
        else
        {
            setPointer(60, 29);
            cout << "Employee Post : ";
            fflush(stdin);
            cin >> search_post;


            stringstream query_holder;
            query_holder << "select * from employee where post_code = "<<search_post<<"";
            string temp_query = query_holder.str();
            const char* final_query = temp_query.c_str();

            adminMain.query_select(final_query);
            rows_in_employee = mysql_num_rows(adminMain.res);

            if(rows_in_employee==0)
            {
                setPointer(60, 32);
                cout << "No Record Found";
            }
            else
            {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(30, 20);
                cout << "ID" << setw(40) << "Name" << setw(20) << "Age" << setw(20) << "Post Code" << setw(20) << "Phone";
                setPointer(30, 21);
                cout << "------------------------------------------------------------------------------------------------------";
                while((adminMain.row = mysql_fetch_row(adminMain.res)))
                {
                    setPointer(30,table_y++);
                    cout <<adminMain.row[0]<< setw(40) <<adminMain.row[1]<< setw(20) <<adminMain.row[2]<< setw(20) <<adminMain.row[3] << setw(20) << adminMain.row[4];
                }
            }
        }
    }

    void employee_registration()
    {
    retry_registeration:
        string emp_name, phone, username_in, password_in;
        int age = 0, post_code = 0, rows_in_userpass = 0, insert_result = 0, insert_result2 = 0;
        float emp_salary = 0, pf = 0;

        top_printing();
		setPointer(60, 17);
		cout << "Registration";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Employee Name :";
		setPointer(60, 24);
		cout << "Age           :";
		setPointer(60, 26);
		cout << "Post          :";
		setPointer(60, 28);
		cout << "Phone         :";

		setPointer(76, 22);
		fflush(stdin);
		getline(cin, emp_name);

		setPointer(76, 24);
		fflush(stdin);
		cin >> age;
		if(age<18 || age >88)
        {
            setPointer(60, 31);
            cout << "Wrong AGE!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_registeration;
			};
        }
		setPointer(76, 26);
		fflush(stdin);
		cin >> post_code;
		if(post_code != 1 && post_code != 2)
        {
            setPointer(60, 31);
            cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_registeration;
			}
        }
		setPointer(76, 28);
		fflush(stdin);
		getline(cin,phone);
		if(phone.size()<10)
        {
            setPointer(60, 31);
            cout << "Wrong Phone!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_registeration;
			}
        }
retry_credentials:
		setPointer(60, 31);
		cout << "Login Credentials :";

		setPointer(60, 33);
		cout << "USERNAME      : ";
		setPointer(60, 35);
		cout << "PASSWORD      : ";

		setPointer(76, 33);
		fflush(stdin);
        cin >> username_in;

        stringstream query_holder;
        query_holder << "select * from userpass where username = '"<<username_in<<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        adminMain.row = mysql_fetch_row(adminMain.res);
        rows_in_userpass = mysql_num_rows(adminMain.res);

        if(rows_in_userpass!=0)
        {
            setPointer(60, 37);
            cout << "Username is Already Taken! Retry";
            _getch();
            setPointer(86, 33);
            cout <<"\b\b\b\b\b\b\b\b\b\b          ";
            setPointer(92, 37);
            cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                                ";
            goto retry_credentials;
        }

        setPointer(76, 35);
        fflush(stdin);
        cin >> password_in;

        stringstream query_holder2;
        query_holder2 << "INSERT INTO `employee`(`id`, `name`, `age`, `post_code`, `phone`) VALUES (NULL,'"<<emp_name<<"', '"<<age<<"', '"<<post_code<<"', '"<<phone<<"')";
        string temp_query2 = query_holder2.str();
        const char* final_query2 = temp_query2.c_str();

        insert_result = adminMain.query_executor(final_query2);

        stringstream query_holder3;
        query_holder3 << "INSERT INTO `userpass` (`id`, `username`, `password`, `post_code`) VALUES (NULL,'"<<username_in<<"', '"<<password_in<<"','"<<post_code<<"')";
        string temp_query3 = query_holder3.str();
        const char* final_query3 = temp_query3.c_str();

        insert_result2 = adminMain.query_executor(final_query3);

        if(insert_result  == 1 && insert_result2  == 1)
        {
            setPointer(60, 38);
            cout << "Recorded!!";
            setPointer(60, 39);
            cout << "Hit Enter to continue....";
            _getch();

            stringstream query_holder4;
            query_holder4 << "SELECT * FROM `employee` WHERE `name` LIKE '"<<emp_name<<"'";
            string temp_query4 = query_holder4.str();
            const char* final_query4 = temp_query4.c_str();

            adminMain.query_select(final_query4);
            adminMain.row = mysql_fetch_row(adminMain.res);

            top_printing();
            setPointer(60, 17);
            cout << "Registration";
            setPointer(60, 19);
            cout << "Salary Input";
            setPointer(60, 21);
            cout << "Salary : ";
            fflush(stdin);
            cin >> emp_salary;

            pf = 0.1*emp_salary;

            stringstream query_holder5;
            query_holder5 << "INSERT INTO `salary`(`id`, `emp_id`, `pf`, `advance_salary`, `salary_deduction`, `rent`, `travel`, `salary`) VALUES ('NULL','"<<adminMain.row[0]<<"','"<<pf<<"','NULL','NULL','NULL','NULL','"<<emp_salary<<"')";
            string temp_query5 = query_holder5.str();
            const char* final_query5 = temp_query5.c_str();

            adminMain.query_executor(final_query5);

            setPointer(60, 24);
            cout << "Salary Recorded!!";
            setPointer(60, 26);
            cout << "Hit Enter to continue....";
            _getch();

            top_printing();
            setPointer(60, 17);
            cout << "Registration";
            setPointer(60, 19);
            cout << "Employee Details Successfully Inserted.";
            setPointer(60, 21);
            cout << "Employee ID : " << adminMain.row[0];
            setPointer(60, 24);
            cout << "Hit Enter to continue....";
            _getch();
        }
        else
        {
            setPointer(60, 37);
            cout << "Insert Failed!";
            _getch();
        }
    }

    void employee_update()
    {
        string emp_name, phone;
        int employee_id = 0, rows_in_employee, age = 0, post_code = 0, update_result = 0;

    retry_update:

        top_printing();
		setPointer(60, 17);
		cout << "Employee Update";
		setPointer(60, 20);
		cout << "Employee ID :";
		setPointer(74, 20);
		fflush(stdin);
		cin >> employee_id;

		stringstream query_holder;
        query_holder << "select * from employee where id = "<<employee_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        adminMain.row = mysql_fetch_row(adminMain.res);
        rows_in_employee = mysql_num_rows(adminMain.res);

        if(rows_in_employee==0)
        {
            setPointer(60, 32);
            cout << "No Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_update;
			}
        }
        else
        {
            setPointer(60, 32);
            cout << "Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to continue....";
            _getch();

            top_printing();
            setPointer(60, 17);
            cout << "Registration";
            setPointer(60, 18);
            cout << "Fill in the Details :";

            setPointer(60, 22);
            cout << "Employee Name :";
            setPointer(60, 24);
            cout << "Age           :";
            setPointer(60, 26);
            cout << "Post          :";
            setPointer(60, 28);
            cout << "Phone         :";

            setPointer(76, 22);
            fflush(stdin);
            getline(cin, emp_name);

            setPointer(76, 24);
            fflush(stdin);
            cin >> age;
            if(age<18 || age >88)
            {
                setPointer(60, 31);
                cout << "Wrong AGE!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                };
            }
            setPointer(76, 26);
            fflush(stdin);
            cin >> post_code;
            if(post_code != 1 && post_code != 2)
            {
                setPointer(60, 31);
                cout << "Wrong Input!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                }
            }
            setPointer(76, 28);
            fflush(stdin);
            getline(cin,phone);
            if(phone.size()<10)
            {
                setPointer(60, 31);
                cout << "Wrong Phone!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                }
            }

            stringstream query_holder2;
            query_holder2 << "UPDATE `employee` SET `name`='"<<emp_name<<"',`age`='"<<age<<"',`post_code`='"<<post_code<<"',`phone`='"<<phone<<"' WHERE id = "<<employee_id<<"";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            update_result = adminMain.query_executor(final_query2);

            if(update_result == 1)
            {
                setPointer(60, 38);
                cout << "Recorded Updated!!";
                setPointer(60, 39);
                cout << "Hit Enter to continue....";
                _getch();
            }
            else
            {
                setPointer(60, 37);
                cout << "Update Failed!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto retry_update;
                }
            }
        }
    }

    void employee_delete()
    {
        int employee_id = 0, delete_emp = 0, delete_emp2 = 0;
        top_printing();

		setPointer(60, 17);
		cout << "Employee Delete";
		setPointer(60, 20);
		cout << "Employee ID :";
		setPointer(74, 20);
		fflush(stdin);
		cin >> employee_id;

		stringstream query_holder;
        query_holder << "DELETE FROM `employee` WHERE id = "<<employee_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        delete_emp = adminMain.query_executor(final_query);

        stringstream query_holder2;
        query_holder2 << "DELETE FROM `userpass` WHERE id = "<<employee_id<<"";
        string temp_query2 = query_holder2.str();
        const char* final_query2 = temp_query2.c_str();

        delete_emp2 = adminMain.query_executor(final_query2);

        if(delete_emp == 1 && delete_emp2 == 1)
        {
            setPointer(60, 23);
            cout << "Deleted!!";
        }
        else
        {
            setPointer(60, 23);
            cout << "Deletation Failed!!";
        }
    }

    void work_assignment()
    {
        string work, employee_name;
        int employee_name_search = 0, work_assign_result = 0;

    retry_work_assignment:
        top_printing();

		setPointer(60, 17);
		cout << "Work Assignment";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Work Name     :";
		setPointer(60, 24);
		cout << "Employee Name :";
		setPointer(76, 22);
		fflush(stdin);
		getline(cin, work);
		setPointer(76, 24);
		fflush(stdin);
		getline(cin, employee_name);

		stringstream query_holder;
        query_holder << "SELECT * FROM `employee` WHERE `name` LIKE '"<<employee_name<<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        adminMain.row = mysql_fetch_row(adminMain.res);
        employee_name_search = mysql_num_rows(adminMain.res);

        if(employee_name_search == 0)
        {
            setPointer(60, 32);
            cout << "There is no Employee named " << employee_name;
            setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_work_assignment;
			}
        }
        else
        {
            stringstream query_holder2;
            query_holder2 << "INSERT INTO `work`(`id`, `work_name`, `work_by`, `work_to`) VALUES ('NULL','"<<work<<"','Admin','"<<employee_name<<"')";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            work_assign_result = adminMain.query_executor(final_query2);

            if(work_assign_result == 1)
            {
                setPointer(60, 32);
                cout << "Work Assisgned!!";
            }
            else
            {
                setPointer(60, 32);
                cout << "Work Not Assisgned!!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_work_assignment;
                }
            }
        }
    }

    void advance_salary()
    {
        float advance_salary_amount;
        string employee_name, temp_employee_id;
        int employee_name_search = 0, advance_salary_result = 0;

    retry_advance_salary:
        top_printing();

		setPointer(60, 17);
		cout << "Advance Salary";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Employee Name  :";
		setPointer(60, 24);
		cout << "Total Amount   :";
		setPointer(77, 22);
		fflush(stdin);
		getline(cin, employee_name);
		setPointer(77, 24);
		fflush(stdin);
		cin >> advance_salary_amount;

		stringstream query_holder;
        query_holder << "SELECT * FROM `employee` WHERE `name` = '"<<employee_name<<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        adminMain.row = mysql_fetch_row(adminMain.res);
        employee_name_search = mysql_num_rows(adminMain.res);

        temp_employee_id = adminMain.row[0];

        if(employee_name_search == 0)
        {
            setPointer(60, 32);
            cout << "There is no Employee named " << employee_name;
            setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_advance_salary;
			}
        }
        else
        {
            stringstream query_holder2;
            query_holder2 << "UPDATE `salary` SET `advance_salary`='"<< advance_salary_amount <<"' WHERE emp_id = "<< temp_employee_id <<"";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            advance_salary_result = adminMain.query_executor(final_query2);

            if(advance_salary_result == 1)
            {
                setPointer(60, 32);
                cout << "Advance Salary Recorded!!";
            }
            else
            {
                setPointer(60, 32);
                cout << "Advance Salary NOT Recorded!!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto retry_advance_salary;
                }
            }
        }
    }

    void notice()
    {
        string notice_title, notice_body, notice_by;
        int notice_result = 0;
    retry_notice:
        top_printing();

		setPointer(60, 17);
		cout << "Notice";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Notice Title  :";
		setPointer(60, 24);
		cout << "Notice Body   :";
		setPointer(60, 26);
		cout << "Notice BY     :";
		setPointer(76, 22);
		fflush(stdin);
		getline(cin, notice_title);
		setPointer(76, 24);
		fflush(stdin);
		getline(cin, notice_body);
		setPointer(76, 26);
		fflush(stdin);
		getline(cin, notice_by);

		stringstream query_holder;
        query_holder << "INSERT INTO `notice`(`id`, `notice_title`, `notice_body`, `notice_by`) VALUES ('NULL','"<<notice_title<<"','"<<notice_body<<"','"<<notice_by<<"')";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        notice_result = adminMain.query_executor(final_query);

        if(notice_result == 1)
        {
            setPointer(60, 32);
            cout << "Notice Posted!!";
        }
        else
        {
            setPointer(60, 32);
            cout << "Notice Post Failed!!";
            setPointer(60, 44);
            cout << "Hit Enter to re-enter and Esc to exit ....";
            retry_key = _getch();

            if (retry_key == 27)
            {
                exit(0);
            }
            else
            {
                goto  retry_notice;
            }
        }
    }

    void username_password_change()
    {
        int employee_id = 0, rows_in_employee = 0, update_result = 0;
        string username, password;

     retry_update:
        top_printing();
		setPointer(60, 17);
		cout << "Username/Password Update";
		setPointer(60, 20);
		cout << "Employee ID :";
		setPointer(74, 20);
		cin >> employee_id;

		stringstream query_holder;
        query_holder << "select * from employee where id = "<<employee_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        adminMain.row = mysql_fetch_row(adminMain.res);
        rows_in_employee = mysql_num_rows(adminMain.res);

        if(rows_in_employee==0)
        {
            setPointer(60, 32);
            cout << "No Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_update;
			}
        }
        else
        {
            setPointer(60, 32);
            cout << "Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to continue....";
            _getch();

            top_printing();
            setPointer(60, 17);
            cout << "LOGIN";
            setPointer(60, 20);
            cout << "Username : " << endl;
            setPointer(60, 22);
            cout << "Password : ";
            setPointer(71, 20);
            cin >> username;
            setPointer(71, 22);
            cin >> password;

            stringstream query_holder2;
            query_holder2 << "UPDATE `userpass` SET `username`='"<<username<<"',`password`='"<<password<<"' WHERE id = "<<employee_id<<"";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            update_result = adminMain.query_executor(final_query2);

            if(update_result == 1)
            {
                setPointer(60, 38);
                cout << "Recorded Updated!!";
                setPointer(60, 39);
                cout << "Hit Enter to continue....";
                _getch();
            }
            else
            {
                setPointer(60, 37);
                cout << "Update Failed!";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                }
            }
        }
    }

    void employee_salary()
    {
        string search_name, temp_employee_id;
        float salary_cut = 0, rent_allowance = 0, travel_allowance = 0;
        int employee_name_search = 0, salary_result = 0;

    retry_insert_salary:
        top_printing();
		setPointer(60, 17);
		cout << "Make Salary";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Employee Name    :";
		setPointer(60, 24);
		cout << "Salary Deduction :";
		setPointer(60, 26);
		cout << "Rent             :";
		setPointer(60, 28);
		cout << "Travel           :";
		setPointer(79, 22);
		getline(cin, search_name);

		stringstream query_holder;
        query_holder << "SELECT * FROM `employee` WHERE `name` = '"<< search_name <<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        adminMain.row = mysql_fetch_row(adminMain.res);
        employee_name_search = mysql_num_rows(adminMain.res);

        temp_employee_id = adminMain.row[0];

        if(employee_name_search == 0)
        {
            setPointer(60, 32);
            cout << "There is no Employee named " << search_name;
            setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_insert_salary;
			}
        }
        else
        {
            setPointer(79, 24);
            cin >> salary_cut;
            setPointer(79, 26);
            cin >> rent_allowance;
            setPointer(79, 28);
            cin >> travel_allowance;

            stringstream query_holder2;
            query_holder2 << "UPDATE `salary` SET `salary_deduction`='"<< salary_cut <<"',`rent`='"<< rent_allowance <<"',`travel`='"<< travel_allowance <<"' WHERE emp_id = "<< temp_employee_id <<"";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            salary_result = adminMain.query_executor(final_query2);

            if(salary_result == 1)
            {
                setPointer(60, 32);
                cout << "Salary Updated!!";
            }
            else
            {
                setPointer(60, 32);
                cout << "Salary NOT Updated!!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto retry_insert_salary;
                }
            }
        }
    }

    void view_salary()
    {
        int search_id = 0, rows_in_salary = 0, table_y = 22;
        float total_salary, temp_salary[7];

        top_printing();
		setPointer(60, 17);
		cout << "View Salary";
        setPointer(60, 19);
        cout << "Employee ID : ";
        fflush(stdin);
        cin >> search_id;

        stringstream query_holder;
        query_holder << "select * from salary where emp_id = "<<search_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        rows_in_salary = mysql_num_rows(adminMain.res);

        if(rows_in_salary == 0)
        {
            setPointer(60, 32);
            cout << "No Record Found";
        }
        else
        {
            top_printing();
            setPointer(60, 17);
            cout << "Query Result";
            setPointer(25, 20);
            cout << "ID" << setw(30) << "PF" << setw(15) << "AS" << setw(15) << "SD" << setw(15) << "Rent" << setw(15) << "Travel" << setw(15) << "Salary" << setw(15) <<"Total";
            setPointer(25, 21);
                cout << "--------------------------------------------------------------------------------------------------------------------------";
            while((adminMain.row = mysql_fetch_row(adminMain.res)))
            {
                for (int salary_covn = 2; salary_covn <= 7; salary_covn++)
                {
                    temp_salary[salary_covn] = stof(adminMain.row[salary_covn]);
                }
                total_salary = (temp_salary[5] + temp_salary[6] + temp_salary[7]) - (temp_salary[2] + temp_salary[3] + temp_salary[4]);
                setPointer(25,table_y++);
                cout <<adminMain.row[1]<< setw(30) <<adminMain.row[2]<< setw(15) <<adminMain.row[3]<< setw(15) <<adminMain.row[4] << setw(15) << adminMain.row[5] << setw(15) << adminMain.row[6] << setw(15) << adminMain.row[7] << setw(15) << total_salary;
            }
        }
    }

    void view_work()
    {
        int rows_in_view_work  = 0, table_y = 22;

        top_printing();
		setPointer(60, 17);
		cout << "View Work";

		stringstream query_holder;
        query_holder << "SELECT * FROM `work`";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        rows_in_view_work = mysql_num_rows(adminMain.res);

        if(rows_in_view_work == 0)
        {
            setPointer(60, 32);
            cout << "You Have no work right now, Get Relaxed!";
            setPointer(60, 33);
            cout << "Hit Esc to exit....";
			retry_key = _getch();
            exit(0);
        }
        else
        {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(35, 20);
                cout << "ID" << setw(40) <<"Work Name"<< setw(40) <<"Work BY"<< setw(20) <<"Work TO";
                setPointer(35, 21);
                cout << "------------------------------------------------------------------------------------------------------";
                while((adminMain.row = mysql_fetch_row(adminMain.res)))
                {
                    setPointer(35,table_y++);
                    cout <<adminMain.row[0]<< setw(40) <<adminMain.row[1]<< setw(40) <<adminMain.row[2]<< setw(20) <<adminMain.row[3];
                }
        }
    }

    void view_notice()
    {
        int rows_in_notice  = 0, table_y = 22;

        top_printing();
		setPointer(60, 17);
		cout << "View Notice";

		stringstream query_holder;
        query_holder << "SELECT * FROM `notice`";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        adminMain.query_select(final_query);
        rows_in_notice = mysql_num_rows(adminMain.res);

        if(rows_in_notice == 0)
        {
            setPointer(60, 32);
            cout << "Nothing to worry, No notice!!";
            setPointer(60, 33);
            cout << "Hit Esc to exit....";
			retry_key = _getch();
            exit(0);
        }
        else
        {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(15, 20);
                cout << "ID" << setw(20) << "Notice Title" << setw(80) << "Notice Body" << setw(30) << "Notice By";
                setPointer(15, 21);
                cout << "------------------------------------------------------------------------------------------------------------------------------------";
                while((adminMain.row = mysql_fetch_row(adminMain.res)))
                {
                    setPointer(15,table_y++);
                    cout <<adminMain.row[0]<< setw(20) <<adminMain.row[1]<< setw(80) <<adminMain.row[2]<< setw(30) <<adminMain.row[3];
                }
        }
    }

    void notice_delete()
    {
        int notice_id = 0, delete_notice = 0;
        top_printing();

		setPointer(60, 17);
		cout << "Notice Delete";
		setPointer(60, 20);
		cout << "Notice ID :";
		setPointer(74, 20);
		fflush(stdin);
		cin >> notice_id;

		stringstream query_holder;
        query_holder << "DELETE FROM `notice` WHERE id = "<<notice_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        delete_notice = adminMain.query_executor(final_query);
        delete_notice = adminMain.query_executor(final_query);

        if(delete_notice == 1 )
        {
            setPointer(60, 23);
            cout << "Deleted!!";
        }
        else
        {
            setPointer(60, 23);
            cout << "Deletation Failed!!";
        }
    }

    void logout()
    {
        exit_status = 1;
    }
};

class Manager: public Admin
{
public:
    void manager_panel()
    {
	re_try_manager:

		top_printing();
		setPointer(60, 17);
		cout << "Manager Panel";
		setPointer(60, 19);
		cout << "1. Search Employee";
		setPointer(60, 21);
		cout << "2. Register Employee";
		setPointer(60, 23);
		cout << "3. Update Employee";
		setPointer(60, 25);
		cout << "4. Delete Employee";
		setPointer(60, 27);
		cout << "5. Employee Salary";
		setPointer(60, 29);
		cout << "6. View Salary";
		setPointer(60, 31);
		cout << "7. Work Assignment";
		setPointer(60, 33);
		cout << "8. Advance Salary";
        setPointer(60, 35);
		cout << "9. Notice";
		setPointer(60, 37);
		cout << "10. Logout";
		setPointer(60, 41);
		cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		switch (menu_select)
		{
		case 1:
		    employee_searching();
			break;
		case 2:
		    employee_registration();
			break;
		case 3:
		    employee_update();
			break;
		case 4:
		    employee_delete();
			break;
		case 5:
		    employee_salary();
			break;
		case 6:
		    view_salary();
			break;
        case 7:
            work_assignment();
			break;
        case 8:
            advance_salary();
			break;
        case 9:
            notice();
			break;
        case 10:
            logout();
            break;
		default:
			setPointer(60, 42);
			cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  re_try_manager;
			}
		}
    }
};

class Employee: public Admin
{
public:
    void employee_panel()
    {
	re_try_manager:

		top_printing();
		setPointer(60, 17);
		cout << "Employee Panel";
		setPointer(60, 19);
		cout << "1. Update Employee";
		setPointer(60, 21);
		cout << "2. View Salary";
		setPointer(60, 23);
		cout << "3. View Work";
		setPointer(60, 25);
		cout << "4. Advance Salary";
		setPointer(60, 27);
		cout << "5. Notice";
		setPointer(60, 29);
		cout << "6. Logout";
		setPointer(60, 41);
		cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		switch (menu_select)
		{
		case 1:
		    employee_update();
			break;
		case 2:
		    view_salary();
			break;
		case 3:
		    view_work();
			break;
		case 4:
		    advance_salary();
			break;
		case 5:
		    view_notice();
			break;
        case 6:
            logout();
            break;
		default:
			setPointer(60, 42);
			cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  re_try_manager;
			}
		}
    }
};

class Login
{
	char username[20], password[10];
	char admin_username[20] = "admin";
	char admin_password[10] = "123";

	Mysql loginValidate;

public:
	void login_input()
	{
	re_try_login:

        int login_check;

		top_printing();

		setPointer(60, 17);
		cout << "LOGIN";
		setPointer(60, 20);
		cout << "Username : " << endl;
		setPointer(60, 22);
		cout << "Password : ";
		setPointer(71, 20);
		cin >> username;
		setPointer(71, 22);
		cin >> password;

        stringstream query_holder;
        query_holder << "SELECT * FROM `userpass` WHERE `username` = '"<< username <<"' AND `password` = '"<< password <<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        loginValidate.query_select(final_query);
        loginValidate.row = mysql_fetch_row(loginValidate.res);
        login_check = mysql_num_rows(loginValidate.res);

		// Check if the user is valid or not
		if (strcmp(admin_username, username) == 0 && strcmp(admin_password, password) == 0)
		{
		    strcpy(user_type, "0");
			setPointer(60, 25);
			cout << "Success!";
			setPointer(60, 28);
			cout << "Proceeding to the panel ......";
			Sleep(1500);
			Admin adminMain;
			adminMain.admin_panel();
		}
		else if (login_check == 1)
		{
			setPointer(60, 25);
			cout << "Success!";
			setPointer(60, 28);
			cout << "Proceeding to the panel ......";
			Sleep(1500);

			if(strcmp("1", loginValidate.row[3]) == 0)
            {
                strcpy(user_type, loginValidate.row[3]);
                Manager managerMain;
                managerMain.manager_panel();
            }
            else
            {
                strcpy(user_type, loginValidate.row[3]);
                Employee employeeMain;
                employeeMain.employee_panel();
            }
		}
		else
		{
			setPointer(60, 25);
			cout << "Fail!";
			if (login_fail <= 10)
			{
				setPointer(60, 28);
				cout << "Hit Esc to exit and Enter to retry ....";
				retry_key = _getch();
				if (retry_key == 27)
				{
					exit(0);
				}
				else
				{
					login_fail++;
					goto re_try_login;
				}
			}
			else
			{
				setPointer(60, 28);
				cout << "You are not a valid user !!!";
				system("PAUSE");
				exit(0);
			}
		}
	}
};

int main()
{
    Mysql connect;
    Admin redirectAdmin;
    Manager redirectManager;
    Employee redirectEmployee;

    fullscreen();
    system("COLOR 0");
    top_printing();

    setPointer(60, 20);
	cout << "WELCOME TO THE PROGRAM";
	setPointer(60, 21);
	cout << "Coded by : ......";

	// Checks if the connection between the database and the program
    if(connect.mysql_connection())
    {
        setPointer(60, 30);
        cout << "Connected to Database!!";
        Sleep(2000);
    }
    else
    {
        setPointer(60, 30);
        cout << "Not Connected to Database!!";
        setPointer(60, 31);
        cout << "Exiting..";
        Sleep(6000);
        exit(0);
    }

    // Now the login page is executed
    Login mainLogin;
    mainLogin.login_input();

    while(exit_status == 0)
    {
        setPointer(60, 45);
        cout << "Hit Esc to exit and Enter to continue to Panel....";
        retry_key = _getch();
        if (retry_key == 27)
        {
            exit(0);
        }

        if(strcmp(user_type, "0") == 0)
        {
            redirectAdmin.admin_panel();
        }
        else if(strcmp(user_type, "1") == 0)
        {
            redirectManager.manager_panel();
        }
        else
        {
            redirectEmployee.employee_panel();
        }
    }

    top_printing();
    setPointer(60, 17);
    cout << "You have Successfully Logged out!";
    setPointer(60, 19);
    cout << "Thanks for using the Program.";
    setPointer(60, 25);
    cout << "Exiting.....";
    Sleep(1500);

    mysql_close(connection);
    return 0;
}
