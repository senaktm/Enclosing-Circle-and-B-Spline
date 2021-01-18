#include<graphics.h>
#include<math.h> 

int pencerenin_eni=900;
int pencerenin_boyu=900;
int ikinokta_arasi=30;
int artim=10;
float olcek=ikinokta_arasi/artim;
void ciz_koordinat_sistemi()
{
     line(0, pencerenin_boyu/2, pencerenin_eni, pencerenin_boyu/2);
     
     line(pencerenin_eni/2, 0, pencerenin_eni/2, pencerenin_boyu);

int i,j;
setfillstyle(1,WHITE);
setcolor(WHITE);
     for(i=0;i<=pencerenin_eni;i+=ikinokta_arasi)
        { 
        	fillellipse(i,pencerenin_boyu/2,3,3);
	 
   	    }
setcolor(WHITE);
     for(i=0;i<=pencerenin_boyu;i+=ikinokta_arasi)
        { 
		    fillellipse(pencerenin_eni/2,i,3,3);
	    }	

char str[1000];
j=0;
for(i=pencerenin_eni/2;i<=pencerenin_eni;i+=ikinokta_arasi)
{
	sprintf(str,"%d",j);
	outtextxy(i-12,pencerenin_boyu/2+2,str);
	j+=artim;
}
j=0;
for(i=pencerenin_eni/2;i>=-pencerenin_eni;i-=ikinokta_arasi)
{
	sprintf(str,"%d",j);
	outtextxy(i-12,pencerenin_boyu/2+2,str); // -10 koordinat görselliði için
	j-=artim;
}
j=0;
for(i=pencerenin_boyu/2;i<=pencerenin_boyu;i+=ikinokta_arasi)
{
	sprintf(str,"%d",j);
	outtextxy(pencerenin_eni/2+2,i-12,str);
	j-=artim;
}
j=0;
for(i=pencerenin_boyu/2;i>=-pencerenin_boyu;i-=ikinokta_arasi)
{
	sprintf(str,"%d",j);
	outtextxy(pencerenin_eni/2+2,i-12,str);
	j+=artim;
}

}

void ciz_nokta(double x, double y)
{
fillellipse(pencerenin_eni/2+x*olcek,pencerenin_boyu/2-y*olcek,3,3);	
}

void ciz_cember(double x,double y,double r)
{ setcolor(BLUE);
circle(pencerenin_eni/2+x*olcek,pencerenin_boyu/2-y*olcek,r*olcek);
}

  double max;
  double deneme;
double toplamX=0,toplamY=0;
double uzaklik(double a,double b)
{ return sqrt(a*a+b*b);
}

void ciz_r(double a,double b,double r)
{   double a1=  pencerenin_eni/2+a*olcek;
    double a2=pencerenin_eni/2+a*olcek+r*olcek;
    double b1=pencerenin_boyu/2-b*olcek;
    double b2=pencerenin_boyu/2-b*olcek;
	line(a1,b1,a2,b2);
}

double sirala(int xx[],int yy[],int noktaadedi1)
{int i,j;
int temp,temp1;

for(i=0;i<noktaadedi1-1;i++)
{ for(j=i+1;j<noktaadedi1;j++)
{if(xx[i]>xx[j] )
 { temp=xx[i];
   xx[i]=xx[j];
   xx[j]=temp;
   temp1=yy[i];
   yy[i]=yy[j];
   yy[j]=temp1;
 
 }
 else if(xx[i]==xx[j])
 {
 	if(yy[i]>yy[j])
 	{
 		temp1=yy[i];
 		yy[i]=yy[j];
 		yy[j]=temp1;
	 }
 }
 
}
	
}

	
}
void ciz_minimal_cember(int xx[],int yy[],int noktaadedi)
{ int i,j;
double toplamX=0,toplamY=0;
for(i=0;i<noktaadedi;i++)
{ toplamX+=xx[i];
  toplamY+=yy[i];	
} 
toplamX/=noktaadedi;
toplamY/=noktaadedi;
double tasima_miktari=0.001;
       for(i=0;i<30000;i++)
       { int index=0;
         max= uzaklik(toplamX-xx[0],toplamY-yy[0]);
        for(j=1;j<noktaadedi;j++)
        { 
		deneme= uzaklik(toplamX-xx[j],toplamY-yy[j]);
        if(max<deneme)
        { max=deneme;
          index=j;	
		}
		
       	}
		toplamX+=(xx[index]-toplamX)*tasima_miktari;
		toplamY+=(yy[index]-toplamY)*tasima_miktari;
		tasima_miktari*=0.999;
        }
     
       printf("MERKEZ NOKTASI :  { %1f , %1f }\n\n",toplamX,toplamY);
       printf("YARICAP UZUNLUGU : %1f\n ",max);
       ciz_cember(toplamX,toplamY,max);
       setcolor(BLUE);
       setfillstyle(1,BLUE);
       fillellipse(pencerenin_eni/2+toplamX*olcek,pencerenin_boyu/2-toplamY*olcek,5,5); // merkez noktasý cizdirmek icin
       setcolor(YELLOW);
       ciz_r(toplamX,toplamY,max);
       
	   
}
double BSpline_3nokta_uzeri(int xx[],int yy[],int noktaadedi)
{ int i,j;
double spline_ciz_x[100000];
double spline_ciz_y[100000];
int sayac = 0;
sirala(xx,yy,noktaadedi);
double u,Nx,Ny;
for ( i = 0; i < noktaadedi - 3; i++)
{
         for(u=0;u<=1;u+=0.0001)
        {
	

        Nx = (double)(pow(1-u, 3) / 6.0) * xx[i]*olcek
		+  (double)((3 * pow(u, 3) - 6 * pow(u, 2) + 4) / 6.0) * xx[i + 1]*olcek
		+ (double)((-3 * pow(u, 3) + 3 * pow(u, 2) + 3 * u + 1) / 6.0) * xx[i + 2]*olcek
		+ (double)(pow(u, 3) / 6.0) * xx[i + 3]*olcek;
        Ny = (double)(pow(1-u, 3) / 6.0) * yy[i]*olcek
	    +  (double)((3 * pow(u, 3) - 6 * pow(u, 2) + 4) / 6.0) * yy[i + 1]*olcek 
		+ (double)((-3 * pow(u, 3) + 3 * pow(u, 2) + 3 * u + 1) / 6.0) * yy[i + 2]*olcek
		+ (double)(pow(u, 3) / 6.0) * yy[i + 3]*olcek;

		spline_ciz_x[sayac] = Nx;
        spline_ciz_y[sayac]=Ny;
       	setfillstyle(1,GREEN);
        setcolor(GREEN);
        fillellipse(pencerenin_eni/2+spline_ciz_x[sayac],pencerenin_boyu/2-spline_ciz_y[sayac],2,2);
		sayac++;
    }    
      
} 

}

