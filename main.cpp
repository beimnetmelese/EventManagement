#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
using namespace std;

struct user{
	char UserID[5];
	char FirstName[255];
	char LastName[255];
	char Username[255];
	char Email[255];
	char Sex[1];
	string Password;
};

struct event {
	char EventID[5];
	string Title;
	string Descriptions;
	string Location;
	char Date[11];
	char time[10];
	string OrganizerID;
};

struct registered {
	char RegistrationID[255];
	string UserID;
	char EventID[5]; 
};

int main() {
	char EventID[5];
	char UserID[255];
	registered registered;
	user user;
	event event;
	MYSQL* obj;
	int choice, choice2, choice3;
	int answer;
	char* consult;
	char* sentence;
	string sentence_aux;
	string Username, Password;
	landingpage:
	cout << "********************************************************************" << endl;
	cout << "Welcome to our Event Management System" << endl;
	cout << endl;
	cout << "1.Create An Account" << endl;
	cout << "2.Log In" << endl;
	cout << "3.Quit" << endl;
	cout << "Enter Your Answer: ";
	cin >> choice;
	
	if (!(obj = mysql_init(0)))
	{
		cout << "can't add data to the database";
	}
	else {
		if(!mysql_real_connect(obj,"localhost","root", "aguero16", "EventManagement", 3306, NULL, 0)) {
			cout << "some databse info is not correct";
			cout << mysql_error(obj) << endl;
		}
		else {
			if(choice == 1) {
			registration:
			cout << endl << "************************************************************************" << endl;
			cout << "Welcome to the Registration Page" << endl;
			cout << endl;
			userregistration:
			cout << "Enter your ID: ";
			cin >> user.UserID;
			cout << "Enter your First Name: ";
			cin >> user.FirstName;
			cout << "Enter your Last Name: ";
			cin >> user.LastName;
			cout << "Enter your Username: ";
			cin >> user.Username;
			cout << "Enter your Email: ";
			cin >> user.Email;
			cout << "Enter your Password: ";
			cin >> user.Password;
			cout << "Enter your Sex(M/F): ";
			cin >> user.Sex;
			sentence_aux = "INSERT INTO User (UserID,FirstName,LastName,Username,Email,Password, Sex) values ('%s', '%s', '%s', '%s', '%s', '%s','%s')";
			sentence = new char[sentence_aux.length() + 1];
			strcpy(sentence, sentence_aux.c_str());
			consult = new char[strlen(sentence) + strlen(user.UserID) + strlen(user.FirstName) + strlen(user.LastName) + strlen(user.Username) + strlen(user.Email) + user.Password.length() +  strlen(user.Sex) + 1];
			sprintf(consult, sentence, user.UserID, user.FirstName, user.LastName, user.Username, user.Email, user.Password.c_str() ,user.Sex);
			
			if(mysql_ping(obj)) {
				cout << "Impossible to connect" << endl;
				cout << mysql_error(obj) << endl;
				cout << endl;
				goto userregistration;
			}
			
			if (mysql_query(obj, consult)){
				cout << "Error: " << mysql_error(obj) << endl;
				rewind(stdin);
				getchar();
				cout << endl;
				goto userregistration;
			}
			else {
				cout << "You have registered succesfully!!" << endl;
			}
			mysql_store_result(obj);
			goto label;
		}
		
		else if (choice == 2) {
			label:
			cout << endl;
			cout << "*******************************************************************************" << endl;
			cout << "Welcome to the LogIn Page" << endl;
			cout << endl;
			login:
			cout << "Enter your username: ";
            cin >> Username;
            cout << "Enter your password: ";
            cin >> Password;

            sentence_aux = "SELECT * FROM User WHERE Username='%s' AND Password='%s'";
            sentence = new char[sentence_aux.length() + 1];
            strcpy(sentence, sentence_aux.c_str());
            consult = new char[strlen(sentence) + Username.length() + Password.length()];
            sprintf(consult, sentence, Username.c_str(), Password.c_str());

            if (mysql_ping(obj)) {
                cout << "Impossible to connect" << endl;
                cout << mysql_error(obj) << endl;
                cout << endl;
				goto login;
                }

            if (mysql_query(obj, consult)) {
                cout << "Error: " << mysql_error(obj) << endl;
                rewind(stdin);
                getchar();
                cout << endl;
				goto login;
            } else {
                MYSQL_RES* result = mysql_store_result(obj);
                if (mysql_num_rows(result) == 1) {
                    cout << "Login Successfully!" << endl;
                    cout << endl << "*********************************************************************************" << endl;
                    home:
                    cout << "Welcome To The Home Page" << endl;
                    cout << endl;
                    cout << "1.Create Event" << endl;
                    cout << "2.See Events" << endl;
                    cout << "3.See Your Own Events" << endl;
                    cout << "4.Event You Registered" << endl;
                    cout << "5.Account Info" << endl;
                    cout << "6.Quit" << endl;
                    cout << "Enter Your answer: ";
                    cin >> answer;
                    cout << endl;
                    if (answer == 1) {
                    	cout << "*******************************************************************************************" << endl;
                    	cout << "Welcome to the Event Create Page" << endl;
                    	cout << endl;
                    	event:
                    	cout << "Enter the event ID: ";
                    	cin >> event.EventID;
                    	cout << "Enter the Title: ";
                    	cin >> event.Title;
                    	cout << "Enter the Descriptions: ";
                    	cin >> event.Descriptions;
                    	cout << "Enter the Date: ";
                    	cin >> event.Date;
                    	cout << "Enter the Location: ";
                    	cin >> event.Location;
                    	cout << "Enter the Time: ";
                    	cin >> event.time;
                    	event.OrganizerID = Username;
                    	sentence_aux = "INSERT INTO Event (EventID,Title,Descriptions,Date,Location,Time,OrganizerID) values ('%s', '%s', '%s', '%s', '%s', '%s', '%s')";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(event.EventID) + strlen(event.Title.c_str()) + strlen(event.Descriptions.c_str()) + strlen(event.Date) + strlen(event.Location.c_str()) + strlen(event.time) + strlen(event.OrganizerID.c_str()) + 1];
						sprintf(consult, sentence, event.EventID, event.Title.c_str(), event.Descriptions.c_str(), event.Date ,event.Location.c_str(), event.time, event.OrganizerID.c_str());
						if(mysql_ping(obj)) {
						cout << "Impossible to connect" << endl;
						cout << mysql_error(obj) << endl;
						cout << endl;
				        goto event;
						}
						if (mysql_query(obj, consult)){
						cout << "Error: " << mysql_error(obj) << endl;
						rewind(stdin);
						getchar();
						cout << endl;
				        goto event;
						}
						else {
						cout << "Event succesfully Created !!" << endl;
						}
						mysql_store_result(obj);
						cout << endl;
						cout << "What do you want to do" << endl;
						cout << "1. Create Another Event" << endl;
						cout << "2. Go back to Home" << endl;
						cout << "3. Quit" << endl;
						cin >> choice;
						if (choice == 1) {
						cout << endl;
						goto event;}
						else if(choice == 2) {
							cout << endl;
							goto home;
						}
					}
					else if( answer == 2) {
						cout << "*************************************************************************************************" << endl;
						cout << "Welcome to The event display and event registration page" << endl;
						cout << endl;
						eventdisplay:
						MYSQL_RES* result2;
						MYSQL_ROW row;
						if (mysql_query(obj, "SELECT * FROM Event")) {
						cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						mysql_close(obj);
						cout << endl;
				        goto landingpage;
						}
						result2 = mysql_store_result(obj);
						if (!result2) {
						cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						mysql_close(obj);
						cout << endl;
				        goto landingpage;
						}
						if (mysql_num_rows(result2) == 0) {
							cout << "There is no events" << endl;
							cout << endl;
							goto home;
						}
						cout << "EventID"<<"\t" << "Title" <<"\t"<< "        Descriptions" << "\t" << "Location       " << "Date" << "       Time" << "\t" << "      OrganizerID" << endl;
						while ((row = mysql_fetch_row(result2))) {
						for (int i = 0; i < mysql_num_fields(result2); i++) {
						cout << row[i] << "\t";
						}
						cout << endl;
					}
					    mysql_free_result(result2);
					    cout << endl;
					    registersearch:
						cout << "What do you Want to Do" << endl;
						cout << "1.Register to event" << endl;
						cout << "2.Search Event" << endl;
						cout << "3.quit" << endl;
						cout << "Enter Your Answer: ";
						cin >> choice2;
						cout << endl;
						if (choice2 == 1) {
						eventregister:
						cout << "Enter Registration ID: ";
						cin >> registered.RegistrationID;
						cout << "Enter The EventID You want to register: ";
						cin >> registered.EventID;
						registered.UserID = Username;
						sentence_aux = "INSERT INTO Registration (RegistrationID,EventID,UserID) values ('%s', '%s', '%s')";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(registered.RegistrationID) + strlen(registered.EventID) + strlen(registered.UserID.c_str()) + 1];
						sprintf(consult, sentence, registered.RegistrationID, registered.EventID, registered.UserID.c_str());
						if(mysql_ping(obj)) {
						cout << "Impossible to connect" << endl;
						cout << mysql_error(obj) << endl;
						cout << endl;
				        goto eventregister;
						}
						if (mysql_query(obj, consult)){
						cout << "Error: " << mysql_error(obj) << endl;
						rewind(stdin);
						getchar();
						cout << endl;
				        goto eventregister;
						}
						else {
						cout << "You have succesfully Registered To the Event!!" << endl;
						}
						mysql_store_result(obj);	
						}
						else if (choice2 == 2) {
							MYSQL_RES* result3;
						    MYSQL_ROW row;
						    cout << endl;
						    cout << "**************************************************************************************************" << endl;
                            cout << "Welcome to the Event Search Page" << endl;
                            cout << endl;
                            search:
					    	cout << "Enter the Event Title You want to search: ";
					    	cin >> event.Title;
						    sentence_aux = "SELECT * FROM Event WHERE Title = '%s'";
			                sentence = new char[sentence_aux.length() + 1];
						    strcpy(sentence, sentence_aux.c_str());
						    consult = new char[strlen(sentence) + strlen(event.Title.c_str()) + 1];
						    sprintf(consult, sentence, event.Title.c_str());
						    if (mysql_query(obj, consult)) {
						    cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    result3 = mysql_store_result(obj);
						    if (!result) {
						    cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    if (mysql_num_rows(result3) == 0) {
							cout << "No event by that title" << endl;
							cout << endl;
							goto registersearch;
						}
						    cout << "EventID"<<"\t" << "Title" <<"\t"<< "        Descriptions" << "\t" << "Location       " << "Date" << "       Time" << "\t" << "      OrganizerID" << endl;
						    while ((row = mysql_fetch_row(result3))) {
						    for (int i = 0; i < mysql_num_fields(result3); i++) {
						    cout << row[i] << "\t" << "\t";
						    }
						    cout << endl;
						}
						cout << "Do you want to search again" << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if(choice == 1) {
							cout << endl;
							goto search;
						}
						}
						
						cout << endl;
						cout << "What do you want to do" << endl;
						cout << "1. See events again" << endl;
						cout << "2. Go back to Home" << endl;
						cout << "3. Quit" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						cout << endl;
						goto eventdisplay;}
						else if(choice == 2) {
							cout << endl;
							goto home;
						}
						}
						
						else if (answer == 3) {
						MYSQL_RES* result2;
						MYSQL_ROW row;
						cout << "***************************************************************************" << endl;
						cout << "Welcome to your Events Page" << endl;
						cout << endl;
						yourevent:
						sentence_aux = "SELECT * FROM EVENT WHERE OrganizerID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence, Username.c_str());
						if (mysql_query(obj, consult)) {
						cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						mysql_close(obj);
						cout << endl;
				        goto landingpage;
						}
						result2 = mysql_store_result(obj);
						if (!result) {
						cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						mysql_close(obj);
						cout << endl;
				        goto landingpage;
						}
						if (mysql_num_rows(result2) == 0) {
							cout << "You don have any events" << endl;
							cout << endl;
							goto home;
						}
						cout << "EventID"<<"\t" << "Title" <<"\t"<< "        Descriptions" << "\t" << "Location       " << "Date" << "       Time" << "\t" << "      OrganizerID" << endl;
						while ((row = mysql_fetch_row(result2))) {
						for (int i = 0; i < mysql_num_fields(result2); i++) {
						cout << row[i] << "\t";
						}
						cout << endl;
					}
					    mysql_free_result(result2);
					    cout << endl;
					    eventchoice:
					    cout << "What Do you want to do" << endl;
					    cout << "1. Registered User" << endl;
					    cout << "2. Edit Event" << endl;
					    cout << "3. Delete Event" << endl;
					    cout << "4. Quit" << endl;
					    cout << "Enter Your Choice: ";
					    cin >> choice3;
					    if (choice3 == 1) {
					    	MYSQL_RES* result3;
						    MYSQL_ROW row;
						    cout << endl;
						    cout << "**************************************************************************************************" << endl;
                            cout << "Welcome to the User registered Page" << endl;
                            cout << endl;
					    	cout << "Enter the EventID You want to see who registered: ";
					    	cin >> EventID;
						    sentence_aux = "SELECT RegistrationID, UserID, RegisteredDate FROM Registration WHERE EventID = '%s'";
			                sentence = new char[sentence_aux.length() + 1];
						    strcpy(sentence, sentence_aux.c_str());
						    consult = new char[strlen(sentence) + strlen(EventID) + 1];
						    sprintf(consult, sentence, EventID);
						    if (mysql_query(obj, consult)) {
						    cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    result3 = mysql_store_result(obj);
						    if (!result) {
						    cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    if (mysql_num_rows(result3) == 0) {
							cout << "No one registered to this Event" << endl;
							cout << endl;
							goto eventchoice;
						}
						    cout << "RegistrationID"<<"\t" << "UserID" << "\t" <<"\t" <<"RegisteredDate"<< endl;
						    while ((row = mysql_fetch_row(result3))) {
						    for (int i = 0; i < mysql_num_fields(result3); i++) {
						    cout << row[i] << "\t" << "\t";
						    }
						    cout << endl;
						}
						cout << endl;
						usersearchchoice:
						cout << "What do you want to do" << endl;
						cout << "1. Ban User" << endl;
						cout << "2. Search User" << endl;
						cout << "3. Quit" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						cout << endl;
						cout << "***************************************************************************************" << endl;
                        cout << "Welcome to the User ban Page" << endl;
                        cout << endl;
                        ban:
                        cout << "Enter the User ID you want to delete: ";
                        cin >> UserID;
                        sentence_aux = "DELETE FROM Registration WHERE UserID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(UserID) + 1];
						sprintf(consult, sentence, UserID);
                        if (mysql_query(obj, consult)){
                            cout << "Error banning user: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto ban;
                        } else {
                            cout << "User banned successfully!" << endl;
                        }
                        cout << endl;
                        cout << "Do you want ban another user" << endl;
                        cout << "1.Yes" << endl;
                        cout << "2.No" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 1) {
                        	goto ban;
						}	
						}
						else if (choice == 2) {
							MYSQL_RES* result3;
						    MYSQL_ROW row;
						    cout << endl;
						    cout << "**************************************************************************************************" << endl;
                            cout << "Welcome to the registered User Search Page" << endl;
                            cout << endl;
                            usersearch:
					    	cout << "Enter the UserID You want to search: ";
					    	cin >> user.Username;
						    sentence_aux = "SELECT RegistrationID, UserID, RegisteredDate FROM Registration WHERE UserID = '%s' AND EventID = '%s'";
			                sentence = new char[sentence_aux.length() + 1];
						    strcpy(sentence, sentence_aux.c_str());
						    consult = new char[strlen(sentence) + strlen(user.Username) + strlen(EventID) + 1];
						    sprintf(consult, sentence, user.Username, EventID);
						    if (mysql_query(obj, consult)) {
						    cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    result3 = mysql_store_result(obj);
						    if (!result) {
						    cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    if (mysql_num_rows(result3) == 0) {
						    cout << endl; 
							cout << "This user didn't register for this event'" << endl;
							cout << endl;
							goto usersearchchoice;
						}
						    cout << "RegistrationID"<<"\t" << "UserID" << "\t" <<"\t" <<"RegisteredDate"<< endl;
						    while ((row = mysql_fetch_row(result3))) {
						    for (int i = 0; i < mysql_num_fields(result3); i++) {
						    cout << row[i] << "\t" << "\t";
						    }
						    cout << endl;
						}
						cout << "Do you want to search again" << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if(choice == 1) {
							cout << endl;
							goto usersearch;
						}
						}
						mysql_free_result(result3);		
						}
					else if (choice3 == 2) {
						cout << "*************************************************************************************" << endl;
						cout << "Welcome to you Edit Event Page" << endl;
						cout << endl;
						cout << "Enter the EventID you want to edit: ";
						cin >> EventID;
						cout << "Which Event info you want to edit" << endl;
						cout << "1. Title" << endl;
						cout << "2. Descriptions" << endl;
						cout << "3. Location" << endl;
						cout << "4. Date" << endl;
						cout << "5. Time" << endl;
						cout << "6. quit" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						title:
						cout << "Enter your New Title: ";
						cin >> event.Title;
						sentence_aux = "UPDATE Event SET Title = '%s' WHERE EventID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(event.Title.c_str()) + strlen(EventID) + 1];
						sprintf(consult, sentence,event.Title.c_str(), EventID);
                        if (mysql_query(obj, consult)){
                            cout << "Error Editing The title: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto title;
                        } else {
                            cout << "Edited successfully!" << endl;
                    }
                        cout << endl;
						goto eventchoice;
						}
						else if (choice == 2) {
						descriptions:
						cout << "Enter your New descriptions: ";
						cin >> event.Descriptions;
						sentence_aux = "UPDATE Event SET  Descriptions = '%s' WHERE EventID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(event.Descriptions.c_str()) + strlen(EventID) + 1];
						sprintf(consult, sentence,event.Descriptions.c_str(), EventID);
                        if (mysql_query(obj, consult)){
                            cout << "Error editing the descriptions: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto descriptions;
                        } else {
                            cout << "edited successfully!" << endl;
                        }
                        cout << endl;
						goto eventchoice;
						}
						else if (choice == 3) {
						location:
						cout << "Enter your New Locations: ";
						cin >> event.Location;
						sentence_aux = "UPDATE Event SET  Location = '%s' WHERE EventID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(event.Location.c_str()) + strlen(EventID) + 1];
						sprintf(consult, sentence,event.Location.c_str(), EventID);
                        if (mysql_query(obj, consult)){
                            cout << "Error editing the Location: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto location;
                        } else {
                            cout << "edited successfully!" << endl;
                        }
                        cout << endl;
						goto eventchoice;
						}
						else if (choice == 4) {
						date:
						cout << "Enter your New Date: ";
						cin >> event.Date;
						sentence_aux = "UPDATE Event SET  Date = '%s' WHERE EventID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(event.Date) + strlen(EventID) + 1];
						sprintf(consult, sentence,event.Date, EventID);
                        if (mysql_query(obj, consult)){
                            cout << "Error editing the date: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto date;
                        } else {
                            cout << "edited successfully!" << endl;
                        }
                        cout << endl;
						goto eventchoice;
						}
						else if (choice == 5) {
						time:
						cout << "Enter your New Time: ";
						cin >> event.time;
						sentence_aux = "UPDATE Event SET  Time = '%s' WHERE EventID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(event.time) + strlen(EventID) + 1];
						sprintf(consult, sentence,event.time, EventID);
                        if (mysql_query(obj, consult)){
                            cout << "Error editing the time: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto time;
                        } else {
                            cout << "edited successfully!" << endl;
                        }
                        cout << endl;
						goto eventchoice;
						}
						else {
							cout << endl;
							goto eventchoice;
						}
					}
					else if (choice3 == 3) {
						cout << endl;
						cout << "****************************************************************************************************************************" << endl;
                        cout << "Welcome to the Delete Event Page" << endl;
                        cout << endl;
                        delete_event:
                        cout << "Enter the Event ID you want to delete: ";
                        cin >> EventID;
                        sentence_aux = "DELETE FROM Event WHERE EventID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(EventID) + 1];
						sprintf(consult, sentence, EventID);
                        if (mysql_query(obj, consult)){
                            cout << "Error deleting event: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto delete_event;
                        } else {
                            cout << "Event deleted successfully!" << endl;
                        }
                        cout << endl;
                        cout << "Do you want delete another event" << endl;
                        cout << "1.Yes" << endl;
                        cout << "2.No" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 1) {
                        	goto delete_event;
						}
				}	
						cout << endl;
						cout << "What do you want to do" << endl;
						cout << "1. See your Events" << endl;
						cout << "2. Go back to Home" << endl;
						cout << "3. Quit" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						cout << endl;
						goto yourevent;}
						if(choice == 2) {
							cout << endl;
							goto home;
						}
					}
					else if(answer == 4) {
						    MYSQL_RES* result3;
						    MYSQL_ROW row;
						    cout << endl;
						    cout << "**************************************************************************************************" << endl;
                            cout << "Welcome to events you are registered page" << endl;
                            cout << endl;
                            registered:
						    sentence_aux = "SELECT RegistrationID, EventID, RegisteredDate FROM Registration WHERE UserID = '%s'";
			                sentence = new char[sentence_aux.length() + 1];
						    strcpy(sentence, sentence_aux.c_str());
						    consult = new char[strlen(sentence) + strlen(Username.c_str()) + 1];
						    sprintf(consult, sentence, Username.c_str());
						    if (mysql_query(obj, consult)) {
						    cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    result3 = mysql_store_result(obj);
						    if (!result) {
						    cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    if (mysql_num_rows(result3) == 0) {
							cout << "You didn't register to any event" << endl;
							cout << endl;
							goto home;
						}
						    cout << "RegistrationID"<<"\t" << "EventID" << "\t" <<"\t" <<"RegisteredDate"<< endl;
						    while ((row = mysql_fetch_row(result3))) {
						    for (int i = 0; i < mysql_num_fields(result3); i++) {
						    cout << row[i] << "\t" << "\t";
						    }
						    cout << endl;
						}
						cout << endl;
						youregister:
						cout << "What do you want to do" << endl;
						cout << "1. Unregistered from event" << endl;
						cout << "2. Search Event" << endl;
						cout << "3. Quit" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						cout << endl;
						cout << "***************************************************************************************" << endl;
                        cout << "Welcome to the unregistration Page" << endl;
                        cout << endl;
                        unregister:
                        cout << "Enter the EventID you want to unregister: ";
                        cin >> EventID;
                        sentence_aux = "DELETE FROM Registration WHERE EventID = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(EventID) + 1];
						sprintf(consult, sentence, EventID);
                        if (mysql_query(obj, consult)){
                            cout << "Error Unregistering you from this event: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto unregister;
                        } else {
                            cout << "unregistered successfully!" << endl;
                        }
                        cout << endl;
                        cout << "Do you want to unregister from other event agian" << endl;
                        cout << "1.Yes" << endl;
                        cout << "2.No" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 1) {
                        	goto unregister;
						}	
						}
						else if (choice == 2) {
							MYSQL_RES* result3;
						    MYSQL_ROW row;
						    cout << endl;
						    cout << "**************************************************************************************************" << endl;
                            cout << "Welcome to the event you registered Search Page" << endl;
                            cout << endl;
                            userregistersearch:
					    	cout << "Enter the EventID You want to search: ";
					    	cin >> EventID;
						    sentence_aux = "SELECT RegistrationID, EventID, RegisteredDate FROM Registration WHERE UserID = '%s' AND EventID = '%s'";
			                sentence = new char[sentence_aux.length() + 1];
						    strcpy(sentence, sentence_aux.c_str());
						    consult = new char[strlen(sentence) + strlen(Username.c_str()) + strlen(EventID) + 1];
						    sprintf(consult, sentence, Username.c_str(), EventID);
						    if (mysql_query(obj, consult)) {
						    cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    result3 = mysql_store_result(obj);
						    if (!result) {
						    cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    if (mysql_num_rows(result3) == 0) {
						    cout << endl; 
							cout << "You didn't register for this event'" << endl;
							cout << endl;
							goto youregister;
						}
						    cout << "RegistrationID"<<"\t" << "EventID" << "\t" <<"\t" <<"RegisteredDate"<< endl;
						    while ((row = mysql_fetch_row(result3))) {
						    for (int i = 0; i < mysql_num_fields(result3); i++) {
						    cout << row[i] << "\t" << "\t";
						    }
						    cout << endl;
						}
						cout << "Do you want to search again" << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if(choice == 1) {
							cout << endl;
							goto userregistersearch;
						}
						}
						cout << endl;
						cout << "What do you want to do" << endl;
						cout << "1. See Events you registered " << endl;
						cout << "2. Go back to Home" << endl;
						cout << "3. Quit" << endl;
						cin >> choice;
						if (choice == 1) {
						cout << endl;
						goto registered;}
						else if(choice == 2) {
							cout << endl;
							goto home;
						}
						else if (choice == 3) {
							cout << endl;
							goto home;
						}
						mysql_free_result(result3);
					}
					else if (answer == 5) {
							MYSQL_RES* result4;
						    MYSQL_ROW row;
						    cout << "*************************************************************************************" << endl;
						    cout << "Welcome to you Account Info Page" << endl;
						    cout << endl;
						    account:
						    sentence_aux = "SELECT * FROM User WHERE Username = '%s'";
			                sentence = new char[sentence_aux.length() + 1];
						    strcpy(sentence, sentence_aux.c_str());
						    consult = new char[strlen(sentence) + strlen(Username.c_str()) + 1];
						    sprintf(consult, sentence, Username.c_str());
						    if (mysql_query(obj, consult)) {
						    cout << "Error querying MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    result4 = mysql_store_result(obj);
						    if (!result) {
						    cout << "Error getting result from MySQL: " << mysql_error(obj) << endl;
						    mysql_close(obj);
						    cout << endl;
				            goto landingpage;
						    }
						    cout << "UserID"<<"\t" << "First Name" << "\t" << "Last Name " << "\t" << "    "<< "Username" << "\t"  << "     "<< "Email" << "\t" << "\t"  << "\t" << "    "<< "Sex"<<"\t" <<"Password"<< endl;
						    while ((row = mysql_fetch_row(result4))) {
						    for (int i = 0; i < mysql_num_fields(result4); i++) {
						    cout << row[i] << "\t" << "    ";
						    }
						    cout << endl;
						}
						mysql_free_result(result4);
						cout << endl;
						accountchoice:
						cout << "What do you want to do" << endl;
						cout << "1. Update your acoount" << endl;
						cout << "2. Go back to Home" << endl;
						cout << "3. Log Out" << endl;
						cout << "4. Delete Your acoount" << endl;
						cout << "5. Quit" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						cout << "*************************************************************************************" << endl;
						cout << "Welcome to you Account Info Update Page" << endl;
						cout << endl;
						cout << "Which acoount info you want to update" << endl;
						cout << "1. First Name" << endl;
						cout << "2. Last Name" << endl;
						cout << "3. Username" << endl;
						cout << "4. Email" << endl;
						cout << "5. Sex" << endl;
						cout << "6. Password" << endl;
						cout << "7. quit" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						firstname:
						cout << "Enter your New first name: ";
						cin >> user.FirstName;
						sentence_aux = "UPDATE User SET FirstName = '%s' WHERE Username = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(user.FirstName) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence,user.FirstName, Username.c_str());
                        if (mysql_query(obj, consult)){
                            cout << "Error updating your first name: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto firstname;
                        } else {
                            cout << "updated successfully!" << endl;
                    }
                        cout << endl;
						goto accountchoice;
						}
						else if (choice == 2) {
						lastname:
						cout << "Enter your New last name: ";
						cin >> user.LastName;
						sentence_aux = "UPDATE User SET  LastName = '%s' WHERE Username = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(user.LastName) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence,user.LastName, Username.c_str());
                        if (mysql_query(obj, consult)){
                            cout << "Error updating your last name: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto lastname;
                        } else {
                            cout << "updated successfully!" << endl;
                        }
                        cout << endl;
						goto accountchoice;
						}
						else if (choice == 3) {
						username:
						cout << "Enter your new username: ";
						cin >> user.Username;
						sentence_aux = "UPDATE User SET  Username = '%s' WHERE Username = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(user.Username) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence,user.Username, Username.c_str());
                        if (mysql_query(obj, consult)){
                            cout << "Error updating your Username: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto username;
                        } else {
                            cout << "updated successfully!" << endl;
                            Username = user.Username;
                        }
                        cout << endl;
						goto accountchoice;
						}
						else if (choice == 4) {
						email:
						cout << "Enter your New Email: ";
						cin >> user.Email;
						sentence_aux = "UPDATE User SET  Email = '%s' WHERE Username = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(user.Email) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence,user.Email, Username.c_str());
                        if (mysql_query(obj, consult)){
                            cout << "Error updating your Email: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto email;
                        } else {
                            cout << "updated successfully!" << endl;
                        }
						cout << endl;
						goto accountchoice;	
						}
						else if (choice == 5) {
						sex:
						cout << "Enter your New Sex: ";
						cin >> user.Sex;
						sentence_aux = "UPDATE User SET  Sex = '%s' WHERE Username = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(user.Sex) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence,user.Sex, Username.c_str());
                        if (mysql_query(obj, consult)){
                            cout << "Error updating your sex: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto sex;
                        } else {
                            cout << "updated successfully!" << endl;
                        }
                        cout << endl;
						goto accountchoice;
						}
						else if (choice == 6) {
						password:
						cout << "Enter your New Password: ";
						cin >> user.Password;
						sentence_aux = "UPDATE User SET  Password = '%s' WHERE Username = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(user.Password.c_str()) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence,user.Password.c_str(), Username.c_str());
                        if (mysql_query(obj, consult)){
                            cout << "Error updating your password: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto password;
                        } else {
                            cout << "updated successfully!" << endl;
                        }
                        cout << endl;
						goto accountchoice;
						}
						else {
							cout << endl;
							goto accountchoice;
						}	
						}
						else if (choice == 2) {
						cout << endl;
						goto home;}
						else if (choice == 3) {
						cout << endl;
						goto landingpage;
						}
						else if (choice == 4) {
						cout << "Are you sure you want to delete your account" << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						if (choice == 1) {
						sentence_aux = "DELETE FROM User WHERE Username = '%s'";
			            sentence = new char[sentence_aux.length() + 1];
						strcpy(sentence, sentence_aux.c_str());
						consult = new char[strlen(sentence) + strlen(Username.c_str()) + 1];
						sprintf(consult, sentence, Username.c_str());
                        if (mysql_query(obj, consult)){
                            cout << "Error Deleting your Account: " << mysql_error(obj) << endl;
                            cout << endl;
				            goto accountchoice;
                        } else {
                            cout << "Account deleted successfully!" << endl;
                            cout << endl;
                            goto landingpage;
                        }
                    }
                    else {
                    	cout << endl;
                    	goto account;
					}
						}
					}
                } else {
                	cout << endl;
                    cout << "Login failed. Invalid username or password." << endl;
                    cout << "Do you have an account" << endl;
                    cout << "1.Yes" << endl;
                    cout << "2.No" << endl;
                    cout << "Enter Your Choice: ";
                    cin >> choice;
                    if( choice == 1) {
                    cout << endl;
                    cout << "Try again by filling the correct username and password for your account" << endl;
                    cout << endl;
                    goto login;
					}
					else if (choice == 2) {
						cout << endl;
						cout << "To use this program You have to register first!!" << endl;
						cout << "Please register by filling the below form" << endl;
						goto registration;
					}
                    }
                    mysql_free_result(result);
		}
	}
}
}
mysql_close(obj);
	return 0;
}
