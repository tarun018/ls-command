#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <dirent.h>
#include <err.h>
#include <time.h>
#define BUF_SIZE 1024

//size
struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

int n_tu(int number, int count)
{
  int result=1;
  while(count-- > 0)
  result *=number;  

  return result;
}

char* myitoaa(long i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    long shifter = i;
    do{ 
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ 
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}
long long countlength(long long i)
{
	long long count=0;
	while(i!=0)
	{
		count++;
		i=i/10;
	}
	return count;
}
void getdate(unsigned long date)
{
	int len = countlength(date);
	char top[len+1];
	myitoaa(date,top);
	if (len==1)
	{
		write(1," ",1);
	}
	write(1,top,mystrlen(top));
	write(1," ",1);
}
void gethours(unsigned long hours)
{
	int len = countlength(hours);
	char top[len+1];
	myitoaa(hours,top);
	if (hours==0)
	{
		write(1,"00",2);
		return;	
	}
	if (len==1)
	{
		write(1,"0",1);
	}
	write(1,top,mystrlen(top));
}
void getminute(unsigned long minute)
{
	int len = countlength(minute);
	char top[len+1];
	myitoaa(minute,top);
	if (minute==0)
	{
		write(1,"00 ",3);
		return;	
	}
	if (len==1)
	{
		write(1,"0",1);
	}
	write(1,top,mystrlen(top));
	write(1," ",1);
}
void getmonth(unsigned long month)
{	
	if (month==1)
		write(1,"Jan",3);
	else if (month==2)
		write(1,"Feb",3);
	else if (month==3)
		write(1,"Mar",3);
	else if (month==4)
		write(1,"Apr",3);
	else if (month==5)
		write(1,"May",3);
	else if (month==6)
		write(1,"Jun",3);
	else if (month==7)
		write(1,"Jul",3);
	else if (month==8)
		write(1,"Aug",3);
	else if (month==9)
		write(1,"Sep",3);
	else if (month==10)
		write(1,"Oct",3);
	else if (month==11)
		write(1,"Nov",3);
	else if (month==12)
		write(1,"Dec",3);
	write(1," ",1);
	
}
int checkleap(unsigned long year)
{
	if ( year%400 == 0)
    	return 1;
  else if ( year%100 == 0)
    	return 0;
  else if ( year%4 == 0 )
    	return 1;
  else
    	return 0; 
}
void getmodifiedtime(unsigned long epoch)
{
	epoch+=19800;
	unsigned long second; 
    unsigned long minute; 
    unsigned long hour;   
    unsigned long day;    
    unsigned long month;  
    unsigned long year;
	const static unsigned short days[4][12] =
	{
	    {   0,  31,  60,  91, 121, 152, 182, 213, 244, 274, 305, 335},
	    { 366, 397, 425, 456, 486, 517, 547, 578, 609, 639, 670, 700},
	    { 731, 762, 790, 821, 851, 882, 912, 943, 974,1004,1035,1065},
	    {1096,1127,1155,1186,1216,1247,1277,1308,1339,1369,1400,1430},
	};

    second = epoch%60;
   	epoch /= 60;
    minute = epoch%60;
    epoch /= 60;
  	hour   = epoch%24; 
  	epoch /= 24;

    unsigned long years = epoch/(365*4+1)*4; 
    epoch %= 365*4+1;

    for (year=3; year>0; year--)
    {
        if (epoch >= days[year][0])
            break;
    }

    for (month=11; month>0; month--)
    {
        if (epoch >= days[year][month])
            break;
    }

    int ch=0;
    day   = epoch-days[year][month]+1;
    year  = years+year;
    month = month+1;
    if (month==1 || month==3 || month==5 ||month==7 || month==8 || month==10 || month==12)
    {
    	if (day==31)
    	{
    		ch=1;
	 		day=1;
	 		month+=1;
	 	}
    }
    if (month==4 || month==6 ||month==9 || month==11)
    {
    	if (day==30)
    	{
    		ch=1;
	 		day=1;
	 		month+=1;
	 	}
    }
    if (month==2)
    {
    	if (checkleap(year)==1)
    	{
    		if(day==29)
    		{ 	
    			ch=1;
    			day=1;
    			month+=1;
    		}
    	}
    	else
    	{
    		if(day==28)
    		{
    			ch=1;
    			day=1;
    			month+=1;
    		}
    	}
    }
    if (ch==0)
    	day++;
    getmonth(month);
    getdate(day);
    gethours(hour);
    write(1,":",1);
    getminute(minute);
}

char* myitoa(long long i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    long long shifter = i;
    do{ 
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ 
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}


void float_to_string(float f, char r[])
{
	long long int length, length2, i, number, position, sign;
	float number2;

	sign=-1;  
	if (f <0)
	{
		sign='-';
		f *= -1;    
	}   


	number2=f;  
	number=f;
	length=0;  
	length2=0; 


	while( (number2 - (float)number) != 0.0 && !((number2 - (float)number) < 0.0) )
	{	

		number2= f * (n_tu(10.0,length2+1));
		number=number2; 

		length2++;

	}	

	for(length=(f> 1) ? 0 : 1; f > 1; length++) 
  		f /= 10;


 	position=length;
 	length=length+1+length2;
 	number=number2;
 	if(sign=='-')
 	{
 		length++;
 		position++;
 	}

 	for(i=length; i >= 0 ; i--)
 	{
		if(i== (length))
  			r[i]='\0';
		else if(i==(position))
  			r[i]='.';
		else if(sign=='-' && i==0)
  			r[i]='-';
		else  
		{		
  			r[i]= (number % 10)+'0';
  			number /=10;
		}
	}
}
char* mystrcpy(char *s1, const char *s2)
{ 
    char *s = s1; 
    while ((*s++ = *s2++) != 0) ;
    return (s1);
}

char* myStrStr(const char* str, const char* target)
{
	if(!*target) return NULL;
	char *p1 = (char*)str;
	while(*p1)
	{
		char *p1Begin = p1, *p2 = (char*)target;
		while(*p1 && *p2 && *p1 == *p2)
		{
			p1++;
			p2++;
		}
		if(!*p2)
			return p1Begin;
		p1 = p1Begin + 1;
	}
	return NULL;
}


void get_name(int uid)
{
	int fd = open("/etc/passwd", O_RDONLY), i;
	char buf[100000] = {'\0'};
	char num[100000] = {0};
	myitoa(uid,num);
	struct stat sb;
	fstat(fd, &sb);
	read(fd, &buf,(int)sb.st_size);
	char* ptr = myStrStr(buf,num);
	char* temp;
	while(*(ptr)!='\n')
	{
		ptr--;
	}
	ptr++;
	temp=ptr;
	i=0;
	while(*(ptr)!=':')
	{
		ptr++;
		i++;
	}
	write(1,temp,i);
	write(1," ",1);
	return;
}

int mystrlen( char *s )
{
    char *start;
    start = s;
    while( *s != 0 )
    {
        ++s;
    }
    return s - start;
}

char* mystrcat(char *s1, const char *s2)
{
    mystrcpy(&s1[mystrlen(s1)], s2);
    return s1;
}



void getnumoflinks(struct stat fileStat)
{
	long numoflinks = fileStat.st_nlink;
	long sizeof_numoflinks = countlength(numoflinks);
	char count[sizeof_numoflinks+1];
	myitoa(numoflinks,count);
	write(1,count,mystrlen(count));
	int p;
	for (p = 0; p < 2-(mystrlen(count)); ++p)
		write(1," ",1);		
}

void getfilesize(struct stat fileStat)
{
	long filesize = fileStat.st_size;
	long sizeof_filesize = countlength(filesize);
	char count[sizeof_filesize+1];
	myitoa(filesize,count);
	write(1,count,mystrlen(count));
	int p;
	for (p = 0; p < 12 -(mystrlen(count)); ++p)
		write(1," ",1);		
}

void getfilesize_with_h(struct stat fileStat,int block,long long blocks)
{
	float filesize;
	int y=0,p,overallprint=0,inita=0;
	if (block==0)
	{
		filesize =(float)fileStat.st_size;
	}
	else if (block==1)
	{
		filesize =(float)blocks;
	}
	while(filesize>=1024)
	{
		y++;
		filesize=(float)((float)filesize/(float)1024);
	}
	long siz = (long)filesize;
	long h = countlength(filesize);
	char ans[h+1];
	float_to_string(filesize,ans);
	for (p=0;p<mystrlen(ans);p++)
	{
		if (ans[p]=='.' && siz==filesize)
		{
			inita=1;
			break;
		}
		else if (ans[p]=='.')
		{
			overallprint+=2;
			write(1,".",1);
			write(1,(ans+p+1),1);
			break;
		}
		else
		{
			write(1,(ans+p),1);
			overallprint++;
		}	
	}
	char suffix[5]={'K','M','G','T'};

	if (y!=0)
	{
		if (inita==1)
		{
			write(1,".0",2);
			overallprint+=2;
		}
		write(1,(suffix+y-1),1);
		overallprint++;
	}
	int u;
	for (u = 0; u < 5-overallprint; ++u)
		write(1," ",1);		
}


void printinginfo(struct stat fileStat,char **argv,int direct,int harg)
{
	if (S_ISLNK(fileStat.st_mode))		
		write(1,"l",1);
	else if (S_ISDIR(fileStat.st_mode))
		write(1,"d",1);
	else
		write(1,"-",1);
	write(1,((fileStat.st_mode & S_IRUSR) ? "r" : "-"),1);
	write(1,((fileStat.st_mode & S_IWUSR) ? "w" : "-"),1);
	write(1,((fileStat.st_mode & S_IXUSR) ? "x" : "-"),1);
	write(1,((fileStat.st_mode & S_IRGRP) ? "r" : "-"),1);
	write(1,((fileStat.st_mode & S_IWGRP) ? "w" : "-"),1);
	write(1,((fileStat.st_mode & S_IXGRP) ? "x" : "-"),1);
	write(1,((fileStat.st_mode & S_IROTH) ? "r" : "-"),1);
	write(1,((fileStat.st_mode & S_IWOTH) ? "w" : "-"),1);
	write(1,((fileStat.st_mode & S_IXOTH) ? "x" : "-"),1);
	write(1," ",1);
	getnumoflinks(fileStat);
	write(1," ",1);
	if(fileStat.st_uid == 0)
		write(1,"root ",5);
	else
		get_name(fileStat.st_uid);
	if(fileStat.st_gid == 0)
		write(1,"root ",5);
	else
		get_name(fileStat.st_gid);
	char *size;	
	if (harg==1)		
		getfilesize_with_h(fileStat,0,1);			
	else
		getfilesize(fileStat);			
	write(1," ",1);
	char *f,toprint[17];
	getmodifiedtime(fileStat.st_mtime);
	/*f = ctime(&fileStat.st_mtime);			
	int i=0,j=0;				
	for(i=4;i<16;i++)
		toprint[j++]=f[i];
	toprint[j++]='\0';				
	write(1,toprint,mystrlen(toprint));
	write(1," ",1);*/
}

void read_link(char *path,struct stat sb)
{
	char linkname[sb.st_size + 1];
	ssize_t r;

	r = readlink(path, linkname, sb.st_size + 1);

	if (r == -1) 
	{
		perror("readlink error");
		_exit(1);
	}

	if (r > sb.st_size) 
	{
		perror("Error");
		_exit(1);	
	}
	linkname[r] = '\0';
	write(1,"\033[1m\x1b[34m",mystrlen("\033[1m\x1b[34m"));
	write(1,linkname,(size_t)mystrlen(linkname));
	write(1,"\x1b[0m",mystrlen("\x1b[0m"));
}
void listdir(char **argv,int direct,int argl,int arga,int argh)
{
	int fd, nread;
	long long block=0;	
	char buf[BUF_SIZE];
	struct linux_dirent *d;
	int bpos;
	char d_type;
	struct stat fileStat;
	char path[BUF_SIZE];

	fd = open(argv[direct], O_RDONLY | O_DIRECTORY);
	if (fd == -1)
	{        	
		perror("open");
		_exit(1);
	}
	for ( ; ; )
	{
		nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
		if (nread == -1)
		{			
			perror("getdents");
			_exit(1);
		}
		if (nread == 0)
			break;

		for (bpos = 0; bpos < nread;) 
		{
			d = (struct linux_dirent *) (buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			if ((argl==0 && arga==0 && argh==0) || (argl==0 && arga==0 && argh==1) || (argl==0 && arga==1 && argh==0) || (argl==0 && arga==1 && argh==1)) 
			{			
				mystrcpy(path,argv[direct]);
				mystrcat(path,"/");
				mystrcat(path,d->d_name);
				if(!lstat(path,&fileStat))
				{
					if(arga==0 && (d->d_name)[0]=='.')
					{
						bpos += d->d_reclen; 
						continue; 
					}
					if (S_ISDIR(fileStat.st_mode))
					{
						write(1,"\033[1m\x1b[34m",mystrlen("\033[1m\x1b[34m"));
						write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\x1b[0m",mystrlen("\x1b[0m"));
						write(1,"\n",1);
					}
					else if (S_ISLNK(fileStat.st_mode))
					{
						write(1,"\033[1m\x1b[36m",mystrlen("\033[1m\x1b[36m"));
						write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\x1b[0m",mystrlen("\x1b[0m"));
						write(1,"\n",1);
					}
					else if((fileStat.st_mode > 0) && (S_IEXEC & fileStat.st_mode))
					{
						write(1,"\033[1m\x1b[32m",mystrlen("\033[1m\x1b[32m"));
						write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\x1b[0m",mystrlen("\x1b[0m"));
						write(1,"\n",1);
					} 
					else
					{
						int i,topr=1;
						for (i=0;i<mystrlen(d->d_name);i++)
							if ((d->d_name[i]=='.' && d->d_name[i+1]=='t' && d->d_name[i+2]=='a' && d->d_name[i+3]=='r') || (d->d_name[i]=='.' && d->d_name[i+1]=='z' && d->d_name[i+2]=='i' && d->d_name[i+3]=='p'))
							{
								topr=0;
								write(1,"\033[1m\x1b[31m",mystrlen("\033[1m\x1b[31m"));
								write(1,d->d_name,(size_t)mystrlen(d->d_name));
								write(1,"\x1b[0m",mystrlen("\x1b[0m"));
								break;
							}
						if (topr == 1)
							write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\n",1);
					}				
				}
			}
			else if((argl==1 && arga==0 && argh==0) || (argl==1 && arga==0 && argh==1) || (argl==1 && arga==1 && argh==0) || (argl==1 && arga==1 && argh==1))
			{
				if(arga==0 && (d->d_name)[0]=='.')
				{
					bpos += d->d_reclen; 
					continue; 
				}	
				mystrcpy(path,argv[direct]);
				mystrcat(path,"/");
				mystrcat(path,d->d_name);
				if(!lstat(path,&fileStat))
				{
					if (S_ISDIR(fileStat.st_mode))
					{
						printinginfo(fileStat,argv,direct,argh);
						write(1,"\033[1m\x1b[34m",mystrlen("\033[1m\x1b[34m"));
						write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\x1b[0m",mystrlen("\x1b[0m"));
						write(1,"\n",1);					
					}
					else if (S_ISLNK(fileStat.st_mode))
					{
						printinginfo(fileStat,argv,direct,argh);
						write(1,"\033[1m\x1b[36m",mystrlen("\033[1m\x1b[36m"));
						write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\x1b[0m",mystrlen("\x1b[0m"));
						write(1," -> ",4);
						read_link(path,fileStat);
						write(1,"\n",1);					
					}
					else if((fileStat.st_mode > 0) && (S_IEXEC & fileStat.st_mode))
					{
						printinginfo(fileStat,argv,direct,argh);
						write(1,"\033[1m\x1b[32m",mystrlen("\033[1m\x1b[32m"));
						write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\x1b[0m",mystrlen("\x1b[0m"));
						write(1,"\n",1);
					}  
					else
					{
						printinginfo(fileStat,argv,direct,argh);
						int i,topr=1;
						for (i=0;i<mystrlen(d->d_name);i++)
							if ((d->d_name[i]=='.' && d->d_name[i+1]=='t' && d->d_name[i+2]=='a' && d->d_name[i+3]=='r') || (d->d_name[i]=='.' && d->d_name[i+1]=='z' && d->d_name[i+2]=='i' && d->d_name[i+3]=='p'))
							{
								topr=0;
								write(1,"\033[1m\x1b[31m",mystrlen("\033[1m\x1b[31m"));
								write(1,d->d_name,(size_t)mystrlen(d->d_name));
								write(1,"\x1b[0m",mystrlen("\x1b[0m"));
								break;
							}
						if (topr == 1)
							write(1,d->d_name,(size_t)mystrlen(d->d_name));
						write(1,"\n",1);
					}			
				}
			}
			block+=fileStat.st_blocks;			
			bpos += d->d_reclen;    	    
		}
	 }
	if (argl==1)
	{
		write(1,"total ",6);
		if (argh==1)
			getfilesize_with_h(fileStat,1,(long)((long)block/(long)2)*(long)1024);
		else
		{
			int jj = countlength((long)((long)block/(long)2));
			char ri[jj+1];
			myitoa(((long)((long)block/(long)2)),ri);
			write(1,ri,mystrlen(ri));
		}
		write(1,"\n",1);
	}
}
int main(int args,char **argv)
{
	if(args<2)
	{	
		perror("Provide folder name\n");
		_exit(1);
	}
	int k,arg,direct;
	for (k=0;k<args;k++)
	{
		if(argv[k][0]=='-')
			arg=k;
		else
			direct=k;
	}

	struct stat fileStat;
	char path[102];
	if(lstat(argv[direct],&fileStat)<0)
	{
		perror(argv[direct]);		
		return 1;
	}
	if ((args==2))
	{
		if((fileStat.st_mode & S_IFMT)==S_IFREG)
		{
       		write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
			write(1,"\n",1); 
		}
		else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
		{			
			listdir(argv,direct,0,0,0);
		}
		/*else if((fileStat.st_mode & S_IFMT)==S_IFLNK)
		{
			char *t;			
			t = read_link(argv[direct],fileStat);
			listdir(t,direct,0,0,0);
		}*/
	}
	else if(args==3)
	{
		if ((mystrlen(argv[arg])==2 && argv[arg][1]=='l'))
		{
			if((fileStat.st_mode & S_IFMT)==S_IFREG)
			{
				printinginfo(fileStat,argv,direct,0);
				write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
				write(1,"\n",1); 				
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
			{
				listdir(argv,direct,1,0,0);
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFLNK)
			{
				printinginfo(fileStat,argv,direct,0);
				write(1,"\033[1m\x1b[36m",mystrlen("\033[1m\x1b[36m"));
				write(1,argv[direct],(size_t)mystrlen(argv[direct]));
				write(1,"\x1b[0m",mystrlen("\x1b[0m"));
				write(1," -> ",4);
				read_link(argv[direct],fileStat);
				write(1,"\n",1);
			}	
		}
		else if ((mystrlen(argv[arg])==2 && argv[arg][1]=='a'))
		{
			if((fileStat.st_mode & S_IFMT)==S_IFREG)
			{
	       			write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
				write(1,"\n",1); 
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
			{
				listdir(argv,direct,0,1,0);
			}
		}
		else if ((mystrlen(argv[arg])==2 && argv[arg][1]=='h'))
		{
			if((fileStat.st_mode & S_IFMT)==S_IFREG)
			{
	       			write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
				write(1,"\n",1); 
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
			{
				listdir(argv,direct,0,0,1);
			}
		}
		else if((mystrlen(argv[arg])==3) && ((argv[arg][1]=='a' && argv[arg][2]=='l') || (argv[arg][1]=='l' && argv[arg][2]=='a')))
		{
			if((fileStat.st_mode & S_IFMT)==S_IFREG)
			{
				printinginfo(fileStat,argv,direct,0);
				write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
				write(1,"\n",1); 				
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
			{
				listdir(argv,direct,1,1,0);
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFLNK)
			{
				printinginfo(fileStat,argv,direct,0);
				write(1,"\033[1m\x1b[36m",mystrlen("\033[1m\x1b[36m"));
				write(1,argv[direct],(size_t)mystrlen(argv[direct]));
				write(1,"\x1b[0m",mystrlen("\x1b[0m"));
				write(1," -> ",4);
				read_link(argv[direct],fileStat);
				write(1,"\n",1);
			}	
	
		}
		else if((mystrlen(argv[arg])==3) && ((argv[arg][1]=='a' && argv[arg][2]=='h') || (argv[arg][1]=='h' && argv[arg][2]=='a')))
		{
			if((fileStat.st_mode & S_IFMT)==S_IFREG)
			{
	       			write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
				write(1,"\n",1); 
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
			{
				listdir(argv,direct,0,1,1);
			}
			
		}
		else if((mystrlen(argv[arg])==3) && ((argv[arg][1]=='h' && argv[arg][2]=='l') || (argv[arg][1]=='l' && argv[arg][2]=='h')))
		{
			if((fileStat.st_mode & S_IFMT)==S_IFREG)
			{
				printinginfo(fileStat,argv,direct,1);
				write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
				write(1,"\n",1); 				
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
			{
				listdir(argv,direct,1,0,1);
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFLNK)
			{
				printinginfo(fileStat,argv,direct,0);
				write(1,"\033[1m\x1b[36m",mystrlen("\033[1m\x1b[36m"));
				write(1,argv[direct],(size_t)mystrlen(argv[direct]));
				write(1,"\x1b[0m",mystrlen("\x1b[0m"));
				write(1," -> ",4);
				read_link(argv[direct],fileStat);
				write(1,"\n",1);
			}	

		}
		else if (mystrlen(argv[arg])==4)
		{
			if((fileStat.st_mode & S_IFMT)==S_IFREG)
			{
				printinginfo(fileStat,argv,direct,1);
				write(1,argv[direct],(size_t)mystrlen(argv[direct])); 
				write(1,"\n",1); 				
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFDIR)
			{
				listdir(argv,direct,1,1,1);
			}
			else if((fileStat.st_mode & S_IFMT)==S_IFLNK)
			{
				printinginfo(fileStat,argv,direct,0);
				write(1,"\033[1m\x1b[36m",mystrlen("\033[1m\x1b[36m"));
				write(1,argv[direct],(size_t)mystrlen(argv[direct]));
				write(1,"\x1b[0m",mystrlen("\x1b[0m"));
				write(1," -> ",4);
				read_link(argv[direct],fileStat);
				write(1,"\n",1);
			}	
		}
		else
			write(1,"command not recognized\n",24);
	}
}
