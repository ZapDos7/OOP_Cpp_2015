#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

string good_names[10] = {"Fourclouds", "Manados", "Shaedlass", "Elanaria", "Valustraa", "Shadewhisper", "Moonstalker", "Saelienne", "Lotherias", "Moonshadow"}; //nightelves
string bad_names[10] = {"Sunsworn", "Ardalan", "Mathredis", "Lethtendris", "Ithania", "Dawnsinger", "Pyreanor", "Dusksinger", "Sunsorrow", "Firehand"}; //bloodelves

unsigned int all=0;
unsigned int goodies = 0;
unsigned int zombies = 0;

class creature 
{
	protected:
		string name;
		unsigned int L;
		unsigned int pos;
		//
	public:
		creature (string n, int l, int here) : name(n), L(l), pos (here)
		{
			cout << "A creature is born!" << endl;	
			all++;
		}
		
		~creature ()
		{
			cout << "Farewell, creature!" << endl;
		//	all--;
		}
		
		creature (const creature &c) : name(c.name), L(c.L), pos(c.pos)
		{
			cout << "Copying a creature, because I can!" << endl;
		}

		virtual creature* clone() { }
		
		virtual bool bless() { }
		
		void beat()
		{
			if (this->is_a_zombie() == false)
			{
				L--;
			}
			else cout << "Can't beat a zombie, don't be rude!" << endl;
			if (this->L == 0) zombies++;
		}
		
		bool is_a_zombie()
		{
			return (L==0);
		}
		
		virtual	bool is_a_good() { }
		
		int get_pos ()
		{
			return pos;
		}
		
		int get_l ()
		{
			return L;
		}
		
		virtual int get_thresh ()
		{
			//des meta
		}
};

class good : public creature
{
	int gthresh;
	
	public:
		good (string gn, int gl, int ghere, int gt) : creature (gn, gl, ghere), gthresh(gt)
		{
		//	string gh, ggn;
		//	itoa (ghere, gh, 10);
		//	gh = to_string (ghere); //stringstream -> ?
		//	ggn = gn + gh;
			cout << "A good creature is born!" << endl;	
			goodies++;
		}
		
		good (const good &g) : creature (g), gthresh (g.gthresh) { goodies++; }
		
		bool is_a_good()
		{
			return true;
		}
		
		creature* clone()
		{
			creature * goodguy;
			goodguy = new good (*this) ;
			return goodguy;
		}
		
		bool bless()
		{
			if  ( (this->is_a_good() == true) && (this->is_a_zombie() == false) ) L++;
			return true;
		}
		
		int get_thresh ()
		{
			return gthresh;
		}
};

class bad : public creature
{
	int bthresh;
	
	public:
		bad (string bn, int bl, int bhere, int bt) : creature (bn,bl,bhere), bthresh(bt)
		{
			cout << "A bad creature is born!" << endl;	
		}

		bad (const bad &b) : creature(b), bthresh (b.bthresh) { }

		bool is_a_good()
		{
			return false;
		}
		
		creature* clone()
		{
			creature * badguy;
			badguy = new bad (*this);
			return badguy;
		}
		
		bool bless()
		{
			if  ( (this->is_a_good() == false) && (this->is_a_zombie() == false) ) L++;
			return false;
		}
				
		int get_thresh ()
		{
			return bthresh;
		}
};

class community 
{
	class node
	{
		public:
			creature * dis;
			node * next;
			
			node (creature * cp, node* np = NULL) : dis(cp), next(np)
			{
				cout << "Creating a member of the community, horray!" << endl;
			}
			
			~node()
			{
				cout << "Destroying a member of the community. RIP" << endl;
			}
	};
	
	unsigned int size;
	node * first;
	
	public:
		
