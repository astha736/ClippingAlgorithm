#include <iostream>
#include <stdio.h>
using namespace std;
FILE* fp;
FILE* fp2;
struct point
{
	float x;
	float y;
};

typedef struct point point;

struct window
{
	point w1;
	point w2;
	point w3;
	point w4;
};

typedef struct window window;

float transx (point p, float c)
{
	return (p.x - c*p.y);
}

float invtransx (point p, float c)
{
	return (p.x + c*p.y);
}
float transy (point p, float c)
{
	return (-c*p.x+p.y);
}
float invtransy (point p, float c)
{
	return (p.y + c*p.x);
}


int main(int argc, char const *argv[])
{
	window w;
	window transwindow;
	point p1;
	point p2;
	point t1;
	point t2;
	int flag = 0;
	float c;
	float temp;
	
	w.w1.x = 50;
	w.w1.y = 50;
	w.w2.x = 50;
	w.w2.y = 100;
	w.w3.x = 100;
	w.w3.y = 100;
	w.w4.x = 100;
	w.w4.y = 50;	

	//cin>>p1.x>>p1.y;
	//cin>>p2.x>>p2.y;
	int count = 0 ;
	fp = fopen("testcases.txt","r");
	fp2 = fopen("output2.txt", "w");
	if(!fp)
		printf("file not open\n");
	while(!feof(fp))
	{
		count++;
		fscanf(fp,"%f %f",&p1.x, &p1.y);
		fscanf(fp,"%f %f",&p2.x,&p2.y);
		fprintf(fp2, "Test case %d \n",count);
		//printf("%f %f \n",p1.x,p1.y);
		//step 1
		t1.x = p1.x;
		t1.y = p1.y;
		t2.x = p2.x;
		t2.y = p2.y;


		bool f1 = w.w1.x <= p1.x && w.w4.x >= p1.x && w.w1.y <= p1.y && w.w3.y >= p1.y;
		bool f2 = w.w1.x <= p2.x && w.w4.x >= p2.x && w.w1.y <= p2.y && w.w3.y >= p2.y;

		if((p1.x <= w.w1.x && p2.x <= w.w1.x) || (p1.x >= w.w4.x && p2.x >= w.w4.x))
		//return 0;
		{fprintf(fp2,"Trivial rejection \n");
		continue;}

		if((p1.y <= w.w1.y && p2.y <= w.w1.y) || (p1.y >= w.w3.y && p2.y >= w.w3.y))
		//return 0;
		{fprintf(fp2,"Trivial rejection \n");
		continue;}
		//step 3

		else if (f1 && f2)
		{
			/* code */
			fprintf(fp2,"%f %f \n", t1.x, t1.y);
			fprintf(fp2,"%f %f \n",t2.x, t2.y);
			//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
			//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
		}
		// step 4
		else if (p1.y == p2.y)
		{
			/* code */
			int temp;
			if(p1.x > p2.x)
			{
				temp = p1.x;
				p1.x = p2.x;
				p2.x = temp;
				temp = p1.y;
				p1.y = p2.y;
				p2.y = temp;

				temp = t1.x;
				t1.x = t2.x;
				t2.x = temp;
				temp = t1.y;
				t1.y = t2.y;
				t2.y = temp;

			}

			if(p1.x <= w.w1.x && p2.x >= w.w2.x)
			{
				t1.x = w.w1.x;
				t2.x = w.w4.x;
				//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
				//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
				fprintf(fp2,"%f %f \n", t1.x, t1.y);
				fprintf(fp2,"%f %f \n",t2.x, t2.y);
				//return 0;

				continue;
			}
			else if (p1.x <= w.w1.x && p2.x >= w.w1.x)
			{
				/* code */
				t1.x = w.w1.x;
				fprintf(fp2,"%f %f \n", t1.x, t1.y);
			 	fprintf(fp2,"%f %f \n",t2.x, t2.y);
				//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
				//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
				//return 0;
				continue;
			}
			else if (p1.x <= w.w4.x && p2.x >= w.w4.x)
			{
				/* code */
				t2.x = w.w4.x;
				fprintf(fp2,"%f %f \n", t1.x, t1.y);
			 	fprintf(fp2,"%f %f \n",t2.x, t2.y);
				//return 0;
				continue;
			}
		}

		else if (p1.x == p2.x)
		{
			/* code */
			int temp;
			if(p1.y > p2.y)
			{
				temp = p1.x;
				p1.x = p2.x;
				p2.x = temp;
				temp = p1.y;
				p1.y = p2.y;
				p2.y = temp;

				temp = t1.x;
				t1.x = t2.x;
				t2.x = temp;
				temp = t1.y;
				t1.y = t2.y;
				t2.y = temp;

			}

			if(p1.y <= w.w1.y && p2.y >= w.w3.y)
			{
				t1.y = w.w1.y;
				t2.y = w.w3.y;
				fprintf(fp2,"%f %f \n", t1.x, t1.y);
			 	fprintf(fp2,"%f %f \n",t2.x, t2.y);
				//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
				//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
				//return 0;
				continue;
			}
			else if (p1.y <= w.w1.y && p2.y>= w.w1.y)
			{
				/* code */
				t1.y = w.w1.y;
				fprintf(fp2,"%f %f \n", t1.x, t1.y);
			 	fprintf(fp2,"%f %f \n",t2.x, t2.y);
				//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
				//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
				//return 0;
				continue;
			}
			else if (p1.y <= w.w3.y && p2.y >= w.w3.y)
			{
				/* code */
				t2.y = w.w3.y;
				fprintf(fp2,"%f %f \n", t1.x, t1.y);
			 	fprintf(fp2,"%f %f \n",t2.x, t2.y);
				//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
				//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
				//return 0;
				continue;
			}
		}

		else
		{
			c = (p1.x - p2.x)/(p1.y - p2.y);

			if(p1.y > p2.y)
			{
				temp = p1.x;
				p1.x = p2.x;
				p2.x = temp;
				temp = p1.y;
				p1.y = p2.y;
				p2.y = temp;

				temp = t1.x;
				t1.x = t2.x;
				t2.x = temp;
				temp = t1.y;
				t1.y = t2.y;
				t2.y = temp;

			}
			float temp1 = p1.x;
			float temp2 = p2.x;
			p1.x = transx(p1,c);
			p2.x = transx(p2,c);

			transwindow.w1.x = transx(w.w1,c);
			transwindow.w2.x = transx(w.w2,c);
			transwindow.w3.x = transx(w.w3,c);
			transwindow.w4.x = transx(w.w4,c);

			if(c > 0 && ((p1.x >= transwindow.w4.x) || (p1.x <= transwindow.w2.x)))
			{
				//return 0;
				continue;
			}	
			if(c < 0 && ((p1.x >= transwindow.w3.x) || (p1.x <= transwindow.w1.x)))
			{
				//return 0;
				continue;
			}
			else
			{
				if (p1.x >= transwindow.w1.x && p1.x <= transwindow.w4.x)
				{
					flag++;
					if (p1.y <= w.w1.y && p2.y >= w.w1.y )
						p1.y = w.w1.y;
					t1.x = invtransx(p1,c);
					t1.y = p1.y;
				}
				
				if (p1.x >= transwindow.w2.x && p1.x <= transwindow.w3.x)
				{
					flag++;
					if (p1.y <= w.w2.y && p2.y >= w.w2.y )
						p2.y = w.w2.y;
					t2.x = invtransx(p2,c);
					t2.y = p2.y;
				}

				if (flag == 2)
				{
					fprintf(fp2,"%f %f \n", t1.x, t1.y);
			 		fprintf(fp2,"%f %f \n",t2.x, t2.y);
					//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
					//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
					//return 0;
					continue;
				}

				p1.x = temp1;
				p2.x = temp2;

				if(p1.x > p2.x)
				{
					temp = p1.x;
					p1.x = p2.x;
					p2.x = temp;
					temp = p1.y;
					p1.y = p2.y;
					p2.y = temp;

					temp = t1.x;
					t1.x = t2.x;
					t2.x = temp;
					temp = t1.y;
					t1.y = t2.y;
					t2.y = temp;

				}
				c = 1/c;
				p1.y = transy(p1,c);
				p2.y = transy(p2,c);

				transwindow.w1.y = transy(w.w1,c);
				transwindow.w2.y = transy(w.w2,c);
				transwindow.w3.y = transy(w.w3,c);
				transwindow.w4.y = transy(w.w4,c);

				if ((p1.y >= transwindow.w1.y) && p1.y <= transwindow.w2.y)
				{
					flag++;
					if (p1.x <= w.w1.x && p2.x >= w.w1.x)
						p1.x = w.w1.x;
					t1.y = invtransy(p1,c);
					t1.x = p1.x;
				}

				if ((p1.y >= transwindow.w1.y) && p1.y <= transwindow.w3.y)
				{
					flag++;
					if (p1.x <= w.w4.x && p2.x >= w.w4.x)
						p2.x = w.w4.x;
					t2.y = invtransy(p2,c);
					t2.x = p2.x;
				}

				fprintf(fp2,"%f %f \n", t1.x, t1.y);
			 	fprintf(fp2,"%f %f \n",t2.x, t2.y);
			//cout<<"("<<t1.x<<","<<t1.y<<")"<<endl;
			//cout<<"("<<t2.x<<","<<t2.y<<")"<<endl;
			 }

		}

	}
	fclose(fp);
	fclose(fp2);
	return 0;
}