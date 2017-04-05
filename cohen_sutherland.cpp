#include <iostream>
#include <stdio.h>
FILE* fp;
FILE* fp2;
class clipping
{
private:
	float x;  
	float y;
	int code[4];
public:
	clipping();
	void readxy(char p[5]);  //function to read the x and y coordinates of point from file
	void encode(int top, int bottom, int right, int left); //to assign code to points
	int getcodeAtindex(int k); //function to find if the code at position k is non-zero
	float getx(void);
	float gety(void);
	friend int accept(clipping p1,clipping p2); //for trivial acceptance
	friend int reject(clipping p1, clipping p2); //for trivial rejection
	friend void swap(clipping &p1, clipping &p2); //to swap two points
	int isPoint_inside(void);
	//void clipping::operator = (clipping p2); 
	void changex(int yboundary, float m);  //for iterative clipping
	void changey(int xboundary, float m); 
};

clipping::clipping()
{
	int i;
	x=0;
	y=0;
	for (i=0;i<4;i++)
		code[i]=0;

}

float clipping::getx(void)
{
	return (x);
}

float clipping::gety(void)
{
	return (y);
}

void clipping::readxy(char p[5])
{
	//cout<<"\nReading coordinates of point "<<p;
	fscanf (fp,"%f",&x);
	fscanf (fp,"%f",&y);
}

void clipping::encode(int top, int bottom,int right,int left)
{
	if(y > top)
		code[0]=1;
	else 
		code[0]=0;
	if(y < bottom)
		code[1]=1;
	else
		code[1]=0;
	if (x > right)
		code[2]=1;
	else
		code[2]=0;
	if (x< left)
		code[3]=1;
	else
		code[3]=0;
}

int clipping::getcodeAtindex(int k)
{
	if(code[k] == 1)
		return 1;
	return 0;
}

int accept(clipping p1, clipping p2)
{
	int i;
	for(i=0;i<4;i++)
		{
			if(p1.getcodeAtindex(i) || p2.getcodeAtindex(i))
			return 0;
		 }
	return 1;
}

int reject(clipping p1, clipping p2)
{
	int i ;
	for (i=0;i<4;i++)
	{
		if(p1.getcodeAtindex(i) && p2.getcodeAtindex(i))
			return 1;
	}
	return 0;
}

int clipping::isPoint_inside(void)
{
	if(code[0] || code[1] || code[2] || code[3])
		return 0;
	return 1;
}

void swap(clipping &p1, clipping &p2) 
{
	clipping temp;
	temp= p1;
	p1 =p2;
	p2 =temp;
}

/*void clipping::operator = clipping(p2)
{
	int i;
	x=p2.x;
	y=p2.y;
	for (i=0; i<4;i++)
		code[i]=p2.code[i];
}*/

void clipping::changex(int yboundary, float m)
{
	x = x+ (yboundary - y)/m;
	y = yboundary;
}

void clipping::changey(int xboundary, float m)
{
	y = y + (xboundary - x)/m;
	x=xboundary;
}

int main()
{
	clipping p1, p2, tmp;
	int top,bottom,right,left, done =0, draw=0;
	float m;
	top = 100;   //getmaxy() / 2 + 50;
	bottom = 50;  //getmaxy() / 2 - 50;
	right = 100;  //getmaxx() / 2 + 50;
	left = 50; 
	fp = fopen("testcases.txt","r");
	fp2 = fopen("output1.txt", "w");
	int count=0;
	while(!feof(fp))
	{	
		count++;
		p1.readxy("p1");
		p2.readxy("p2");
		fprintf(fp2,"Test case %d \n",count);
		//printf("%f %f \n",p1.getx(),p1.gety());  
		done = 0; draw=0;
		while (done == 0)
		{
			p1.encode(top, bottom,right,left);
			p2.encode(top, bottom,right,left);
			if (accept(p1,p2))
			{
				done=1;
				draw =1;
			}
			else if (reject(p1,p2))
			{
				fprintf(fp2,"Trivial rejection \n");
				done=1;
			}
			else
			{

	            if (p1.isPoint_inside())
	                swap(p1,p2);
	            m = (p2.gety() - p1.gety()) / (p2.getx() - p1.getx());
	            if(p1.getcodeAtindex(0))
	            	p1.changex(top, m);
	            else if(p1.getcodeAtindex(1))
	                p1.changex(bottom, m);
	            else if(p1.getcodeAtindex(2))
	            	p1.changey(right,m);
	            else if(p1.getcodeAtindex(3))
	            	p1.changey(left, m);
			}
			
		}
		if (draw)
		{
			fprintf(fp2,"%f %f \n", p1.getx(), p1.gety());
			fprintf(fp2,"%f %f \n", p2.getx(), p2.gety());
			//std::cout<<"\n Clipped line segment is"<<"("<<p1.getx()<<","<<p1.gety()<<")"<<"("<<p2.getx()<<","<<p2.gety()<<")\n";
		}
	}
	fclose(fp);
	fclose(fp2);
	return 0;
}