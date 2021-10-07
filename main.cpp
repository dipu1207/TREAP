# include<iomanip>
# include<iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include<time.h>
#include <bits/stdc++.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class Node{
	private:
		int data ;
		int priority;
		Node*lchild;
		Node*rchild;
	
	public:
 	    Node(int key,int prio)
 	    {
 	    	data=key;
 	    	priority=prio;
 	    	lchild=NULL;
 	    	rchild=NULL;
		 }
	 	friend class Treap;
 	
	 	~Node(){
 			delete lchild;
 			delete rchild;
			 }
};
class Treap{
	private:Node*root;
	public:
		Treap(){
			root=new Node(0,INT_MAX);
		}
		
		void insert(int key,int priority);
		void deletion(int key);
		int search(int key);
        void print_tree(); 		
		~Treap()
		{
			delete root;
		}
};

void Treap::insert(int key,int priority)
{

   Node* temp=new Node(key,priority);
   //if tree is empty then we will set root as this node
   
   if(root->rchild==NULL)
   {
        root->rchild=temp;
        return;
   }
   Node*iterator=root->rchild;
   Node*parent;
   stack<Node*> path;
   path.push(root);
   while(iterator!=NULL)
  {
    if(key<iterator->data)
       {
       	parent=iterator;
       	path.push(iterator);
       	iterator=iterator->lchild;
       	 }
    else if(key>iterator->data)
      {
      	parent=iterator;
      	path.push(iterator);
      	iterator=iterator->rchild;
	    }
      else {
      	cout<<"duplicate key,insertion failed"<<endl;
	      return;
	  }
    } 
	
	
	//now parent points to leaf where new node will be inserted
        if(key<parent->data)
		   parent->lchild=temp;
		else parent->rchild=temp;
		
		//now we check priorities and do ratations
		
	 while(!path.empty())
          {
              parent=path.top();
			  path.pop();
			  if(parent==root)
			   {
			   	return;
			   }
			   
			  if(temp->priority < parent->priority)
			  {
			  	//incase of rotations this is parent of parent
			  	Node*parparent=path.top();
				 
			  	//chehck if child is at left or right of parent
			  	if(temp==parent->lchild)
			  	{
				   parent->lchild=temp->rchild;
				   temp->rchild=parent;
				   
				}
				else{
					parent->rchild=temp->lchild;
					temp->lchild=parent;
				}
				//now set child of parparent 
				if(parparent==root)
				   {parparent->rchild=temp;
				    path.pop();
				    break;
					}				  
				
				else if(parent==parparent->rchild)
				  parparent->rchild=temp;
			    else 
			       parparent->lchild=temp;
				}
	
		}
 }
		  			  
     
 
  

int Treap::search(int key){
	Node*searchptr=root->rchild;
	while(searchptr!=NULL)
	{
		if(key<searchptr->data)
		  searchptr=searchptr->lchild;
		else if(key>searchptr->data)
		    searchptr=searchptr->rchild;
		   else {
		          return 1;
				  }
	
	}
	return 0;
}


