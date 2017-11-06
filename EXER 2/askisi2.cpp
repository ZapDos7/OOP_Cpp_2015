#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int initid=0, threadid=0;
string titles_of_threads[4] = {"Rules and FAQ", "First Lesson", "Lab", "Projects"};
string titles_of_posts [3] = {"Hello", "Question on Labs", "Preferable Compiler"};
string creator_names [4] = {"Sam", "Sammy", "Samuel", "Samantha"};
string possible_content[7] = {"This is my first post!", "I like programming!", "How do I change avatar?", "When is the next lab?", "My favorite programming language is C++!", "I am looking for a partener for the project, anyone available?", "When are we going to have Java lessons? I'm so excited!"};

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
		post () : id(initid+1), title (titles_of_posts[initid%3]), creator (creator_names[initid%4]), date_created(), contents(possible_content[initid%7])
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
		}
		string get_name()
		{
			return creator;
		}

};
	
class thread {
	int i;
	string theme;
	string creator;
	date date_created;
	post* threads_posts;
		
	public:
		thread () : theme (titles_of_threads[threadid%4]), creator (creator_names[threadid%4]), date_created ()
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
			cout << "Thread with theme:\"" << theme << "\", created by " << creator << " on " << endl;
			date_created.print();
			for (i=1; i<6; i++)
			{
				threads_posts[i-1].print();
			}
		}
		string titleis ()
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
		}
		
		post* post_adr(int i)
		{
			return &(threads_posts[i]);
		}
};

class list {
	
	class listnode {
		public:
			post * lpost;
			listnode * next;	
			
			listnode(post * p)
				:next(NULL)
			{
				lpost=p;
				cout << "Creating a listnode" << endl;			
			}
			
			~listnode()
			{
				cout << "Deleting a listnode" << endl;
				if (next != NULL) delete next;
			}
			void insert(post *pp)
			{
				if(next==NULL)
				{
					next=new listnode (pp);
				}
				else
				{
					next->insert(pp);
				}
			}
			post* retpost()
			{
				return lpost;
			}			
	};
	
	listnode * lnode;
		
		public:
			list (post * pp)
			{
				lnode= new listnode (pp);
			}
			~list()
			{
				
			}
			void print()
			{
				listnode * tmp;
				tmp = lnode;
				cout << endl;
				while (tmp != NULL)
				{
					tmp->lpost->print();
					cout << endl;
					tmp = tmp->next;
				}
			}
			void insert(post *pp)
			{
				lnode->insert(pp);
			}
			post* returnpost()
			{
				return lnode->retpost();
			}
};

class tree {
	
	class treenode 
	{
		public:
			string creator;
			list * tnlist;
			treenode * apaidi;
			treenode * dpaidi;

			treenode (post * pp) :creator (pp->get_name()), tnlist (NULL), apaidi (NULL), dpaidi (NULL)
			{
				tnlist = new list(pp);
				cout << "Created a treenode with posts form forum member " << creator << "." << endl;
			}
			
			~treenode ()
			{
				cout << "Destroying a treenode." << endl;
				if (apaidi != NULL) delete apaidi;
				
				if (dpaidi != NULL) delete dpaidi;
			}
			
			void printlist()
			{
				if (apaidi != NULL)	apaidi->printlist();
				tnlist->print();
				if (dpaidi != NULL)	dpaidi->printlist();
				cout << "Forum member " << creator << "has posted the following posts:" << endl;
				tnlist->print();
			}
			void insert(post * pp)
			{
				int ret=0;
				string cr;
				cr=pp->get_name();
				
				ret=creator.compare(cr);
				
				if(ret==0)
				{
					tnlist->insert(pp);
				}				
				else if(ret>0)
				{
					if(dpaidi!=NULL) dpaidi->insert(pp);
					else dpaidi=new treenode(pp);
				}
				else
				{
					if(apaidi!=NULL) apaidi->insert(pp);
					else apaidi=new treenode(pp);
				}
							
			}
			list * getlist ()
			{
				return tnlist;
			}
	};
	
	treenode * first;
	
	public:
		tree (thread &t)
		{
			post *pp;
			pp=t.post_adr(0);
			first=new treenode(pp);
			for (int i=1; i<5; i++)
			{
				pp=t.post_adr(i);
				first->insert(pp);
			}			
		}		
		~tree ()
		{
			delete first;
			first = NULL;
		}
		
		void printtree()
		{
			first->printlist();
		}
		
		list * get_list ()
		{
			return first->getlist();
		}
		
		void enhance (tree t)								  //add trees based on creator names D:
		{
			first->insert(t.get_list()->returnpost()); //sto tree opou efarmozetai h enhance bale ta post tou dendrou pou nai orisma
		}
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
		
		void print_sorted () //!!!!!!!!!
		{
			tree * trees[3];

			for (int i=0; i<3; i++)
			{
				trees[i]=new tree(forums_threads[i]);
			}
			trees[0]->printtree();
			for (int j=0; j<3; j++)
			{
				trees[0]->enhance(*(trees[j]));  
			}
			trees[0]->printtree();
		}
};

////////

int main (void)
{	
	forum f;
	f.print_sorted();
}
