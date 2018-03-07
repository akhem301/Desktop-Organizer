#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

#define debug(x) cout<<"### x is: "<<x<<" ###\n";

vector<pair<long long,string> > filelist[6];

char* convert(string str)
{
	return (char*)str.c_str();
}

void search(const char* dirname , vector<pair<long long,string> >& sizelist,bool flag)
{
	DIR* dir; // pointer to an open directory
	struct dirent *entry; //entries in the directory
	struct stat info;
	
	//Open a directory
	dir = opendir(dirname);
	if(!dir)
	{
		cout<<"Error: Directory not found\n";
	}
	
	// Read a driectory
	while((entry = readdir(dir)) != NULL)
	{
		if(entry->d_name[0] != '.')
		{
			string path = string(dirname) + "/" + string(entry->d_name);
			stat(convert(path),&info);
			
			if(S_ISDIR(info.st_mode))
			{
				if(flag)
				search(convert(path),sizelist,flag);
			}
			else
			{
				sizelist.push_back({info.st_size,entry->d_name});
			}
		}
	}
	
	//Close a directory
	closedir(dir);
}

void filter(vector<pair<long long,string> > sizelist, map<string,int> format)
{
	for(int k=0;k<(int)sizelist.size();k++)
	{
		//debug(it.first);
		string extension;
		string rev=sizelist[k].second;
		for(int i=(int)rev.size()-1;i>=0;i--)
		{
			if(rev[i] == '.')
			break;
			extension += rev[i];
		}
		reverse(extension.begin(),extension.end());
		transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
		if(format[extension]!=0)
		filelist[format[extension]].push_back(sizelist[k]);
	}
}

int main()
{	
	vector<pair<long long,string> > sizelist;
	map<string,int> format;
	map<int,string> rmap;
	
	rmap = {{1,"Videos"} , {2,"Photos"} , {3,"Docs"} , {4,"Zip"} , {5,"Music"}};
	
	//-------------------Taking input of extensions from a file for easy updation of new formats--------//
	
	ifstream f("allformats.txt");
	string ft;
	int num;
	while(f >> ft ,f >> num)
	format[ft]=num;
	
	//----------------------------------end-----------------------------------------------------------//
	
	//------------------building the paths for the files----------------------
	
	string home = getenv(convert("HOME"));
	string path0 = home + "/Documents/";
	string path1 = home + "/Documents/filelog.txt";
	string path2 = home + "/Documents/fileinfo.txt";
	string path3 = home + "/Documents/largefiles.txt";
	
	//-----------------------------------------------------------------------
	
	search(convert(home),sizelist,1);
	sort(sizelist.begin(),sizelist.end());
	reverse(sizelist.begin(),sizelist.end());
	
	freopen(convert(path3),"w",stdout);
	int sno=1;
	unsigned long long sizeF=0;
	cout<<"------------------TOP LARGE FILES-------------------\n\n";

	for(int j=0;j<min((int)sizelist.size(),10);j++)
	{
		pair<long long,string> it=sizelist[j];
		printf("%d. %s : %.2f MB\n",sno,(char*)it.second.c_str(),(double)it.first/(1024.0*1024.0));
		sizeF += it.first;
		sno++;
	}
	printf("\nTotal Size: %.2f GB\n\n",(double)sizeF/(1024.0*1024.0*1024.0));
	fclose(stdout);
	
	sizelist.clear();
	
	string pwd = "..";
	search(convert(pwd),sizelist,0);
	//assert(!sizelist.empty());
	
	filter(sizelist,format);
	//sort(sizelist.begin(),sizelist.end());
	freopen(convert(path1),"w",stdout);
	sno=1;
	sizeF=0;
	cout<<"------------------ALL FILES-------------------\n\n";
	for(int i=1;i<=5;i++)
	{
		//string newpath = path0 + rmap[i];
		//mkdir(convert(newpath), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		
		for(int j=0;j<(int)filelist[i].size();j++)
		{
			pair<long long,string> it=filelist[i][j];
			printf("%d. %s : %.2f MB\n",sno,(char*)it.second.c_str(),(double)it.first/(1024.0*1024.0));
			sizeF += it.first;
			sno++;
		}
	}
	printf("\nTotal Size: %.2f GB\n\n",(double)sizeF/(1024.0*1024.0*1024.0));
	fclose(stdout);
	
	//-------------Copying all the file details into another file-------
	
	freopen(convert(path2),"w",stdout);
	for(int i=1;i<=5;i++)
	{
		printf("0\n");
		for(int j=0;j<(int)filelist[i].size();j++)
		{
			pair<long long,string> it=filelist[i][j];
			printf("%s\n",(char*)it.second.c_str());
		}
	}
	fclose(stdout);
	
	//------------------------------------------------------------------
	return 0;
}