void Treap::deletion(int key){
//first we search if element is present or not if not we return
int searchresult=search(key);
if(!searchresult)
   {
   	cout<<"element to be deleted not present"<<endl;
   	return;
   }
   
 //we will go to the node to be deleted and also maintain a parent pointer of node to be deleted
 Node*deletenode=root->rchild;
Node*parent =root;
 while(deletenode->data!=key)
 {
 	if(key<deletenode->data)
 	   {
 	   	parent =deletenode;
 	   	deletenode=deletenode->lchild;
		}
	else if(key>deletenode->data)
	{
		parent=deletenode;
		deletenode=deletenode->rchild;
		}	
		else break;
 }
   
   while(1)
     //chehck if node to be deleted is leaf
     {
	    if(deletenode->lchild==NULL && deletenode->rchild==NULL)
           {//remove the node directly and set its parents child as null
             if(deletenode==parent->lchild)
                parent->lchild=NULL;
                else parent->rchild=NULL;
           	return;
			   }
         //node to be deleted has only one child  	
       else if(deletenode->lchild==NULL||deletenode->rchild==NULL)
	      {
	      	//delete node is left child of its parent
	      	if(deletenode==parent->lchild)
	      	    parent->lchild=deletenode->lchild==NULL?deletenode->rchild:deletenode->lchild;//if deletenode do not has left child then parent's lchild will be delete nodes rchild else lchild
			//delete node is right child of its parent
			else parent->rchild=deletenode->lchild==NULL?deletenode->rchild:deletenode->lchild;
			 return;
			 } 	
         //node to be deleted has two child 
		  else{
                  //now we check priority to decide which child will replace deletenode
				 Node*newparent=deletenode->lchild->priority<deletenode->rchild->priority?deletenode->lchild:deletenode->rchild;		  	
		  	     int rot;//to check for rotation
				   if(newparent==deletenode->lchild)
		  	          rot=1;// right rotation
		  	       else rot=0; //left rotation
				   //now we modify pointer and remove delete node
		  	     //check if delete node is left or right child of parent
		  	     if(deletenode==parent->lchild)
		  	     {
					   parent->lchild=newparent;
				   		if(rot==1)
				   		{
				   	        deletenode->lchild=newparent->rchild;
				   	        newparent->rchild=deletenode;
				   		
							}
				   		else
						   {
						   	deletenode->rchild=newparent->lchild;
						    newparent->lchild=deletenode;
						   }	
				//set new parent
				    parent=newparent;
				}
		  
		         else{
                        parent->rchild=newparent;		
						if(rot==1)
				   		{
				   	        deletenode->lchild=newparent->rchild;
				   	        newparent->rchild=deletenode;
				   		
							}
				   		else
						   {
						   	deletenode->rchild=newparent->lchild;
						    newparent->lchild=deletenode;
						   }	
				    //set new parent=newparent
					parent=newparent;		 
 				 }
		           		 
		  }
	}
}
void Treap::print_tree(){
	 ofstream filepointer;
	 filepointer.open("graphviz.dotgv");
	 filepointer<<"digraph {"<<endl;
	 filepointer<<"node[shape=record,height=.1];"<<endl;
	 Node*treeptr=root->rchild;
	 queue<Node*>levelorder;
	 levelorder.push(treeptr);
    //here i have inserted first half of values of graphviz file 
	 while(!levelorder.empty())
	 {
	 	treeptr=levelorder.front();
	 	levelorder.pop();
	 	filepointer<<treeptr->data<<"[label=\"<L>|<D>"<<treeptr->data<<"|"<<treeptr->priority<<"|<R>\"];"<<endl;
	    if(treeptr->lchild!=NULL)
	       levelorder.push(treeptr->lchild);
	     if(treeptr->rchild!=NULL)
	       levelorder.push(treeptr->rchild);
	 }
	 //now i will insert remaining entreies
	
	 treeptr=root->rchild;
	 queue<Node*>walk;
	 walk.push(treeptr);
	while(!walk.empty())
	{
		treeptr=walk.front();
		walk.pop();
	       if(treeptr->lchild!=NULL)
	       {
		       walk.push(treeptr->lchild);
	          filepointer<<"\""<<treeptr->data<<"\":L->\""<<treeptr->lchild->data<<"\":D;"<<endl;
           }
		 if(treeptr->rchild!=NULL)
	       {
    		   walk.push(treeptr->rchild);
	           filepointer<<"\""<<treeptr->data<<"\":R->\""<<treeptr->rchild->data<<"\":D;"<<endl;

		      }
	}
	 
	 
	 filepointer<<"}"<<endl;
	 filepointer.close();

	 string cmd="dot.exe -Tpng graphviz.dotgv -o Output.png";
	 system((const char*)cmd.c_str());
}

int main(int argc, char** argv) {
	Treap obj;
	int choice,x;
	int key;
	srand(time(0));
	while(1)
  { 
      cout<<endl;
  	cout<<"enter your choice"<<endl<<endl;
  	cout<<"1.insert"<<endl;
  	cout<<"2.search element"<<endl;
  	cout<<"3.delete element"<<endl;
  	cout<<"4.print tree"<<endl;
	cout<<"5.exit"<<endl;
  	cin>>choice;
  	
  	switch(choice){
  		case 1:cout<<"enter no of elements to be inserted"<<"\t";
  		        int count,priority;
				  cin>>count;
  		      
				 for(int i=1;i<=count;i++)
  		       {
  		       	cout<<"entere element"<<"\t"<<i<<"\t";
  		       	 cin>>key;
  		       	 priority=rand();
  		       	 obj.insert(key,priority);
				}
				cout<<"all elements inserted"<<endl;
				break;
		case 2:cout<<"enter element to search";
		        cin>>key;
		        x=obj.search(key);
		        if(x==1)
		         cout<<"element is found"<<endl;
		         else cout<<"element is not found"<<endl;
				break;
		case 3:cout<<"enter element to delete"<<"\t";
		        cin>>key;
		        obj.deletion(key);
		        break;
		case 4:
		        obj.print_tree();
		        break;
		case 5:exit(0);
  		     break;
  		default:exit(0);
	  }
  	
  }
	return 0;
}
