/* A program to perform Euclid's
   Algorithm to computer gcd. */
int gcd(int u,int v)
{
		if(v==0)return u;
		else return gcd(v,u-u/v*v);
}

void main(int a)
{
	int x;int y;
	
	x = input();  y = input();
	output(gcd(x,y));
}
