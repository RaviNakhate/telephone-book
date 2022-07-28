#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <fstream.h>
#include <string.h>

//CRUD Declare
int create();
void read();
void update();
void remove();
//loading component
void load()
{
    delay(200);
    outtextxy(250,200,"l");
    delay(200);
    outtextxy(260,200,"o");
    delay(100);
    outtextxy(270,200,"a");
    delay(200);
    outtextxy(280,200,"d");
    delay(200);
    outtextxy(290,200,"i");
    delay(200);
    outtextxy(300,200,"n");
    delay(200);
    outtextxy(310,200,"g");
    delay(200);
    outtextxy(320,200,".");
    delay(200);
    outtextxy(330,200,".");
    delay(100);
    outtextxy(340,200,".");

}

//welcome component
void welcome()
{
  settextstyle(3,0,4);
  outtextxy(230,150,"Welcome");
  outtextxy(280,185,"to");
  outtextxy(205,220,"Phone Book");

  settextstyle(4,0,1);
  outtextxy(185,400,"press any key to continue...");
  getch();
}

//menus component
void menus()
{
    settextstyle(0,0,0);
    outtextxy(190,185,"1. Add Contact");
    outtextxy(190,205,"2. Update Contact");
    outtextxy(190,225,"3. Delete Contact");
    outtextxy(190,245,"4. List of Contact's");
    outtextxy(190,265,"5. Close application");

}

//arrow component
void arrow(int inc)
{

    //inc==1 >> inc=0
    //inc==2 >> inc=20
    //inc==3 >> inc=40
    //inc==4 >> inc=60
    //inc==5 >> inc=80
    inc=(inc-1)*20;

    int a=180+inc,b=190+inc,c=200+inc;
    int points[]={150,a,170,b,150,c};

	setfillstyle(SOLID_FILL,YELLOW);
	fillpoly(3,points);

}

/* Contact Detail*/
class Contact
{
	private:
		long long int number,check;
		char name[20];
	public:
		int input();
		void show();
		char *getn()
		{
			return name;
		}
};
Contact obj;
int Contact::input()
{
   int len=0;
   gotoxy(12,10);
	 cout<<"Enter Name : ";
	 cin.getline(name,20);
   
   if(!strcmp(name,"")) {return 404; }
	 gotoxy(12,12);
	 cout<<"Enter Mobile Number : ";
	 cin>>number;
   check=number;
     while(check)
     {
         check=check/10;
         len++;
     }
     gotoxy(3,4);
   if(len==10)
   {}
   else {return 405;}
    
   return 1;
}
void Contact::show()
{
	cout<<name<<"\t"<<number;
}
//CRUD Define
fstream f1;
int key,active;

// create
int create()
{  char name[30];
	 long long int number;

	 a:
   int condition=0;
	 cleardevice();
	 gotoxy(24,5);
	 cout<<"****** Contact Details ******";
   condition=obj.input();
   if(condition==1)
   {
    	 setcolor(GREEN);
	     outtextxy(210,250,"successfull created...");

	    //file handling
	    f1.open("contact.dat",ios::app|ios::binary);
	    f1.write((char *)&obj,sizeof(obj));
	    f1.close();
	 

    	 setcolor(WHITE);
	     outtextxy(170,450,"Press \"Ecs\" to go main menus");
	     outtextxy(170,460,"Press \"enter\" to run again");

    	 b:
    	 key=getch();

	     if(key==13)
    	 {  goto a; }
	     else if(key==27)
	      { cleardevice();
	        active=0; }
	     else
	     { goto b; }
   }
   if(condition==404 || condition==405)
   {
      setcolor(RED);
       if(condition==404)
	     {  outtextxy(210,250,"invalid name created...");}
       if(condition==405)
       {outtextxy(210,250,"invalid number created...");}

       setcolor(WHITE);
	     outtextxy(170,450,"Press \"Ecs\" to go main menus");
	     outtextxy(170,460,"Press \"enter\" to create new data");

	    c:
	    key=getch();

	     if(key==13)
	    {  goto a; 
      }
	     else if(key==27)
	      { cleardevice();
	    	active=0; }
	     else
	     { goto c; }
   }
};

// read
void read()
{
      cleardevice();
       
    f1.open("contact.dat",ios::in|ios::binary);
	if(!f1)
	{
        	 gotoxy(30,10);
	         cout<<"empty data...";
	         outtextxy(170,450,"Press \"Ecs\" to go main menus");
	         esc:
	         key=getch();
	         if(key==27)
	         { cleardevice();
	               active=0;
	         }
	         else { goto esc; }
	}
	else
	{
       gotoxy(30,5);
       cout<<"List of Contact's";

	  f1.read((char *)&obj,sizeof(obj));


      int series=1;
	  while(!f1.eof())
       {
       
       for(int i=0;i<15;i++)
       {  if(!f1.eof())
         {
          gotoxy(1,8+i);
          cout<<series;
          series++;
          gotoxy(5,8+i);
          obj.show(); 
          f1.read((char *)&obj,sizeof(obj));
         }
         else { break; }
       }
       
	   outtextxy(170,450,"Press \"Ecs\" to go main menus");
	   outtextxy(170,460,"Press \"enter\" to change page");
	   label:
	   key=getch();
	   if(key==13)
	   {
        cleardevice();
	    gotoxy(30,5);
	    cout<<"List of Contact's";
	    gotoxy(9,8);  
	   }
	   else if(key==27)
	   {
	     cleardevice();
	     active=0;
	     break;
	   }
	   else
	   { goto label; }
	 }
	    
 }
 f1.close();
};