		community (int N, node* fn, int dil, int good_thrsh, int bad_thrsh) : size(N), first(fn) //N apo eisodo
		{
			srand(time(NULL));
			for (int a=0; a<N ; a++)
			{
				creature * kritsour;
				if (rand()%2) 
				{
					kritsour = new good( good_names[all%10], dil, all, good_thrsh);
				}
				else
				{
					kritsour = new bad( bad_names[all%10], dil, all, bad_thrsh);
				}
				node * mhtsos = new node(kritsour);
				this->push_front(mhtsos);
			}
			node * temp = first;
			for (int b=0;b<N;b++) //gia na deixnei ton last ton first
			{
				temp = temp->next;
			}
			temp->next = first;
			cout << "Our monster society is being created!" << endl;
		}
		
		~community ()
		{
			cout << "Our monster society is being destroyed!" << endl;
		}
		
		void push_front (node * neo)
		{
			neo->next = first;
			first = neo;
		}
	
		int get_size ()
		{
			return size;
		}
		
		void clone_next (int thesi)
		{
			node * tempo = first;
			for (int r=0; r<thesi;r++)
			{
				tempo = tempo->next;
			}
			if ( (tempo->dis->is_a_good() == true) && (tempo->dis->get_l() > tempo->dis->get_thresh()) )
			{
				delete tempo->next->dis;
				tempo->next->dis = tempo->dis->clone(); //next thesi
			}
		}
		
		void clone_zombies (int thesoula)
		{
			node * tempor = first;
			for (int t=0; t<thesoula;t++)
			{
				tempor = tempor->next;
			}
			if ((tempor->dis->is_a_good() == false) && (tempor->dis->get_l() > tempor->dis->get_thresh()) && (tempor->dis->get_pos() != all) )
			{
				int q=0;
				while ( ( q < (all - (tempor->dis->get_pos() )) ) && (tempor->dis->is_a_zombie() == true ) )
					{
						delete tempor->next->dis;
						tempor->next->dis = tempor->dis->clone();
						q++;
						zombies--;
					}
			}
		}
		
		void beatr ()
		{
			srand(time(NULL));
			int tbbt;
			tbbt = rand()%(all+1);
			node * ttemp = first;
			for (int w=0;w<tbbt;w++)
			{
				ttemp = ttemp->next;
			}
			ttemp->dis->beat();
		}
		
		void blessr ()
		{
			srand(time(NULL));
			int tbbl;
			tbbl = rand()%(all+1);
			node * ttempp = first;
			for (int e=0;e<tbbl;e++)
			{
				ttempp = ttempp->next;
			}
			ttempp->dis->bless();
		}
		
		
		int get_goods ()
		{
			return goodies;
		}
		
		int get_zombies ()
		{
			return zombies;
		}
};

//

int main ( int argc, char *argv[] ) //argc = 5, arg[1] => N, arg[2] => M arg[3] =>L se constructor, arg[4] = gthresh, arg[5] = bthresh
{
	cout << "Please type desired size of society, times of repeat, desired initial lifepoints and thresholds." << endl;
	
	int good_thrsh, bad_thrsh, size_soc, times, dil, swag;
	//node * firstnode (creature * cr);
	
	size_soc = atoi (argv[1]);
	times = atoi (argv[2]);
	dil = atoi (argv[3]);
	good_thrsh = atoi (argv[4]);
	bad_thrsh = atoi (argv[5]);
	
	community koinwnia (size_soc, node * firstnode(creature * cr) , dil, good_thrsh, bad_thrsh);
	for (int yolo=0;yolo<times;yolo++) //tuxaia epilogh creature kai efarmogh M fores bless h buff sta teratakia
	{
		srand(time(NULL));
		swag = rand()%2; //bless h beat
		if (swag == 0)
		{
			blessr();
		}
		else
		{
			beatr();
		}
	}
	
	if (all == goodies) cout << "Good Dominates in the World." << endl;
	else if (all == zombies) cout << "This is a dead society." << endl;
	else cout << "Try again to improve the world." << endl;
}
