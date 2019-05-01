/* A program to perform Euclid's
   Algorithm to computer gcd. */
int x[20];
int yy;
int ww;
int gcd(int u,int v)
{
		if(v==0)return u;
		else return gcd(v,u-u/v*v);
}

void main(void)
{
	int x;int y;
	x = input();  y = input();
	output(gcd(x,y));
}