//update
void update()
{
    char name[50];
	int found=0;

    top:
    cleardevice();

    gotoxy(12,8);
    cout<<"enter name of contact : ";
    cin>>name;
	f1.open("contact.dat",ios::in|ios::out|ios::binary);
	if(!f1)
	{
      gotoxy(9,5);
	  cout<<"File Not Found";
	  exit(0);
	}
	else
	{
	    f1.read((char *)&obj,sizeof(obj));
	    while(!f1.eof())
	    {  
	       if(strcmpi(name,obj.getn())==0)
	       {
		     found=1;
		     f1.seekg(0,ios::cur);
		     obj.input();
		     f1.seekg(f1.tellg()-sizeof(obj));
		     f1.write((char *)&obj,sizeof(obj));
	       }
	       f1.read((char *)&obj,sizeof(obj));
	    }
	}
	if(found==0)
    {
      
       setcolor(RED);
       outtextxy(180,340,"Name does Not Exist in the Database...");
       setcolor(WHITE);
 
    }
    if(found==1)
    {
       setcolor(GREEN);
       outtextxy(190,340,"Update Successfull...");
       setcolor(WHITE);
    }
	f1.close();


    outtextxy(170,450,"Press \"Ecs\" to go main menus");
    outtextxy(170,460,"Press \"enter\" to run again");
      x:
      key=getch();
      if(key==27)
      { cleardevice();
    	active=0;
      }
      else if(key==13)
      {  goto top; }
      else { goto x; }
}
// remove
void remove()
{
    char n[40];
    int done=0;

    top:
    cleardevice();

    gotoxy(12,8);
	cout<<"Enter Name That Should Be Deleted ? : ";
	cin>>n;

	ofstream o;
    o.open("new.dat",ios::out|ios::binary);
	f1.open("contact.dat",ios::in|ios::binary);
	if(!f1)
	{
        setcolor(RED);
        outtextxy(150,320,"Error : No such file or directory found !");
        setcolor(WHITE);
        done=10;
	}
	else
	{
       
	   f1.read((char *)&obj,sizeof(obj));
	   while(!f1.eof())
	   {
          if(strcmpi(n,obj.getn())==0)
		  {
            done=1;
          }
	      if(strcmpi(n,obj.getn())!=0)
	      {
		  o.write((char *)&obj,sizeof(obj));
         
	      }
	      f1.read((char *)&obj,sizeof(obj));
	   }

	}
	o.close();
	f1.close();
	remove("contact.dat");
	rename("new.dat","contact.dat");
   if(done==1)
    {
        setcolor(GREEN);
        outtextxy(190,340,"Delete Successfull...");
        setcolor(WHITE);
    }
    if(done==0)
    {
       setcolor(RED);
       outtextxy(170,340,"Name does Not Exist in the Database...");
       setcolor(WHITE);       
    }
    outtextxy(170,450,"Press \"Ecs\" to go main menus");
    outtextxy(170,460,"Press \"enter\" to run again");
      x:
      key=getch();
      if(key==27)
      { cleardevice();
    	active=0;
      }
      else if(key==13)
      {  goto top; }
      else { goto x; }
};


int main()
{

  int gd=DETECT,gm,x;
  initgraph(&gd,&gm,"c://turboc3/bgi");

  load();
  cleardevice();
  delay(1000);
  welcome();

  while(1)
  {
    //starting render
    if(active==0)
    {
	  cleardevice();
	  menus();
	  arrow(1);
      active++;
    }
    //when DOWN then render
    key=getch();
    if(!key==13)
    {
      key=getch();
    }
    if(key==80)
    {   cleardevice();
    	menus();
        if(active<5)
          { active++; }
	    else
          { active=1;}
        arrow(active);
    }
    //when UP then render
    if(key==72)
	{
	   cleardevice();
       menus();
       if(active>1)
	      { active--; }
	   else
	      { active=5;}
        arrow(active);
    }
    //when ENTER then render
    if(key==13)
	{
       //Create file
       if(active==1)
       {
         create();
       }
   
       //Read file
       if(active==4)
       {
         read();
	   }

       //update
       if(active==2)
       {
          update();
       }
       //remove
	if(active==3)
       {
         remove();
       }
       //exit
      if(active==5)
	  {
    	 exit(0);
	  }
    }

}
  return 0;
}