double BSpline_3nokta(int xx[],int yy[],int noktaadedi)
{ int i;
int BS_3_nokta_x[noktaadedi+1];
 int  BS_3_nokta_y[noktaadedi+1];
 int toplamx=0,toplamy=0;
	for(i=0;i<noktaadedi;i++)
	{
		BS_3_nokta_x[i]=xx[i];
		toplamx+=BS_3_nokta_x[i];
		BS_3_nokta_y[i]=yy[i];
		toplamy+=BS_3_nokta_y[i];
		
	}
	BS_3_nokta_x[noktaadedi]=toplamx/3;
	BS_3_nokta_y[noktaadedi]=toplamy/3;
	
	sirala(BS_3_nokta_x,BS_3_nokta_y,noktaadedi);
	BSpline_3nokta_uzeri(BS_3_nokta_x,BS_3_nokta_y,noktaadedi+1);
	
}
double BSpline_2_nokta(int xx[],int yy[],int noktaadedi)
{ int i;
int BS_2_nokta_x[noktaadedi+2];
int BS_2_nokta_y[noktaadedi+2];
int toplamx=0,toplamy=0;
for(i=0;i<noktaadedi;i++)
{ 
	BS_2_nokta_x[i]=xx[i];
	BS_2_nokta_y[i]=yy[i];
	toplamx+=BS_2_nokta_x[i];
	toplamy+=BS_2_nokta_y[i];   	
}
BS_2_nokta_x[noktaadedi]=toplamx/2;
BS_2_nokta_y[noktaadedi]=toplamy/2;
BS_2_nokta_x[noktaadedi+1]=(BS_2_nokta_x[noktaadedi]+BS_2_nokta_x[noktaadedi])/3;
BS_2_nokta_y[noktaadedi+1]=(BS_2_nokta_y[noktaadedi]+BS_2_nokta_y[noktaadedi])/3;
sirala(BS_2_nokta_x,BS_2_nokta_y,noktaadedi);
BSpline_3nokta_uzeri(BS_2_nokta_x,BS_2_nokta_y,noktaadedi+2);
	
}

int main()
{
  int i,j;
  int nokta_adedi=0;
  int x[1000],y[1000];
  char karakter;
  FILE *dosya;
        if((dosya=fopen("koordinatlar.txt","r"))!=NULL)
        {  i=0;
           while(!feof(dosya))
           {
           	   fscanf(dosya,"%d%c%d",&x[i],&karakter,&y[i]);
               i++;
               nokta_adedi++;
		   }
        }
        else
        {
           printf("Dosya Bulunamadý");
        }
		printf("GIRILEN NOKTA SAYISI: %d\n\n",nokta_adedi) ;
	    initwindow(pencerenin_eni,pencerenin_boyu,"");
       ciz_koordinat_sistemi();
        
   if(nokta_adedi==1)
   { ciz_nokta(x[i],y[i]);
     printf("HATA: Tek nokta ile cember cizdirilemez.\n");
   }
  
        for(int i=0;i<nokta_adedi;i++)
        { setcolor(RED);
        setfillstyle(1,RED);
		ciz_nokta(x[i],y[i]);
		}
		
 ciz_minimal_cember(x,y,nokta_adedi);
        
      if(nokta_adedi>3)
	  {
	  	BSpline_3nokta_uzeri(x,y,nokta_adedi);
	  }
	  else if(nokta_adedi==3)
	  { 
	      BSpline_3nokta(x,y,nokta_adedi);
	  }
	  else if(nokta_adedi==2)
	  {
	  	BSpline_2_nokta(x,y,nokta_adedi);
	  }
	
	  
	  	getch();
       
       fclose(dosya);
       return 0;
	   
   }
