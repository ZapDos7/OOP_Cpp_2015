#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int initid=0, threadid=0;
string titles_of_threads[3] = {"Rules and FAQ", "First Lesson", "Lab"};
string titles_of_posts [3] = {"Hello", "Question on Labs", "Preferable Compiler"};
string creator_names [4] = {"Sam", "Sammy", "Samuel", "Samantha"};
string possible_content[3] = {"This is my first post!", "I like programming!", "How do I change avatar?"};

class date{
	int day, month, year;
	
	public:
		date () : day(1), month (9), year(2015) { }
		void print() 
		{
			cout << day << "/" << month << "/" << year << endl;
		}
};

class post {
	int id;
	string title;
	string creator;
	date date_created;
	string contents;

	public:
		post () : id(initid+1), title (titles_of_posts[initid%3]), creator (creator_names[initid%4]), date_created(), contents(possible_content[initid%3])
		{
			cout << endl << endl << "Creating a post with ID: " << id << ", title: " << title << ", creator: " << creator << ", created on: " << endl;
			date_created.print();
			cout << endl << "\" " << contents << "\"." << endl << endl << endl;
			initid++;
		}
		
		~post ()
		{
			cout << "Post number: " << id << "is about to be destroyed." << endl;
		}
		void print ()
		{
			cout << "Post with ID: " << id << ", title:" << title << ", creator:" << creator << ", created on: " << endl;
			date_created.print();
			cout << endl << endl << "\"" << contents << "\"" << endl;
		}
		int idis()
		{
			return id;
		};
};
	
class thread {
	int i;
	string theme;
	string creator;
	date date_created;
	post* threads_posts;
	
	public:
		thread () : theme (titles_of_threads[threadid%3]), creator (creator_names[threadid%4]), date_created ()
		{
			threads_posts = new post[5];
			cout << "Thread with subject: " << theme << " has just been created!" << endl;
			threadid++;
		}
		~thread()
		{
			cout << "Thread with theme" << theme << " is about to be destroyed." << endl;
			delete [] threads_posts;
		}
		void print ()
		{
			cout << "Thread with theme: \"" << theme << "\", created by " << creator << " on " << endl;
			date_created.print();
			for (i=1; i<6; i++)
			{
				threads_posts[i-1].print();
			}
		}
	/*	void print_subject ()
		{
			cout << "\"" << theme << "\"" << endl;
		}
	*/	string titleis ()
		{
			return theme;
		}
		void find_post (int query)
		{
			for (i=0; i==5; i++)
			{
				if ((threads_posts[i].idis()) == query)
				{
					threads_posts[i].print();
				}
			}
		};
};
	
class forum {
	int i;
	string title;
	thread* forums_threads;
		
	public:
		forum () : title ("Object Oriented Programming")
		{
		 	forums_threads = new thread [3];
		 	cout << "Forum with title: " << title << " has just been created!" << endl;
		}
		~forum()
		{
			cout << "Forum with title: " << title << " is about to be destroyed!" << endl;
			delete [] forums_threads;
		}
		void print()
		{
			for (i=0; i<3; i++)
			{
				forums_threads[i].print();
				//forums_threads[i].print_subject();
			}
		}
		void find_thread (string name)
		{
			for (i=0; i<3; i++)
			{
				if ((forums_threads[i].titleis()) == name)
				{
					forums_threads[i].print();
				}
			}
		}
		void find_post (int query)
		{
			for (i=0; i<3; i++)
			{
				forums_threads[i].find_post(query);
			}
		}
};

////////
	
int main (void)
{	
	int i;
	forum f;
	f.print();
	f.find_thread("Rules and FAQ");
	srand(time(NULL));
	for (i=0; i==2; i++)
	{
		f.find_post((rand()%15)+1);
	};
}
